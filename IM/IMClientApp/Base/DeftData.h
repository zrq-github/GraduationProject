#pragma once
#include <QObject>
#include "base_global.h"

enum MsgType
{
    USERREGISTER,   //�û�ע��
    USERLOGIN,      //�û���¼
    USERCHANGEPASWD,//�û��޸�����
    USERLEFT,       //�û�����
    USERMSG,            
    FILENAME,       //�����ļ���
    ACCEPTFILE,     //�����ļ�
    REFUSEFILE,     //�ܽӽ����ļ�
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};

