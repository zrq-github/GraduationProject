#include "LogonPanel.h"
#include "ui_LogonPanel.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QSettings>
#include "AppSettings/AppSettings.h"

void LogonPanel::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);
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

void LogonPanel::readLocalSettings()
{
    QString lastId = IMSettings.getLogonSettings("userID").toString();    //上次登录的用户
    bool isRememberPswd = IMSettings.getLogonSettings("isRemember").toBool(); //是否记住密码
    if (isRememberPswd)
    {
        QString lastPasw = IMSettings.getLogonSettings("userPswd").toString(); //取得密码
        ui->editPswd->setText(lastPasw);
    }
    ui->chkboxSavePswd->setChecked(isRememberPswd);
    ui->editUser->setText(lastId);
}

void LogonPanel::readSettings()
{

}

void LogonPanel::writeSettings()
{

}

void LogonPanel::on_btnLogon_clicked()
{
    QString user = ui->editUser->text().trimmed();  //用户名
    QString pswd = ui->editPswd->text().trimmed();  //密码

    //连接数据库


    if (true)
    {   //成功,修改上次登录用户
        IMSettings.setLogonSettings("userId", user);
        bool isSavePswd=ui->chkboxSavePswd->isChecked();
        if (isSavePswd)
        {
            IMSettings.setLogonSettings("userPswd", pswd);
            IMSettings.setLogonSettings("isRemember", true);
        }
        else
        {
            IMSettings.setSetting("LogonSettings", "rememberPswd", false);
        }
        this->accept();    //对话框 accept()，关闭对话框，
    }
    else
    {   //登录失败
        QMessageBox::about(this, "错误", "用户密码不正确");
    }

   ////现在用注册表代替
   // if ((user == m_user) && (encrptPSWD == m_pswd)) //如果用户名和密码正确
   // {
   //     writeSettings();   //保存设置
   //     this->accept();    //对话框 accept()，关闭对话框，

   //     //QMessageBox::about(this,"成功", "用户密码正确");
   // }
   // else
   // {
   //     m_tryCount++;      //错误次数应该有数据库返回
   //     if (m_tryCount > 3)
   //     {
   //         QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
   //         this->reject(); //退出
   //     }
   //     else
   //     {
   //         QMessageBox::warning(this, "错误提示", "用户名或密码错误");
   //     }
   // }
}

QString LogonPanel::encrypt(const QString & str)
{
    return str;
    //QByteArray btArray;
    //btArray.append(str);

    //QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法
    //hash.addData(btArray);  //添加数据到加密哈希值
    //QByteArray resultArray = hash.result();  //返回最终的哈希值
    //QString md5 = resultArray.toHex();//转换为16进制字符串

    //return  md5;
}

LogonPanel::LogonPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::LogonPanel();
    ui->setupUi(this);
    ui->editPswd->setEchoMode(QLineEdit::Password);     //设置为密码输入模式
    this->setAttribute(Qt::WA_DeleteOnClose);           //设置为关闭时删除
    //this->setWindowFlags(Qt::SplashScreen);             //设置为SplashScreen, 窗口无边
    this->setWindowFlags(Qt::FramelessWindowHint);      //无边框，但是在任务显示对话框标题

    ui->btnMinimize->installEventFilter(this);      //安装事件过滤器
    ui->btnClose->installEventFilter(this);

    //{   //给对话框加上最小化
    //    Qt::Window    s flags = Qt::Dialog;
    //    flags |= Qt::WindowMinimizeButtonHint;
    //    flags |= Qt::WindowCloseButtonHint;;
    //    setWindowFlags(flags);
    //}

    readLocalSettings();  //读取本地配置
}

LogonPanel::~LogonPanel()
{
    delete ui;
}

bool LogonPanel::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (obj == ui->btnClose)
            {
                this->close();
                return true;
            }
            if (obj = ui->btnMinimize)
            {
                this->showMinimized();
                return true;
            }
            return QWidget::eventFilter(obj, event);
        }
        return QWidget::eventFilter(obj, event);
    }
    else
    {
        // pass the event on to the parent class
        return QWidget::eventFilter(obj, event);
    }
}
