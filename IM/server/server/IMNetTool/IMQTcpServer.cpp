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

    m_hashTcpClient->remove(handle);//连接管理中心移除断开连接的socket
    delete tcp;

    emit sockDisConnect(handle, ip, prot);
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{
    IMQTcpSocket *tcpTemp = new IMQTcpSocket(socketDescriptor);
    //判断最大连接数,超过连接失败
    {
        
    }
    QThread *thread = new QThread(tcpTemp);
    //绑定信号
    connect(tcpTemp, &IMQTcpSocket::readData, this, &IMQTcpServer::slotReadData);   //服务器接收到发来的数据
    connect(this, &IMQTcpServer::sentData, tcpTemp, &IMQTcpSocket::sentData);   //接受服务器发来的数据
    connect(tcpTemp, &IMQTcpSocket::sockDisConnect, this, &IMQTcpServer::slotSockDisConnect);   //断开连接的处理
    connect(tcpTemp, &IMQTcpSocket::disconnected, thread, &QThread::quit);

    m_hashTcpClient->insert(socketDescriptor, tcpTemp);
    tcpTemp->moveToThread(thread);
    thread->start();

    qDebug() << "incomingConnection THREAD IS：" << QThread::currentThreadId();

    //发送连接信号,
    emit connectClient(tcpTemp->socketDescriptor(), tcpTemp->peerAddress().toString(), tcpTemp->peerPort());
}
