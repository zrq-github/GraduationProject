#include "IMClientApp.h"
#include "ui_IMClientApp.h"
#include "LogonPanel/LogonPanel.h"
#include <QHBoxLayout>
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"
#include "AppSettings/AppSettings.h"
#include "Base/IMQTransport.h"
#include "Base/IMQJson.h"
#include "IMQTcpWord/IMQTcpWord.h"

IMClientApp::IMClientApp(QWidget *parent)
    : QWidget(parent)
    , m_friendPanel(Q_NULLPTR)
    , m_hashFriendPanel(Q_NULLPTR)
{
    ui = new Ui::IMClientAppClass;
    ui->setupUi(this);
    //初始化数据
    m_hashFriendPanel = new QHash<QString, ChatPanel *>;

    createUi();
    bindSigns();

    analyzeFriendData();
}

void IMClientApp::bindSigns()
{ 
    connect(m_friendPanel, &FriendPanel::signCreateChatPanel, this, &IMClientApp::slotCreateChatPanel);
    connect(IMQTcpSocket, &QTcpSocket::readyRead, this, &IMClientApp::slotSocketReadData);
}

void IMClientApp::slotCreateChatPanel(QString id, QString name)
{
    //创建之前先判断该聊天框是否存在
    if (m_hashFriendPanel->value(id)==nullptr)
    {
        ChatPanel *chat = new ChatPanel(id, name);
        connect(chat, &ChatPanel::signClose, this, &IMClientApp::slotDeletChatPanel);
        connect(chat, &ChatPanel::signSendMessage, this, &IMClientApp::slotSendMessage);
        connect(chat, &ChatPanel::signSendFile, this, &IMClientApp::slotSendFile);

        chat->setWindowTitle(name + "(" + id + ")");
        chat->show();
        m_hashFriendPanel->insert(id, chat);
    }
}

void IMClientApp::createUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_friendPanel = new FriendPanel(this);
    layout->addWidget(m_friendPanel);
    this->setLayout(layout);

    //基础数据初始化
    this->setWindowTitle(IMUSERID);
}

void IMClientApp::analyzeFriendData()
{//解析好友数据
    for (int i = 0; i < 10; i++)
    {
        FriendDataPtr d = FriendDataMake();
        d->id = QString::number(i);
        d->name = QString::number(i);
        m_friendData.append(d);
    }
    m_friendPanel->initFriendData(m_friendData);
}

void IMClientApp::slotDeletChatPanel(QString id)
{
    QHash<QString, ChatPanel *>::iterator it = m_hashFriendPanel->find(id);
    if (it != m_hashFriendPanel->end())
    {
        ChatPanel* cp = it.value();
        delete cp;
        cp = Q_NULLPTR;
        m_hashFriendPanel->erase(it);
    }
}

void IMClientApp::slotSendMessage(QString & to, QString & msg)
{//封装数据
    MsgInfo msgInfo;
    msgInfo.msgType = MsgType::USERMSG;
    msgInfo.to = to;
    msgInfo.from = IMUSERID;
    msgInfo.msg = msg;
    QByteArray &byte = IMQPROTOCOL::getMsgQByteArray(msgInfo);

    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void IMClientApp::slotSendFile(QByteArray &byte)
{
    int a = 0;
}

void IMClientApp::requsetFriendData()
{//请求好友数据
    analyzeFriendData();
}

void IMClientApp::slotSocketReadData()
{
    QDataStream in(IMQTcpSocket->readAll());
    MsgInfo info;
    in >> info;

    int msgType = info.msgType;
    QString to = info.to;
    QString from = info.from;

    auto i = m_hashFriendPanel->find(from);
    ChatPanel *chat = i.value();

    if (i == m_hashFriendPanel->end())
    {
        return;
    }
    switch (msgType)
    {
    case MsgType::USERMSG://客服端发送的消息
    {
        QString msg = info.msg;
        chat->setFriendMsg(from, msg);
    }
    break;

    case  MsgType::FILENAME:
    {
        QString address = info.address;
        QString file = info.msg;
        chat->hasPendingFile("", address, "", file);
        break;
    }

    case MsgType::USERFRIENDDATA:
    {
        analyzeFriendData();
        break;
    }
    case MsgType::REFUSEFILE:
        break;
    default:
        break;
    }
}
