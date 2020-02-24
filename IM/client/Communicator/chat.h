#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QtNetwork>
#include <QtGui>
#include "tcpclient.h"
#include "tcpserver.h"

namespace Ui {
    class chat;
}

enum MessageType
{
    Message,
    NewParticipant,
    ParticipantLeft,
    FileName,
    Refuse,
    Xchat
};

class chat : public QDialog
{
    Q_OBJECT


public:
    ~chat();
//    chat();
    chat(QString pasvusername, QString pasvuserip,QString Name);
    QString xpasvuserip;
    QString xpasvusername;
    QUdpSocket *xchat;
    qint32 xport;
    void sendMessage(MessageType type,QString serverAddress="");
    quint16 a;
//    static  qint32 is_opened = 0;
    bool is_opened;



protected:

    void participantLeft(QString userName,QString time);

private:
    Ui::chat *ui;
    TcpServer *server;
    QString name;


    QString getMessage();
    QString getIP();
    QString getUserName();
    QString message;


private slots:


    void on_send_clicked();
    //void on_close_clicked();
    void processPendingDatagrams();

};

#endif // CHAT_H

