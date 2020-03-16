#pragma once
/*
** 
*/

#include <QWidget>
#include <QHash>
#include <QtNetwork/QTcpSocket>
#include "im_global.h"
namespace Ui { class IM; };

class ChatPanel;
class FriendPanel;

class IM_EXPORT IM : public QWidget
{
    Q_OBJECT

public:
    IM(QWidget *parent = Q_NULLPTR);
    ~IM();

protected:
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;           //表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;                  //上一次的鼠标位置
private:
    Ui::IM *ui;
    ChatPanel *chatPanel;       //聊天面板
    FriendPanel *friendPanel;   //好友面板

    QHash<QString, ChatPanel*> *chatList;

private:
    void createUi();
    void binSlots();
    QString getLocalIP();

    QTcpSocket *tcpClient;
    void testServer();          //测试函数,连接服务器的初始配置
private slots:
    void slot_chatPanel_sendMsg(QString &str);          

    //bool eventFilter(QObject *, QEvent *);            //捕获子控件事件
    void onConnected();             
    void onDisconnected();          
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();       //读取socket传入的数据
Q_SIGNALS:
    void sig_getMsg(QString&);      //先放着，不知道干嘛用
};
