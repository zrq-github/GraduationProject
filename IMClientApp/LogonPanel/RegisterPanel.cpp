#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"
#include "QDebugTool/QDebugTool.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

RegisterPanel::RegisterPanel(QWidget *parent,int type)
    : QDialog(parent)
{
    ui = new Ui::RegisterPanel();
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    this->bindSigns();

    this->m_type = type;
    if (m_type)
    {   //根据类型动态变化对话框
        this->changeUi();
    }

    QDEBUG_CONSOLE(QString("new registerp panel"));
}

RegisterPanel::~RegisterPanel()
{
    QDEBUG_CONSOLE(QString("delete registerp panel"));
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

bool RegisterPanel::verifyAccount(QString strId)
{
    return false;
}

bool RegisterPanel::verifyAccountPawd(QString strPawd)
{
    return false;
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
