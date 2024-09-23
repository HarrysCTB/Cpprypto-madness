#include "message_handler.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

MessageHandler::MessageHandler(SecureServerCommunicator* communicator) 
    : communicator_(communicator) {}

void MessageHandler::sendMessage(int socket, const std::string& message) {
    unsigned char buffer[4 + 16 + 1024];

    communicator_->prepareMessage(message, buffer);
    if (write(socket, buffer, sizeof(buffer)) < 0) {
        std::cerr << "Erreur : échec de l'envoi du message. " << std::strerror(errno) << std::endl;
    }
}

std::string MessageHandler::receiveMessage(int socket) {
    unsigned char buffer[4 + 16 + 1024];

    int bytes_received = read(socket, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        uint32_t message_size;
        memcpy(&message_size, buffer, sizeof(message_size));
        unsigned char decryptedtext[1024];
        memset(decryptedtext, 0, 1024);
        communicator_->decrypt(buffer, message_size, decryptedtext);
        return std::string(reinterpret_cast<char*>(decryptedtext), message_size);
    } else if (bytes_received < 0) {
        std::cerr << "Erreur : échec de la réception du message. " << std::strerror(errno) << std::endl;
    }
    return "";
}
