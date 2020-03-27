#pragma once
#include <QObject>
#include "base_global.h"

enum MsgType
{
    USERREGISTER,   //用户注册
    USERLOGIN,      //用户登录
    USERCHANGEPASWD,//用户修改密码
    USERLEFT,       //用户下线
    USERMSG,            
    FILENAME,       //发送文件名
    ACCEPTFILE,     //接受文件
    REFUSEFILE,     //拒接接受文件
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};

