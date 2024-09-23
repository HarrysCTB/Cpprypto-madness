#include "home_page.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: rgb(255, 255, 255);");

    horizontalLayout_ = new QHBoxLayout;
    horizontalLayout_->setContentsMargins(0, 0, 0, 0);

    QWidget *SelectRoomsWidget = new QWidget;
    QVBoxLayout *leftVerticalLayout = new QVBoxLayout;
    leftVerticalLayout->setContentsMargins(0, 0, 0, 0);

    initTopWidget();
    initMiddleWidget();
    initBottomWidget();

    leftVerticalLayout->setSpacing(0);
    leftVerticalLayout->addWidget(topWidget);
    leftVerticalLayout->addWidget(middleWidget);
    leftVerticalLayout->addWidget(conversationsWidget);
    
    SelectRoomsWidget->setLayout(leftVerticalLayout);
    SelectRoomsWidget->setFixedWidth(225);
    SelectRoomsWidget->setObjectName("SelectRoomsWidget");
    SelectRoomsWidget->setStyleSheet("#SelectRoomsWidget { padding: 0px; margin: 0px; background-color: white; border-right: 1px solid #D3D3D3; }");

    rightWidget_ = new QWidget;

    stackedWidget_ = new QStackedWidget(rightWidget_);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget_);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addWidget(stackedWidget_);

    addConvWidget = new QWidget;
    addConvWidget->setStyleSheet("background-color: rgba(0, 0, 0, 0.3);");

    QWidget *addConvCentralWidget = new QWidget;
    addConvCentralWidget->setStyleSheet("background-color: white; border-radius: 5px;");
    addConvCentralWidget->setFixedSize(400, 200);
    QVBoxLayout *addConvLayout = new QVBoxLayout(addConvCentralWidget);
    addConvLayout->setContentsMargins(15, 15, 15, 15);

    QPushButton *addConvCloseButton = new QPushButton("✖");
    addConvCloseButton->setCursor(Qt::PointingHandCursor);
    addConvCloseButton->setStyleSheet("background-color: transparent; border: none; font-size: 16px;");
    addConvLayout->addWidget(addConvCloseButton, 0, Qt::AlignTop | Qt::AlignLeft);
    QObject::connect(addConvCloseButton, &QPushButton::clicked, [=]() {
        setWidget(PageType::Index);
    });

    QLabel *addConvMiddleText = new QLabel("New Conversation");
    addConvMiddleText->setStyleSheet("font: 18px;");
    addConvMiddleText->setAlignment(Qt::AlignCenter);
    addConvLayout->addWidget(addConvMiddleText);

    QLabel *addConvBottomText = new QLabel("To initialize MP with the specified user @Username,\neither to create or join a room #NameRoom.\nIf your room requires a password, use #NameRoom:password.");
    addConvBottomText->setStyleSheet("color: gray; font: 12px;");
    addConvBottomText->setAlignment(Qt::AlignCenter);
    addConvLayout->addWidget(addConvBottomText);

    QWidget *addConvInputLayoutWidget = new QWidget;
    QHBoxLayout *addConvInputLayout = new QHBoxLayout(addConvInputLayoutWidget);

    QLineEdit *addConvInputField = new QLineEdit;
    addConvInputField->setPlaceholderText("@Username or #Room:password");
    addConvInputField->setFixedHeight(23);
    addConvInputField->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid gray;"
        "    border-radius: 5px;"
        "    padding: 2px;"
        "    font-size: 12px;"
        "    text-align: center;"
        "}"
        "QLineEdit::placeholder {"
        "    color: #B0B0B0;"
        "    font-style: italic;"
        "}"
    );
    addConvInputField->setAlignment(Qt::AlignCenter);
    addConvInputLayout->addWidget(addConvInputField);

    QPushButton *addConvSubmitButton = new QPushButton("+");
    addConvSubmitButton->setCursor(Qt::PointingHandCursor);
    addConvSubmitButton->setFixedWidth(45);
    addConvSubmitButton->setFixedHeight(23);
    addConvSubmitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addConvSubmitButton->setObjectName("btnAdd");
    addConvSubmitButton->setStyleSheet(
        "#btnAdd { background-color: #E2E2E2; color: black; text-align: center; padding: 0px; font-size: 15px; border-radius: 5px; }"
        "#btnAdd:hover { background-color: #F1F1F1; }"
        "#btnAdd:pressed { background-color: #F6F6F6; color: rgba(0, 0, 0, 0.3);}"
    );
    addConvInputLayout->addWidget(addConvSubmitButton);
    addConvLayout->addWidget(addConvInputLayoutWidget);
    QObject::connect(addConvSubmitButton, &QPushButton::clicked, [=]() {

        QString inputText = addConvInputField->text();
        if (inputText.startsWith("@")) {
            emit setNewConvUser('@', inputText.mid(1).toStdString());
        } else if (inputText.startsWith("#")) {
            emit setNewConvRoom('#', inputText.mid(1).toStdString());
        }

        setWidget(PageType::Index);
        addConvInputField->setText("");
    });


    QVBoxLayout *addConvMainLayout = new QVBoxLayout(addConvWidget);
    addConvMainLayout->addWidget(addConvCentralWidget, 0, Qt::AlignCenter);

    // Layout horizontal
    horizontalLayout_->setSpacing(0);
    horizontalLayout_->addWidget(SelectRoomsWidget);
    horizontalLayout_->addWidget(rightWidget_);
    setLayout(horizontalLayout_);
}

