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
    USERLOGIN,          //��¼
    USERLOGINSUCCEED,   //��¼�ɹ�
    USERLOGINDEFEAT,    //��¼ʧ��
    USERLOGINREGISTER,  //�û�ע��
    USERMSG,            //ת���û���Ϣ

    USERFRIENDDATA,     //�����û���������
    FILENAME,           //�����ļ�
    REFUSEFILE,         //�ܽӷ����ļ�

    VIDEOCHAT,          //������Ƶ����
    VIDEOCHATREFUSE,    //�ܽ���Ƶ����
    VIDEOCHATACCEPT,    //������Ƶ����
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

//��־�������ʾ��Ϣ
static const char * KEYINFOPREFIX = " Key: \n";
static const char * ERRORPREFIX = " Error: \n";
static const char * WARNINGPREFIX = " Warning: \n";
static const char * INFOPREFIX = " Info: \n";

static const int MAX_STR_LEN = 1024;
//��־����ö��
enum EnumLogLevel
{
    LOGLEVELALL,    //������Ϣ��д��־
    LOGLEVELMID,        //д���󡢾�����Ϣ
    LOGLEVELNORMAL,        //ֻд������Ϣ
    LOGLEVELSTOP,        //��д��־
};

#endif