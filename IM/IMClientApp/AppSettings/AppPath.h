
#ifndef APPPATH_h
#define APPPATH_h

#include "appsettings_global.h"

#define IMPATH AppPath

class APPSETTINGS_EXPORT AppPath
{
public:
    static QString appPath();
    static QString appResourse();
    static QString appImgPath(QString);
};

#endif // APPPATH_h
