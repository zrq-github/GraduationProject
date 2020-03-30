#include "IMQTcpServer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Base/DeftData.h"
#include "Base/IMQJson.h"
#include <IMQtMySql/IMQtMySql.h>
#include <QJsonArray>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

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

    int type = object.value("msgType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();

    IMQTcpSocket *fromSocket = m_hashSocket->find(handle).value();  //判断是谁发送的Socket
    IMQTcpSocket *toSocket = getSocketByUserID(to);                 //拿到是发给谁的Socket

    switch (type)
    {
    case MsgType::USERLOGIN:
    {//连接数据库查询
        QString userPaswd = object.value("data").toString();

        IMQtMySql db;
        db.connect();
        QString userRealPaswd = db.getUserPassword(from);
        if (userPaswd == userRealPaswd)
        {
            QStringList strlist = db.getUserInfo(from);
            QJsonArray jsonArray;
            for (int i = 0; i < strlist.size(); ++i)
            {
                jsonArray.append(strlist[i]);
            }
            QByteArray &byte = IMQJson::getQJsonUserInfo(MsgType::USERLOGINSUCCEED, from, "", jsonArray);
            m_hashClient->insert(from, handle); 
            fromSocket->write(byte);    //发回去
            fromSocket->flush();
        }
        else
        {
            QByteArray &byte = IMQJson::getQJsonByte(MsgType::USERLOGINDEFEAT, from, "", "");
            m_hashClient->insert(from, handle);
            fromSocket->write(byte);    //发回去
            fromSocket->flush();
        }
        db.disconnect();
        break;
    }
    case MsgType::USERMSG:
    {
        if(toSocket!=nullptr)
        {
            toSocket->write(byteArray); //转发
            toSocket->flush();
            emit signClientMessage(to, from, QString("发送了一条信息"));   //给界面ui展示用
        }
        else
        {
            emit signClientMessage(to, from, QString("用户没上线"));
        }
        break;
    }

    case MsgType::FILENAME:
    {
        if(toSocket!=nullptr)
        {
            //QString file = object.value("data").toString();
            //QString address = fromSocket->localAddress().toString();
            //QByteArray byte = IMQJson::getQJsonFile(MsgType::FILENAME, to, from, address, file);
            toSocket->write(byteArray);
            toSocket->flush();

            emit signClientMessage(to, from, QString("发送了一个文件"));
        }
        else
        {   //用户不在线
            QByteArray byte = IMQJson::getQJsonByte(MsgType::REFUSEFILE, from, "server", "");
            toSocket->write(byteArray);
            toSocket->flush();
            emit signClientMessage(to, from, QString("用户没上线"));
        }
        break;
    }

    default:
        break;
    }
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{//新连接执行
    IMQTcpSocket *socket = new IMQTcpSocket(socketDescriptor);
    m_hashSocket->insert(socketDescriptor, socket);     //存放新连接的句柄

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

IMQTcpSocket * IMQTcpServer::getSocketByUserID(QString userID)
{
    QHash<QString, int>::iterator clientIter = m_hashClient->find(userID);
    if (clientIter != m_hashClient->end())
    {
        int hdl = clientIter.value();
        return m_hashSocket->find(hdl).value();
    }
    return nullptr;
}

void IMQTcpServer::slotSocketDisConnect(const int handle, const QString &address, const quint16 port)
{
    m_hashSocket->erase(m_hashSocket->find(handle));
    QString id = m_hashClient->key(handle);
    m_hashClient->erase(m_hashClient->find(id));

    emit signClientDisConnect(handle, address, port);
}