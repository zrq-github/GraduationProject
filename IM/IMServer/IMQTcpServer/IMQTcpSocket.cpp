#include "IMQTcpSocket.h"
#include "QHostAddress"
#include <QThread>

IMQTcpSocket::IMQTcpSocket(qintptr socketDescriptor,QObject *parent)
    : QTcpSocket(parent)
    , socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);
    this->bindSigns();
    

    qDebug() << this->socketDescriptor() << " " << this->peerAddress().toString()
        << " " << this->peerPort() << "myTcpSocket::myTcpSocket thread is " << QThread::currentThreadId();
}

IMQTcpSocket::~IMQTcpSocket()
{
}

void IMQTcpSocket::bindSigns()
{
    connect(this, &IMQTcpSocket::readyRead, this, &IMQTcpSocket::slotDealReadData);
    connect(this, &IMQTcpSocket::disconnected, this, &IMQTcpSocket::slotDisConnect);
}

void IMQTcpSocket::slotDealReadData()
{
    qDebug() << "myTcpSocket::myTcpSocket lambda readData thread is:" << QThread::currentThreadId();
    emit signReadData(socketID, this->peerAddress().toString(), this->peerPort(), this->readAll());  //×ª·¢ÐÅºÅ
}

void IMQTcpSocket::slotDisConnect()
{
    qDebug() << "myTcpSocket::myTcpSocket lambda disConnect thread is:" << QThread::currentThreadId();
    emit signSockDisConnect(socketID, this->peerAddress().toString(), this->peerPort());
}
