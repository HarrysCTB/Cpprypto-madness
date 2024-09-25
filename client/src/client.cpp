#include "client.hpp"
#include "network.hpp"
#include "message_handler.hpp"
#include "canal_handler.hpp"

#include <thread>
#include <iostream>

Client::Client(UserController *userController, MainWindow *mainWindow)
    : userController(userController), mainWindow(mainWindow) { }

void Client::run() {
    connectToServer("127.0.0.1", 9999, username);

    std::thread inputThread(&Client::handleInput, this);
    std::thread receiveThread(&Client::receiveMessages, this);

    inputThread.join();
    receiveThread.join();
}

void Client::connectToServer(const std::string& server_ip, int port, const std::string& username) {
    Network net;
    int sockfd = net.connectToServer(server_ip, port);
    if (sockfd < 0) {
        std::cerr << "Error: Could not connect to server." << std::endl;
        return;
    }
    this->server_socket = sockfd;
    userController->emitStartToServer();
}

void Client::handleInput() {
    CanalHandler canalHandler(server_socket, &communicator_);
    userController->setCanal(&canalHandler);
    std::string input;
    while (true) {}
}

void Client::receiveMessages() {
    MessageHandler msgHandler(&communicator_);
    userController->setMessage(&msgHandler);
    while (true) {
        StructToClient message = msgHandler.receiveMessage(server_socket);
        std::cout << "Message reçu: " << message.opcode << std::endl;
        std::cout << "id : " << message.id << std::endl;
        std::cout << "status : " << message.status[0][0] << std::endl;
        std::cout << message.id << std::endl;        
        emit userController->sendLoginCode(message.status[1][0]);
    }
}