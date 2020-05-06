#include "DataAnalysis.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

QJsonObject DataAnalysis::objectFromMsginfo(MsgInfo & msg)
{
    QJsonObject msgJson;
    msgJson.insert("address", msg.address);
    msgJson.insert("from", msg.from);
    msgJson.insert("msg", msg.msg);
    msgJson.insert("msgType", msg.msgType);
    msgJson.insert("port", msg.port);
    msgJson.insert("to", msg.to);
    return msgJson;
}

QJsonObject DataAnalysis::objectFromUserInfo(UserInfo & user)
{
    QJsonObject userJson;
    userJson.insert("id", user.id);
    userJson.insert("name", user.name);
    userJson.insert("sign", user.sign);

    return userJson;
}

QByteArray DataAnalysis::byteFromMsgInfo(MsgInfo & msg)
{
    QJsonObject msgJson = DataAnalysis::objectFromMsginfo(msg);

    QJsonObject json;
    json.insert("msgInfo", msgJson);

    QJsonDocument document;
    document.setObject(json);

    return document.toJson();
}

QByteArray DataAnalysis::byteFromMsgInfoAdUserInfo(MsgInfo & msg, UserInfo & user)
{
    QJsonObject msgJson = DataAnalysis::objectFromMsginfo(msg);
    QJsonObject userJson = DataAnalysis::objectFromUserInfo(user);

    QJsonObject json;
    json.insert("msgInfo", msgJson);
    json.insert("userInfo", userJson);
    QJsonDocument document;
    document.setObject(json);

    return document.toJson();
}

MsgInfo DataAnalysis::msgFromJsonByte(const QByteArray & byte)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byte,&jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        QJsonObject object = doucment.object();
        if (object.contains("msgInfo"))
        {
            QJsonValue value = object.value("msgInfo");
            if (value.isObject())
            {
                QJsonObject obj = value.toObject();
                MsgInfo info;
                info.address = obj.value("address").toString();
                info.from = obj.value("from").toString();
                info.to = obj.value("to").toString();
                info.msg = obj.value("msg").toString();
                info.msgType = obj.value("msgType").toInt();
                info.port = obj.value("port").toInt();
                return info;
            }
        }
    }
    return MsgInfo();
}

UserInfo DataAnalysis::userFromJsonByte(const QByteArray & byte)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byte, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {  // 解析未发生错误
        QJsonObject object = doucment.object();
        if (object.contains("userInfo"))
        {
            QJsonValue value = object.value("userInfo");
            if (value.isObject())
            {
                QJsonObject obj = value.toObject();
                UserInfo info;
                info.id = obj.value("id").toString();
                info.name = obj.value("name").toString();
                info.sign = obj.value("sign").toString();
                return info;
            }
        }
    }
    return UserInfo();
}
