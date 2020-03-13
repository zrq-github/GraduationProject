#include "IM.h"
#include "ui_IM.h"
#include <QMoveEvent>
#include "IMTitleBarPanel.h"
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"
#include <QSplitter>
#include <QJsonObject>
#include <QJsonDocument>
#include "AppSettings/AppSettings.h"

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QHostInfo>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

IM::IM(QWidget *parent)
    : QWidget(parent)
    , friendPanel(Q_NULLPTR)
    , chatPanel(Q_NULLPTR)
{
    ui = new Ui::IM();
    ui->setupUi(this);
    tcpClient = new QTcpSocket;

    this->createUi();
    //this->setWindowFlags(Qt::FramelessWindowHint);      //�ޱ߿򣬵�����������ʾ�Ի������
    this->binSlots(); 
    this->testServer();

    //ɾ��
    QString who = IMSettings.getSetting("LogonSettings", "lastLogonId").toString();
    this->setWindowTitle(who);
}

IM::~IM()
{
    delete ui;
}

void IM::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mousePressEvent(event);
}

void IM::mouseMoveEvent(QMouseEvent * event)
{
    if (m_moving && (event->buttons() && Qt::LeftButton)
        && (event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void IM::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    m_moving = false; //ֹͣ�ƶ�
}

void IM::createUi()
{
    IMTitleBarPanel *titleBar = new IMTitleBarPanel;
    ui->layoutTitleBar->addWidget(titleBar, 0, Qt::AlignLeft);
    friendPanel = new FriendPanel;
    chatPanel = new ChatPanel;

    QSplitter *splitterLMain = new QSplitter(Qt::Horizontal, 0);
    ui->horizontalLayout->addWidget(splitterLMain);

    QSplitter *splitterLeft = new QSplitter(splitterLMain);
    splitterLeft->setMinimumWidth(100);
    splitterLeft->setChildrenCollapsible(true);
    splitterLeft->addWidget(friendPanel);

    QSplitter *splitterRight = new QSplitter(splitterLMain);
    splitterRight->addWidget(chatPanel);

    splitterLMain->setStretchFactor(1, 3);
}

void IM::binSlots()
{
    //���Ժ��ѽ�����ź�
    connect(friendPanel, SIGNAL(childClick(QString&, QString&)),
        chatPanel, SLOT(slotChatterChange(QString&, QString&)));
    //�������촰�ڵ��ź�
    connect(chatPanel, &ChatPanel::sig_sendMsg, this, &IM::slot_chatPanel_sendMsg);
    //QTcpServer�ź�
    connect(tcpClient, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpClient, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcpClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
        this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(tcpClient, SIGNAL(readyRead()),
        this, SLOT(onSocketReadyRead()));
}

QString IM::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();//����������
    QHostInfo   hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses();//

    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                localIP = aHost.toString();
                break;
            }
        }
    return localIP;
}

void IM::testServer()
{
    QString addr = "127.0.0.1";
    quint16 port = 1200;

    QString localIP = getLocalIP();
    tcpClient->connectToHost(addr, port);
}

void IM::onConnected()
{
    //���ӵ��������������ź�
    {
        chatPanel->getMsg("**�����ӵ�������");
        chatPanel->getMsg("**peer address:" +
            tcpClient->peerAddress().toString());
        chatPanel->getMsg("**peer port:" +
            QString::number(tcpClient->peerPort()));
        chatPanel->getMsg("**�����ӵ�������");
    }
    //���ݽṹЭ��
    QJsonObject json;
    json.insert("to", "server");
    QString id = IMSettings.getSetting("LogonSettings", "lastLogonId").toString();
    json.insert("from", id);
    json.insert("data", "client finshed connect");
    QJsonDocument document = QJsonDocument(json);

    tcpClient->write(document.toJson());
}

void IM::onDisconnected()
{
    int a = 0;
}

void IM::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
}

void IM::onSocketReadyRead()
{
    while (tcpClient->canReadLine())
        chatPanel->getMsg("server to client:\n" + tcpClient->readLine());
}

void IM::slot_chatPanel_sendMsg(QString &str)
{
    chatPanel->getMsg("client to server:\n" + str);//���͸�chat������չʾ

    //��δ���Ҫɾ��
    QString toWho = chatPanel->getTitle();
    QString fromWho = this->windowTitle();

    QJsonObject json;
    json.insert("to", toWho);
    json.insert("from", fromWho);
    json.insert("data", str);
    QJsonDocument document = QJsonDocument(json);

    tcpClient->write(document.toJson());
}