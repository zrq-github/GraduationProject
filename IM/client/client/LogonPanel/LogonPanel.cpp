#include "LogonPanel.h"
#include "ui_LogonPanel.h"

LogonPanel::LogonPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::LogonPanel();
    ui->setupUi(this);
}

LogonPanel::~LogonPanel()
{
    delete ui;
}
