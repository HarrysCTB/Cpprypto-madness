#include "command.hpp"
#include <cstdio>

#ifdef INCLUDE_OPCODE
    extern "C" int callOpCodeFunc(Command *cmd, int opcode, void* clientData, std::vector<std::string>& vec);
    extern "C" Command::CommandHandler Command::function_table_op_code[4] = {
        &Command::handleAuthCommand,
        &Command::handleCreaCommand,
        &Command::handleMessCommand,
        &Command::handleDecoCommand
    };
#else
    extern "C" int callOpCodeFunc(Command *cmd, int opcode, void* clientData, std::vector<std::string>& vec) {}
#endif

Command::Command(ClientQueueThreadPool* queueClient, int port)
    : queueClient_(queueClient), client_(nullptr) {
    setupServer(port);

#ifndef INCLUDE_OPCODE
    commandHandlers_[AUTH_CODE] = &Command::handleAuthCommand;
    commandHandlers_[CREA_CODE] = &Command::handleCreaCommand;
    //commandHandlers_[MESS_CODE] = &Command::handleMessCommand;
    commandHandlers_[DECO_CODE] = &Command::handleDecoCommand;
#endif
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

void Command::sendToClient(ClientData* client, const StructToClient& response) {
    unsigned char buffer[4 + 16 + 1024];
    communicator_.prepareMessage(response, buffer);
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

        StuctToServ message;
        std::memcpy(&message, decryptedtext, sizeof(StuctToServ));

        processCommand(client, message);
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

    StructToClient response;
    response.id = 0;
    response.opcode = CNNT_CODE;
    response.timestamp = std::chrono::system_clock::now();
    response.data = static_cast<void*>(new CnntStruct("220\r\n"));

    unsigned char buffer[4 + 16 + 1024];
    std::memset(buffer, 0, sizeof(buffer));
    communicator_.prepareMessage(response, buffer);

    if (write(clientSocket, buffer, 1044) < 0) {
        std::cerr << "Erreur d'écriture sur le socket " << clientSocket << ": " << std::strerror(errno) << std::endl;
    }

    rooms_ = rooms;
    return clientSocket;
}

void Command::processCommand(ClientData* client, const StuctToServ& message) {
    client_ = client;

#ifdef INCLUDE_OPCODE
    callOpCodeFunc(this, 0x01, client, commands);
#else

    StructToClient response;
    response.id = message.id;
    response.opcode = NONE_CODE;

    auto itCommand = commandHandlers_.find(message.opcode);
    if (itCommand != commandHandlers_.end()) {
        queueClient_->enqueueClientTask(client->socket_fd, [this, client, message, &response, itCommand]() {

            if (!client->authenticated && (message.opcode == AUTH_CODE || message.opcode == CREA_CODE) || client->authenticated) {
                (this->*(itCommand->second))(client, message);
            } else {
                response.setStatus(CodeResponseStatus::Error, 550);
                sendToClient(client, response);
            }
        });
    } else {
        response.setStatus(CodeResponseStatus::Error, 500);
        sendToClient(client, response);
    }
#endif
}
