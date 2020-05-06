#ifndef DATAANALYSIS_H_
#define DATAANALYSIS_H_

#include "datacenter_global.h"
#include "BaseDataType.h"

class DATACENTER_EXPORT DataAnalysis
{
public:
    static QJsonObject objectFromMsginfo(MsgInfo &msg);
    static QJsonObject objectFromUserInfo(UserInfo &user);

    static QByteArray byteFromMsgInfo(MsgInfo &msg);
    static QByteArray byteFromMsgInfoAdUserInfo(MsgInfo &msg,UserInfo &user);

    static MsgInfo msgFromJsonByte(const QByteArray &byte);
    static UserInfo userFromJsonByte(const QByteArray &byte);
};
#endif