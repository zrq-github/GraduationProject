#include "DataCenter.h"
#include <QDebug>

DataCenter::DataCenter()
{
    qDebug() << "DataCenter Init";
}

void DataCenter::setMyInfo(UserInfoPtr info)
{
    this->myInfo = info;
}

UserInfoPtr DataCenter::getMyInfo()
{
    return myInfo;
}

DataCenter & DataCenter::getInstance()
{
    // TODO: 在此处插入 return 语句
    static DataCenter instance;
    return instance;
}

DataCenter::~DataCenter()
{
    qDebug() << "DataCenter desstruct";
}
