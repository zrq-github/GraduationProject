#pragma once

#include <QtWidgets/QWidget>
#include "ui_OpencvServerTest.h"
#include <QUdpSocket>
#include<opencv2/opencv.hpp>

class OpencvServerTest : public QWidget
{
    Q_OBJECT

public:
    OpencvServerTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpencvServerTestClass ui;

    QUdpSocket *m_udpReceivert;
    quint16 m_portReceviert;
private slots:
    void on_btnOpenServer_clicked();

    void processPendingDatagram();
};
