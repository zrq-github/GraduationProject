#include "IMQtMySql.h"
#include <QSqlQuery>
#include "DataCenter/BaseDataType.h"
#include <QDebug>

IMQtMySql::IMQtMySql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(m_host);
    db.setPort(m_port);
    db.setDatabaseName(m_databaseName);
    db.setUserName(m_userName);
    db.setPassword(m_userPassword);
}

IMQtMySql::~IMQtMySql()
{
    this->disconnect();
}

bool IMQtMySql::connect()
{
    if (!db.open())
    {
        return false;
    }
    return true;
}

void IMQtMySql::disconnect()
{
    db.close();
}

QString IMQtMySql::getUserPassword(QString userid)
{
    QString str = QString("select user_password from logon where user_id =  %1").arg(userid);
    qDebug() << str;

    QSqlQuery query(db);
    query.exec(str);

    query.next();
    qDebug() << query.value("user_password").toString();

    return query.value("user_password").toString();
}

QStringList IMQtMySql::getUserInfo(QString userid)
{
    QString str = QString("select user_id,user_name from userinfo where user_id =  %1").arg(userid);
    qDebug() << str;

    QSqlQuery query(db);
    query.exec(str);

    if (query.isActive())
    {//Ö´ÐÐ³É¹¦

        query.next();
        QStringList strList;
        strList.insert(UserInfoType::USERID, query.value(0).toString());
        strList.insert(UserInfoType::USERNAME, query.value(1).toString());

        qDebug() << query.value(0).toString() << "  " + query.value(1).toString();
        return strList;
    }

    return QStringList();
}

bool IMQtMySql::updateLogon(QString userID, QString userPassword)
{
    QString str = QString("UPDATE `im`.`logon` SET `user_password` = '%1' WHERE (`user_id` = '%2');").arg(userPassword, userID);
    qDebug() << str;

    QSqlQuery query(db);
    query.exec(str);
    if (query.isActive())
    {
        qDebug() << QString("%1 query updateLogon succeed!").arg(userID);
        return true;
    }
    else
    {
        qDebug() << QString("%1 query updateLogon failed!").arg(userID);
        return false;
    }
}

bool IMQtMySql::addUser(QString userID, QString userPassword)
{
    QString str = QString("INSERT INTO `im`.`logon` (`user_id`, `user_password`) VALUES ('%1', '%2');").arg(userID, userPassword);
    QString str1 = QString("INSERT INTO `im`.`userinfo` (`user_id`, `user_name`) VALUES ('%1', '%2');").arg(userID, QString("no Name"));
    qDebug() << str + str1;

    QSqlQuery query(db);
    query.exec(str.append(str1));

    if (query.isActive())
    {
        qDebug() << QString("%1 add succeed!").arg(userID);
        return true;
    }
    else
    {
        qDebug() << QString("%1 add failed!").arg(userID);
        return false;
    }
    return false;
}
