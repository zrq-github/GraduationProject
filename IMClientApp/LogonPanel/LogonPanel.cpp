#include "LogonPanel.h"
#include "ui_LogonPanel.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QCryptographicHash>
#include <QMovie>
#include <QSettings>
#include <QHostAddress>
#include "ConfigCenter/ConfigCenter.h"
#include "QtUITool/QImageTool.h"
#include "RegisterPanel.h"
#include "NetSettingsPanel.h"
#include "DataCenter/BaseDataType.h"
#include "DataCenter/IMQTcpWord.h"
#include "DataCenter/DataAnalysis.h"
#include "VerificationCodeLabel.h"

#include "QDebugTool/QDebugTool.h"

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
        move(event->globalPos()- m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void LogonPanel::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    m_moving = false; //停止移动
}

void LogonPanel::creatUI()
{
    QPixmap pixmap;

    ui->editPswd->setEchoMode(QLineEdit::Password);     //设置为密码输入模式
    this->setAttribute(Qt::WA_DeleteOnClose);           //设置为关闭时删除
    //this->setWindowFlags(Qt::SplashScreen);             //设置为SplashScreen, 窗口无边
    this->setWindowFlags(Qt::FramelessWindowHint);      //无边框，但是在任务显示对话框标题

    movie = new QMovie(this);
    movie->setFileName(IMPATH::ImgPath("img_logon_backgroud.gif"));
    movie->setScaledSize(QSize(540, 210));
    this->ui->label->setMovie(movie);
    this->ui->label->setGeometry(0, 0, 540, 210);
    movie->start();

    pixmap.load(IMPATH::ImgPath("img_logon_logo.png"));
    ui->lab_logo->setScaledContents(true);
    this->ui->lab_logo->setPixmap(pixmap);

    this->ui->btnNetSet->setText(NULL);
    pixmap.load(IMPATH::ImgPath("img_btn_set.png"));
    this->ui->btnNetSet->setIcon(QIcon(pixmap));

    pixmap.load(IMPATH::ImgPath("img_logon_default_head.png"));
    ui->lab_head->setScaledContents(true);
    this->ui->lab_head->setPixmap(QImageTool::generatePixmap(IMPATH::ImgPath("img_logon_default_head.png"), 100));
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

    //IMSettings.setLogonSettings("userId", ui->editUser->text().trimmed());
    //bool isSavePswd = ui->chkboxSavePswd->isChecked();
    //if (isSavePswd)
    //{
    //    IMSettings.setLogonSettings("userPswd", ui->editPswd->text().trimmed());
    //    IMSettings.setLogonSettings("isRemember", true);
    //}
    //else
    //{
    //    IMSettings.setSetting("LogonSettings", "rememberPswd", false);
    //}
}

void LogonPanel::bindSigns()
{
    connect(&IMQTcpWord::getInstance(), &IMQTcpWord::signLogonSucceed, this, &LogonPanel::slotLogonSucceed);
}

void LogonPanel::on_btnLogon_clicked()
{
    //启动验证
    if (m_verifyWidget == nullptr && verifyState == 0)
    {
        m_verifyWidget = new VerifyWidget;
        verifyState = m_verifyWidget->exec();
    }
    else if(verifyState == 0)
    {
        verifyState = m_verifyWidget->exec();
    }

    if (verifyState == QDialog::Accepted)
    {//验证成功
        QDEBUG_CONSOLE(QString("clicked logon"));
        if (IMQTcpSocket->state() == QAbstractSocket::SocketState::ConnectedState)
        {   //tcp已连接
            QString user = ui->editUser->text().trimmed();  //用户名
            QString pswd = ui->editPswd->text().trimmed();  //密码

            MsgInfo info(MsgType::USERLOGIN, user, nullptr, pswd, IMQTcpSocket->peerAddress().toString(), IMQTcpSocket->peerPort());

            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);
            IMQTcpSocket->write(byte);
            IMQTcpSocket->flush();
        }
        else
        {   //tcp未连接
            QString addr = IMSettings.getSetting("server", "ip").toString();
            quint16 port = IMSettings.getSetting("server", "port").toInt();
            IMQTcpWordInstance.connectHost(addr, port);
        }
    }
    else if (verifyState == QDialog::Rejected)
    {//验证失败
        qDebug() << "验证失败";
    }


}

