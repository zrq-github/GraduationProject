#include <QtWidgets/QApplication>
//#include "FriendPanel/FriendItemWidget.h"
//#include "FriendPanel/FriendPanel.h"

#include "LogonPanel/VerificationCodeLabel.h"
#include "LogonPanel/LogonPanel.h"
#include "FriendPanel/FriendPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogonPanel *w = new LogonPanel;
    w->show();

    w->show();

    return a.exec();
}
