#include "canal_handler.hpp"
#include "message_handler.hpp"
#include <iostream>

CanalHandler::CanalHandler(int socket_fd) : socket_fd(socket_fd) {}

void CanalHandler::handleCommand(const std::string& command) {
    if (command.find("auth ") == 0) {
        std::string username = command.substr(5);
        handleAuth(username);
    } else if (command.find("mess ") == 0) {
        std::string message = command.substr(5);
        handleMessage(message);
    } else if (command == "deco") {
        handleQuit();
    } else {
        std::cerr << "Commande inconnue." << std::endl;
    }
}

void CanalHandler::handleAuth(const std::string& username) {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "auth " + username);
}

void CanalHandler::handleMessage(const std::string& message) {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "mess " + message);
}

void CanalHandler::handleQuit() {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "deco");
}
