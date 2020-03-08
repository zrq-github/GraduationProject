#include "IMQTcpSocket.h"
#include "QHostAddress"
#include <QThread>
IMQTcpSocket::IMQTcpSocket(qintptr socketDescriptor,QObject *parent)
    : QTcpSocket(parent)
    , socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);

    connect(this, &IMQTcpSocket::readyRead, this, &IMQTcpSocket::slotDealReadData);

    //�Ͽ����ӵ��ź�ת��
    connect(this, &IMQTcpSocket::disconnected, 
        [this]() {
            qDebug() << "myTcpSocket::myTcpSocket lambda sockDisConnect thread is:" << QThread::currentThreadId();
            emit sockDisConnect(socketID, this->peerAddress().toString(), this->peerPort());//���ͶϿ����ӵ��û���Ϣ
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
    emit readData(socketID, this->peerAddress().toString(), this->peerPort(), this->readAll());  //ת���ź�
}

void IMQTcpSocket::sentData(const QByteArray &data, const int id)
{
    if (id == socketID)//�ж��Ƿ��Ǵ�socket����Ϣ
    {
            qDebug() << "myTcpSocket::sentData" << QThread::currentThreadId();
            write(data);
    }

}
