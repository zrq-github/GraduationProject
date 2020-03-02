#pragma once

#include <QtWidgets/QWidget>
#include <QTcpServer>

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

    QTcpServer *tcpServer;      //TCP服务器
    QTcpSocket *tcpSocket;      //TCP通讯的Socket
    QString getLocalIP();       //获取本机IP地址
private slots:
    void slotBtnStartClick();
    void slotBtnSendClick();
    void start();
    //自定义槽函数
    void    onNewConnection();  //QTcpServer的newConnection()信号
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onClientConnected(); //Client Socket connected
    void    onClientDisconnected();//Client Socket disconnected
    void    onSocketReadyRead();//读取socket传入的数据
};
