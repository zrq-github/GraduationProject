#include "ServerApp.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QHostInfo>
#include "ui_ServerApp.h"

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

ServerApp::ServerApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerAppClass)
{
    tcpServer = new QTcpServer;
    ui->setupUi(this);
    bindSlots();
}

void ServerApp::closeEvent(QCloseEvent * event)
{
}

void ServerApp::slotBtnSendClick()
{
    //发送一行字符串，以换行符结束
    QString  msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[server to client] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray  str = msg.toUtf8();
    str.append('\n');//添加一个换行符
    tcpSocket->write(str);
}

void ServerApp::start()
{
    QString IP = ui->comboIP->currentText();//IP地址
    quint16 port = ui->spinPort->value();//端口
    QHostAddress addr(IP);
    tcpServer->listen(addr, port);//
//    tcpServer->listen(QHostAddress::LocalHost,port);// Equivalent to QHostAddress("127.0.0.1").
    ui->plainTextEdit->appendPlainText("**开始监听...");
    ui->plainTextEdit->appendPlainText("**服务器地址："
        + tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**服务器端口："
        + QString::number(tcpServer->serverPort()));


    ui->LabSocketState->setText("监听状态：正在监听");
}

void ServerApp::bindSlots()
{
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slotBtnSendClick()));

    //QTcpServer信号绑定
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

QString ServerApp::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();//本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
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

void ServerApp::slotBtnStartClick()
{

}

void ServerApp::onNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection(); //创建socket

    connect(tcpSocket, SIGNAL(connected()),
        this, SLOT(onClientConnected()));
    onClientConnected();//

    connect(tcpSocket, SIGNAL(disconnected()),
        this, SLOT(onClientDisconnected()));

    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
        this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    onSocketStateChange(tcpSocket->state());

    connect(tcpSocket, SIGNAL(readyRead()),
        this, SLOT(onSocketReadyRead()));
}

void ServerApp::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    //socket状态变化时
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->LabSocketState->setText("scoket状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        ui->LabSocketState->setText("scoket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        ui->LabSocketState->setText("scoket状态：ConnectingState");
        break;

    case QAbstractSocket::ConnectedState:
        ui->LabSocketState->setText("scoket状态：ConnectedState");
        break;

    case QAbstractSocket::BoundState:
        ui->LabSocketState->setText("scoket状态：BoundState");
        break;

    case QAbstractSocket::ClosingState:
        ui->LabSocketState->setText("scoket状态：ClosingState");
        break;

    case QAbstractSocket::ListeningState:
        ui->LabSocketState->setText("scoket状态：ListeningState");
    }
}

void ServerApp::onClientConnected()
{
    //当客户端接入时
    ui->plainTextEdit->appendPlainText("**client socket connected");
    ui->plainTextEdit->appendPlainText("**peer address:" +
        tcpSocket->peerAddress().toString());
    ui->plainTextEdit->appendPlainText("**peer port:" +
        QString::number(tcpSocket->peerPort()));

}

void ServerApp::onClientDisconnected()
{
    ui->plainTextEdit->appendPlainText("**client socket disconnected");
    tcpSocket->deleteLater();
}

void ServerApp::onSocketReadyRead()
{
    while (tcpSocket->canReadLine())
        ui->plainTextEdit->appendPlainText("client to server:" + tcpSocket->readLine());
}
