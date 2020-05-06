#ifndef DATACENTER_H_
#define DATACENTER_H_

#include "BaseDataType.h"
#include "datacenter_global.h"

#define DataCenterInst DataCenter::getInstance() 

class DATACENTER_EXPORT DataCenter
{

public:
    static DataCenter &getInstance();
    void setMyInfo(UserInfoPtr info);
    UserInfoPtr getMyInfo();
    
    ~DataCenter();
private:
    DataCenter();
    UserInfoPtr myInfo;
    static DataCenter *dataCenter;
};
#endif