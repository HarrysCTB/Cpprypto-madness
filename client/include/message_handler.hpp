#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <string>

class MessageHandler {
    public:
        MessageHandler();
        void sendMessage(int socket, const std::string& message);
        std::string receiveMessage(int socket);
};

#endif
