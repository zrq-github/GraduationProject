/**
 * Â·¾¶Àà(QT)
 */
#ifndef APPPATH_h
#define APPPATH_h
#include "configcenter_global.h"

class CONFIGCENTER_EXPORT AppPath
{
public:
    static QString appPath();
    static QString appResourse();
    static QString ImgPath(QString imgName);
};

#endif // APPPATH_h

