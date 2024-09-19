#include "command.hpp"

Command::Command(ClientQueueThreadPool* queueClient, int port)
    : queueClient_(queueClient) {

    client_ = nullptr;
    setupServer(port);

    commandHandlers_["auth"] = &Command::handleAuthCommand;
    commandHandlers_["crea"] = &Command::handleCreaCommand;
    commandHandlers_["mess"] = &Command::handleMessCommand;
    commandHandlers_["deco"] = &Command::handleDecoCommand;
}

void Command::setupServer(int port) {
    std::ostringstream logMessage;

    serverSocketCommand_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketCommand_ < 0) {
        serverStart_ = false;
        return;
    }

    serverAddrCommand_.sin_family = AF_INET;
    serverAddrCommand_.sin_addr.s_addr = INADDR_ANY;
    serverAddrCommand_.sin_port = htons(port);

    if (bind(serverSocketCommand_, (struct sockaddr *)&serverAddrCommand_, sizeof(serverAddrCommand_)) < 0) {
        close(serverSocketCommand_);
        logMessage << " Serveur Error, bind, port : " << port << "\n";
        std::cout << logMessage.str() << std::endl;
        serverStart_ = false;
        return;
    }

    if (listen(serverSocketCommand_, 5) < 0) {
        close(serverSocketCommand_);
        serverStart_ = false;
        logMessage << " Serveur Error, listen, port : " << port << "\n";
        std::cout << logMessage.str() << std::endl;
        return;
    }

    serverStart_ = true;

    logMessage << " Serveur Start, Port : " << port << "\n";
    std::cout << logMessage.str() << std::endl;
}

int Command::getServerSocket() const {
    return serverSocketCommand_;
}

void Command::sendToClient(ClientData *client, const std::string &message) {
    if (send(client->socket_fd, message.c_str(), message.length(), 0) < 0) {
        std::ostringstream logMessage;
        logMessage << "Erreur d'écriture sur le socket " << client->socket_fd << ": " << std::strerror(errno) << std::endl;
        std::cout << logMessage.str() << std::endl;
    }
}

bool Command::handleClient(ClientData *client) {
    char buffer[1024];
    ssize_t bytesRead;
    std::ostringstream logMessage;

    bytesRead = read(client->socket_fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::string command(buffer);
        processCommand(client, command);
        return true;
    } else if (bytesRead == 0) {
        logMessage << "Client Disconnect" << std::endl;
        std::cout << logMessage.str() << std::endl;
        return false;
    } else {
        logMessage << "Erreur de lecture du socket " << client->socket_fd << ": " << std::strerror(errno) << std::endl;
        std::cout << logMessage.str() << std::endl;
        return false;
    }
}

int Command::acceptClient(std::unordered_map<int, Rooms*> *rooms) {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    std::ostringstream logMessage;

    int clientSocket = accept(serverSocketCommand_, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        logMessage << "Erreur d'acceptation de la connexion: " << std::strerror(errno) << std::endl;
        std::cout << (logMessage.str()) << std::endl;
        return -1;
    }

    std::string clientIP = inet_ntoa(clientAddr.sin_addr);
    logMessage << "Client connected (IP: " << clientIP << ")" << std::endl;
    std::cout << logMessage.str() << std::endl;
    std::string message = "220\r\n";
    if (send(clientSocket, message.c_str(), message.length(), 0) < 0) {
        logMessage << "Erreur d'écriture sur le socket " << clientSocket << ": " << std::strerror(errno) << std::endl;
        std::cout << logMessage.str() << std::endl;
    }
    rooms_ = rooms;
    return clientSocket;
}

void Command::processCommand(ClientData *client, const std::string &command) {
    client_ = client;
    std::vector<std::string> commands;

    std::regex re("\\s+");
    std::sregex_token_iterator it(command.begin(), command.end(), re, -1);
    std::sregex_token_iterator end;
    while (it != end) {
        commands.push_back(*it++);
    }

    std::ostringstream logMessage;
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