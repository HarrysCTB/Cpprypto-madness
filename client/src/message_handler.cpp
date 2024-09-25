#include "message_handler.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

MessageHandler::MessageHandler(SecureServerCommunicator* communicator) 
    : communicator_(communicator) {}

void MessageHandler::sendMessage(int socket, const StuctToServ& response) {
    unsigned char buffer[4 + 16 + 1024];
    communicator_->prepareMessage(response, buffer);
    if (write(socket, buffer, sizeof(buffer)) < 0) {
        std::cerr << "Erreur : échec de l'envoi du message. " << std::strerror(errno) << std::endl;
    }
}

StructToClient MessageHandler::receiveMessage(int socket) {
    unsigned char buffer[4 + 16 + 1024];

    StructToClient message;
    int bytes_received = read(socket, buffer, sizeof(buffer));
    if (bytes_received > 0) {
        int message_size;
        memcpy(&message_size, buffer, sizeof(message_size));
    
        unsigned char decryptedtext[1024];
        memset(decryptedtext, 0, 1024);
        communicator_->decrypt(buffer, message_size, decryptedtext);

        std::memcpy(&message, decryptedtext, sizeof(StructToClient));

        return message;
    } else if (bytes_received < 0) {
        std::cerr << "Erreur : échec de la réception du message. " << std::strerror(errno) << std::endl;
    }
    return StructToClient();
}
