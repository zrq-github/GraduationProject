#ifndef IMCLIENTAP_H_
#define IMCLIENTAP_H_

#include <QtWidgets/QWidget>
#include "DataCenter/BaseDataType.h"
#include "ui_IMClientApp.h"

class FriendListWidget;
class QPushButton;
class QLineEdit;
class ChatPanel;

class IMClientApp : public QWidget
{
    Q_OBJECT

public:
    IMClientApp(QWidget *parent = Q_NULLPTR);

private slots:
    void slotOpenChatPanel(UserInfo & userInfo);
    void slotChatMsg(MsgInfo);
private:
    void createUi();
    void bindSignlSlot();
    Ui::IMClientAppClass ui;

    QHash<QString, ChatPanel*> *m_hashChant;
    QPushButton *m_btnUserHead;
    FriendListWidget *friendPanel;
    ChatPanel   *currentChatPanel;
    QLineEdit *m_lineEdit;

    
};
#endif