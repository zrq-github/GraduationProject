#pragma once

#include <QWidget>
#include "chatpanel_global.h"
namespace Ui { class ChatPanel; };

class CHATPANEL_EXPORT ChatPanel : public QWidget
{
    Q_OBJECT
public:
    ChatPanel(QWidget *parent = Q_NULLPTR);
    ~ChatPanel();

    void getMsg(QString &str);
    void getMsg(QString str);

private:
    Ui::ChatPanel *ui;
    QString chatterId;
    QString chatterName;
private:
    void createUi();
    void binSlots();

Q_SIGNALS:
    void sig_sendMsg(QString&);
private slots:
    void slot_btnSend_click();
    void slot_labName_Change();

    void slotChatterChange(QString &id,QString &name);
};
