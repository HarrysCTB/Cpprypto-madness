#include "canal_handler.hpp"
#include "message_handler.hpp"
#include <iostream>

CanalHandler::CanalHandler(int socket_fd) : socket_fd(socket_fd) {}

void CanalHandler::handleAuth(const std::string& username, const std::string& password) {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "auth " + username + " " + password);
}

void CanalHandler::handleCrea(const std::string& username, const std::string& password) {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "crea " + username + " " + password);
}

void CanalHandler::handleMessage(const std::string& message) {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "mess " + message);
}

void CanalHandler::handleQuit() {
    MessageHandler msgHandler;
    msgHandler.sendMessage(socket_fd, "deco");
}
