#include "FrendDemo.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "FriendDemo1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QFile qss("H:\\Code\\IMClientApp\\FrendDemo\\style.qss");
    //QFile qss("H:\\Code\\IMClientApp\\x64\\Debug\\Resources\\demo1.qss");
    //qss.open(QFile::ReadOnly);
    //if (qss.isOpen())
    //{
    //    qApp->setStyleSheet(qss.readAll());
    //    qss.close();
    //}
    //FrendDemo w;
    //w.show();

    //FriendDemo1 *w = new FriendDemo1;
    //w->show();

    //personListBuddy *w = new personListBuddy;
    //w->show();

    personList *w = new personList;
    w->show();

    return a.exec();
}
