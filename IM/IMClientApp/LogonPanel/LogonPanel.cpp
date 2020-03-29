#include "LogonPanel.h"
#include "ui_LogonPanel.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QSettings>
#include "AppSettings/AppSettings.h"
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include "RegisterPanel.h"
#include "IMQTcpWord/IMQTcpWord.h"
#include <QJsonObject>
#include <QJsonDocument>
#include "NetSettingsPanel.h"
#include "Base/DeftData.h"
#include "Base/IMQJson.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

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

void LogonPanel::writeLocalSettings()
{
    IMSettings.setLogonSettings("userId", ui->editUser->text().trimmed());
    bool isSavePswd = ui->chkboxSavePswd->isChecked();
    if (isSavePswd)
    {
        IMSettings.setLogonSettings("userPswd", ui->editPswd->text().trimmed());
        IMSettings.setLogonSettings("isRemember", true);
    }
    else
    {
        IMSettings.setSetting("LogonSettings", "rememberPswd", false);
    }
}

void LogonPanel::bindSigns()
{
    //ui控件绑定
    connect(ui->btnLogon, &QPushButton::clicked, this, &LogonPanel::slot_btnLogon_clicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LogonPanel::slot_btnRegister_clicked);
    connect(ui->btnForgetPasw, &QPushButton::clicked, this, &LogonPanel::slot_btnForgetPaswd_clicked);
    connect(ui->btnNetSet, &QPushButton::clicked, this, &LogonPanel::slot_btnNetSet_clicked);

    connect(IMQTcpSocket, &QTcpSocket::connected, this, &LogonPanel::slotServerConnected);
    connect(IMQTcpSocket, &QTcpSocket::readyRead, this, &LogonPanel::slotServerData);
}

void LogonPanel::slot_btnRegister_clicked()
{
    RegisterPanel *panel = new RegisterPanel(this);
    panel->exec();
}

void LogonPanel::slot_btnForgetPaswd_clicked()
{
    RegisterPanel *panel = new RegisterPanel(this,1);
    panel->exec();
}

void LogonPanel::slot_btnNetSet_clicked()
{
    NetSettingsPanel *netSet = new NetSettingsPanel(this);
    netSet->show();
}

void LogonPanel::slotServerConnected()
{//成功连接后,发送账号密码验证
    //验证账号密码
    QString user = ui->editUser->text().trimmed();  //用户名
    QString pswd = ui->editPswd->text().trimmed();  //密码

    QByteArray  byte = IMQJson::getQJsonByte(MsgType::USERLOGIN, "server" , user, pswd);

    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void LogonPanel::slotServerData()
{
    QJsonDocument document = QJsonDocument::fromJson(IMQTcpSocket->readAll());
    QJsonObject object = document.object();

    int type = object.value("msgType").toInt();
    QString to = object.value("to").toString();
    QString from = object.value("from").toString();

    switch (type)
    {
    case MsgType::USERLOGINSUCCEED:
    {
        IMSettings.setUserID(to);
        this->accept();
        break;
    }
    case MsgType::USERLOGINDEFEAT:
    {
        QMessageBox::information(NULL, "错误", "账号密码不正确");
        break;
    }
    default:
        break;
    }
}

void LogonPanel::slot_btnLogon_clicked()
{
    if (IMQTcpSocket->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        slotServerConnected();
    }
    else
    {
        //尝试连接服务器
        QString addr = IMSettings.getSetting("server", "ip").toString();
        quint16 port = IMSettings.getSetting("server", "port").toInt();

        IMQTcpSocket->connectToHost(addr, port);
    }

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

    bindSigns();
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
