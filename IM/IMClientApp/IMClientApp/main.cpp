#include "IMClientApp.h"
#include <QtWidgets/QApplication>
#include "LogonPanel/LogonPanel.h"
#include "FriendPanel/FriendPanel.h"
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<FriendData>("FrdItemData");
    qRegisterMetaType<FriendData>("FrdItemData&");
    LogonPanel *w = new LogonPanel;
    if (w->exec() == QDialog::Accepted)
    {
        IMClientApp *im = new IMClientApp;
        im->show();
        return a.exec();
    }
    else
    {
        return 0;
    }
    //FriendPanel *w = new FriendPanel;
    //w->show();
    //return a.exec();
}
