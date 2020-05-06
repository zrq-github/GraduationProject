#include "IMClientApp.h"
#include <QtWidgets/QApplication>
#include "LogonPanel/LogonPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogonPanel *w = new LogonPanel();
    int ret = w->exec();
    if(ret==QDialog::Accepted)
    {
        IMClientApp *app = new IMClientApp;
        app->show();
    }
    return a.exec();
}
