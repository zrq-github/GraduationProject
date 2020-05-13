#include "VideoWidgetDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoWidgetDemo w;
    w.show();
    return a.exec();
}
