#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QWidget>
#include <QtNetwork>
#include <QtGui>
#include "tcpclient.h"
#include "tcpserver.h"
#include "chat.h"




class QUdpSocket;
class TcpServer;


namespace Ui {
class Widget;
}



class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0,QString s="");
private slots:

    void processPendingDatagrams();

    void getFileName(QString);

    void on_sendButton_clicked();
    void on_sendToolButton_clicked();
    void on_save_clicked();

    void on_userTableWidget_doubleClicked(QModelIndex index);




    void on_boldToolBtn_clicked();
    void on_pinkButtun_clicked();
    void on_gray_clicked();
    void on_lightblue_clicked();

public:

    ~Widget();
    chat* privatechat;
    chat* privatechat1;

protected:

    void newParticipant(QString userName,
                            QString ipAddress);
    void participantLeft(QString userName,
                             QString time);
    void sendMessage(MessageType type, QString serverAddress="");


        QString getIP();
        QString getUserName();
        QString getMessage();

        void hasPendingFile(QString userName, QString serverAddress,
                                QString clientAddress, QString fileName);




private:
    Ui::Widget *ui;
    QString qstring;
    QUdpSocket *udpSocket;
    qint16 port;
    qint32 bb;
     int i;// use to bold
    QString fileName;
        TcpServer *server;

        bool saveFile(const QString& filename);
        void showxchat(QString name,QString ip,QString myname);



};

#endif // WIDGET_H
