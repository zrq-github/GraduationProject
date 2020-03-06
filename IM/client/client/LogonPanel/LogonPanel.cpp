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

void LogonPanel::readSettings()
{
    QString lastId = appSettingsInstance.getSetting("LogonSettings", "lastLogonId").toString();     //上次登录的用户
    bool isRememberPswd = appSettingsInstance.getSetting("LogonSettings", "rememberPswd").toBool(); //是否记住密码
    if (isRememberPswd)
    {
        QString lastPasw = appSettingsInstance.getSetting("LogonSettings", "lastLogonPswd").toString(); //取得密码
        ui->editPswd->setText(lastPasw);
    }
    ui->chkboxSavePswd->setChecked(isRememberPswd);
    ui->editUser->setText(lastId);

    //QString organization = "IM";    //用于注册表
    //QString appName = "user";       //HKEY_CURRENT_USER/Software/IM/user
    //QSettings settings(organization, appName);//创建注册表信息

    ////数据库加入后更改,这样注册表只能实现单人登录
    //bool saved = settings.value("saved", false).toBool();       //读取 saved键的值
    //m_user = settings.value("Username", "user").toString();     //读取 Username 键的值，缺省为“user”
    //QString defaultPSWD = encrypt("12345");                     //缺省密码"12345"加密后的数据
    //m_pswd = settings.value("PSWD", defaultPSWD).toString();    //读取PSWD 键的值，
    // 
    //if (saved)
    //{
    //    ui->editUser->setText(m_user);
    //    ui->editPswd->setText(m_pswd);
    //    ui->chkboxSavePswd->setChecked(saved);
    //}
}

void LogonPanel::writeSettings()
{

    //QSettings  settings("IM", "user"); //注册表键组
    //settings.setValue("Username", m_user); //用户名
    //settings.setValue("PSWD", m_pswd);   //密码，经过加密的
    //settings.setValue("saved", ui->chkboxSavePswd->isChecked());
}

void LogonPanel::on_btnLogon_clicked()
{
    QString user = ui->editUser->text().trimmed();  //用户名
    QString pswd = ui->editPswd->text().trimmed();  //密码

    //连接数据库
    if (true)
    {//成功,修改上次登录用户
        appSettingsInstance.setSetting("LogonSettings", "lastLogonId", user);
        bool isSavePswd=ui->chkboxSavePswd->isChecked();
        if (isSavePswd)
        {
            appSettingsInstance.setSetting("LogonSettings", "lastLogonPswd", pswd);
            appSettingsInstance.setSetting("LogonSettings", "rememberPswd", true);
        }
        else
        {
            appSettingsInstance.setSetting("LogonSettings", "rememberPswd", false);
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

    readSettings();  //读取存储的用户名和密码
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
