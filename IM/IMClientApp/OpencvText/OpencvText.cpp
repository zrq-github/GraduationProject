#include "OpencvText.h"
#include <QBuffer>

OpencvText::OpencvText(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    cap = NULL;
    timer = new QTimer(this);
    imag = new QImage();         // ��ʼ�� 

    //�������ó�ʼ��
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
    //��ʼ���������
    int delay = 1000 / 10;
    timerID = this->startTimer(delay);

    //cap = cvCreateCameraCapture(0);
    //cv::Mat edges;
    //while (1)
    //{
    //    cv::Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��  
    //    capture >> frame;  //��ȡ��ǰ֡                          
    //    if (frame.empty())
    //    {
    //        break;
    //    }
    //    else
    //    {
    //        cvtColor(frame, edges, CV_BGR2GRAY);//��ɫת���ɻҶ�  
    //        blur(edges, edges, cv::Size(7, 7));//ģ����  
    //        Canny(edges, edges, 0, 30, 3);//��Ե��  
    //        imshow("Video", frame); //��ʾ��ǰ֡  
    //    }
    //    cv::waitKey(30); //��ʱ30ms 
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
        //�ֽ����� Ҫ���д��������ת���������ʽ
        QBuffer buff(&byte);
        // ����һ������IO��д�Ļ�����
        image.save(&buff, "JPEG");
        // image������תΪbyte�����ͣ��ٴ���buff
        QByteArray compressByte = qCompress(byte, 1);
        //����ѹ���㷨
        QByteArray base64Byte = compressByte.toBase64();
        
        m_udpSend->writeDatagram(base64Byte.data(), base64Byte.size(),QHostAddress::LocalHost, 8001);

        ui.labVideo->setPixmap(QPixmap::fromImage(image));
        ui.labVideo->resize(image.width(), image.height());
    }
}

void OpencvText::on_btnCloseCamera_clicked()
{
    //capture.release();//�ͷ���Դ
    cv::destroyAllWindows();//�ر����д���
}

void OpencvText::on_btnConnect_clicked()
{

}

void OpencvText::on_btnSend_clicked()
{
    QHostAddress targetAddr(QHostAddress::LocalHost);
    quint16 targetPort = 9001;

    QString  msg = "client send msg";//���͵���Ϣ����
    QByteArray byteStr = msg.toUtf8();

    m_udpSend->writeDatagram(byteStr, targetAddr, targetPort);
}

void OpencvText::processPendingDatagram()
{
    QByteArray   datagram;
    // ��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������
    datagram.resize(m_udpSend->pendingDatagramSize());

    // �������ݱ��������ŵ�datagram��
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