HomePage::~HomePage() {
    delete conversationsButtons_;
    delete rightWidget_;
    delete convButtonClicked_;
    delete horizontalLayout_;
    delete stackedWidget_;
}

void HomePage::initTopWidget() {
    topWidget = new QWidget;
    topWidget->setFixedHeight(100);
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(10, 0, 0, 0);

    QWidget *roundWidget = new QWidget;
    roundWidget->setFixedSize(70, 70);
    roundWidget->setObjectName("topRoundedWidget");
    roundWidget->setStyleSheet("#topRoundedWidget { background-color: #E2E2E2; border: 0.5px solid #FD7014; border-radius: 35px;}");
    roundWidget->setContentsMargins(10, 10, 10, 10);
    QLabel *initalUser = new QLabel("JS");
    initalUser->setObjectName("topInitialLabel");
    initalUser->setStyleSheet("#topInitialLabel { background-color: transparent; color: black; }");
    initalUser->setAlignment(Qt::AlignCenter);
    QVBoxLayout *layoutInitial = new QVBoxLayout(roundWidget);
    layoutInitial->addWidget(initalUser, 0, Qt::AlignCenter);
    roundWidget->setLayout(layoutInitial);
   
    QWidget *infoWidget = new QWidget;
    infoWidget->setFixedSize(130, 55);
    infoWidget->setStyleSheet("background-color: transparent;");
    QVBoxLayout *infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setContentsMargins(0, 0, 0, 0);
    infoLayout->setSpacing(0);
    QLabel *firstLabel = new QLabel("@jordan0923");
    firstLabel->setStyleSheet("padding: 0px;");
    infoLayout->addWidget(firstLabel, 0, Qt::AlignBottom);
    infoWidget->setLayout(infoLayout);
    QPushButton *iconSettingButton = new QPushButton();
    iconSettingButton->setCursor(Qt::PointingHandCursor);
    iconSettingButton->setObjectName("topButtonSettingWidget");
    iconSettingButton->setStyleSheet(
        "#topButtonSettingWidget { background-color: transparent; border: none; padding-bottom: 10px; padding-right: 5px;}"
    );
    QPixmap pixmap("./client/assets/logoSetting.png");
    iconSettingButton->setIcon(QIcon(pixmap));
    iconSettingButton->setIconSize(QSize(20, 20));
    QObject::connect(iconSettingButton, &QPushButton::clicked, [=]() {
        convButtonClicked_->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "border-bottom: 0.5px solid #E5E5E5; "
            "color: #BDBDBD; "
            "padding-left: 10px; "
            "text-align: left;"
            "}"
            "QPushButton:hover {"
            "color: #B2B2B2; "
            "border-bottom: 0.5px solid #B2B2B2; "
            "}"
        );

        setWidget(PageType::Setting);
    });

    topLayout->addWidget(roundWidget, 0, Qt::AlignRight);
    topLayout->addWidget(infoWidget, 0, Qt::AlignTop);
    topLayout->addWidget(iconSettingButton, 0, Qt::AlignBottom | Qt::AlignRight);
    topWidget->setLayout(topLayout);

    topWidget->setObjectName("topWidget");
    topWidget->setStyleSheet(" #topWidget { padding: 0px; margin: 0px; background-color: white; border-bottom: 1px solid #D3D3D3; border-right: 1px solid #D3D3D3;}");
}

void HomePage::initMiddleWidget() {
    middleWidget = new QWidget;
    middleWidget->setFixedHeight(50);
    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->setContentsMargins(10, 0, 20, 0);
    QLabel *textLabel = new QLabel("All Conversation");
    textLabel->setObjectName("allConv");
    textLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    textLabel->setStyleSheet(
        " #allConv {padding: 0px; font-size: 15px; margin: 0px; background-color: transparent; color: black; }"
        " #allConv:hover {padding: 0px; font-size: 33px; margin: 0px; background-color: transparent; color: black; }"
    );

    addConvButton = new QPushButton("+");
    addConvButton->setCursor(Qt::PointingHandCursor);
    addConvButton->setFixedWidth(45);
    addConvButton->setFixedHeight(23);
    addConvButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addConvButton->setObjectName("btnAdd");
    addConvButton->setStyleSheet(
        "#btnAdd { background-color: #E2E2E2; color: black; text-align: center; padding: 0px; font-size: 15px; border-radius: 5px; }"
        "#btnAdd:hover { background-color: #F1F1F1; }"
        "#btnAdd:pressed { background-color: #F6F6F6; color: rgba(0, 0, 0, 0.3);}"
    );
    middleLayout->addWidget(textLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    middleLayout->addStretch();
    middleLayout->addWidget(addConvButton, 0, Qt::AlignRight | Qt::AlignVCenter);
    middleWidget->setLayout(middleLayout);
    middleWidget->setObjectName("middleWidget");
    middleWidget->setStyleSheet(" #middleWidget { padding: 0px; margin: 0px; background-color: white; border-bottom: 0.5px solid #E2E2E2; border-right: 1px solid #D3D3D3;}");

    QObject::connect(addConvButton, &QPushButton::clicked, [=]() {
        convButtonClicked_->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "border-bottom: 0.5px solid #E5E5E5; "
            "color: #BDBDBD; "
            "padding-left: 10px; "
            "text-align: left;"
            "}"
            "QPushButton:hover {"
            "color: #B2B2B2; "
            "border-bottom: 0.5px solid #B2B2B2; "
            "}"
        );

        setWidget(PageType::Index);
        stackedWidget_->addWidget(addConvWidget);
    });
}

