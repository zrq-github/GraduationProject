#pragma once
#include <QObject>
#include "deftdata_global.h"

enum MsgType
{
    USERLOGIN,
    USERMSG,

    FILENAME,
    REFUSEFILE,
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};


