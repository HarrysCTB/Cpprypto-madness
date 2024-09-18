#include "../include/client.hpp"
#include "../include/network.hpp"
#include "../include/message_handler.hpp"
#include "../include/canal_handler.hpp"
#include <thread>
#include <iostream>

Client::Client() {}

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
}

void Client::handleInput() {
    CanalHandler canalHandler(server_socket);
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        canalHandler.handleCommand(input);
    }
}

void Client::receiveMessages() {
    MessageHandler msgHandler;
    while (true) {
        std::string message = msgHandler.receiveMessage(server_socket);
        if (!message.empty()) {
            std::cout << "Message reçu: " << message << std::endl;
        }
    }
}
