#include "IMClientSocket.h"

IMClientSocket::IMClientSocket(QObject *parent)
    : QTcpSocket(parent)
{
    bindSigns();
}

IMClientSocket::~IMClientSocket()
{
}

void IMClientSocket::bindSigns()
{
    connect(this, &IMClientSocket::connected, this, &IMClientSocket::slotConnected);
}

void IMClientSocket::slotConnected()
{

}
