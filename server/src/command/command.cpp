#include "command.hpp"

Command::Command(ClientQueueThreadPool* queueClient, int port)
    : queueClient_(queueClient), client_(nullptr) {
    setupServer(port);
    
    commandHandlers_["auth"] = &Command::handleAuthCommand;
    commandHandlers_["crea"] = &Command::handleCreaCommand;
    commandHandlers_["mess"] = &Command::handleMessCommand;
    commandHandlers_["deco"] = &Command::handleDecoCommand;
}

void Command::setupServer(int port) {
    serverSocketCommand_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketCommand_ < 0) {
        serverStart_ = false;
        std::cerr << "Erreur de création du socket" << std::endl;
        return;
    }

    serverAddrCommand_.sin_family = AF_INET;
    serverAddrCommand_.sin_addr.s_addr = INADDR_ANY;
    serverAddrCommand_.sin_port = htons(port);

    if (bind(serverSocketCommand_, (struct sockaddr *)&serverAddrCommand_, sizeof(serverAddrCommand_)) < 0) {
        close(serverSocketCommand_);
        std::cerr << "Erreur lors du bind, port : " << port << " - " << std::strerror(errno) << std::endl;
        serverStart_ = false;
        return;
    }

    if (listen(serverSocketCommand_, 5) < 0) {
        close(serverSocketCommand_);
        std::cerr << "Erreur lors de l'écoute, port : " << port << " - " << std::strerror(errno) << std::endl;
        serverStart_ = false;
        return;
    }

    serverStart_ = true;
    std::cout << "Serveur démarré, Port : " << port << std::endl;
}

int Command::getServerSocket() const {
    return serverSocketCommand_;
}

void Command::sendToClient(ClientData* client, const std::string& message) {
    unsigned char buffer[4 + 16 + 1024];
    communicator_.prepareMessage(message, buffer);
    if (write(client->socket_fd, buffer, sizeof(buffer)) < 0) {
        std::cerr << "Erreur d'écriture sur le socket " << client->socket_fd << ": " << std::strerror(errno) << std::endl;
    }
}

bool Command::handleClient(ClientData* client) {
    unsigned char buffer[4 + 16 + 1024];
    ssize_t bytesRead = read(client->socket_fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        int message_size;
        memcpy(&message_size, buffer, sizeof(message_size));

        unsigned char decryptedtext[1024];
        memset(decryptedtext, 0, 1024);
        communicator_.decrypt(buffer, message_size, decryptedtext);

        std::string command(reinterpret_cast<char*>(decryptedtext), message_size);
        processCommand(client, command);
        return true;
    } else if (bytesRead == 0) {
        std::cout << "Client déconnecté" << std::endl;
        return false;
    } else {
        std::cerr << "Erreur de lecture du socket " << client->socket_fd << ": " << std::strerror(errno) << std::endl;
        return false;
    }
}

int Command::acceptClient(std::unordered_map<int, Rooms*>* rooms) {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int clientSocket = accept(serverSocketCommand_, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        std::cerr << "Erreur d'acceptation de la connexion: " << std::strerror(errno) << std::endl;
        return -1;
    }

    std::string clientIP = inet_ntoa(clientAddr.sin_addr);
    std::cout << "Client connecté (IP: " << clientIP << ")" << std::endl;

    std::string message = "220\r\n";
    unsigned char buffer[4 + 16 + 1024];
    communicator_.prepareMessage(message, buffer);

    if (write(clientSocket, buffer, 1044) < 0) {
        std::cerr << "Erreur d'écriture sur le socket " << clientSocket << ": " << std::strerror(errno) << std::endl;
    }

    rooms_ = rooms;
    return clientSocket;
}

void Command::processCommand(ClientData* client, const std::string& command) {
    client_ = client;
    std::vector<std::string> commands;

    std::regex re("\\s+");
    std::sregex_token_iterator it(command.begin(), command.end(), re, -1);
    std::sregex_token_iterator end;
    while (it != end) {
        commands.push_back(*it++);
    }

    auto itCommand = commandHandlers_.find(commands[0]);
    if (itCommand != commandHandlers_.end()) {
        queueClient_->enqueueClientTask(client->socket_fd, [this, client, commands, itCommand]() {
            if (!client->authenticated && (commands[0] == "auth" || commands[0] == "crea") || client->authenticated) {
                (this->*(itCommand->second))(client, commands);
            } else {
                sendToClient(client, "550\r\n");
            }
        });
    } else {
        sendToClient(client, "500\r\n");
    }
}
