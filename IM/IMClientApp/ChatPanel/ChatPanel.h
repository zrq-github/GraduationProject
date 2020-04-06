#pragma once

#include <QWidget>
#include "chatpanel_global.h"
#include <QListWidgetItem>
#include "Base/DeftData.h"
namespace Ui { class ChatPanel; };
class FileCilentPanel;
class FileServerPanel;
class VideoChatPanel;

class CHATPANEL_EXPORT ChatPanel : public QWidget
{
    Q_OBJECT
public:
    ChatPanel(QString id = Q_NULLPTR, QString name = Q_NULLPTR, QWidget *parent = Q_NULLPTR);
    ~ChatPanel();

    QString getTitle();
public:
    void setFriendMsg(QString &chtId, QString &msg);
    void hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename);
    
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::ChatPanel *ui;
    QString m_chatID;
    QString m_chatName;

    QString m_fileName;
    FileServerPanel *fileSrv;
    //视频聊天参数
    VideoChatPanel *m_videoChat;
private:
    void createUi();
    void binSign();
    void dealMessage(QString &sendId,QString &time,QString &data);
Q_SIGNALS:
    void signClose(QString);
    void signSendMessage(QString &to,QString &msg);

    void signSendFile(QByteArray&);
private slots :
    void slot_btnSend_click();
    void on_btnSendFile_clicked();  //发送文件消息
    void on_btnVideoChat_clicked(); //打开视频聊天功能

    void slotSendFile(QString);     //发送文件名
    void slotSaveFile(QByteArray);
public slots:
    void slotVidelChat(MsgInfo);       //处理视频聊天功能
};
