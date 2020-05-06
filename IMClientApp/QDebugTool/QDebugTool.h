#ifndef QDEBUG_H_
#define QDEBUG_H_

#include "qdebugtool_global.h"
#include <QDebug>

void QDEBUGTOOL_EXPORT QDebugTool(QString str);

#define QDEBUG_CONSOLE(x) QDebugTool(x)
#define QDEBUG_COUT qDebug()<<"["<<_FILE_<<":"<<_LINE_<<"]"

#endif
