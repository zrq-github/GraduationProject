#pragma once

#include <QtWidgets/QWidget>
#include "ui_IMClientApp.h"

class FriendPanel;
class ChatPanel;

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
private:
    Ui::IMClientAppClass ui;
    FriendPanel *m_friendPanel;
    QHash<QString, ChatPanel*> *m_hashFriendPanel;
};
