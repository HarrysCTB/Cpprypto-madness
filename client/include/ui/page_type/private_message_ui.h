#ifndef PRIVATE_MESSAGEUI_H
#define PRIVATE_MESSAGEUI_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFontMetrics>

class PrivateMessageUi : public QWidget {
    Q_OBJECT

public:
    explicit PrivateMessageUi(std::string nameUser, QWidget *parent = nullptr);
    ~PrivateMessageUi();

private:
    void initaliseChatScrollArea();
    void initaliseSendMsg();

    QVBoxLayout *mainLayout;
    QVBoxLayout *scrollLayout;

    std::string nameUser_;

signals:
    void sendMsg(const std::string& nameUser, const std::string& msg);

public slots:
    void setUserMsg(const std::string& nameUser, const std::string& msg);
    void setMsg(const std::string& nameUser, const std::string& msg);
};

#endif // PRIVATE_MESSAGEUI_H
