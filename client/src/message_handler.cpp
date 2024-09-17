#include "../include/message_handler.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

MessageHandler::MessageHandler() {}

void MessageHandler::sendMessage(int socket, const std::string& message) {
    if (send(socket, message.c_str(), message.length(), 0) < 0) {
        std::cerr << "Error: Failed to send message." << std::endl;
    }
}

std::string MessageHandler::receiveMessage(int socket) {
    char buffer[1024];
    int bytes_received = recv(socket, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        return std::string(buffer, bytes_received);
    }
    return "";
}
