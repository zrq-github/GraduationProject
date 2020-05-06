#include "AppPath.h"
#include <QtWidgets/QApplication>

QString AppPath::appPath()
{
    return QApplication::applicationDirPath();
}

QString AppPath::appFilePath(QString str)
{
    return QApplication::applicationDirPath() + "\\" + str;
}

QString AppPath::ImgPath(QString fileName, QString fielPath)
{
    return AppPath::appFilePath(fielPath) + "\\" + fileName;
}
