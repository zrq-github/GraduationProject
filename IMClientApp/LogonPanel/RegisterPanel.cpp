#include "RegisterPanel.h"
#include "ui_RegisterPanel.h"
#include "QDebugTool/QDebugTool.h"
#include "ConfigCenter/ConfigCenter.h"
#include "DataCenter/BaseDataType.h"
#include "DataCenter/DataAnalysis.h"
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
#include <QHostAddress>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

RegisterPanel::RegisterPanel(QWidget *parent,int type)
    : QDialog(parent)
    , m_socket(nullptr)
{
    ui = new Ui::RegisterPanel();
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    m_socket = new QTcpSocket(this);

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
    m_socket->disconnectFromHost();
    this->disconnect();
    delete ui;
}

void RegisterPanel::bindSigns()
{
    //内部控件
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterPanel::slot_btnRegister_clicked);
    //网络信号绑定
    connect(m_socket, &QTcpSocket::disconnected, this, []() {qDebug() << "RegisterPanel socket disconnected!"; });
    connect(m_socket, &QTcpSocket::readyRead, this, &RegisterPanel::slot_sockt_readData);
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

void RegisterPanel::slot_sockt_readData()
{
    QByteArray byte = m_socket->readAll();
    MsgInfo msgInfo = DataAnalysis::msgFromJsonByte(byte);

    if (msgInfo.msgType == MsgType::USERCHANGEPASSWORD)
    {
        if (msgInfo.msg == "1")
        {//修改成功
            QMessageBox::about(this, QString("修改密码"), QString("密码修改成功"));
            this->close();
        }
        else
        {
            QMessageBox::about(this, QString("修改密码"), QString("密码修改失败"));
        }
        return;
    }

    if (msgInfo.msgType == MsgType::USERLOGINREGISTER)
    {
        if (msgInfo.msg == "1")
        {//新增用户成功
            QMessageBox::about(this, QString("注册"), QString("注册成功"));
            this->close();
        }
        else
        {
            QMessageBox::about(this, QString("注册"), QString("注册失败"));
        }
        return;
    }
}

void RegisterPanel::slot_btnRegister_clicked()
{//连接服务器
    QString addr = IMSettings.getSetting("server", "ip").toString();
    quint16 port = IMSettings.getSetting("server", "port").toInt();
    QString userId = ui->editID->text();
    QString userPswd = ui->editPswd->text();
    QString userPswd2 = ui->editUserPswd_2->text();

    if (userPswd != userPswd2)
    {//再次密码一样
        QMessageBox::about(this, QString("错误"), QString("两次输入的密码不一致"));
        return;
    }

    m_socket->connectToHost(addr, port);
    if (m_socket->waitForConnected(1000))
        qDebug("Connected!");

    if (m_socket->state() == QAbstractSocket::SocketState::ConnectedState)
    {
        if (this->m_type==0)
        {//进行注册验证

            MsgInfo info(MsgType::USERLOGINREGISTER, userId, nullptr, userPswd2, m_socket->peerAddress().toString(), m_socket->peerPort());
            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);

            m_socket->write(byte);
            m_socket->flush();
        }
        else if(this->m_type == 1)
        {//进行修改密码验证
            MsgInfo info(MsgType::USERCHANGEPASSWORD, userId, nullptr, userPswd2, m_socket->peerAddress().toString(), m_socket->peerPort());
            QByteArray byte = DataAnalysis::byteFromMsgInfo(info);

            m_socket->write(byte);
            m_socket->flush();
        }
    }
}
