#pragma once

#include <QWidget>
#include "opencv2/opencv.hpp"
namespace Ui { class VideoChatPanel; };
class QUdpSocket;

class VideoChatPanel : public QWidget
{
    Q_OBJECT

public:
    VideoChatPanel(QString name="", QWidget *parent = Q_NULLPTR);
    ~VideoChatPanel();

    void init();
    void openCamera();
    void setAddress(QString &address);
    void setIsTransfer(bool is);
private:
    Ui::VideoChatPanel *ui;

    //网络设置参数
    QUdpSocket *m_udpSocket;
    bool    m_isTransfer;
    QString m_address;
    quint16 m_port;
    //quint16 m_otherPort;  //测试用端口
    //播放器参数
    cv::Mat frame;
    cv::Mat bfFrame;
    int timerID;
    cv::VideoCapture capture;

    void timerEvent(QTimerEvent *event);
private slots:
    void slotPendingDatagram();
};
