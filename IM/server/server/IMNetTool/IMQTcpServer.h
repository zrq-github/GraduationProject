#pragma once
#include <QtNetwork/QTcpServer>
#include "imnettool_global.h"
#include "IMQTcpSocket.h"


class IMNETTOOL_EXPORT IMQTcpServer :
    public QTcpServer
{
    Q_OBJECT
public:
    explicit IMQTcpServer(QObject *parent = 0, int numConnections = 10000);
    ~IMQTcpServer();

    void setMaxPendingConnections(int numConnections);

signals:
    void connectClient(const int, const QString&, const quint16);   //发送新用户连接信息,Descriptor,address,port
    void readData(const int, const QString&, const quint16, const QByteArray&);//发送获得用户发过来的数据
    void sockDisConnect(const int, const QString&, const quint16);  //断开连接的用户信息
    void sentData(const QByteArray&, const int);//向socoket发送消息
    
    void signDisConnect(int);   //断开服务
public slots:
    void slotSendDataToClient(const QByteArray &data, const int handle); //用户发送消息

    void slotReadData(const int handle, const QString &ip, const quint16 port, const QByteArray& data);//发送获得用户发过来的数据
    void slotSockDisConnect(const int handle,const QString &ip,const quint16 prot);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QHash<int, IMQTcpSocket*> *hashTcpClients;
    int m_maxConnections; //最大连接数
};

