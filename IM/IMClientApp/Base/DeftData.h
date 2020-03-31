#pragma once
#include <QObject>
#include "deftdata_global.h"
#include <memory>


enum MsgType
{
    USERLOGIN,          //登录
    USERLOGINSUCCEED,   //登录成功
    USERLOGINDEFEAT,    //登录失败
    USERLOGINREGISTER,  //用户注册
    USERMSG,            //转发用户消息

    USERFRIENDDATA,     //请求用户好友数据
    FILENAME,           //发送文件
    REFUSEFILE,
};

enum UserInfoType
{
    USERID,
    USERNAME,
};

class FriendData
{
public:
    QString id;
    QString name;
    QString sign;
};
#define FriendDataPtr std::shared_ptr<FriendData>
#define FriendDataMake std::make_shared<FriendData>