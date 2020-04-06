#pragma once

#include <QtWidgets/QWidget>
#include "ui_OpencvText.h"
#include<opencv2/opencv.hpp>
#include <QImage> 
#include <QTimer>     // 设置采集数据的间隔时间 
#include <QtNetwork/QUdpSocket>

class OpencvText : public QWidget
{
    Q_OBJECT

public:
    OpencvText(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpencvTextClass ui;
    CvCapture *cap;
    QTimer    *timer;
    QImage    *imag;
    //IplImage  *frame;
    //网络设置参数
    QUdpSocket *m_udpSend;
    QUdpSocket *m_udpReceiver;
    int m_portSend;
    int m_porReceivert;
    //播放器参数
    cv::Mat frame;
    int timerID;        //记时操作
    cv::VideoCapture capture;


    int t;
    void timerEvent(QTimerEvent *event);
private slots:
    void on_btnCamera_clicked();
    void on_btnCloseCamera_clicked();
    void on_btnConnect_clicked();
    void on_btnSend_clicked();

    void processPendingDatagram();
};
