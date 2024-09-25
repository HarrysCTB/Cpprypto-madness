#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <string>

#include "secure_server_communicator.hpp"

class MessageHandler {
    public:
        MessageHandler(SecureServerCommunicator *communicator);
        void sendMessage(int socket, const StuctToServ& response);
        StructToClient receiveMessage(int socket);
    
    private:
        SecureServerCommunicator *communicator_;
};

#endif
