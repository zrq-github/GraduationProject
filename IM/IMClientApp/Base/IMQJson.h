#pragma once

#include <QObject>
#include "base_global.h"


static class BASE_EXPORT IMQJson
{
public:

    //static QByteArray getQJsonByte(int type, QString to, QString from, QString & data);
    static QByteArray getQJsonByte(int type, QString to, QString from, QString data);

    static QByteArray getQJsonFile(int type, QString to, QString from, QString address,QString file);

    static QMap<QString, QVariant> getQMap(QByteArray &data);
};
