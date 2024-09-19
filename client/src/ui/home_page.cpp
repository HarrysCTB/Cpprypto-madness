#include "home_page.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: #222831;");

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->setContentsMargins(0, 0, 0, 0);


    QWidget *SelectRoomsWidget = new QWidget;
    QVBoxLayout *leftVerticalLayout = new QVBoxLayout;
    leftVerticalLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *topWidget = new QWidget;
    topWidget->setFixedHeight(100);

    QWidget *middleWidget = new QWidget;
    middleWidget->setFixedHeight(50);
    QHBoxLayout *middleLayout = new QHBoxLayout;
    QLabel *textLabel = new QLabel("All Conversation");
    QPushButton *button = new QPushButton("+");

    middleLayout->addWidget(textLabel);
    middleLayout->addWidget(button);
    middleLayout->setContentsMargins(10, 0, 10, 0);
    middleLayout->setSpacing(10);

    middleWidget->setLayout(middleLayout);

    QWidget *bottomWidget = new QWidget;

    leftVerticalLayout->addWidget(topWidget);
    leftVerticalLayout->addWidget(middleWidget);
    leftVerticalLayout->addWidget(bottomWidget);

    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    SelectRoomsWidget->setLayout(leftVerticalLayout);
    SelectRoomsWidget->setFixedWidth(225);
    
    SelectRoomsWidget->setStyleSheet(
        "QWidget#SelectRoomsWidget { background-color: #222831; border-right: 1px solid white; }"
        "QWidget#topWidget { background-color: transparent; border-bottom: 1px solid white; }"
        "QWidget#middleWidget { background-color: transparent; border-bottom: 0.5px solid rgba(255, 255, 255, 0.4); }"
        "QWidget#bottomWidget { background-color: transparent; }"
        "QLabel { color: white; }"
        "QPushButton { background-color: #37414F; color: white; width: 44px; height: 25px; border-radius: 5px}"
    );

    SelectRoomsWidget->setObjectName("SelectRoomsWidget");
    topWidget->setObjectName("topWidget");
    middleWidget->setObjectName("middleWidget");
    bottomWidget->setObjectName("bottomWidget");




    QWidget *roomsWidget = new QWidget;
    QVBoxLayout *roomsLayout = new QVBoxLayout;

    QPushButton *rightButton1 = new QPushButton("Colonne Droite - Bouton 1");
    QPushButton *rightButton2 = new QPushButton("Colonne Droite - Bouton 2");
    roomsLayout->addWidget(rightButton1);
    roomsLayout->addWidget(rightButton2);

    roomsWidget->setLayout(roomsLayout);

    horizontalLayout->addWidget(SelectRoomsWidget);
    horizontalLayout->addWidget(roomsWidget);

    setLayout(horizontalLayout);
}

HomePage::~HomePage() {
    
}
