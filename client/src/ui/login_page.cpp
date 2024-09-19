#include "login_page.h"
#include "home_page.h"

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {
    this->setStyleSheet("background-color: #222831;");

    QLabel *iconLabel = new QLabel(this);
    QPixmap pixmap("../client/assets/logo.png");
    iconLabel->setPixmap(pixmap);
    iconLabel->setScaledContents(true);
    iconLabel->setFixedSize(35, 35);

    QLabel *title = new QLabel("Vortex Messenger", this);
    title->setStyleSheet("font-size: 16px; color: #FFFFFF; font-weight: semibold;");

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addWidget(iconLabel);
    titleLayout->addWidget(title);

    QWidget *titleWidget = new QWidget(this);
    titleWidget->setLayout(titleLayout);

    QFrame *loginCard = new QFrame(this);
    loginCard->setStyleSheet(
            "QFrame {"
            "    background-color: #37414f;"
            "    border-radius: 10px;"
            "    padding-bottom: 20px;"
            "    padding-top: 20px;"
            "}"
    );
    loginCard->setFixedSize(320, 280);

    QLabel *subtitle = new QLabel("Login", loginCard);
    subtitle->setStyleSheet("font-size: 20px; color: #FFFFFF; font-weight: bold;");

    QLabel *usernameLabel = new QLabel("Username", loginCard);
    usernameLabel->setStyleSheet("font-size: 12px; color: #A9A9A9");
    usernameInput = new QLineEdit(loginCard);
    usernameInput->setPlaceholderText("username");
    usernameInput->setStyleSheet("border-bottom: 2px solid gray; padding: 5px; font-size: 14px;");
    usernameInput->setFixedSize(200, 30);

    QLabel *passwordLabel = new QLabel("Password", loginCard);
    passwordLabel->setStyleSheet("font-size: 12px; color: #A9A9A9");
    passwordInput = new QLineEdit(loginCard);
    passwordInput->setPlaceholderText("password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet("border-bottom: 2px solid gray; padding: 5px; font-size: 14px;");
    passwordInput->setFixedSize(200, 30);

    loginButton = new QPushButton("Connexion", loginCard);
    loginButton->setStyleSheet(
            "QPushButton {"
            "background-color: #fd7014; color: white; font-size: 16px; padding: 10px; border-radius: 5px;"
            "}"
            "QPushButton:hover {"
            "background-color: #ff8c42;"
            "}"
    );
    loginButton->setFixedSize(100, 40);

    QVBoxLayout *cardLayout = new QVBoxLayout(loginCard);
    cardLayout->addWidget(subtitle, 0, Qt::AlignCenter);
    cardLayout->addSpacing(20);
    cardLayout->addWidget(usernameLabel);
    cardLayout->addWidget(usernameInput);
    cardLayout->addSpacing(5);
    cardLayout->addWidget(passwordLabel);
    cardLayout->addWidget(passwordInput);
    cardLayout->addSpacing(20);
    cardLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    cardLayout->setAlignment(Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addStretch();
    mainLayout->addWidget(titleWidget, 0, Qt::AlignCenter);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(loginCard, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::handleLogin);
}

void LoginPage::handleLogin() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur de connexion", "Veuillez entrer un nom d'utilisateur et un mot de passe.");
    } else {
        QMessageBox::information(this, "Connexion réussie", "Bienvenue " + username + " !");
    }

    HomePage *homePage = new HomePage();
    homePage->show();
    this->close();
}



