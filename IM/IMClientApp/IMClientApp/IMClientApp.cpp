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
#include "IMQTcpWord/IMQTcpWord.h"

enum sendObject
{
    IMSERVER,
    OTHERUSER,
    YOUSELF,
};

enum operationType
{
    LOGONG,//登录
    RETRANSMIT,//转发
    GETFRIENDDATA,//请求好友数据
};

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
    this->setWindowTitle(IMSettings.getLogonSettings("userID").toString());
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
    QJsonObject json;
    json.insert("sendObject", sendObject::OTHERUSER);
    json.insert("operationType", operationType::RETRANSMIT);
    json.insert("to", to);
    json.insert("from", IMUSERID);
    json.insert("data", msg);
    QJsonDocument document = QJsonDocument(json);

    qDebug() << IMQTcpSocket->state();

    IMQTcpSocket->write(document.toJson());
    IMQTcpSocket->flush();
}

void IMClientApp::slotSocketReadData()
{
    QJsonDocument document = QJsonDocument::fromJson(IMQTcpSocket->readAll());
    QJsonObject object = document.object();

    int sendObject = object.value("sendObject").toInt();
    int operationType = object.value("operationType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();
    QString data = object.value("data").toString();

    if (sendObject == sendObject::OTHERUSER)
    {
        auto i = m_hashFriendPanel->find(from);
        if (i != m_hashFriendPanel->end())
        {
            ChatPanel *chat = i.value();
            chat->setFriendMsg(from,data);
        }
    }
}
