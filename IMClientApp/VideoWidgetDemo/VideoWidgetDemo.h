#pragma once

#include <QtWidgets/QWidget>
#include "ui_VideoWidgetDemo.h"
#include "videowidget.h"
class VideoWidgetDemo : public QWidget
{
    Q_OBJECT

public:
    VideoWidgetDemo(QWidget *parent = Q_NULLPTR);

    void createUi();

    VideoWidget *v1;
    VideoWidget *v2;
    VideoWidget *v3;
    VideoWidget *v4;

private:
    Ui::VideoWidgetDemoClass ui;
};
