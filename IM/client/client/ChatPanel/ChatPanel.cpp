#include "ChatPanel.h"
#include "ui_ChatPanel.h"
#include <QLineEdit>

void ChatPanel::getMsg(QString str)
{
    ui->editChat->append(str);
}

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

void ChatPanel::createUi()
{
    //初始化部分值
    chatterId = "0000";
    chatterName = "";

    ui->editChat->document()->setMaximumBlockCount(200);    //设置最多显示行数
}

void ChatPanel::binSlots()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //发送文本事件
}

void ChatPanel::slot_labName_Change()
{

}

void ChatPanel::slotChatterChange(QString & id, QString & name)
{
    if (chatterId != id || chatterName != name)
    {
        ui->editChat->clear();      //更换聊天对象 文本清空
        ui->editSend->clear();

        this->chatterId = id;
        ui->labName->setText(name);
    }
}

void ChatPanel::slot_btnSend_click()
{
    QString &str = ui->editSend->toPlainText();     //得到编辑框的文字
    {
        //将文字进行大小处理
    }
    ui->editChat->append(str);                      //将编辑框的文字转到聊天框

    //
    emit sig_sendMsg(str);
    
    ui->editSend->clear();  //清空编辑框
}

void ChatPanel::getMsg(QString &str)
{
    ui->editChat->append(str);
}