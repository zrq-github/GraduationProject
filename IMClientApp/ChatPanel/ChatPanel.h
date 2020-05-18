#pragma once

#include <QWidget>
#include "chatpanel_global.h"
#include <QListWidgetItem>
#include "DataCenter/BaseDataType.h"
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
    //��Ƶ�������
    VideoChatPanel *m_videoChat;
private:
    void createUi();
    void binSign();
    void dealMessage(QString &sendId,QString &time,QString &data);
Q_SIGNALS:
    void signClose(QString);

    void signSendFile(QByteArray&);
private slots :
    void slot_btnSend_click();          //������Ϣ�Ĺ���
    void on_btnSendFile_clicked();      //�����ļ���Ϣ
    void on_btnVideoChat_clicked();     //����Ƶ���칦��

    void slotSendFile(QString);         //�����ļ���

    void slotSaveFile(MsgInfo);           //������������ļ�

public slots:
    void slotVidelChat(MsgInfo);       //������Ƶ���칦��
};