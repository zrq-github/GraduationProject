#pragma once

#include <QWidget>
#include "chatpanel_global.h"
#include "QNChatMessage.h"
#include <QListWidgetItem>
namespace Ui { class ChatPanel; };
class FileCilentPanel;
class FileServerPanel;

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
private:
    void createUi();
    void binSign();
    void dealMessage(QString &sendId,QString &time,QString &data);
Q_SIGNALS:
    void signClose(QString);
    void signSendMessage(QString &to,QString &msg);

    void signSendFile(QByteArray&);
private slots:
    void slot_btnSend_click();
    void on_btnSendFile_clicked();  //发送文件消息

    void slotSendFile(QString);     //发送文件名
    void slotSaveFile(QByteArray);
};
