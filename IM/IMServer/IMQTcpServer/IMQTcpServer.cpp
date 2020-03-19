#include "IMQTcpServer.h"
#include <QJsonDocument>
#include <QJsonObject>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

enum sendObject
{
    IMSERVER,
    OTHERUSER,
    YOUSELF,
};

enum operationType
{
    LOGONG,//登录
    RETRANSMIT,//转发
    GETFRIENDDATA,//请求好友数据
};

enum dataType 
{
    TXT
};

IMQTcpServer::IMQTcpServer(QObject * parent, int numConnections)
    :QTcpServer(parent)
{
    m_hashSocket = new QHash<int, IMQTcpSocket *>;
    m_maxConnections = numConnections;
    m_threadPool = new QThreadPool;
    m_hashClient = new QHash<QString, int>;
}

IMQTcpServer::~IMQTcpServer()
{
    delete m_hashSocket;
}

void IMQTcpServer::slotDealSocketData(const int handle, const QString & address, const quint16 port, const QByteArray & byteArray)
{//需要处理的socket数据
    QJsonDocument document = QJsonDocument::fromJson(byteArray);
    QJsonObject object = document.object();

    int sendObject = object.value("sendObject").toInt();
    int operationType = object.value("operationType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();

    if (sendObject == sendObject::IMSERVER)
    {//发送给服务器的信息
        if (operationType == operationType::LOGONG)
        {//登录验证
            QString data = object.value("data").toString();//返回的data应该是密码
            //查询数据库
            if (true)
            {
                m_hashClient->insert(from, handle);

                object.insert("sendObject", sendObject::YOUSELF);
                object.insert("data", 1);
                object.insert("to", from);
                object.insert("from", "");
                QJsonDocument newDocument = QJsonDocument(object);
                IMQTcpSocket *sockt = m_hashSocket->find(handle).value();
                sockt->write(newDocument.toJson());
                sockt->flush();
            }
        }
    }

    if (sendObject == sendObject::OTHERUSER)
    {//给其他用户处理的信息
        if (operationType == operationType::RETRANSMIT)
        {//让服务器转发
            auto i = m_hashClient->find(to);
            if (i != m_hashClient->end())
            {
                emit signClientMessage(to, from, QString("发送了一条信息"));
                int sockeHanlde = i.value();
                IMQTcpSocket *socket = m_hashSocket->constFind(sockeHanlde).value();
                socket->write(byteArray);
                socket->flush();
            }
            else
            {
                emit signClientMessage(to, from, QString("用户没上线"));
            }
        }
    }
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{//新连接执行
    IMQTcpSocket *socket = new IMQTcpSocket(socketDescriptor);
    m_hashSocket->insert(socketDescriptor, socket);
    //绑定socket信号
    connect(socket, &IMQTcpSocket::signReadData, this, &IMQTcpServer::slotDealSocketData);
    connect(socket, &IMQTcpSocket::signSockDisConnect, this, &IMQTcpServer::slotSocketDisConnect);

    QThread *thread = new QThread(socket);
    socket->moveToThread(thread);
    thread->start();

    qDebug() << "incomingConnection THREAD IS：" << QThread::currentThreadId();

    //发送有新客户端的连接信号
    emit signNewClientConnect(socketDescriptor, socket->peerAddress().toString(), socket->peerPort());
}

void IMQTcpServer::slotSocketDisConnect(const int handle, const QString &address, const quint16 port)
{
    m_hashSocket->erase(m_hashSocket->find(handle));
    QString id = m_hashClient->key(handle);
    m_hashClient->erase(m_hashClient->find(id));

    emit signClientDisConnect(handle, address, port);
}