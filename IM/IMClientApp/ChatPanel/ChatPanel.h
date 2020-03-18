#pragma once

#include <QWidget>
#include "chatpanel_global.h"
namespace Ui { class ChatPanel; };

class CHATPANEL_EXPORT ChatPanel : public QWidget
{
    Q_OBJECT
public:
    ChatPanel(QString id = Q_NULLPTR, QString name = Q_NULLPTR, QWidget *parent = Q_NULLPTR);
    ~ChatPanel();

    void getMsg(QString &str);
    void getMsg(QString str);

    QString getTitle();

protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::ChatPanel *ui;

    QString m_chatID;
    QString m_chatName;
private:
    void createUi();
    void binSlots();

Q_SIGNALS:
    void sig_sendMsg(QString&);
    void signClose(QString);
private slots:
    void slot_btnSend_click();
    void slot_labName_Change();

    void slotChatterChange(QString &id,QString &name);
};
