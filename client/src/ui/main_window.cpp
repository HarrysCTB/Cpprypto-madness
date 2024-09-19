#include "main_window.h"

MainWindow::MainWindow(UserController *userController, QWidget *parent)
    : QMainWindow(parent), authPage(new AuthPage(this)), homePage(new HomePage(this)), userController(userController)
{
    QWidget *loadingWidget = new QWidget(this);
    QLabel *iconLabel = new QLabel(loadingWidget);
    QPixmap pixmap("./client/assets/logo.png");
    iconLabel->setPixmap(pixmap);
    iconLabel->setScaledContents(true);
    iconLabel->setFixedSize(150, 150);

    QVBoxLayout *layout = new QVBoxLayout(loadingWidget);
    layout->addWidget(iconLabel);
    layout->setAlignment(Qt::AlignCenter);
    loadingWidget->setLayout(layout);
    loadingWidget->setStyleSheet("background-color: #222831;");

    setCentralWidget(loadingWidget);

    authPage->setWindowTitle("Vortex Messenger");
    authPage->resize(350, 430);
    authPage->hide();

    homePage->hide();

    setFixedSize(350, 430);

    connect(userController, &UserController::connectToServer, this, [this, loadingWidget] {
        authPage->show();
        setCentralWidget(authPage);
        loadingWidget->hide();
    });

    connect(authPage, &AuthPage::LoginOk, this, [this] {
        setCentralWidget(homePage);
        setFixedSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        resize(1280, 720);
        setMinimumSize(800, 600);

        homePage->resize(1280, 720);
        homePage->setWindowTitle("Vortex Messenger");
        homePage->show();

        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();
        move((screenGeometry.width() - width()) / 2, (screenGeometry.height() - height()) / 2);
    });

    connect(authPage, &AuthPage::newLogin, userController, &UserController::sendLogin);
    connect(authPage, &AuthPage::newRegister, userController, &UserController::sendRegister);
    connect(userController, &UserController::sendLoginCode, authPage, &AuthPage::responseLogin);
    connect(userController, &UserController::sendRegisterCode, authPage, &AuthPage::responseRegister);
}

MainWindow::~MainWindow() {
    delete authPage;
    delete homePage;
}

void MainWindow::handleNewConnection() {
    homePage->show();
}
