#include "OpencvServerTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpencvServerTest w;
    w.show();
    return a.exec();
}
