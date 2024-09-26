#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "secure_server_communicator.hpp"

#include "user_controller.h"
#include "main_window.h"

#include <string>
#include <unordered_map>
#include <thread>

class UserController;
class MainWindow;


class Client {
public:
    Client(UserController *UserController, MainWindow *mainWindow);
    void run();
    bool connectToServer(const std::string& server_ip, int port, const std::string& username);
    void handleInput();
    void receiveMessages();
    void stop();

private:
    std::string username;
    int server_socket;
    bool isRunning_;
    
    UserController *userController;
    MainWindow *mainWindow;

    SecureServerCommunicator communicator_;

    std::unordered_map<uint32_t, std::function<void(int)>> commandQueue;
    std::mutex queueMutex;
    std::condition_variable queueCv;

public:
    void addCommandToQueue(uint32_t id, std::function<void(int)> callback);
    void processCommandQueue(const StructToClient& msg);
};

#endif
