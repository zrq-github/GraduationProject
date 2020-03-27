#pragma once

#include <QtWidgets/QWidget>

namespace Ui {
    class IMClientAppClass;
}

class FriendPanel;
class ChatPanel;
class QTcpSocket;

class IMClientApp : public QWidget
{
    Q_OBJECT

public:
    IMClientApp(QWidget *parent = Q_NULLPTR);
private:
    void bindSigns();
    void createUi();
   
private:
    Ui::IMClientAppClass *ui;

    FriendPanel *m_friendPanel;
    QHash<QString, ChatPanel*> *m_hashFriendPanel;
protected slots:
    void slotCreateChatPanel(QString id, QString name);     //创建聊天窗口
    void slotDeletChatPanel(QString id);                    //删除聊天窗口
    void slotSendMessage(QString &to, QString &msg);        //发送聊天消息
    void slotSendFile(QByteArray&);                     //发送文件

    void slotSocketReadData();                      //处理服务器返回的信息
};
