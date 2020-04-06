#include "OpencvText.h"
#include <QBuffer>

OpencvText::OpencvText(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    cap = NULL;
    timer = new QTimer(this);
    imag = new QImage();         // 初始化 

    //网络设置初始化
    m_udpSend = new QUdpSocket(this);
    m_portSend = 8001;
    m_udpReceiver = new QUdpSocket(this);
    m_porReceivert = 8002;
    m_udpSend->bind(QHostAddress::LocalHost, m_portSend);

    m_udpReceiver->bind(QHostAddress::LocalHost, m_porReceivert);
    connect(m_udpReceiver, &QUdpSocket::readyRead, this, &OpencvText::processPendingDatagram);
    connect(m_udpSend, &QUdpSocket::readyRead, this, &OpencvText::processPendingDatagram);

    t = 0;
}

void OpencvText::on_btnCamera_clicked()
{
    capture.open(0);
    if (!capture.isOpened())
    {
        qDebug() << "open camera failed" << endl;
    }
    //初始化相机参数
    int delay = 1000 / 10;
    timerID = this->startTimer(delay);

    //cap = cvCreateCameraCapture(0);
    //cv::Mat edges;
    //while (1)
    //{
    //    cv::Mat frame; //定义一个Mat变量，用于存储每一帧的图像  
    //    capture >> frame;  //读取当前帧                          
    //    if (frame.empty())
    //    {
    //        break;
    //    }
    //    else
    //    {
    //        cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度  
    //        blur(edges, edges, cv::Size(7, 7));//模糊化  
    //        Canny(edges, edges, 0, 30, 3);//边缘化  
    //        imshow("Video", frame); //显示当前帧  
    //    }
    //    cv::waitKey(30); //延时30ms 
    //}
}

void OpencvText::timerEvent(QTimerEvent * event)
{
    if (event->timerId() == timerID)
    {
        if (capture.isOpened())
        {
            capture.read(frame);
        }
        cvtColor(frame, frame, CV_BGR2RGB);
        QImage image((unsigned char *)(frame.data),
            frame.cols, frame.rows,
            QImage::Format_RGB888);

        QByteArray byte;
        //字节数组 要进行传输必须先转换成这个格式
        QBuffer buff(&byte);
        // 建立一个用于IO读写的缓冲区
        image.save(&buff, "JPEG");
        // image先向下转为byte的类型，再存入buff
        QByteArray compressByte = qCompress(byte, 1);
        //数据压缩算法
        QByteArray base64Byte = compressByte.toBase64();
        
        m_udpSend->writeDatagram(base64Byte.data(), base64Byte.size(),QHostAddress::LocalHost, 8001);

        ui.labVideo->setPixmap(QPixmap::fromImage(image));
        ui.labVideo->resize(image.width(), image.height());
    }
}

void OpencvText::on_btnCloseCamera_clicked()
{
    //capture.release();//释放资源
    cv::destroyAllWindows();//关闭所有窗口
}

void OpencvText::on_btnConnect_clicked()
{

}

void OpencvText::on_btnSend_clicked()
{
    QHostAddress targetAddr(QHostAddress::LocalHost);
    quint16 targetPort = 9001;

    QString  msg = "client send msg";//发送的消息内容
    QByteArray byteStr = msg.toUtf8();

    m_udpSend->writeDatagram(byteStr, targetAddr, targetPort);
}

void OpencvText::processPendingDatagram()
{
    QByteArray   datagram;
    // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
    datagram.resize(m_udpSend->pendingDatagramSize());

    // 接收数据报，将其存放到datagram中
    m_udpSend->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());
    QByteArray uncompressByte = qUncompress(decryptedByte);
    QImage image;
    image.loadFromData(uncompressByte);

    qDebug() << ui.label->width() << " " << ui.label->height();
    image.scaled(ui.label->size());

    ui.label->setPixmap(QPixmap::fromImage(image).scaled(340, 130));
}
