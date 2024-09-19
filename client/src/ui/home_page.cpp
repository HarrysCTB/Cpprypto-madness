#include "home_page.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    channelList = new QListWidget(this);
    channelList->addItem("Canal 1");
    channelList->addItem("Canal 2");
    channelList->addItem("Canal 3");
    channelList->setFixedWidth(250);

    channelList->setStyleSheet(
            "QListWidget {"
            "   border: none;"
            "   background-color: #20232A;"
            "   color: white;"
            "   padding: 10px;"
            "}"
            "QListWidget::item {"
            "   margin: 5px;"
            "   padding: 15px;"
            "   border-radius: 10px;"
            "   background-color: #2E3238;"
            "}"
            "QListWidget::item:hover {"
            "   background-color: #40444B;"
            "}"
            "QListWidget::item:selected {"
            "   background-color: #4A5058;"
            "}"
    );

    chatHistory = new QTextEdit(this);
    chatHistory->setReadOnly(true);
    chatHistory->setPlaceholderText("Chat history...");
    chatHistory->setStyleSheet(
            "QTextEdit {"
            "   background-color: #18191C;"
            "   color: white;"
            "   border: none;"
            "}"
    );


    QLineEdit *messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Entrez votre message...");
    messageInput->setStyleSheet(
            "QLineEdit {"
            "   background-color: #20232A;"
            "   color: white;"
            "   border-radius: 5px;"
            "   padding: 8px;"
            "}"
    );

    QPushButton *sendButton = new QPushButton("Envoyer", this);
    sendButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #fd7014;"
            "   color: white;"
            "   padding: 8px 15px;"
            "   border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #ff8c42;"
            "}"
    );

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(messageInput, 1);
    inputLayout->addWidget(sendButton);

    QVBoxLayout *chatLayout = new QVBoxLayout();
    chatLayout->addWidget(chatHistory, 1);
    chatLayout->addLayout(inputLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(channelList, 1);
    mainLayout->addLayout(chatLayout, 2);

    setLayout(mainLayout);
    setWindowTitle("Home Page");
    this->setStyleSheet("background-color: #222831;");
    resize(800, 600);
}


