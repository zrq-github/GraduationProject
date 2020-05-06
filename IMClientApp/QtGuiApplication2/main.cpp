#include <QtWidgets/QApplication>
//#include "FriendPanel/FriendItemWidget.h"
//#include "FriendPanel/FriendPanel.h"

#include "FriendPanel/FriendPanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FriendPanel *w = new FriendPanel;
    w->show();

    w->show();

    return a.exec();
}
