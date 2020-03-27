#include "IMClientApp.h"
#include "ui_IMClientApp.h"
#include "LogonPanel/LogonPanel.h"
#include <QHBoxLayout>
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"
#include "AppSettings/AppSettings.h"
#include "IMClientSocket.h"
#include <QJsonObject>
#include <QJsonDocument>
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
    QByteArray &byte = IMQJson::getQJsonByte(MsgType::USERMSG, to, IMUSERID,msg);

    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void IMClientApp::slotSendFile(QByteArray &byte)
{
    int a = 0;
}

void IMClientApp::slotSocketReadData()
{
    QByteArray byte = IMQTcpSocket->readAll();
    QJsonDocument document = QJsonDocument::fromJson(byte);
    QJsonObject object = document.object();

    int msgType = object.value("msgType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();

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
        QString data = object.value("data").toString();
        chat->setFriendMsg(from, data);
    }
    break;

    case  MsgType::FILENAME:
    {
        QString address = object.value("address").toString();
        QString file = object.value("file").toString();
        chat->hasPendingFile("", address, "", file);
        break;
    }

    case MsgType::REFUSEFILE:
        break;
    default:
        break;
    }
}
