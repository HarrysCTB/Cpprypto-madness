#include "canal_handler.hpp"
#include "message_handler.hpp"
#include <iostream>

CanalHandler::CanalHandler(int socket_fd, SecureServerCommunicator *communicator, std::function<void(uint32_t, std::function<void(int)>)> addCommandFunc, UserController *userController)
    : socket_fd(socket_fd),  communicator_(communicator), addCommandFunc_(addCommandFunc), userController_(userController) {}

static uint32_t randomId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis;

    return (dis(gen));
}

void CanalHandler::callbackAuth(int code) {
    std::cout << "Callback function Auth" << std::endl;
    std::cout << "Code : " << code << std::endl;

    emit userController_->sendLoginCode(code);
}

void CanalHandler::handleAuth(const std::string& username, const std::string& password) {
    MessageHandler msgHandler(communicator_);

    StuctToServ msg;
    msg.id = randomId();
    msg.opcode = AUTH_CODE;

    std::copy(username.begin(), username.end(), msg.data.username);
    msg.data.username[std::min(username.size(), sizeof(msg.data.username) - 1)] = '\0';
    std::copy(password.begin(), password.end(), msg.data.password);
    msg.data.password[std::min(password.size(), sizeof(msg.data.password) - 1)] = '\0';
    addCommandFunc_(msg.id, [&](int code) {
        callbackAuth(code);
    });
    msgHandler.sendMessage(socket_fd, msg);
}

void CanalHandler::handleCrea(const std::string& username, const std::string& password) {
    MessageHandler msgHandler(communicator_);

    StuctToServ msg;
    msg.id = randomId();
    msg.opcode = CREA_CODE;
    std::copy(username.begin(), username.end(), msg.data.username);
    msg.data.username[std::min(username.size(), sizeof(msg.data.username) - 1)] = '\0';
    std::copy(password.begin(), password.end(), msg.data.password);
    msg.data.password[std::min(password.size(), sizeof(msg.data.password) - 1)] = '\0';
    msgHandler.sendMessage(socket_fd, msg);
}

void CanalHandler::handleMessage(const std::string& message) {
    MessageHandler msgHandler(communicator_);

    StuctToServ msg;
    msg.id = randomId();
    msg.opcode = MESS_CODE;
    msgHandler.sendMessage(socket_fd, msg);
}

void CanalHandler::handleQuit() {
    MessageHandler msgHandler(communicator_);

    StuctToServ msg;
    msg.id = randomId();
    msg.opcode = DECO_CODE;
    msgHandler.sendMessage(socket_fd, msg);
}
