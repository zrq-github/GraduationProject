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
    // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
    datagram.resize(m_udpReceivert->pendingDatagramSize());

    // 接收数据报，将其存放到datagram中
    m_udpReceivert->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());
    QByteArray uncompressByte = qUncompress(decryptedByte);
    QImage image;
    image.loadFromData(uncompressByte);

    ui.label->setPixmap(QPixmap::fromImage(image));
}
