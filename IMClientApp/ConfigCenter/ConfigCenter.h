#ifndef CONFIGCENTER_H_
#define CONFIGCENTER_H_

#include "AppPath.h"
#include "AppSettings.h"

#define IMPATH AppPath
#define IMSettings AppSettings::getInstance()
#define IMUSERID AppSettings::getInstance().getUserID()

#endif //CONFIGCENTER_H_
