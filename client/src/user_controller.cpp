#include "user_controller.h"

UserController::UserController(QObject *parent) : QObject(parent) { }

//init
void UserController::setCanal(CanalHandler *canal) {
    this->canal = canal;
}

void UserController::setMessage(MessageHandler *message) {
    this->message = message;
}

// start
void UserController::emitStartToServer() {
    emit connectToServer();
}

// register / login
void UserController::sendRegister(const std::string &username, const std::string &password) {
    canal->handleCrea(username, password);
}

void UserController::sendLogin(const std::string &username, const std::string &password) {
    canal->handleAuth(username, password);
}

