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
    void readData(const int, const QString &, const quint16, const QByteArray &);//���ͻ���û�������������
    void sockDisConnect(const int, const QString &, const quint16);//�Ͽ����ӵ��û���Ϣ
public slots:
    void thisReadData();//������յ�������
    void sentData(const QByteArray &, const int);//�����źŵĲ�
private:
    qintptr socketID;
};
