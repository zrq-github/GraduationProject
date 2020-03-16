#include "IMClientApp.h"
#include "LogonPanel/LogonPanel.h"
#include <QHBoxLayout>

IMClientApp::IMClientApp(QWidget *parent)
    : QWidget(parent)
    , friendPanel(Q_NULLPTR)
{
    ui.setupUi(this);
    createUi();
    bindSigns();
}

void IMClientApp::bindSigns()
{
}

void IMClientApp::createUi()
{
}
