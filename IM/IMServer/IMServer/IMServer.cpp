#include "IMServer.h"
#include <QDebug>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

IMServer::IMServer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    m_tcpServer = new IMQTcpServer(this);
    createUi();
    bindSigns();
}

void IMServer::createUi()
{
}

void IMServer::bindSigns()
{
    //界面信号
    connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(m_tcpServer, &IMQTcpServer::signNewClientConnect, this, &IMServer::slotNewConnect);
    connect(m_tcpServer, &IMQTcpServer::signClientDisConnect, this, &IMServer::slotClientDisConnect);
    connect(m_tcpServer, &IMQTcpServer::signClientMessage, this, &IMServer::slotClientMessage);
}

void IMServer::slotNewConnect(const int handle, const QString& address, const quint16 port)
{
    ui.textEdit->append("*******New Connect*******");
    ui.textEdit->append("this client handle:"+QString::number(handle));
    ui.textEdit->append("this client address:" + address);
    ui.textEdit->append("this client port:" + QString::number(port));
}

void IMServer::slotStart()
{
    QString IP = ui.comboIP->currentText();//IP地址
    quint16 port = ui.spinPort->value();//端口
    QHostAddress addr(IP);
    m_tcpServer->listen(addr, port);
    if (m_tcpServer->isListening())
    {
        ui.textEdit->append("服务器监听成功:");
        ui.textEdit->append("IP:" + IP);
        ui.textEdit->append("Port:" + QString::number(port));
    }
    else
    {
        ui.textEdit->append("服务器监听失败");
        ui.textEdit->append(m_tcpServer->errorString());
    }
}

void IMServer::slotClientDisConnect(const int handle, const QString address, const quint16 port)
{
    ui.textEdit->append("*******One client DisConnect*******");
    ui.textEdit->append("this client handle:" + QString::number(handle));
    ui.textEdit->append("this client address:" + address);
    ui.textEdit->append("this client port:" + QString::number(port));
}

void IMServer::slotClientMessage(QString & to, QString from, QString & msg)
{
    ui.textEdit->append("*******Msg*******");
    ui.textEdit->append("this to client :" + to);
    ui.textEdit->append("this from client:" + from);
    ui.textEdit->append("this client msg:" + msg);
}

void IMServer::slotSelectFile()
{
}
