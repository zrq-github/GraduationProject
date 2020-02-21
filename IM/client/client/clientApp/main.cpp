#include <QtWidgets/QApplication>
#include "LogonPanel/LogonPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IM::LogonPanel logonApp;
    logonApp.show();
    return a.exec();
}
