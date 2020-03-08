#pragma once

#include <QtWidgets/QWidget>
#include <IMNetTool/IMQTcpServer.h>
#include <IMNetTool/IMQTcpSocket.h>
#include <QHash>

namespace Ui {
    class ServerAppClass;
}

class ServerApp : public QWidget
{
    Q_OBJECT

public:
    ServerApp(QWidget *parent = Q_NULLPTR);
protected:
    void    closeEvent(QCloseEvent *event);
    
private:
    void bindSlots();
private:
    Ui::ServerAppClass *ui;
    IMQTcpServer *tcpServer;      //TCP服务器
    IMQTcpSocket *tcpSocket;      //TCP通讯的Socket
    QString getLocalIP();       //获取本机IP地址
    
    QHash<QString, int> *hashClients;   //int handle，Qstring id
signals:
    void sendDataToClient(const QByteArray,const int);
private slots:
    void slotBtnStartClick();
    void slotBtnSendClick();
    void slotStart();

    //绑定IMQTcpServer中的信号
    void slotNewConnectFromClient(const int descriptor, const QString &address, const quint16 port);
    void slotClientDisConnect(const int descriptor, const QString &address, const quint16 port);
    void slotReadDataFromClient(const int handle, const QString &ip, const quint16 port, const QByteArray& data);
};
