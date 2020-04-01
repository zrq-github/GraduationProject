#include "IMQTransport.h"

QByteArray IMQTransport::getMsgQByteArray(MsgInfo & info)
{
    QByteArray byte;
    QDataStream sendOut(&byte, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    sendOut << info;

    return byte;
}

QByteArray IMQTransport::getUserInfoQByteArray(MsgInfo & msgInfo, UserInfo & userInfo)
{
    QByteArray byte;
    QDataStream sendOut(&byte, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    sendOut << msgInfo << userInfo;

    return byte;
}
