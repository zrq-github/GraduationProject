#pragma once

#include <QtWidgets/QWidget>
#include "ui_IMServer.h"
#include "IMQTcpServer/IMQTcpServer.h"
#include "IMQTcpServer/IMQTcpSocket.h"

class IMServer : public QWidget
{
    Q_OBJECT

public:
    IMServer(QWidget *parent = Q_NULLPTR);
    void createUi();
    void bindSigns();
private slots:
    void slotStart();
    void slotNewConnect(const int handle, const QString& address, const quint16 port);
    void slotClientDisConnect(const int handle, const QString address, const quint16 port);
    void slotClientMessage(QString &to, QString from, QString &msg);        //给ui界面用

    void slotSelectFile();
private:
    Ui::IMServerClass ui;
    IMQTcpServer *m_tcpServer;
};
