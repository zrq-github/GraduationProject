#ifndef APPPATH_h
#define APPPATH_h
/**
 * ·����(QT)
 */
#include "qttool_global.h"

class AppPath
{
public:
    static QString appPath();
    static QString appResourse();
    static QString ImgPath(QString imgName);
};

#endif // APPPATH_h

