#include "IMQTcpServer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "Base/DeftData.h"
#include "Base/IMQJson.h"
#include <IMQtMySql/IMQtMySql.h>
#include <QJsonArray>
#include "Base/IMQTransport.h"

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
{//��Ҫ�����socket����
    QDataStream in(byteArray);
    MsgInfo info;
    in >> info;

    int type = info.msgType;
    QString to = info.to;
    QString from = info.from;

    IMQTcpSocket *fromSocket = m_hashSocket->find(handle).value();  //�ж���˭���͵�Socket
    IMQTcpSocket *toSocket = getSocketByUserID(to);                 //�õ��Ƿ���˭��Socket

    switch (type)
    {
    case MsgType::USERLOGIN:
    {//�������ݿ��ѯ
        QString userPaswd = info.msg;
        IMQtMySql db;
        db.connect();
        QString userRealPaswd = db.getUserPassword(from);
        if (userPaswd == userRealPaswd)
        {
            QStringList strList = db.getUserInfo(from);   //�õ����û�����Ϣ
            UserInfo userInfo;
            userInfo.id = strList[UserInfoType::USERID];
            userInfo.name = strList[UserInfoType::USERNAME];

            info.msgType = MsgType::USERLOGINSUCCEED;
            QByteArray &byte = IMQPROTOCOL::getUserInfoQByteArray(info, userInfo);
            m_hashClient->insert(from, handle); 
            fromSocket->write(byte);    //����ȥ
            fromSocket->flush();
        }
        else
        {
            info.msgType = MsgType::USERLOGINDEFEAT;
            QByteArray &byte = IMQPROTOCOL::getMsgQByteArray(info);

            m_hashClient->insert(from, handle);
            fromSocket->write(byte);    //����ȥ
            fromSocket->flush();
        }
        db.disconnect();
        break;
    }
    case MsgType::USERMSG:
    {
        if(toSocket!=nullptr)
        {
            toSocket->write(byteArray); //ת��
            toSocket->flush();
            emit signClientMessage(to, from, QString("������һ����Ϣ"));   //������uiչʾ��
        }
        else
        {
            emit signClientMessage(to, from, QString("�û�û����"));
        }
        break;
    }

    case MsgType::FILENAME:
    {
        if(toSocket!=nullptr)
        {
            toSocket->write(byteArray);
            toSocket->flush();

            emit signClientMessage(to, from, QString("������һ���ļ�"));
        }
        else
        {   //�û�������
            QByteArray byte = IMQJson::getQJsonByte(MsgType::REFUSEFILE, from, "server", "");
            toSocket->write(byteArray);
            toSocket->flush();
            emit signClientMessage(to, from, QString("�û�û����"));
        }
        break;
    }

    default:
        break;
    }
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{//������ִ��
    IMQTcpSocket *socket = new IMQTcpSocket(socketDescriptor);
    m_hashSocket->insert(socketDescriptor, socket);     //��������ӵľ��

    //��socket�ź�
    connect(socket, &IMQTcpSocket::signReadData, this, &IMQTcpServer::slotDealSocketData);
    connect(socket, &IMQTcpSocket::signSockDisConnect, this, &IMQTcpServer::slotSocketDisConnect);

    QThread *thread = new QThread(socket);
    socket->moveToThread(thread);
    thread->start();

    qDebug() << "incomingConnection THREAD IS��" << QThread::currentThreadId();

    //�������¿ͻ��˵������ź�
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