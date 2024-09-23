#include "private_message_ui.h"

PrivateMessageUi::PrivateMessageUi(std::string nameUser, QWidget *parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    initaliseChatScrollArea();

    nameUser_ = nameUser;
    initaliseSendMsg();

    setMsg("jordan", "salut");
    setMsg("jordan", "cava ?");
    setUserMsg("yassine", "salut, oui cava et toi ?");
    setMsg("jordan", "cava merci");
    setUserMsg("yassine", "je suis a l'ecole t'es ou ?");
    setMsg("jordan", "j'arrive il y avais des bouchon, je suis tomber en panne avec ma voiture laisse tombe c'etais un chantier tu reste juska quel heur a l'ecole ?");
    setUserMsg("yassine", "ah oe c'est la merde jusu'a 17h et toi ?");
    setMsg("jordan", "pareil je pense");
    setMsg("jordan", "bon j'arrive");
    setUserMsg("yassine", "vasy a ++");

}

PrivateMessageUi::~PrivateMessageUi() { }

void PrivateMessageUi::initaliseChatScrollArea() {
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
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

    QWidget *scrollWidget = new QWidget;
    scrollWidget->setStyleSheet("border: none;");
    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->setSpacing(10);
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);
}

void PrivateMessageUi::initaliseSendMsg() {
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setFixedHeight(50);
    bottomWidget->setObjectName("bottomWidget");
    bottomWidget->setStyleSheet(" #bottomWidget { background-color: white; border-top: 1px solid #D3D3D3; }");

    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomLayout->setContentsMargins(20, 0, 20, 0);

    QLineEdit *inputMsg = new QLineEdit;
    inputMsg->setFixedHeight(40);
    inputMsg->setStyleSheet(" border: none; ");
    inputMsg->setPlaceholderText("Send a message...");
    inputMsg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QPushButton *sendBtn = new QPushButton;
    sendBtn->setCursor(Qt::PointingHandCursor);
    sendBtn->setStyleSheet(" border: none; ");
    sendBtn->setIcon(QIcon("./client/assets/sendMsgBtn.png"));
    sendBtn->setIconSize(QSize(40, 40));
    sendBtn->setFixedSize(45, 45);

    connect(sendBtn, &QPushButton::clicked, [this, inputMsg]() {
        emit sendMsg(nameUser_, inputMsg->text().toStdString());
        inputMsg->setText("");
    });

    bottomLayout->addWidget(inputMsg);
    bottomLayout->addWidget(sendBtn);
    mainLayout->addWidget(bottomWidget);
}

void PrivateMessageUi::setUserMsg(const std::string& nameRoom, const std::string& msg) {
    
    QHBoxLayout *msgLayout = new QHBoxLayout();
    QLabel *msgLabel = new QLabel(QString::fromStdString(msg));
    int maxWidth = 450;
    msgLabel->setStyleSheet("background-color: #FD7014; font-size: 12px; color: white; padding: 10px; border-radius: 5px;");
    msgLabel->setMaximumWidth(maxWidth);
    QFontMetrics metrics(msgLabel->font());
    int textWidth = metrics.horizontalAdvance(msgLabel->text());
    if (textWidth > maxWidth) {
        msgLabel->setWordWrap(true);
        msgLabel->setFixedWidth(maxWidth);
    } else {
        msgLabel->setWordWrap(false);
    }
    int numLines = 0;
    int totalHeight = metrics.height() * 2;
    if (msgLabel->wordWrap()) {
        numLines = (textWidth / maxWidth) + 2;
        totalHeight = numLines * metrics.height();
    }
    msgLabel->setFixedHeight(totalHeight);
    msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    msgLayout->addWidget(msgLabel, 0, Qt::AlignLeft);
    msgLayout->setContentsMargins(20, 10, 20, 10);
    scrollLayout->addLayout(msgLayout);
}

void PrivateMessageUi::setMsg(const std::string& nameRoom, const std::string& msg) {
    
    QHBoxLayout *msgLayout = new QHBoxLayout();
    QLabel *msgLabel = new QLabel(QString::fromStdString(msg));
    int maxWidth = 450;
    msgLabel->setStyleSheet("background-color: #E2E2E2; font-size: 12px; color: black; padding: 10px; border-radius: 5px;");
    msgLabel->setMaximumWidth(maxWidth);
    QFontMetrics metrics(msgLabel->font());
    int textWidth = metrics.horizontalAdvance(msgLabel->text());
    if (textWidth > maxWidth) {
        msgLabel->setWordWrap(true);
        msgLabel->setFixedWidth(maxWidth);
    } else {
        msgLabel->setWordWrap(false);
    }
    int numLines = 0;
    int totalHeight = metrics.height() * 2;
    if (msgLabel->wordWrap()) {
        numLines = (textWidth / maxWidth) + 2;
        totalHeight = numLines * metrics.height();
    }
    msgLabel->setFixedHeight(totalHeight);
    msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    msgLayout->addWidget(msgLabel, 0, Qt::AlignRight);
    msgLayout->setContentsMargins(20, 10, 20, 10);
    scrollLayout->addLayout(msgLayout);
}
