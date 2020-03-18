#include "ChatPanel.h"
#include "ui_ChatPanel.h"
#include <QLineEdit>

void ChatPanel::getMsg(QString str)
{
    ui->editChat->append(str);
}

QString ChatPanel::getTitle()
{
    return ui->labName->text();
}

void ChatPanel::closeEvent(QCloseEvent * event)
{//关闭前发送信号
    emit signClose(m_chatID);
}

ChatPanel::ChatPanel(QString id,QString name, QWidget *parent)
    : QWidget(parent)
{
    this->m_chatID = id;
    this->m_chatName = name;
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
    m_chatID = "0000";
    m_chatName = "";

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
    if (m_chatID != id || m_chatName != name)
    {
        ui->editChat->clear();      //更换聊天对象 文本清空
        ui->editSend->clear();

        this->m_chatID = id;
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