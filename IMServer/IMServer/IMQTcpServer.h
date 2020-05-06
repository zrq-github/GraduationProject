#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include "IMQTcpSocket.h"

class IMQTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    IMQTcpServer(QObject *parent = Q_NULLPTR, int numConnections = 10000);
    ~IMQTcpServer();

    virtual void incomingConnection(qintptr socketDescriptor);

private slots:
    virtual void slotDealSocketData(const int handle, const QString &address, const quint16 port, const QByteArray &data);
    void slotSocketDisConnect(const int handle, const QString &address, const quint16 port);
signals:
    void signNewClientConnect(const int handle, const QString& address, const quint16 port);
    void signClientMessage(QString &to, QString from, QString &msg);    //��ui������
    void signClientDisConnect(const int handle, const QString address, const quint16 port);
private:
    QHash<int, IMQTcpSocket*> *m_hashSocket;    //���socket���
    QHash<QString, int> *m_hashClient;          //����û�ID����Ӧ�ľ��

    int m_maxConnections; //���������
    QThreadPool *m_threadPool;

    IMQTcpSocket *getSocketByUserID(QString userID);
};
