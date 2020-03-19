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
    LOGONG,//��¼
    RETRANSMIT,//ת��
    GETFRIENDDATA,//�����������
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
{//��Ҫ�����socket����
    QJsonDocument document = QJsonDocument::fromJson(byteArray);
    QJsonObject object = document.object();

    int sendObject = object.value("sendObject").toInt();
    int operationType = object.value("operationType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();

    if (sendObject == sendObject::IMSERVER)
    {//���͸�����������Ϣ
        if (operationType == operationType::LOGONG)
        {//��¼��֤
            QString data = object.value("data").toString();//���ص�dataӦ��������
            //��ѯ���ݿ�
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
    {//�������û��������Ϣ
        if (operationType == operationType::RETRANSMIT)
        {//�÷�����ת��
            auto i = m_hashClient->find(to);
            if (i != m_hashClient->end())
            {
                emit signClientMessage(to, from, QString("������һ����Ϣ"));
                int sockeHanlde = i.value();
                IMQTcpSocket *socket = m_hashSocket->constFind(sockeHanlde).value();
                socket->write(byteArray);
                socket->flush();
            }
            else
            {
                emit signClientMessage(to, from, QString("�û�û����"));
            }
        }
    }
}

void IMQTcpServer::incomingConnection(qintptr socketDescriptor)
{//������ִ��
    IMQTcpSocket *socket = new IMQTcpSocket(socketDescriptor);
    m_hashSocket->insert(socketDescriptor, socket);
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

void IMQTcpServer::slotSocketDisConnect(const int handle, const QString &address, const quint16 port)
{
    m_hashSocket->erase(m_hashSocket->find(handle));
    QString id = m_hashClient->key(handle);
    m_hashClient->erase(m_hashClient->find(id));

    emit signClientDisConnect(handle, address, port);
}