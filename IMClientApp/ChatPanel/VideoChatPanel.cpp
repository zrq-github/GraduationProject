#include "VideoChatPanel.h"
#include "ui_VideoChatPanel.h"
#include "QUdpSocket"
#include <QDebug>
#include <QBuffer>
#include "AppSettings/AppPath.h"
#include "DataCenter/IMQTcpWord.h"
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

VideoChatPanel::VideoChatPanel(QString name,QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::VideoChatPanel();
    ui->setupUi(this);

    this->setWindowTitle("��" + name + "����");

    this->init();
    openCamera();
}

VideoChatPanel::~VideoChatPanel()
{
    delete ui;
}

void VideoChatPanel::init()
{
    m_isTransfer = false;
    m_port = 9001;
    m_otherPort = 9002; //�����ö˿�
    //�����ʼ��
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(IMQTcpSocket->peerAddress(), quint16(m_port));
    
    qDebug() << IMQTcpSocket->peerAddress();

    if (!m_udpSocket->isValid())
    {
        qDebug() << QHostAddress::LocalHost+" udpsock��ʧ��";
    }
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &VideoChatPanel::slotPendingDatagram);
}

void VideoChatPanel::openCamera()
{
    capture.open(0);
    if (!capture.isOpened())
    {
        qDebug() << "open camera failed" << endl;
    }
    int delay = 1000 / 10;
    timerID = this->startTimer(delay);
}

void VideoChatPanel::setAddress(QString & address)
{
    this->m_address = address;
}

void VideoChatPanel::setIsTransfer(bool is)
{
    this->m_isTransfer = is;
}

void VideoChatPanel::timerEvent(QTimerEvent * event)
{
    if (event->timerId() == timerID)
    {
        if (capture.isOpened())
        {
            capture.read(frame);
        }
        bfFrame = frame;
        //if (frame.channels() == 4) {
        //    cv::cvtColor(bfFrame, frame, CV_BGRA2GRAY);
        //}
        //else if (frame.channels() == 3) {
        //    cv::cvtColor(bfFrame, frame, CV_BGR2GRAY);
        //}
        //else if (frame.channels() == 2) {
        //    cv::cvtColor(bfFrame, frame, CV_BGR5652GRAY);
        //}
        QImage image = QImage((const unsigned char*)(bfFrame.data),
            bfFrame.cols, bfFrame.rows,bfFrame.step,
            QImage::Format_RGB888).rgbSwapped();

        ui->labVideoMe->setPixmap(QPixmap::fromImage(image));

        if (m_isTransfer)
        {//�ж��Ƿ���д���
            QByteArray byte;
            //�ֽ����� Ҫ���д��������ת���������ʽ
            QBuffer buff(&byte);
            // ����һ������IO��д�Ļ�����
            image.save(&buff, "JPEG");
            // image������תΪbyte�����ͣ��ٴ���buff
            QByteArray compressByte = qCompress(byte, 1);
            //����ѹ���㷨
            QByteArray base64Byte = compressByte.toBase64();

            m_udpSocket->writeDatagram(base64Byte.data(), base64Byte.size(), QHostAddress(m_address), m_port);
        }
    }
}

void VideoChatPanel::slotPendingDatagram()
{//���շ�������Ƶ��
    QByteArray   datagram;
    // ��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������
    datagram.resize(m_udpSocket->pendingDatagramSize());
    // �������ݱ��������ŵ�datagram��
    m_udpSocket->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());
    QByteArray uncompressByte = qUncompress(decryptedByte);
    QImage image;
    image.loadFromData(uncompressByte);

    //qDebug() << ui->labVideoOther->width() << " " << ui->labVideoOther->height();
    ui->labVideoOther->setPixmap(QPixmap::fromImage(QImage(AppPath::ImgPath("img_logon_default_head.png"))));
}
