#ifndef APPPATH_h
#define APPPATH_h
/**
 * Â·¾¶Àà(QT)
 */
#include "appsettings_global.h"

#define IMPATH AppPath

class APPSETTINGS_EXPORT AppPath
{
public:
    static QString appPath();
    static QString appResourse();
    static QString ImgPath(QString imgName);
};

#endif // APPPATH_h

