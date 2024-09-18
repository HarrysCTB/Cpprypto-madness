#ifndef CANAL_HANDLER_HPP
#define CANAL_HANDLER_HPP

#include <string>

class CanalHandler {
    public:
        CanalHandler(int socket_fd);
        void handleCommand(const std::string& command);

    private:
        void handleAuth(const std::string& username);
        void handleMessage(const std::string& message);
        void handleQuit();

        int socket_fd;
};

#endif
