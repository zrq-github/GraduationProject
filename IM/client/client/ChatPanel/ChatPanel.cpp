#include "ChatPanel.h"
#include "ui_ChatPanel.h"

ChatPanel::ChatPanel(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::ChatPanel();
    ui->setupUi(this);
    binSlots();
}

ChatPanel::~ChatPanel()
{
    delete ui;
}

void ChatPanel::binSlots()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(on_btnSend_click()));
}

void ChatPanel::on_btnSend_click()
{
    QString &str = ui->editSend->toPlainText();
    ui->editChat->setText(str);
}
