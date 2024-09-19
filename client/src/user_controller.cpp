#include "user_controller.h"

UserController::UserController(QObject *parent) : QObject(parent) { }

void UserController::setCanal(CanalHandler *canal) {
    this->canal = canal;
}

void UserController::setMessage(MessageHandler *message) {
    this->message = message;
}

void UserController::emitStartToServer() {
    emit connectToServer();
}

void UserController::sendRegister(const std::string &username, const std::string &password) {
    canal->handleCrea(username, password);
}

void UserController::sendLogin(const std::string &username, const std::string &password) {
    canal->handleAuth(username, password);
}
