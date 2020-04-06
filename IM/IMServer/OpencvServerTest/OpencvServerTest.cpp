#include "OpencvServerTest.h"


OpencvServerTest::OpencvServerTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_udpReceivert = new QUdpSocket(this);
    m_portReceviert = 9001;
    m_udpReceivert->bind(QHostAddress::LocalHost, m_portReceviert);
    connect(m_udpReceivert, &QUdpSocket::readyRead, this, &OpencvServerTest::processPendingDatagram);
}

void OpencvServerTest::on_btnOpenServer_clicked()
{
}

void OpencvServerTest::processPendingDatagram()
{
    QByteArray   datagram;
    // ��datagram�Ĵ�СΪ�ȴ���������ݱ��Ĵ�С���������ܽ��յ�����������
    datagram.resize(m_udpReceivert->pendingDatagramSize());

    // �������ݱ��������ŵ�datagram��
    m_udpReceivert->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());
    QByteArray uncompressByte = qUncompress(decryptedByte);
    QImage image;
    image.loadFromData(uncompressByte);

    ui.label->setPixmap(QPixmap::fromImage(image));
}
