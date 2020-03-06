#include "IMQTcpSocket.h"
IMQTcpSocket::IMQTcpSocket(qintptr socketDescriptor,QObject *parent)
    : QTcpSocket(parent)
{
    socketID = socketDescriptor;
}

IMQTcpSocket::~IMQTcpSocket()
{
}

void IMQTcpSocket::thisReadData()
{
}

void IMQTcpSocket::sentData(const QByteArray &, const int)
{
    int a = 0;
}
