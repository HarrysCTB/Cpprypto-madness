#include "client.hpp"
#include "main_window.h"
#include "user_controller.h"
#include <thread>

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    UserController userController;

    MainWindow mainWindow(&userController);
    mainWindow.show();

    std::thread t([&userController, &mainWindow]() {
        Client client(&userController, &mainWindow);
        client.run();
    });

    app.exec();
    t.join();
    return 0;
}