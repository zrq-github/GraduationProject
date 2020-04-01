#pragma once

#include <QObject>
#include "DeftData.h"
#include "base_global.h"

#define IMQPROTOCOL IMQTransport

class BASE_EXPORT IMQTransport
{
public:
    static QByteArray getMsgQByteArray(MsgInfo &info);
    static QByteArray getUserInfoQByteArray(MsgInfo &msgInfo, UserInfo &userInfo);
};
