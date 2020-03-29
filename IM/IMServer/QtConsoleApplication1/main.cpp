#include <QtCore/QCoreApplication>

#include "IMQtMySql/IMQtMySql.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IMQtMySql *db = new IMQtMySql;
    qDebug() << db->connect() << endl;
    db->getUserPassword("1");
    db->disconnect();
    return a.exec();
}
