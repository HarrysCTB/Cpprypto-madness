#ifndef CANAL_HANDLER_HPP
#define CANAL_HANDLER_HPP

#include <string>

class CanalHandler {
    public:
        CanalHandler(int socket_fd);

        void handleAuth(const std::string& username, const std::string& password);
        void handleCrea(const std::string& username, const std::string& password);
        void handleMessage(const std::string& message);
        void handleQuit();

    private:
        int socket_fd;
};

#endif
