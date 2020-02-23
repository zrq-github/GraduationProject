#include "IMTitleBarPanel.h"
#include "ui_IMTitleBarPanel.h"
#include <QMoveEvent>

IMTitleBarPanel::IMTitleBarPanel(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::IMTitleBarPanel();
    ui->setupUi(this);
    this->createUi();
    this->setWindowFlag(Qt::FramelessWindowHint);
}

IMTitleBarPanel::~IMTitleBarPanel()
{
    delete ui;
}

void IMTitleBarPanel::createUi()
{
    ui->layout->setAlignment(Qt::AlignLeft|Qt::AlignTop);
}


