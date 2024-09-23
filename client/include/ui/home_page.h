#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include "room_ui.h"
#include "private_message_ui.h"

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStackedWidget>

#include <iostream>

enum ConvType {
    PM,
    RM
};

enum PageType {
    Index,
    Setting,
    PrivateMessage,
    Room
};

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private:
    void initTopWidget();
    void initMiddleWidget();
    void initBottomWidget();

    void setWidget(PageType pageType, QString data);
    void setWidget(PageType pageType);

    void newConv();
    QPushButton *convButtonClicked_;

    QHBoxLayout *horizontalLayout_;
    QVBoxLayout *conversationsButtons_;
    QWidget *rightWidget_;
    QStackedWidget *stackedWidget_;

    QWidget *topWidget;
    QWidget *middleWidget;
    QWidget *conversationsWidget;

    QWidget *addConvWidget;
    QPushButton *addConvButton;

signals:
    void setNewConvUser(char type, const std::string& nam);
    void setNewConvRoom(char type, const std::string& name);
    void newConvUser(const std::string& name);
    void newConvRoom(const std::string& name);

public slots:
    void addConv(ConvType convType, QString data);
};

#endif  // HOME_PAGE_H
