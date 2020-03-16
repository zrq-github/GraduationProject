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
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;           //��ʾ�����Ƿ������������ƶ�
    QPoint  m_lastPos;                  //��һ�ε����λ��
private:
    Ui::IM *ui;
    ChatPanel *chatPanel;       //�������
    FriendPanel *friendPanel;   //�������

    QHash<QString, ChatPanel*> *chatList;

private:
    void createUi();
    void binSlots();
    QString getLocalIP();

    QTcpSocket *tcpClient;
    void testServer();          //���Ժ���,���ӷ������ĳ�ʼ����
private slots:
    void slot_chatPanel_sendMsg(QString &str);          

    //bool eventFilter(QObject *, QEvent *);            //�����ӿؼ��¼�
    void onConnected();             
    void onDisconnected();          
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    void onSocketReadyRead();       //��ȡsocket���������
Q_SIGNALS:
    void sig_getMsg(QString&);      //�ȷ��ţ���֪��������
};
