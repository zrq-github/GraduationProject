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

void IMQTcpServer::slotDealSocketData(const int handle, const QString & address, const quint16 port, const QByteArray & byteArray)
{//��Ҫ�����socket����
    qDebug() << handle << "  deal Data start";
    MsgInfo info = DataAnalysis::msgFromJsonByte(byteArray);

    int type = info.msgType;
    QString to = info.to;       //����˭
    QString from = info.from;   //����˭

    IMQTcpSocket *fromSocket = m_hashSocket->find(handle).value();  //�ж���˭���͵�Socket
    IMQTcpSocket *toSocket = getSocketByUserID(to);                 //�õ��Ƿ���˭��Socket


    if (!db.connect())
    {
        qDebug() << "���ݿ�����ʧ�ܣ�";
        return;
    }

    switch (type)
    {
    case MsgType::USERLOGIN:
    {//�������ݿ��ѯ
        qDebug() << from << " userlogin request ";
        QString userPaswd = info.msg;

        QString userRealPaswd = db.getUserPassword(from);

        if (userPaswd == userRealPaswd)
        {   //�����¼�ɹ�,�����û��û�����
            QStringList strList = db.getUserInfo(from);   //�õ����û�����Ϣ
            UserInfo userInfo;
            userInfo.id = strList[UserInfoType::USERID];
            userInfo.name = strList[UserInfoType::USERNAME];

            info.msgType = MsgType::USERLOGINSUCCEED;

            QByteArray byte = DataAnalysis::byteFromMsgInfoAdUserInfo(info, userInfo);
            m_hashClient->insert(from, handle); //��Ÿ�socket����Ӧ���û�

            fromSocket->write(byte);    //����ȥ
            fromSocket->flush();
        }
        else
        {   //������֤����
            info.msgType = MsgType::USERLOGINDEFEAT;
            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);

            m_hashClient->insert(from, handle);
            fromSocket->write(byte);    //����ȥ
            fromSocket->flush();
        }
        break;
    }
    case MsgType::USERMSG:
    {
        if (toSocket != nullptr)
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

    //        emit signClientMessage(to, from, QString("������һ���ļ�"));
    //    }
    //    else
    //    {   //�û�������
    //        MsgInfo infoFile;
    //        infoFile.msgType = MsgType::REFUSEFILE;
    //        infoFile.to = from;
    //        infoFile.from = "server";

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoFile);
    //        toSocket->write(byteArray);
    //        toSocket->flush();
    //        emit signClientMessage(to, from, QString("�û�û����"));
    //    }
    //    break;
    //}
    //case MsgType::VIDEOCHAT:
    //{
    //    if (toSocket != nullptr)
    //    {
    //        toSocket->write(byteArray);
    //        toSocket->flush();

    //        emit signClientMessage(to, from, QString("������һ����Ƶ����"));
    //    }
    //    else
    //    {   //�û�������
    //        MsgInfo infoVideoChat;
    //        infoVideoChat.msgType = MsgType::VIDEOCHATREFUSE;
    //        infoVideoChat.to = from;
    //        infoVideoChat.from = "server";

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoVideoChat);
    //        fromSocket->write(byteArray);
    //        fromSocket->flush();
    //        emit signClientMessage(to, from, QString("�û�û����"));
    //    }
    //    break;
    //}
    //case MsgType::VIDEOCHATACCEPT:
    //{
    //    if (toSocket != nullptr)
    //    {
    //        toSocket->write(byteArray);
    //        toSocket->flush();

    //        emit signClientMessage(to, from, QString("������һ����Ƶ����"));
    //    }
    //    else
    //    {   //�û�������
    //        MsgInfo infoVideoChat;
    //        infoVideoChat.msgType = MsgType::VIDEOCHATREFUSE;
    //        infoVideoChat.to = from;

    //        QByteArray byte = IMQPROTOCOL::getMsgQByteArray(infoVideoChat);
    //        fromSocket->write(byteArray);
    //        fromSocket->flush();
    //        emit signClientMessage(to, from, QString("�û�û����"));
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