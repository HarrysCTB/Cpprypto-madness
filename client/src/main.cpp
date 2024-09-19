#include "client.hpp"
#include "login_page.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    LoginPage loginPage;

    loginPage.setWindowTitle("Connect to Vortex Messenger");
    loginPage.resize(800, 600);

    loginPage.show();

    //Client client;
    //client.run();
    return app.exec();
}