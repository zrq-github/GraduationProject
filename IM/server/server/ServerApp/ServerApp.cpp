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
    //����һ���ַ������Ի��з�����
    QString  msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[server to client] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray  str = msg.toUtf8();
    str.append('\n');//���һ�����з�
    tcpSocket->write(str);
}

void ServerApp::start()
{
    QString IP = ui->comboIP->currentText();//IP��ַ
    quint16 port = ui->spinPort->value();//�˿�
    QHostAddress addr(IP);
    tcpServer->listen(addr, port);//
//    tcpServer->listen(QHostAddress::LocalHost,port);// Equivalent to QHostAddress("127.0.0.1").
    ui->plainTextEdit->appendPlainText("**��ʼ����...");
    ui->plainTextEdit->appendPlainText("**��������ַ��"
        + tcpServer->serverAddress().toString());
    ui->plainTextEdit->appendPlainText("**�������˿ڣ�"
        + QString::number(tcpServer->serverPort()));


    ui->LabSocketState->setText("����״̬�����ڼ���");
}

void ServerApp::bindSlots()
{
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slotBtnSendClick()));

    //QTcpServer�źŰ�
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

QString ServerApp::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();//����������
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
    tcpSocket = tcpServer->nextPendingConnection(); //����socket

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
    //socket״̬�仯ʱ
    switch (socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->LabSocketState->setText("scoket״̬��UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        ui->LabSocketState->setText("scoket״̬��HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        ui->LabSocketState->setText("scoket״̬��ConnectingState");
        break;

    case QAbstractSocket::ConnectedState:
        ui->LabSocketState->setText("scoket״̬��ConnectedState");
        break;

    case QAbstractSocket::BoundState:
        ui->LabSocketState->setText("scoket״̬��BoundState");
        break;

    case QAbstractSocket::ClosingState:
        ui->LabSocketState->setText("scoket״̬��ClosingState");
        break;

    case QAbstractSocket::ListeningState:
        ui->LabSocketState->setText("scoket״̬��ListeningState");
    }
}

void ServerApp::onClientConnected()
{
    //���ͻ��˽���ʱ
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
