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
    //内部控件
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterPanel::slot_btnRegister_clicked);
}

void RegisterPanel::changeUi()
{
    ui->btnRegister->setText("修改密码");
    this->setWindowTitle("修改密码");
}

void RegisterPanel::slot_btnRegister_clicked()
{   //连接服务器
    if (this->m_type)
    {//进行注册验证
    }
    else
    {//进行修改密码验证

    }
}
