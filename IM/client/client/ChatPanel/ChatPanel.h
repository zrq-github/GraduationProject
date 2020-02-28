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

private:
    Ui::ChatPanel *ui;
    QString chatterId;
    QString chatterName;
private:
    void createUi();
    void binSlots();
private slots:
    void on_btnSend_click();
    void on_labName_Change();

    void slotChatterChange(QString &id,QString &name);
};
