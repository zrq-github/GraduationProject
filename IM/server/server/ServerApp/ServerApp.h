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

    QTcpServer *tcpServer;      //TCP������
    QTcpSocket *tcpSocket;      //TCPͨѶ��Socket
    QString getLocalIP();       //��ȡ����IP��ַ
private slots:
    void slotBtnStartClick();
    void slotBtnSendClick();
    void start();
    //�Զ���ۺ���
    void    onNewConnection();  //QTcpServer��newConnection()�ź�
    void    onSocketStateChange(QAbstractSocket::SocketState socketState);
    void    onClientConnected(); //Client Socket connected
    void    onClientDisconnected();//Client Socket disconnected
    void    onSocketReadyRead();//��ȡsocket���������
};
