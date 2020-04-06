#pragma once

#include <QtWidgets/QWidget>
#include "Base/DeftData.h"

namespace Ui {
    class IMClientAppClass;
}

class FriendPanel;
class ChatPanel;
class QTcpSocket;

class IMClientApp : public QWidget
{
    Q_OBJECT

public:
    IMClientApp(QWidget *parent = Q_NULLPTR);
    void requsetFriendData();                      //�����������
private:
    void bindSigns();
    void createUi();

    void analyzeFriendData();
private:
    Ui::IMClientAppClass *ui;

    FriendPanel *m_friendPanel;
    QHash<QString, ChatPanel*> *m_hashFriendPanel;
    QVector<FriendDataPtr>  m_friendData;

signals:
    void signChatVideoChat(MsgInfo);
protected slots:
    void slotCreateChatPanel(QString id, QString name);     //�������촰��
    void slotDeletChatPanel(QString id);                    //ɾ�����촰��
    void slotSendMessage(QString &to, QString &msg);        //����������Ϣ
    void slotSendFile(QByteArray&);                         //�����ļ�


    void slotSocketReadData();                      //������������ص���Ϣ
};
