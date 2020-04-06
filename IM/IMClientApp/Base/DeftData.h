#ifndef DEFTDATA_H
#define DEFTDATA_H
#include <QObject>
#include "deftdata_global.h"
#include <memory>
#include <QByteArray>
#include <QDataStream>

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
    int msgType;
    QString from;
    QString to;
    QString msg;
    QString address;
    QString port;

    friend QDataStream &operator<<(QDataStream &output, const MsgInfo &data) {
        output << data.msgType << data.from << data.to << data.msg << data.address << data.port;
        return output;
    }
    friend QDataStream &operator>>(QDataStream &intput, MsgInfo &data) {
        intput >> data.msgType >> data.from >> data.to >> data.msg >> data.address >> data.port;
        return intput;
    }
};

struct UserInfo
{
public:
    QString id;
    QString name;
    QString sign;

    friend QDataStream &operator<<(QDataStream &output, const UserInfo &data)
    {
        output << data.id << data.name << data.sign;
        return output;
    }
    friend QDataStream &operator>>(QDataStream &intput, UserInfo &data) {
        intput >> data.id >> data.name >> data.sign;
        return intput;
    }
};

#define FriendDataPtr std::shared_ptr<UserInfo>
#define FriendDataMake std::make_shared<UserInfo>

#endif // !DEFTDATA_H