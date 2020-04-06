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

QString AppPath::appImgPath(QString imgPath)
{
    return AppPath::appResourse() + "\\" + imgPath;
}
