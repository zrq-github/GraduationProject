#ifndef APPPATH_h
#define APPPATH_h
/**
 * Â·¾¶Àà(QT)
 */
#include "appsettings_global.h"
#include <QObject>

#define IMPATH AppPath
class APPSETTINGS_EXPORT AppPath
{
public:
    static QString appPath();
    static QString appFilePath(QString str = "Resources");
    static QString ImgPath(QString fileName,QString fielPath="Resources");
};

#endif // APPPATH_h

