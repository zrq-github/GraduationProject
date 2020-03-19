#pragma once
#include <QtNetwork/QTcpServer>
#include "imqtcpserver_global.h"
#include "IMQTcpSocket.h"
#include <QThreadPool>

class IMQTCPSERVER_EXPORT IMQTcpServer:
    public QTcpServer
{
    Q_OBJECT
public:
    explicit IMQTcpServer(QObject *parent = Q_NULLPTR, int numConnections = 10000);
    ~IMQTcpServer();


private slots:
    virtual void slotDealSocketData(const int handle, const QString &address, const quint16 port, const QByteArray &data);
    void slotSocketDisConnect(const int handle, const QString &address, const quint16 port);
signals:
    void signNewClientConnect(const int handle, const QString& address, const quint16 port);
    void signClientMessage(QString &to, QString from, QString &msg);    //给ui界面用
    void signClientDisConnect(const int handle, const QString address, const quint16 port);
protected:
    void incomingConnection(qintptr socketDescriptor);  //每当有新连接执行
private:
    QHash<int, IMQTcpSocket*> *m_hashSocket;  //存放socket句柄
    QHash<QString, int> *m_hashClient;
    int m_maxConnections; //最大连接数
    QThreadPool *m_threadPool;
};
