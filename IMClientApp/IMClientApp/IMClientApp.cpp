#include "IMClientApp.h"
#include "QtUITool/QImageTool.h"
#include "AppSettings/AppPath.h"
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"
#include "FriendPanel/FriendListWidget.h"
#include "DataCenter/DataCenter.h"
#include "DataCenter/IMQTcpWord.h"
#include <memory>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

IMClientApp::IMClientApp(QWidget *parent)
    : QWidget(parent)
    , currentChatPanel(nullptr)
{
    ui.setupUi(this);
    m_hashChant = new QHash<QString, ChatPanel *>;

    this->createUi();
    this->bindSignlSlot();
}

void IMClientApp::slotOpenChatPanel(UserInfo &userInfo)
{
    if (currentChatPanel != nullptr)
    {
        currentChatPanel->hide();
    }
    ChatPanel *chat = m_hashChant->value(userInfo.id);
    if (chat != nullptr)
    {
        chat->show();
        currentChatPanel = chat;
    }
    else
    {
        chat=new ChatPanel(userInfo.id, userInfo.name, this);
        m_hashChant->insert(userInfo.id, chat);
        currentChatPanel = chat;
        ui.chatWidgetLayout->addWidget(chat);
    }
}

void IMClientApp::slotChatMsg(MsgInfo msgInfo)
{
    ChatPanel *chatPanel = m_hashChant->value(msgInfo.from);
    if (chatPanel != nullptr)
    {
        chatPanel->setFriendMsg(msgInfo.from, msgInfo.msg);
    }
    qDebug() << "current chatPanel no open ";
}

void IMClientApp::createUi()
{
    //标题
    QPixmap pixmap;
    ui.label->setPixmap(QPixmap(IMPATH::ImgPath("img_btn_normal.png")));
    ui.label->setScaledContents(true);
    ui.label->setStyleSheet(
        "border:2px groove gray;border-radius:15px;"
    );
    pixmap.load(IMPATH::ImgPath("img_logon_default_head.png"));
    m_btnUserHead = new QPushButton(this);
    m_btnUserHead->setFlat(true);
    m_btnUserHead->setIcon(QImageTool::generatePixmap(IMPATH::ImgPath("img_logon_default_head.png"), 60));
    m_btnUserHead->setIconSize(QSize(60, 60));
    m_btnUserHead->setGeometry(5, 5, 60, 60);
    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setGeometry(75, 25, 100, 20);
    m_lineEdit->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px");

    //好友界面
    //friendPanel = new FriendPanel(this);
    //ui.friendWidgetLayout->addWidget(friendPanel);
    friendPanel = new FriendListWidget(this);
    ui.friendWidgetLayout->addWidget(friendPanel);

    //测试label
    QLabel *label = new QLabel(this);
    label->setGeometry(300, 25, 100, 20);
    UserInfoPtr info = DataCenterInst.getMyInfo();
    label->setText(QString("I am is %1,my ID is%2").arg(info->name, info->id));
}

void IMClientApp::bindSignlSlot()
{
    //好友界面传来的信号
    connect(friendPanel, &FriendListWidget::signUserInfo, this, &IMClientApp::slotOpenChatPanel);
    connect(&IMQTcpWordInstance, &IMQTcpWord::signChatMsg, this, &IMClientApp::slotChatMsg);

}
