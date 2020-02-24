#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{

    QString s;
    s=ui->lineEdit->text();
    ptr=new Widget(0,s);




    this->hide();
    ptr->show();
}
