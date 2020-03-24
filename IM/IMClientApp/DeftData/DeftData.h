#pragma once
#include <QObject>
#include "deftdata_global.h"

enum sendObject
{
    IMSERVER,   //�ͻ��˷��͸�������
    OTHERUSER,  //�ͷ��˷��͸��ͷ���
    YOUSELF,    //���������͸��ͷ���
};

enum operationType
{
    LOGONG,         //��¼
    RETRANSMIT,     //ת��
    GETFRIENDDATA,  //�����������
};

enum dataType
{
    TXT,        //�����ı���Ϣ
    FILE,       //�����ļ�
};

struct FriendData
{
    QString id;
    QString name;
    QString sign;
};

class DEFTDATA_EXPORT DeftData
{
public:
    DeftData();
};
