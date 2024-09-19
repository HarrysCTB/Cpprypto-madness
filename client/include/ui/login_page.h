#ifndef LOGIN_PAGE_H
#define LOGIN_PAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>


class LoginPage : public QWidget {

public:
    explicit LoginPage(QWidget *parent = nullptr);

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QVBoxLayout *layout;

    void handleLogin();
};

#endif  // LOGIN_PAGE_H

