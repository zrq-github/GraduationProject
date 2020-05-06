#ifndef BASEDATATYPE_H_
#define BASEDATATYPE_H_

#include <QObject>
#include "datacenter_global.h"
#include <memory>
#include <QByteArray>
#include <QDataStream>
#include <QMetaType>


enum MsgType
{
    USERLOGIN,          //登录
    USERLOGINSUCCEED,   //登录成功
    USERLOGINDEFEAT,    //登录失败
    USERLOGINREGISTER,  //用户注册
    USERMSG,            //转发用户消息

    USERFRIENDDATA,     //请求用户好友数据
    FILENAME,           //发送文件
    REFUSEFILE,         //拒接发送文件

    VIDEOCHAT,          //请求视频聊天
    VIDEOCHATREFUSE,    //拒接视频聊天
    VIDEOCHATACCEPT,    //接受视频聊天
};

enum UserInfoType
{
    USERID,
    USERNAME,
};

struct MsgInfo
{
public:
    MsgInfo(int msgType=0,QString from=nullptr,QString to=nullptr,QString msg=nullptr,QString address=nullptr, quint16 port=0)
    {
        this->msgType = msgType;
        this->to = to;
        this->from = from;
        this->msg = msg;
        this->address = address;
        this->port = port;
    }

    int msgType;
    QString from;
    QString to;
    QString msg;
    QString address;
    quint16 port;
};
typedef std::shared_ptr<MsgInfo> MsgInfoPtr;
Q_DECLARE_METATYPE(MsgInfo)

struct UserInfo
{
public:
    QString id;
    QString name;
    QString sign;

    QString imgPath;
};
typedef std::shared_ptr<UserInfo> UserInfoPtr;
Q_DECLARE_METATYPE(UserInfo)

//日志级别的提示信息
static const char * KEYINFOPREFIX = " Key: \n";
static const char * ERRORPREFIX = " Error: \n";
static const char * WARNINGPREFIX = " Warning: \n";
static const char * INFOPREFIX = " Info: \n";

static const int MAX_STR_LEN = 1024;
//日志级别枚举
enum EnumLogLevel
{
    LOGLEVELALL,    //所有信息都写日志
    LOGLEVELMID,        //写错误、警告信息
    LOGLEVELNORMAL,        //只写错误信息
    LOGLEVELSTOP,        //不写日志
};

#endif