#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
    public:
        Client();
        void run();
        void connectToServer(const std::string& server_ip, int port, const std::string& username);
        void handleInput();
        void receiveMessages();

    private:
        std::string username;
        int server_socket;
};

#endif
