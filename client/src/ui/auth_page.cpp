#include "auth_page.h"

AuthPage::AuthPage(QWidget *parent) : QFrame(parent), switchButtonStatus(false) {
    this->setStyleSheet("background-color: #222831;");

    QLabel *iconLabel = new QLabel(this);
    QPixmap pixmap("./client/assets/logo.png");
    iconLabel->setPixmap(pixmap);
    iconLabel->setScaledContents(true);
    iconLabel->setFixedSize(100, 100); 

    QLabel *title = new QLabel("Vortex Messenger", this);
    title->setStyleSheet("font-size: 22px; color: #FFFFFF; font-weight: semibold;");

    QLabel *description = new QLabel("Encrypted messaging", this);
    description->setStyleSheet("font-size: 12px; color: rgba(255, 255, 255, 0.7);");
    description->setAlignment(Qt::AlignCenter);

    QVBoxLayout *titleLayout = new QVBoxLayout(this);
    titleLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
    titleLayout->addWidget(title, 0, Qt::AlignCenter);
    titleLayout->addWidget(description, 0, Qt::AlignCenter);

    QWidget *titleWidget = new QWidget(this);
    titleWidget->setLayout(titleLayout);

    QFrame *loginCard = new QFrame(this);

    switchButton = new QPushButton("Register", loginCard);
    switchButton->setStyleSheet(
            "QPushButton {"
            "background-color: transparent; color: rgba(255, 255, 255, 0.7); font-size: 14px; text-decoration: underline;"
            "}"
            "QPushButton:hover {"
            "background-color: transparent; color: rgba(255, 255, 255, 1); font-size: 14px; text-decoration: underline;"
            "}"
    );
    switchButton->setCursor(QCursor(Qt::PointingHandCursor));

    usernameInput = new QLineEdit(loginCard);
    usernameInput->setPlaceholderText("Username");
    usernameInput->setStyleSheet(R"(
        QLineEdit {
            border: none;
            border-bottom: 0.5px solid rgba(255, 255, 255, 0.5);
            padding: 5px;
            font-size: 14px;
            color: white;
        }
        QLineEdit:focus {
            border-bottom: 0.5px solid rgba(255, 255, 255, 0.8);
        }
    )");

    passwordInput = new QLineEdit(loginCard);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet(R"(
        QLineEdit {
            border: none;
            border-bottom: 0.5px solid rgba(255, 255, 255, 0.5);
            padding: 5px;
            font-size: 14px;
            color: white;
        }
        QLineEdit:focus {
            border-bottom: 0.5px solid rgba(255, 255, 255, 0.8);
        }
    )");

    sendButton = new QPushButton("Login", loginCard);
    sendButton->setStyleSheet(
            "QPushButton {"
            "background-color: transparent; color: rgba(255, 255, 255, 0.7); font-size: 16px;"
            "}"
            "QPushButton:hover {"
            "background-color: transparent; color: rgba(255, 255, 255, 1); font-size: 16px;"
            "}"
    );
    sendButton->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *cardLayout = new QVBoxLayout(loginCard);
    cardLayout->addWidget(usernameInput);
    cardLayout->addWidget(passwordInput);
    cardLayout->addSpacing(30);
    cardLayout->addWidget(sendButton, 0, Qt::AlignCenter);
    cardLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(switchButton, 0, Qt::AlignLeft);
    mainLayout->addWidget(titleWidget, 0, Qt::AlignCenter);
    mainLayout->addWidget(loginCard, 0, Qt::AlignCenter);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(sendButton, &QPushButton::clicked, this, [this] {
        if (switchButtonStatus) {
            handleRegister();
        } else {
            handleLogin();
        }
    });
    connect(switchButton, &QPushButton::clicked, this, [this] {
        switchButtonStatus = !switchButtonStatus;
        if (switchButtonStatus) {
            sendButton->setText("Register");
            switchButton->setText("Login");
        } else {
            sendButton->setText("Login");
            switchButton->setText("Register");
        }
    });
}

void AuthPage::handleLogin() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Erreur de connexion");
        msgBox.setText("Veuillez entrer un nom d'utilisateur et un mot de passe.");
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    color: white;"
            "}"
            "QPushButton {"
            "    color: white;"
            "    border: none;"
            "    border-radius: 3px;"
            "}"
            "QLabel { color: white; }"
        );

        QPushButton *okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setStyleSheet(
            "QPushButton {"
            "    color: white;"
            "    background-color: rgba(234, 120, 50, 1);"
            "    border: none;"
            "    padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "    background-color: rgba(234, 120, 50, 0.9);"
            "}"
        );

        msgBox.exec();
        return;
    }
    emit newLogin(username.toStdString(), password.toStdString());
}

void AuthPage::handleRegister() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Erreur d'inscription");
        msgBox.setText("Veuillez entrer un nom d'utilisateur et un mot de passe.");
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    color: white;"
            "}"
            "QPushButton {"
            "    color: white;"
            "    border: none;"
            "    border-radius: 3px;"
            "}"
            "QLabel { color: white; }"
        );

        QPushButton *okButton = msgBox.addButton(QMessageBox::Ok);
        okButton->setStyleSheet(
            "QPushButton {"
            "    color: white;"
            "    background-color: rgba(234, 120, 50, 1);"
            "    border: none;"
            "    padding: 5px 10px;"
            "}"
            "QPushButton:hover {"
            "    background-color: rgba(234, 120, 50, 0.9);"
            "}"
        );

        msgBox.exec();
        return;
    }
    emit newRegister(username.toStdString(), password.toStdString());
}

AuthPage::~AuthPage() {
    delete switchButton;
    delete usernameInput;
    delete passwordInput;
    delete sendButton;
}

void AuthPage::responseLogin(int code) {
    QMessageBox msgBox(this);
    msgBox.setStyleSheet(
        "QMessageBox {"
        "    color: white;"
        "}"
        "QPushButton {"
        "    color: white;"
        "    border: none;"
        "    border-radius: 3px;"
        "}"
        "QLabel { color: white; }"
    );

    QPushButton *okButton = msgBox.addButton(QMessageBox::Ok);
    okButton->setStyleSheet(
        "QPushButton {"
        "    color: white;"
        "    background-color: rgba(234, 120, 50, 1);"
        "    border: none;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(234, 120, 50, 0.9);"
        "}"
    );

    if (code == 250) {
        emit LoginOk();
        this->close();
    } else {
        msgBox.setWindowTitle("Login Error");
        msgBox.setText("Login ou mot de passe incorrect.");
        msgBox.exec();
        usernameInput->setText("");
        passwordInput->setText("");
    }
}

void AuthPage::responseRegister(int code) {
    QMessageBox msgBox(this);
    msgBox.setStyleSheet(
        "QMessageBox {"
        "    color: white;"
        "}"
        "QPushButton {"
        "    color: white;"
        "    border: none;"
        "    border-radius: 3px;"
        "}"
        "QLabel { color: white; }"
    );

    QPushButton *okButton = msgBox.addButton(QMessageBox::Ok);
    okButton->setStyleSheet(
        "QPushButton {"
        "    color: white;"
        "    background-color: rgba(234, 120, 50, 1);"
        "    border: none;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(234, 120, 50, 0.9);"
        "}"
    );

    if (code == 250) {
        msgBox.setWindowTitle("Register Success");
        msgBox.setText("register success");
        msgBox.exec();
        sendButton->setText("Register");
        switchButton->setText("Login");
    } else {
        msgBox.setWindowTitle("Register Error");
        msgBox.setText("register error");
        msgBox.exec();
        usernameInput->setText("");
        passwordInput->setText("");
    }
}