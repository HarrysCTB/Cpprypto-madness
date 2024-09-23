#include "client.hpp"
#include "network.hpp"
#include "message_handler.hpp"
#include "canal_handler.hpp"

#include <thread>
#include <iostream>

Client::Client(UserController *userController, MainWindow *mainWindow)
    : userController(userController), mainWindow(mainWindow) {
        communicator_.readKeyFromFile(KEY_FILE_PATH);
    }

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
    while (true) { }
}

void Client::receiveMessages() {
    MessageHandler msgHandler(&communicator_);
    userController->setMessage(&msgHandler);
    while (true) {
        std::string message = msgHandler.receiveMessage(server_socket);
        if (!message.empty()) {
            std::cout << "Message reçu: " << message << std::endl;
            std::string firstThreeChars = message.substr(0, 3);
            int number = std::stoi(firstThreeChars);
            emit userController->sendLoginCode(number);
        } 
    }
}