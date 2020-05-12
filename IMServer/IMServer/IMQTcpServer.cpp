#include "IMQTcpServer.h"
#include <QDebug>
#include "DataCenter/BaseDataType.h"
#include "DataCenter/DataAnalysis.h"
#include "IMQtMySql/IMQtMySql.h"

IMQTcpServer::IMQTcpServer(QObject *parent/* = Q_NULLPTR*/, int numConnections/* = 10000*/)
    : QTcpServer(parent)
{
    m_hashSocket = new QHash<int, IMQTcpSocket *>;
    m_maxConnections = numConnections;
    m_threadPool = new QThreadPool;
    m_hashClient = new QHash<QString, int>;

    qDebug() << "server initialize succeed";
    db.connect();
}

IMQTcpServer::~IMQTcpServer()
{
    db.disconnect();
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{
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

void IMQTcpServer::slotDealSocketData(const int handle, const QString & address, const quint16 port, const QByteArray & byteArray)
{//需要处理的socket数据
    qDebug() << handle << "  deal Data start";
    MsgInfo info = DataAnalysis::msgFromJsonByte(byteArray);

    int type = info.msgType;
    QString to = info.to;       //发给谁
    QString from = info.from;   //来自谁

    IMQTcpSocket *fromSocket = m_hashSocket->find(handle).value();  //判断是谁发送的Socket
    IMQTcpSocket *toSocket = getSocketByUserID(to);                 //拿到是发给谁的Socket


    if (!db.connect())
    {
        qDebug() << "数据库连接失败！";
        return;
    }

    switch (type)
    {
    case MsgType::USERLOGIN:
    {//连接数据库查询
        qDebug() << from << " userlogin request ";
        QString userPaswd = info.msg;

        QString userRealPaswd = db.getUserPassword(from);

        if (userPaswd == userRealPaswd)
        {   //如果登录成功,返回用户用户数据
            QStringList strList = db.getUserInfo(from);   //拿到该用户的信息
            UserInfo userInfo;
            userInfo.id = strList[UserInfoType::USERID];
            userInfo.name = strList[UserInfoType::USERNAME];

            info.msgType = MsgType::USERLOGINSUCCEED;

            QByteArray byte = DataAnalysis::byteFromMsgInfoAdUserInfo(info, userInfo);
            m_hashClient->insert(from, handle); //存放该socket所对应的用户

            fromSocket->write(byte);    //发回去
            fromSocket->flush();
        }
        else
        {   //密码验证错误
            info.msgType = MsgType::USERLOGINDEFEAT;
            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);

            m_hashClient->insert(from, handle);
            fromSocket->write(byte);    //发回去
            fromSocket->flush();
        }
        break;
    }
    case MsgType::USERMSG:
    {
        if (toSocket != nullptr)
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
    case MsgType::USERCHANGEPASSWORD:
    {
        bool is= db.updateLogon(from, info.msg);
        if (is)
        {
            info.msgType = MsgType::USERCHANGEPASSWORD;
            info.to = info.from;
            info.from = "server";
            info.msg = "1";
            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);
            fromSocket->write(byte);
            fromSocket->flush();
        }
        
        
        break;
    }
    //case MsgType::FILENAME:
    //{
    //    if (toSocket != nullptr)
    //    {
    //        toSocket->write(byteArray);
    //        toSocket->flush();

    //        emit signClientMessage(to, from, QString("发送了一个文件"));
    //    }
    //    else
    //    {   //用户不在线
    //        MsgInfo infoFile;
    //        infoFile.msgType = MsgType::REFUSEFILE;
    //        infoFile.to = from;
    //        infoFile.from = "server";

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoFile);
    //        toSocket->write(byteArray);
    //        toSocket->flush();
    //        emit signClientMessage(to, from, QString("用户没上线"));
    //    }
    //    break;
    //}
    //case MsgType::VIDEOCHAT:
    //{
    //    if (toSocket != nullptr)
    //    {
    //        toSocket->write(byteArray);
    //        toSocket->flush();

    //        emit signClientMessage(to, from, QString("发送了一个视频请求"));
    //    }
    //    else
    //    {   //用户不在线
    //        MsgInfo infoVideoChat;
    //        infoVideoChat.msgType = MsgType::VIDEOCHATREFUSE;
    //        infoVideoChat.to = from;
    //        infoVideoChat.from = "server";

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoVideoChat);
    //        fromSocket->write(byteArray);
    //        fromSocket->flush();
    //        emit signClientMessage(to, from, QString("用户没上线"));
    //    }
    //    break;
    //}
    //case MsgType::VIDEOCHATACCEPT:
    //{
    //    if (toSocket != nullptr)
    //    {
    //        toSocket->write(byteArray);
    //        toSocket->flush();

    //        emit signClientMessage(to, from, QString("接受了一个视频请求"));
    //    }
    //    else
    //    {   //用户不在线
    //        MsgInfo infoVideoChat;
    //        infoVideoChat.msgType = MsgType::VIDEOCHATREFUSE;
    //        infoVideoChat.to = from;

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoVideoChat);
    //        fromSocket->write(byteArray);
    //        fromSocket->flush();
    //        emit signClientMessage(to, from, QString("用户没上线"));
    //    }
    //    break;
    //}
    default:
        break;
    }
}

void IMQTcpServer::slotSocketDisConnect(const int handle, const QString & address, const quint16 port)
{
    m_hashSocket->erase(m_hashSocket->find(handle));
    QString id = m_hashClient->key(handle);
    m_hashClient->erase(m_hashClient->find(id));

    emit signClientDisConnect(handle, address, port);
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