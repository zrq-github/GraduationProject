#include "QDebugTool.h"

void QDebugTool(QString str)
{
#ifdef _DEBUG
    qDebug() << str;
#endif
}
