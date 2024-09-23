#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <string>

#include "secure_server_communicator.hpp"

class MessageHandler {
    public:
        MessageHandler(SecureServerCommunicator *communicator);
        void sendMessage(int socket, const std::string& message);
        std::string receiveMessage(int socket);
    
    private:
        SecureServerCommunicator *communicator_;
};

#endif
