#pragma once
#include <QObject>
#include "deftdata_global.h"

enum MsgType
{
    USERLOGIN,          //��¼
    USERLOGINSUCCEED,   //��¼�ɹ�
    USERLOGINDEFEAT,    //��¼ʧ��
    USERMSG,            //ת���û���Ϣ

    FILENAME,           //�����ļ�
    REFUSEFILE,
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};


