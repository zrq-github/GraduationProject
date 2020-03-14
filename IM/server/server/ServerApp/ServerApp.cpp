#include "ServerApp.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QHostInfo>
#include "ui_ServerApp.h"
#include <QJsonDocument>
#include <QJsonObject>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

ServerApp::ServerApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerAppClass)
    , hashClients(new QHash<QString, int>)
{
    tcpServer = new IMQTcpServer;
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

void ServerApp::slotStart()
{
    QString IP = ui->comboIP->currentText();//IP地址
    quint16 port = ui->spinPort->value();//端口
    QHostAddress addr(IP);
    tcpServer->listen(addr, port);//
    if (tcpServer->isListening())
    {
        ui->plainTextEdit->appendPlainText("**开始监听...");
        ui->plainTextEdit->appendPlainText("**服务器地址："
            + tcpServer->serverAddress().toString());
        ui->plainTextEdit->appendPlainText("**服务器端口："
            + QString::number(tcpServer->serverPort()));
    }

    ui->LabSocketState->setText("监听状态：正在监听");
}

void ServerApp::slotNewConnectFromClient(const int descriptor, const QString & address, const quint16 port)
{//每当服务器接收到来自新客户端的处理逻辑
    ui->plainTextEdit->appendPlainText("NewClient Connect:");
    ui->plainTextEdit->appendPlainText("descriptor:" + QString::number(descriptor));
    ui->plainTextEdit->appendPlainText("address:" + address);
    ui->plainTextEdit->appendPlainText("port:" + QString::number(port));
}

void ServerApp::slotClientDisConnect(const int descriptor, const QString & address, const quint16 port)
{//客户端断开连接
    ui->plainTextEdit->appendPlainText("Client Close Connect:");
    ui->plainTextEdit->appendPlainText("descriptor:" + QString::number(descriptor));
    ui->plainTextEdit->appendPlainText("address:" + address);
    ui->plainTextEdit->appendPlainText("port:" + QString::number(port));
}

void ServerApp::slotReadDataFromClient(const int handle, const QString & ip, const quint16 port, const QByteArray & data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject object = document.object();

    QString &toWho = object.value("to").toString();
    QString &fromWho = object.value("from").toString();
    QString &type = object.value("type").toString();
    QString &dataWho = object.value("data").toString();

    if (toWho == "server")
    {//发送给服务器处理的信息
        if (type == "logon")
        {   //登录验证
            //连接数据库，查表，判断是否成功
            if (true)
            {
                hashClients->insert(fromWho, handle); //绑定userID和socke对象
                QJsonObject json;
                json.insert("to", fromWho);
                json.insert("from", toWho);
                json.insert("type", "logon");
                json.insert("data", true);
                QJsonDocument document = QJsonDocument(json);
                emit sendDataToClient(document.toJson(), handle);
            }
        }
    }
    else
    {   //发给其他用户的消息
        auto i = hashClients->find(toWho);
        if (i != hashClients->end())
        {
            int clientHandle = i.value();
            ui->plainTextEdit->appendPlainText(fromWho+"给"+toWho+"发送了消息");
            emit sendDataToClient(data, clientHandle);
        }
        else
        {
            //用户不在线的处理事件
            qDebug() << "该用户:" + toWho + "不在线";
            ui->plainTextEdit->appendPlainText("该用户:" + toWho + "不在线");
        }
    }
}

void ServerApp::bindSlots()
{
    //界面信号
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slotBtnSendClick()));

    //来自IMQTcpServer类对象的信号
    connect(tcpServer, &IMQTcpServer::connectClient, this, &ServerApp::slotNewConnectFromClient);
    connect(tcpServer, &IMQTcpServer::sockDisConnect, this, &ServerApp::slotClientDisConnect);
    connect(tcpServer, &IMQTcpServer::readData, this, &ServerApp::slotReadDataFromClient);
    
    connect(this, &ServerApp::sendDataToClient, tcpServer, &IMQTcpServer::slotSendDataToClient);
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
