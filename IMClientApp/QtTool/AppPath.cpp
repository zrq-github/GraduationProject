#include "AppPath.h"
#include <QtWidgets/QApplication>

QString AppPath::appPath()
{
    return QApplication::applicationDirPath();
}

QString AppPath::appResourse()
{
    return QApplication::applicationDirPath() + "\\Resources";
}

QString AppPath::ImgPath(QString imgName)
{
    return AppPath::appResourse() + "\\" + imgName;
}
