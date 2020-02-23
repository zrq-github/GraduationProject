
#include "clientApp.h"
#include <QtWidgets/QApplication>
#include "LogonPanel/LogonPanel.h"
#include "IM/IM.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //测试登录面板
    //LogonPanel w;
    //w.show();

    //测试主面板
    IM *im = new IM;
    im->show();


    return a.exec();

    //LogonPanel *w = new LogonPanel;
    //if (w->exec() == QDialog::Accepted)
    //{
    //    IM *im = new IM;
    //    im->show();
    //    return a.exec();
    //}
    //else
    //{
    //    return 0;
    //}
}
