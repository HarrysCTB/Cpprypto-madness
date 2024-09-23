#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "secure_server_communicator.hpp"

#include "user_controller.h"
#include "main_window.h"

#include <string>

class UserController;
class MainWindow;

class Client {
    public:
        Client(UserController *UserController, MainWindow *mainWindow);
        void run();
        void connectToServer(const std::string& server_ip, int port, const std::string& username);
        void handleInput();
        void receiveMessages();

    private:
        std::string username;
        int server_socket;
    
    UserController *userController;
    MainWindow *mainWindow;

    SecureServerCommunicator communicator_;
};

#endif
