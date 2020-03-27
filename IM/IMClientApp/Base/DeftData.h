#pragma once
#include <QObject>
#include "deftdata_global.h"

enum sendObject
{
    IMSERVER,   //客户端发送给服务器
    OTHERUSER,  //客服端发送给客服端
    YOUSELF,    //服务器发送给客服端
};

enum operationType
{
    LOGONG,         //登录
    RETRANSMIT,     //转发
    GETFRIENDDATA,  //请求好友数据
};

enum dataType
{
    TXT,        //发送文本信息
    FILE,       //发送文件
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};

class DEFTDATA_EXPORT DeftData
{
public:
    DeftData();
};
