#include "ChatPanel.h"
#include "ui_ChatPanel.h"
#include <QLineEdit>
#include <QDateTime>
#include <QDebug>
#include "AppSettings/AppSettings.h"
#include <QFile>
#include <QFileDialog>
#include "FileCilentPanel.h"
#include "FileServerPanel.h"
#include "DataCenter/IMQTcpWord.h"
#include "DataCenter/DataAnalysis.h"
#include "DataCenter/DataCenter.h"
#include <QMessageBox>
#include "AppSettings/AppPath.h"
#include "VideoChatPanel.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

QString ChatPanel::getTitle()
{
    return ui->labName->text();
}

void ChatPanel::setFriendMsg(QString & chtId, QString & msg)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");

    dealMessage(m_chatID, current_date,msg);
}

void ChatPanel::closeEvent(QCloseEvent * event)
{//关闭前发送信号
    emit signClose(m_chatID);
}

ChatPanel::ChatPanel(QString id,QString name, QWidget *parent)
    : QWidget(parent)
    ,m_videoChat(NULL)
{
    this->m_chatID = id;
    this->m_chatName = name;

    ui = new Ui::ChatPanel();
    ui->setupUi(this);
    createUi();
    binSign();
}

ChatPanel::~ChatPanel()
{
    delete ui;
}

void ChatPanel::createUi()
{
    ui->textEdit->setReadOnly(true);
    ui->labName->setText(QString("%1(%2)").arg(m_chatName, m_chatID));


    qDebug() << IMPATH::ImgPath("img_btn_video_chat.png");
    ui->btnVideoChat->setIcon(QIcon(IMPATH::ImgPath("img_btn_video_chat.png")));
    ui->btnVideoChat->setIconSize(QSize(20, 20));
}

void ChatPanel::binSign()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //发送文本事件
}

void ChatPanel::dealMessage(QString & sendId, QString & time, QString & data)
{
    QString qstr = sendId + " " + time + "\n" + data + "\n";
    ui->textEdit->append(qstr);
}

void ChatPanel::hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename)
{
    int btn = QMessageBox::information(this, tr("接受文件"), tr("来自%1(%2)的文件：%3,是否接收？").arg(usrname).arg(srvaddr).arg(filename), QMessageBox::Yes, QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        QString name = QFileDialog::getSaveFileName(0, tr("保存文件"), filename);
        if (!name.isEmpty())
        {
            FileCilentPanel *clnt = new FileCilentPanel(this);
            clnt->setFileName(name);
            clnt->setHostAddr(QHostAddress(srvaddr));
            clnt->show();
        }
    }
    else 
    {
        //拒接应该处理的语句
    }
}

void ChatPanel::slot_btnSend_click()
{
    UserInfoPtr myInfo = DataCenterInst.getMyInfo();    //拿到个人的信息
    //拿到文本
    QString strMsg = ui->editSend->toPlainText();
    ui->editSend->setText("");
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");
    dealMessage(myInfo->id, current_date, strMsg);//ui交互

    //封装
    MsgInfo msgInfo(MsgType::USERMSG, myInfo->id, m_chatID, strMsg);
    QByteArray byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void ChatPanel::on_btnSendFile_clicked()
{
    fileSrv = new FileServerPanel(this);
    connect(fileSrv, &FileServerPanel::signFileName, this, &ChatPanel::slotSendFile);

    fileSrv->show();
    fileSrv->initSrv();
}

void ChatPanel::on_btnVideoChat_clicked()
{
    if (m_videoChat == NULL)
    {
        m_videoChat = new VideoChatPanel(m_chatID + "(" + m_chatName + ")");
    }
    m_videoChat->show();

    MsgInfo msgInfo;// (MsgType::VIDEOCHAT, IMUSERID, m_chatID, nullptr, IMQTcpSocket->peerAddress().toString());

    QByteArray &byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
}

void ChatPanel::slotSendFile(QString file)
{
    MsgInfo msgInfo;// (MsgType::FILENAME, IMUSERID, m_chatID, file, IMQTcpSocket->peerAddress().toString());

    QByteArray &byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
    //emit signSendFile(byte);
}

void ChatPanel::slotSaveFile(QByteArray)
{
}

void ChatPanel::slotVidelChat(MsgInfo info)
{
    if (info.msgType == MsgType::VIDEOCHAT)
    {
        QString address = info.address;
        int btn = QMessageBox::information(this, tr("视频请求"), tr("来自%1(%2)的视频请求").arg(m_chatName).arg(address), QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes)
        {
            if (m_videoChat == NULL)
            {
                m_videoChat = new VideoChatPanel(m_chatID + "(" + m_chatName + ")");
                m_videoChat->show();
                m_videoChat->setAddress(address);   //拿到对方的ip地址
                m_videoChat->setIsTransfer(true);   //将自己的摄像头数据传输给对方
                //提示对方，我已经接受你的视频请求，让对方开始传输数据
                MsgInfo msgInfo;// (MsgType::VIDEOCHATACCEPT, IMUSERID, m_chatID, IMQTcpSocket->peerAddress().toString());

                QByteArray byte = DataAnalysis::byteFromMsgInfo(msgInfo);
                IMQTcpSocket->write(byte);
            }
        }
        else
        {
            //拒接应该处理的语句
        }
    }
    else if (info.msgType == MsgType::VIDEOCHATACCEPT)
    {
        m_videoChat->setIsTransfer(true);
    }
}

