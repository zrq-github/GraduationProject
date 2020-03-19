#include "IMServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IMServer w;
    w.show();
    return a.exec();
}
