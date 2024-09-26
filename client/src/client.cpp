#include "client.hpp"
#include "network.hpp"
#include "message_handler.hpp"
#include "canal_handler.hpp"

#include <thread>
#include <iostream>

Client::Client(UserController *userController, MainWindow *mainWindow)
    : userController(userController), mainWindow(mainWindow) {
        isRunning_ = true;
    }

void Client::run() {
    while (!connectToServer("127.0.0.1", 9999, username));

    std::thread inputThread(&Client::handleInput, this);
    std::thread receiveThread(&Client::receiveMessages, this);

    inputThread.join();
    receiveThread.join();
}

bool Client::connectToServer(const std::string& server_ip, int port, const std::string& username) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    Network net;
    int sockfd = net.connectToServer(server_ip, port);
    if (sockfd < 0) {
        return (false);
    } else {
        this->server_socket = sockfd;
        return (true);
    }
    return (false);
}

void Client::handleInput() {
    CanalHandler canalHandler(server_socket, &communicator_, [&](uint32_t id, std::function<void(int)> callback) {
        addCommandToQueue(id, callback);
    }, userController);
    userController->setCanal(&canalHandler);
    while (true) {

    }
}

void Client::receiveMessages() {
    MessageHandler msgHandler(&communicator_);
    userController->setMessage(&msgHandler);
    while (true) {
        StructToClient message = msgHandler.receiveMessage(server_socket);
        std::cout << "Op Code     : " << message.opcode << std::endl;
        if (message.opcode != NONE_CODE) {
            if (message.opcode == CNNT_CODE) {
                std::cout << "Connected to server !" << std::endl;
                userController->emitStartToServer();
            } else if (message.opcode == RVUM_CODE) {
                std::cout << "Recive Message User !" << std::endl;
            } else if (message.opcode == RVRM_CODE) {
                std::cout << "Recive Message Room !" << std::endl;
            }
        } else {
            std::thread([this, message]() {
                processCommandQueue(message);
            }).detach();
        }
    }
}

void Client::stop() {
    isRunning_ = false;
    queueCv.notify_all();
}

void Client::addCommandToQueue(uint32_t id, std::function<void(int)> callback) {
    std::lock_guard<std::mutex> lock(queueMutex);
    commandQueue[id] = callback;
    queueCv.notify_one();
}

void Client::processCommandQueue(const StructToClient& msg) {

    while (isRunning_) {
        std::unique_lock<std::mutex> lock(queueMutex);

        queueCv.wait(lock, [this] { return !commandQueue.empty(); });

        auto it = commandQueue.find(msg.id);
        if (it != commandQueue.end()) {

            std::cout << "id command     : " << msg.id << std::endl;
            std::cout << "status command : " << msg.status[0][0] << std::endl;
            std::cout << "code           : " << msg.status[1][0] << std::endl;

            std::function<void(int)> callback = it->second;
            if (msg.status[0][0] == CodeResponseStatus::Ok || msg.status[0][0] == CodeResponseStatus::Error) {
                commandQueue.erase(it);

            }

            if (msg.status[0][0] == CodeResponseStatus::Ok || msg.status[0][0] == CodeResponseStatus::Error) {
                callback(msg.status[1][0]);
            }
            lock.unlock();
            return;
        }
    }
}