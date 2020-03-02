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
    //��ʼ������ֵ
    chatterId = "0000";
    chatterName = "";

    ui->editChat->document()->setMaximumBlockCount(200);    //���������ʾ����
}

void ChatPanel::binSlots()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //�����ı��¼�
}

void ChatPanel::slot_labName_Change()
{

}

void ChatPanel::slotChatterChange(QString & id, QString & name)
{
    if (chatterId != id || chatterName != name)
    {
        ui->editChat->clear();      //����������� �ı����
        ui->editSend->clear();

        this->chatterId = id;
        ui->labName->setText(name);
    }
}

void ChatPanel::slot_btnSend_click()
{
    QString &str = ui->editSend->toPlainText();     //�õ��༭�������
    {
        //�����ֽ��д�С����
    }
    ui->editChat->append(str);                      //���༭�������ת�������

    //
    emit sig_sendMsg(str);
    
    ui->editSend->clear();  //��ձ༭��
}

void ChatPanel::getMsg(QString &str)
{
    ui->editChat->append(str);
}