void LogonPanel::on_btnRegister_clicked()
{
    QDEBUG_CONSOLE(QString("clicked register"));
    RegisterPanel *panel = new RegisterPanel(this);
    panel->exec();
}

void LogonPanel::on_btnForgetPasw_clicked()
{
    QDEBUG_CONSOLE(QString("clicked forgetpaswd"));
    RegisterPanel *panel = new RegisterPanel(this, 1);
    panel->exec();
}

void LogonPanel::on_btnNetSet_clicked()
{
    QDEBUG_CONSOLE(QString("clicked netset"));
    NetSettingsPanel *netSet = new NetSettingsPanel(this);
    netSet->exec();
}

void LogonPanel::slotLogonSucceed()
{
    if (ui->chkboxSavePswd->checkState() == Qt::Checked)
    {//记住密码被点击
        IMSettings.setLogonSettings("userID", ui->editUser->text());
        IMSettings.setLogonSettings("userPswd", ui->editPswd->text());
        IMSettings.setLogonSettings("isRemember", true);
    }
    else
    {
        IMSettings.setLogonSettings("isRemember", false);
    }
    this->accept();
}

void LogonPanel::slotServerConnected()
{
}

void LogonPanel::slotServerData()
{
}

void LogonPanel::slotSocketError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QAbstractSocket::SocketError::ConnectionRefusedError)
    {
        qDebug() << "The connection was refused by the peer (or timed out)";
        QMessageBox::information(NULL, "网络连接错误", "The connection was refused by the peer (or timed out)");
    }
}

LogonPanel::LogonPanel(QWidget *parent)
    : QDialog(parent)
    , m_verifyWidget(nullptr)
{
    ui = new Ui::LogonPanel();
    ui->setupUi(this);
    ui->btnMinimize->installEventFilter(this);      //安装事件过滤器
    ui->btnClose->installEventFilter(this);

    creatUI();
    bindSigns();
    readLocalSettings();  //读取本地配置
    QDEBUG_CONSOLE("new LogonPanel");
}

LogonPanel::~LogonPanel()
{
    QDEBUG_CONSOLE("delete LogonPanel and dis all connect");
    this->disconnect();
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

VerifyWidget::VerifyWidget(QWidget *parent)
    : QDialog(parent)
    , m_verifyLab(nullptr)
    , m_verifyEdit(nullptr)
    , m_verifyBtn(nullptr)
{
    this->setWindowTitle(QString("验证码"));
    this->setFixedSize(400, 120);
    this->setAttribute(Qt::WA_DeleteOnClose);           //设置为关闭时删除
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    this->createUI();
    this->bindSlots();

    m_verifyLab->installEventFilter(this);
}

VerifyWidget::~VerifyWidget()
{
}

bool VerifyWidget::eventFilter(QObject * object, QEvent * event)
{
    return false;
}

void VerifyWidget::createUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    m_verifyLab = new VerificationCodeLabel(this);
    m_verifyLab->setGeometry(0, 0, 150, 70);
    layout->addWidget(m_verifyLab);

    m_verifyEdit = new QLineEdit(this);
    m_verifyEdit->setGeometry(160, 30, 100, 25);
    layout->addWidget(m_verifyEdit);

    m_verifyState = new QLabel(this);
    m_verifyState->setFixedSize(this->width(), 20);
    m_verifyState->setText(QString("请输入验证码，该验证码区分大小写"));
    layout->addWidget(m_verifyState);

    m_verifyBtn = new QPushButton(this);
    m_verifyBtn->setObjectName(QString("btnVerify"));
    m_verifyBtn->setGeometry(140, 80, 80, 30);
    m_verifyBtn->setText(QString("确定"));
    layout->addWidget(m_verifyBtn);
}

void VerifyWidget::bindSlots()
{
    connect(m_verifyBtn, &QPushButton::clicked, this, &VerifyWidget::slot_verifyBtn_clicked);
}

void VerifyWidget::slot_verifyBtn_clicked()
{
    QString userCode = m_verifyEdit->text();
    QString realCode = m_verifyLab->getVerify();
    if (QString::compare(userCode, realCode) == 0)
    {//两个数相等
        this->accept();
    }
    else
    {
        m_verifyState->setText("验证码错误，请重新输入");
        m_verifyLab->refreshVerify();//刷新验证码
    }
}

