#pragma once

#include <QWidget>
#include "chatpanel_global.h"
#include "QNChatMessage.h"
#include <QListWidgetItem>
namespace Ui { class ChatPanel; };

class CHATPANEL_EXPORT ChatPanel : public QWidget
{
    Q_OBJECT
public:
    ChatPanel(QString meID= Q_NULLPTR, QString id = Q_NULLPTR, QString name = Q_NULLPTR, QWidget *parent = Q_NULLPTR);
    ~ChatPanel();

    QString getTitle();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::ChatPanel *ui;

    QString m_chatID;
    QString m_chatName;
    QString m_meID;
private:
    void createUi();
    void binSlots();

    void dealMessage(QString &sendId,QString &time,QString &data);
   

    //void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    //void dealMessageTime(QString curMsgTime);
Q_SIGNALS:
    void signClose(QString);
private slots:
    void slot_btnSend_click();
};
