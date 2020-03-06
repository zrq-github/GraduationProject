#pragma once

#include <QTcpSocket>
#include "imnettool_global.h"

class IMNETTOOL_EXPORT IMQTcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    IMQTcpSocket(qintptr socketDescriptor, QObject *parent = Q_NULLPTR);
    ~IMQTcpSocket();

signals:
    void readData(const int, const QString &, const quint16, const QByteArray &);//发送获得用户发过来的数据
    void sockDisConnect(const int, const QString &, const quint16);//断开连接的用户信息
public slots:
    void thisReadData();//处理接收到的数据
    void sentData(const QByteArray &, const int);//发送信号的槽
private:
    qintptr socketID;
};
