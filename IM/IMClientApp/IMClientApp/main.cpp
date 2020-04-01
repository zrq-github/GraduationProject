#include "IMClientApp.h"
#include <QtWidgets/QApplication>
#include "LogonPanel/LogonPanel.h"
#include "FriendPanel/FriendPanel.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogonPanel *w = new LogonPanel;
    if (w->exec() == QDialog::Accepted)
    {
        IMClientApp *im = new IMClientApp;
        im->show();
        im->requsetFriendData();
        return a.exec();
    }
    else
    {
        return 0;
    }

    //IMClientApp *w = new IMClientApp;
    //w->show();
    //return a.exec();
}
