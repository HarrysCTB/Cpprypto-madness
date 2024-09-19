#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>


class HomePage : public QWidget {

public:
    explicit HomePage(QWidget *parent = nullptr);

private:
    QListWidget *channelList;
    QTextEdit *chatHistory;
    QLineEdit *messageInput;
    QPushButton *sendButton;
};

#endif  // HOME_PAGE_H
