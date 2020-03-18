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
{//�ر�ǰ�����ź�
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
    //��ʼ������ֵ
    m_chatID = "0000";
    m_chatName = "";

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
    if (m_chatID != id || m_chatName != name)
    {
        ui->editChat->clear();      //����������� �ı����
        ui->editSend->clear();

        this->m_chatID = id;
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