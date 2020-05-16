#include <QtCore/QCoreApplication>
#include "IMQTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IMQTcpServer *server = new IMQTcpServer;
    server->listen(QHostAddress("10.60.17.197"), 4567);
    if (server->isListening())
    {
        qDebug() << "server listrn succeed";
    }
    else
    {
        qDebug() << server->serverAddress() << " " << server->serverPort();
        qDebug() << "server listening flase";
    }
    return a.exec();
}
