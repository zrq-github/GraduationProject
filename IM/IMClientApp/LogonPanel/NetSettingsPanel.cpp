#include "NetSettingsPanel.h"
#include "ui_NetSettingsPanel.h"
#include "AppSettings/AppSettings.h"

NetSettingsPanel::NetSettingsPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::NetSettingsPanel();
    ui->setupUi(this);
    this->createUi();
    bindSign();

    ui->lineIP->setText(IMSettings.getSetting("server", "ip").toString());
    ui->linePort->setText(IMSettings.getSetting("server", "port").toString());
}

NetSettingsPanel::~NetSettingsPanel()
{
    delete ui;
}

void NetSettingsPanel::slotBtnSave()
{
    QString ip = ui->lineIP->text();
    QString port = ui->linePort->text();
    IMSettings.setSetting("server", "ip", ip);
    IMSettings.setSetting("server", "port", port);
    this->close();
}

void NetSettingsPanel::createUi()
{
    QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    ui->lineIP->setValidator(new QRegExpValidator(rx, this));
}

void NetSettingsPanel::bindSign()
{
    connect(ui->btnSave, &QPushButton::clicked, this, &NetSettingsPanel::slotBtnSave);
}
