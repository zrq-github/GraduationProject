#include "IMQtMySql.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>

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
