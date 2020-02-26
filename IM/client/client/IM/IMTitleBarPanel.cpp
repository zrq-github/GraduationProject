#include "IMTitleBarPanel.h"
#include <QMoveEvent>
#include "ui_IMTitleBarPanel.h"

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


