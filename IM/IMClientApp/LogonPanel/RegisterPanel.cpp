#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

RegisterPanel::RegisterPanel(QWidget *parent,int type)
    : QDialog(parent)
{
    ui = new Ui::RegisterPanel();
    ui->setupUi(this);
    this->bindSigns();

    this->m_type = type;
    if (m_type)
    {
        this->changeUi();
    }

}

RegisterPanel::~RegisterPanel()
{
    delete ui;
}

void RegisterPanel::bindSigns()
{
    //�ڲ��ؼ�
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterPanel::slot_btnRegister_clicked);
}

void RegisterPanel::changeUi()
{
    ui->btnRegister->setText("�޸�����");
    this->setWindowTitle("�޸�����");
}

void RegisterPanel::slot_btnRegister_clicked()
{   //���ӷ�����
    if (this->m_type)
    {//����ע����֤
    }
    else
    {//�����޸�������֤

    }
}
