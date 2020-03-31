#pragma once
#include <QObject>
#include "deftdata_global.h"
#include <memory>


enum MsgType
{
    USERLOGIN,          //��¼
    USERLOGINSUCCEED,   //��¼�ɹ�
    USERLOGINDEFEAT,    //��¼ʧ��
    USERLOGINREGISTER,  //�û�ע��
    USERMSG,            //ת���û���Ϣ

    USERFRIENDDATA,     //�����û���������
    FILENAME,           //�����ļ�
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