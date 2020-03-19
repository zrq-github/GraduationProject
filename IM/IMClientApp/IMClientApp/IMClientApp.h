#pragma once

#include <QtWidgets/QWidget>
#include "ui_IMClientApp.h"

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
    
protected slots:
    void slotCreateChatPanel(QString id, QString name);
    void slotDeletChatPanel(QString id);
    void slotSendMessage(QString &to, QString &msg);

    void slotSocketReadData();
private:
    Ui::IMClientAppClass ui;

    FriendPanel *m_friendPanel;
    QHash<QString, ChatPanel*> *m_hashFriendPanel;
};
