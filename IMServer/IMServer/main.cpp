#include <QtCore/QCoreApplication>
#include "IMQTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IMQTcpServer *server = new IMQTcpServer;
    server->listen(QHostAddress("127.0.0.1"), 4567);
    if (server->isListening())
    {
        qDebug() << "server listrn succeed";
    }
    return a.exec();
}
