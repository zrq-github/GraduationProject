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
    void signReadData(const int, const QString &, const quint16, const QByteArray &);   //���ͻ���û�������������
    void signSockDisConnect(const int, const QString &, const quint16);                 //�Ͽ����ӵ��û���Ϣ

public slots:
    void slotDealReadData();    //���յ����ݵ�ʱ��Ӧ����ô��
    void slotDisConnect();
private:
    qintptr socketID;
};
