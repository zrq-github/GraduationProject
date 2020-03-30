#ifndef IMQtMySql_H
#define IMQtMySql_H

#include <QObject>
#include "imqtmysql_global.h"
#include <QSqlDatabase>

class IMQTMYSQL_EXPORT IMQtMySql
{
public:
    IMQtMySql();
    ~IMQtMySql();

    bool connect();
    void disconnect();
    QString getUserPassword(QString userid);
    QStringList getUserInfo(QString userid);
private:
    QSqlDatabase db;
    QString m_database = "QMYSQL";    //ÓÃµÄÊÇmysql
    QString m_host = "localhost";
    int m_port = 3306;
    QString m_databaseName = "im";
    QString m_userName = "root";
    QString m_userPassword = "123456";
};

#endif // IMQtMySql_H