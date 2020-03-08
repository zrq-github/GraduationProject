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
    void connectClient(const int, const QString&, const quint16);   //�������û�������Ϣ,Descriptor,address,port
    void readData(const int, const QString&, const quint16, const QByteArray&);//���ͻ���û�������������
    void sockDisConnect(const int, const QString&, const quint16);  //�Ͽ����ӵ��û���Ϣ
    void sentData(const QByteArray&, const int);//��socoket������Ϣ
    
    void signDisConnect(int);   //�Ͽ�����
public slots:
    void slotSendDataToClient(const QByteArray &data, const int handle); //�û�������Ϣ

    void slotReadData(const int handle, const QString &ip, const quint16 port, const QByteArray& data);//���ͻ���û�������������
    void slotSockDisConnect(const int handle,const QString &ip,const quint16 prot);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QHash<int, IMQTcpSocket*> *hashTcpClients;
    int m_maxConnections; //���������
};

