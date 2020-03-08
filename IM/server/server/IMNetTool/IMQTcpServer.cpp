#include "IMQTcpServer.h"
#include <QThread>
#include <QDebug>

IMQTcpServer::IMQTcpServer(QObject *parent /* = 0 */, int numConnections /* = 10000 */)
{
    hashTcpClients = new QHash<int, IMQTcpSocket *>;
    setMaxPendingConnections(numConnections);
}

IMQTcpServer::~IMQTcpServer()
{
    emit this->signDisConnect(-1);
    delete hashTcpClients;
}

void IMQTcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);
    this->m_maxConnections = numConnections;
}

void IMQTcpServer::slotSendDataToClient(const QByteArray & data, const int handle)
{
    IMQTcpSocket *sockt = hashTcpClients->find(handle).value();
    sockt->write(data);
}

void IMQTcpServer::slotReadData(const int handle, const QString &ip, const quint16 port, const QByteArray& data)
{
    qDebug() << "server accept client data" << endl;
    emit readData(handle, ip, port, data);
}

void IMQTcpServer::slotSockDisConnect(const int handle,const QString &ip,const quint16 prot)
{
    qDebug() << "MyTcpServer::sockDisConnectSlot thread is:" << QThread::currentThreadId();
    IMQTcpSocket * tcp = hashTcpClients->value(handle);

    hashTcpClients->remove(handle);//���ӹ��������Ƴ��Ͽ����ӵ�socket
    delete tcp;

    emit sockDisConnect(handle, ip, prot);
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{
    IMQTcpSocket *tcpTemp = new IMQTcpSocket(socketDescriptor);
    //�ж����������,��������ʧ��
    {
        
    }
    QThread *thread = new QThread(tcpTemp);
    //���ź�
    connect(tcpTemp, &IMQTcpSocket::readData, this, &IMQTcpServer::slotReadData);   //���������յ�����������
    connect(this, &IMQTcpServer::sentData, tcpTemp, &IMQTcpSocket::sentData);   //���ܷ���������������
    connect(tcpTemp, &IMQTcpSocket::sockDisConnect, this, &IMQTcpServer::slotSockDisConnect);   //�Ͽ����ӵĴ���
    connect(tcpTemp, &IMQTcpSocket::disconnected, thread, &QThread::quit);

    hashTcpClients->insert(socketDescriptor, tcpTemp);
    tcpTemp->moveToThread(thread);
    thread->start();

    qDebug() << "incomingConnection THREAD IS��" << QThread::currentThreadId();

    //���������ź�,
    emit connectClient(tcpTemp->socketDescriptor(), tcpTemp->peerAddress().toString(), tcpTemp->peerPort());
}
