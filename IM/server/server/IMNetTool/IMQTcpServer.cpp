#include "IMQTcpServer.h"
#include <QThread>
#include <QDebug>

IMQTcpServer::IMQTcpServer(QObject *parent /* = 0 */, int numConnections /* = 10000 */)
{
    m_hashTcpClient = new QHash<int, IMQTcpSocket *>;
    setMaxPendingConnections(numConnections);
}

IMQTcpServer::~IMQTcpServer()
{
    emit this->signDisConnect(-1);
    delete m_hashTcpClient;
}

void IMQTcpServer::setMaxPendingConnections(int numConnections)
{
    this->QTcpServer::setMaxPendingConnections(numConnections);
    this->m_maxConnections = numConnections;
}

void IMQTcpServer::setData(const QByteArray & data, const int handle)
{
}

void IMQTcpServer::slotReadData(const int, const QString &, const quint16, const QByteArray &)
{
}

void IMQTcpServer::slotSockDisConnect(int handle, QString ip, quint16 prot)
{
    qDebug() << "MyTcpServer::sockDisConnectSlot thread is:" << QThread::currentThreadId();
    IMQTcpSocket * tcp = m_hashTcpClient->value(handle);

    m_hashTcpClient->remove(handle);//���ӹ��������Ƴ��Ͽ����ӵ�socket
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

    m_hashTcpClient->insert(socketDescriptor, tcpTemp);
    tcpTemp->moveToThread(thread);
    thread->start();

    qDebug() << "incomingConnection THREAD IS��" << QThread::currentThreadId();

    //���������ź�,
    emit connectClient(tcpTemp->socketDescriptor(), tcpTemp->peerAddress().toString(), tcpTemp->peerPort());
}
