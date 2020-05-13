#include "VideoWidgetDemo.h"
#include "AppSettings/AppPath.h"

VideoWidgetDemo::VideoWidgetDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    createUi();
}

void VideoWidgetDemo::createUi()
{
    v1 = new VideoWidget(this);
    v2 = new VideoWidget(this);
    v1->setGeometry(0, 0, 300, 300);
    v2->setGeometry(300, 0, 300, 300);
    v1->setFlowEnable(true);
    v2->setFlowEnable(true);

    v1->open();
}
