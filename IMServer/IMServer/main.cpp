#include <QtCore/QCoreApplication>
#include "IMQTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IMQTcpServer *server = new IMQTcpServer;
    server->listen(QHostAddress("192.168.20.103"), 4567);
    if (server->isListening())
    {
        qDebug() << "server listrn succeed";
    }
    return a.exec();
}
