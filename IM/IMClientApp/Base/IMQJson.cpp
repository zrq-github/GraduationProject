#include "IMQJson.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QVariant>
#include <QJsonArray>

QByteArray IMQJson::getQJsonByte(int type, QString to, QString from, QString data)
{
    QJsonObject json;
    json.insert("msgType", type);
    json.insert("to", to);
    json.insert("from", from);
    json.insert("data", data);
    QJsonDocument document = QJsonDocument(json);

    return document.toJson();
}

QByteArray IMQJson::getQJsonFile(int type, QString to, QString from, QString address, QString file)
{
    QJsonObject json;
    json.insert("msgType", type);
    json.insert("to", to);
    json.insert("from", from);

    json.insert("address", address);
    json.insert("file", file);
    QJsonDocument document = QJsonDocument(json);

    return document.toJson();
}

QByteArray IMQJson::getQJsonUserInfo(int type, QString to, QString from, QJsonArray array)
{
    QJsonObject json;
    json.insert("msgType", type);
    json.insert("to", to);
    json.insert("from", from);

    json.insert("info", array);
    QJsonDocument document = QJsonDocument(json);
    return document.toJson();
}

//QByteArray IMQJson::getQJsonUserInfo(int type, QString to, QString from, QStringList strlist)
//{
//    QJsonObject json;
//    json.insert("msgType", type);
//    json.insert("to", to);
//    json.insert("from", from);
//
//    return QByteArray();
//}

QMap<QString, QVariant> IMQJson::getQMap(QByteArray & data)
{
    return QMap<QString, QVariant>();
}
