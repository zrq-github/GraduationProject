#include "IMQJson.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QVariant>

//QByteArray IMQJson::getQJsonByte(int type, QString to, QString from, QString & data)
//{
//    QJsonObject json;
//    json.insert("msgType", type);
//    json.insert("to", to);
//    json.insert("from", from);
//    json.insert("data", data);
//    QJsonDocument document = QJsonDocument(json);
//
//    return document.toJson();
//}

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

QMap<QString, QVariant> IMQJson::getQMap(QByteArray & data)
{
    return QMap<QString, QVariant>();
}
