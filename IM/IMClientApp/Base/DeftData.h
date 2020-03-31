#pragma once
#include <QObject>
#include "deftdata_global.h"

enum MsgType
{
    USERLOGIN,          //��¼
    USERLOGINSUCCEED,   //��¼�ɹ�
    USERLOGINDEFEAT,    //��¼ʧ��
    USERLOGINREGISTER,  //�û�ע��
    USERMSG,            //ת���û���Ϣ

    FILENAME,           //�����ļ�
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


