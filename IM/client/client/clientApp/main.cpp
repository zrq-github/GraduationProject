
#include "clientApp.h"
#include <QtWidgets/QApplication>
#include <LogonPanel/LogonPanel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LogonPanel w;
    //w.show();

    LogonPanel *w = new LogonPanel;
    w->show();

    return a.exec();
}
