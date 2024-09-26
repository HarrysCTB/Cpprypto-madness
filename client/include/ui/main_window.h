#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "auth_page.h"
#include "home_page.h"
#include "user_controller.h"

#include <QMainWindow>
#include <QScreen>

class UserController;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(UserController *userController, QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void handleNewConnection(); 

private:
    AuthPage *authPage;
    HomePage *homePage;

    UserController *userController;
};

#endif // MAIN_WINDOW_H
