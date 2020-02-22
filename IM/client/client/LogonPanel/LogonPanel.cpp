﻿
#include "LogonPanel.h"
#include "ui_LogonPanel.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QSettings>

void LogonPanel::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        //记录下鼠标相对于窗口的位置
        //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
        //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);  //
}

void LogonPanel::mouseMoveEvent(QMouseEvent * event)
{
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (m_moving && (event->buttons() && Qt::LeftButton)
        && (event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void LogonPanel::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    m_moving = false; //停止移动
}

void LogonPanel::readSettings()
{
    QString organization = "IM";    //用于注册表
    QString appName = "user";       //HKEY_CURRENT_USER/Software/IM/user
    QSettings settings(organization, appName);//创建注册表信息

    //数据库加入后更改,这样注册表只能实现单人登录
    bool saved = settings.value("saved", false).toBool();       //读取 saved键的值
    m_user = settings.value("Username", "user").toString();     //读取 Username 键的值，缺省为“user”
    QString defaultPSWD = encrypt("12345");                     //缺省密码"12345"加密后的数据
    m_pswd = settings.value("PSWD", defaultPSWD).toString();    //读取PSWD 键的值，

    if (saved)
    {
        ui->editUser->setText(m_user);
        ui->chkboxSavePswd->setChecked(saved);
    }
}

void LogonPanel::writeSettings()
{
    QSettings  settings("IM", "user"); //注册表键组
    settings.setValue("Username", m_user); //用户名
    settings.setValue("PSWD", m_pswd);   //密码，经过加密的
    settings.setValue("saved", ui->chkboxSavePswd->isChecked());
}

void LogonPanel::on_btnLogon_clicked()
{
    QString user = ui->editUser->text().trimmed();  //用户名
    QString pswd = ui->editPswd->text().trimmed();  //密码

    QString encrptPSWD = encrypt(pswd); //对输入密码进行加密
   //连接数据库，判断密码是否正确

   //现在用注册表代替
    if ((user == m_user) && (encrptPSWD == m_pswd)) //如果用户名和密码正确
    {
        writeSettings();   //保存设置
        //this->accept();    //对话框 accept()，关闭对话框，
        QMessageBox::about(this,"成功", "用户密码正确");
    }
    else
    {
        m_tryCount++;      //错误次数应该有数据库返回
        if (m_tryCount > 3)
        {
            QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
            this->reject(); //退出
        }
        else
        {
            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
        }
    }
}

QString LogonPanel::encrypt(const QString & str)
{
    QByteArray btArray;
    btArray.append(str);

    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法
    hash.addData(btArray);  //添加数据到加密哈希值
    QByteArray resultArray = hash.result();  //返回最终的哈希值
    QString md5 = resultArray.toHex();//转换为16进制字符串

    return  md5;
}

LogonPanel::LogonPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::LogonPanel();
    ui->setupUi(this);
    ui->editPswd->setEchoMode(QLineEdit::Password);     //设置为密码输入模式
    this->setAttribute(Qt::WA_DeleteOnClose);           //设置为关闭时删除
    this->setWindowFlags(Qt::SplashScreen);             //设置为SplashScreen, 窗口无边
    //this->setWindowFlags(Qt::FramelessWindowHint);      //无边框，但是在任务显示对话框标题

    readSettings();  //读取存储的用户名和密码
}

LogonPanel::~LogonPanel()
{
    delete ui;
}