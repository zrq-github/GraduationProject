#include "IMQTcpSocket.h"
#include "QHostAddress"
#include <QThread>
IMQTcpSocket::IMQTcpSocket(qintptr socketDescriptor,QObject *parent)
    : QTcpSocket(parent)
    , socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);

    connect(this, &IMQTcpSocket::readyRead, this, &IMQTcpSocket::slotDealReadData);

    //断开连接的信号转换
    connect(this, &IMQTcpSocket::disconnected, 
        [this]() {
            qDebug() << "myTcpSocket::myTcpSocket lambda sockDisConnect thread is:" << QThread::currentThreadId();
            emit sockDisConnect(socketID, this->peerAddress().toString(), this->peerPort());//发送断开连接的用户信息
    });

    qDebug() << this->socketDescriptor() << " " << this->peerAddress().toString()
        << " " << this->peerPort() << "myTcpSocket::myTcpSocket thread is " << QThread::currentThreadId();
}

IMQTcpSocket::~IMQTcpSocket()
{
}

void IMQTcpSocket::slotDealReadData()
{
    qDebug() << "myTcpSocket::myTcpSocket lambda readData thread is:" << QThread::currentThreadId();
    emit readData(socketID, this->peerAddress().toString(), this->peerPort(), this->readAll());  //转发信号
}

void IMQTcpSocket::sentData(const QByteArray &data, const int id)
{
    if (id == socketID)//判断是否是此socket的信息
    {
            qDebug() << "myTcpSocket::sentData" << QThread::currentThreadId();
            write(data);
    }

}
