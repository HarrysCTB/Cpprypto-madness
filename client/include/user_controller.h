#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "message_handler.hpp"
#include "canal_handler.hpp"

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

class MessageHandler;
class CanalHandler;

class UserController : public QObject {
    Q_OBJECT

public:
    explicit UserController(QObject *parent = nullptr);

    void setCanal(CanalHandler *canal);
    void setMessage(MessageHandler *message);

    void emitStartToServer();

private:
    CanalHandler *canal;
    MessageHandler *message;

signals:
    void connectToServer();
    int sendLoginCode(int code);
    int sendRegisterCode(int code);

public slots:
    void sendRegister(const std::string &username, const std::string &password);
    void sendLogin(const std::string &username, const std::string &password);

};

#endif  // USER_CONTROLLER_H
