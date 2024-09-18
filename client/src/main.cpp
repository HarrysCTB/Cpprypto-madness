#include "client.hpp"
#include <QApplication>
#include <QWidget>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget window;

    window.setWindowTitle("Ma Fenêtre Qt");
    window.resize(800, 600);

    window.show();

    //Client client;
    //client.run();
    return app.exec();
}