void HomePage::initBottomWidget() {
    conversationsWidget = new QWidget;

    conversationsButtons_ = new QVBoxLayout;
    conversationsButtons_->setContentsMargins(0, 0, 0, 0);
    conversationsButtons_->setSpacing(0);

    convButtonClicked_ = new QPushButton;

    addConv(ConvType::PM, "@elarif3310");           // Todo remove
    addConv(ConvType::RM, "La Plateforme");         // Todo remove
    addConv(ConvType::PM, "@yassKiFouR");           // Todo remove
    addConv(ConvType::RM, "Projet Chat Chiffrer");  // Todo remove

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setContentsMargins(0, 0, 1, 0);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    background: transparent;"
        "    width: 5px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(0, 0, 0, 0.4);"
        "    border-radius: 2px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0;"
        "    width: 0;"
        "}"
    );

    QWidget *innerWidgetBtn = new QWidget;
    innerWidgetBtn->setContentsMargins(0, 0, 1, 0);
    innerWidgetBtn->setStyleSheet("margin: 0; padding: 0;");
    innerWidgetBtn->setLayout(conversationsButtons_);
    scrollArea->setWidget(innerWidgetBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(conversationsWidget);
    mainLayout->setContentsMargins(0, 0, 1, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(scrollArea);

    conversationsWidget->setObjectName("conversationsWidget");
    conversationsWidget->setStyleSheet("#conversationsWidget { background-color: transparent; padding: 0; margin: 0; border: none; border-right: 1px solid #D3D3D3; }");
}

void HomePage::setWidget(PageType pageType, QString name) {
    while (stackedWidget_->count() > 0) {
        QWidget *widget = stackedWidget_->widget(0);
        stackedWidget_->removeWidget(widget);
    }

    if (pageType == PageType::Index) {
        std::cout << "Index" << std::endl;
        // stackedWidget_->addWidget();
    } else if (pageType == PageType::Setting) {
        std::cout << "Setting" << std::endl;
        // stackedWidget_->addWidget();
    } else if (pageType == PageType::PrivateMessage) {
        stackedWidget_->addWidget(new PrivateMessageUi(name.toStdString()));
    } else if (pageType == PageType::Room) {
        stackedWidget_->addWidget(new RoomUi(name.toStdString()));
    }
}

void HomePage::setWidget(PageType pageType) {
    setWidget(pageType, "");
}

void HomePage::addConv(ConvType convType, QString data) {
    QPushButton *button = new QPushButton();
    button->setFixedHeight(40);
    button->setFixedWidth(175);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(
        "QPushButton {"
        "border: none; "
        "border-bottom: 0.5px solid #E5E5E5; "
        "color: #BDBDBD; "
        "padding-left: 10px; "
        "text-align: left;"
        "}"
        "QPushButton:hover {"
        "color: #B2B2B2; "
        "border-bottom: 0.5px solid #B2B2B2; "
        "}"
    );
    conversationsButtons_->addWidget(button);

    QString name(data);
    button->setText(name);
    QObject::connect(button, &QPushButton::clicked, [=]() {
        convButtonClicked_->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "border-bottom: 0.5px solid #E5E5E5; "
            "color: #BDBDBD; "
            "padding-left: 10px; "
            "text-align: left;"
            "}"
            "QPushButton:hover {"
            "color: #B2B2B2; "
            "border-bottom: 0.5px solid #B2B2B2; "
            "}"
        );
        button->setStyleSheet(
            "QPushButton {"
            "border: none; "
            "border-bottom: 0.5px solid #FD7014; "
            "color: #FD7014; "
            "padding-left: 10px; "
            "text-align: left;"
            "}"
        );
        if (convType == ConvType::PM) {
            setWidget(PageType::PrivateMessage, name);
        } else if (convType == ConvType::RM) {
            setWidget(PageType::Room, name);
        }
        convButtonClicked_ = button;
    });
}

void HomePage::newConv() {

}
