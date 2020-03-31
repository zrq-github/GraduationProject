#pragma once
#include <QObject>
#include "deftdata_global.h"

enum MsgType
{
    USERLOGIN,          //登录
    USERLOGINSUCCEED,   //登录成功
    USERLOGINDEFEAT,    //登录失败
    USERLOGINREGISTER,  //用户注册
    USERMSG,            //转发用户消息

    FILENAME,           //发送文件
    REFUSEFILE,
};

enum UserInfoType
{
    USERID,
    USERNAME,
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};


