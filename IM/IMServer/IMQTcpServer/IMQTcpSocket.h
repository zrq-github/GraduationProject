#pragma once

#include <QTcpSocket>
#include <QObject>
#include "imqtcpserver_global.h"

class IMQTCPSERVER_EXPORT IMQTcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    IMQTcpSocket(qintptr socketDescriptor, QObject *parent = Q_NULLPTR);
    ~IMQTcpSocket();


private:
    void bindSigns();
signals:
    void signReadData(const int, const QString &, const quint16, const QByteArray &);   //发送获得用户发过来的数据
    void signSockDisConnect(const int, const QString &, const quint16);                 //断开连接的用户信息

public slots:
    void slotDealReadData();    //当收到数据的时候应该怎么做
    void slotDisConnect();
private:
    qintptr socketID;
};
