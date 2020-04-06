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
#include "IMQTcpWord/IMQTcpWord.h"
#include <QMessageBox>
#include "Base/IMQTransport.h"
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
{//�ر�ǰ�����ź�
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

    qDebug() << IMPATH::appImgPath("img_btn_video_chat.png");
    ui->btnVideoChat->setIcon(QIcon(IMPATH::appImgPath("img_btn_video_chat.png")));
    ui->btnVideoChat->setIconSize(QSize(20, 20));
}

void ChatPanel::binSign()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //�����ı��¼�
}

void ChatPanel::dealMessage(QString & sendId, QString & time, QString & data)
{
    QString qstr = sendId + " " + time + "\n" + data + "\n";
    ui->textEdit->append(qstr);
}

void ChatPanel::hasPendingFile(QString usrname, QString srvaddr, QString clntaddr, QString filename)
{
    int btn = QMessageBox::information(this, tr("�����ļ�"), tr("����%1(%2)���ļ���%3,�Ƿ���գ�").arg(usrname).arg(srvaddr).arg(filename), QMessageBox::Yes, QMessageBox::No);
    if (btn == QMessageBox::Yes) {
        QString name = QFileDialog::getSaveFileName(0, tr("�����ļ�"), filename);
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
        //�ܽ�Ӧ�ô�������
    }
}

void ChatPanel::slot_btnSend_click()
{
    //�õ��ı�
    QString msg = ui->editSend->toPlainText();
    ui->editSend->setText("");
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");

    dealMessage(IMUSERID, current_date, msg);//ui����

    emit signSendMessage(m_chatID, msg);
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

    MsgInfo msgInfo;
    msgInfo.msgType = MsgType::VIDEOCHAT;
    msgInfo.to = m_chatID;
    msgInfo.from = IMUSERID;
    msgInfo.address = IMQTcpSocket->peerAddress().toString();

    QByteArray &byte = IMQPROTOCOL::getMsgQByteArray(msgInfo);
    IMQTcpSocket->write(byte);
}

void ChatPanel::slotSendFile(QString file)
{
    MsgInfo msgInfo;
    msgInfo.msgType = MsgType::FILENAME;
    msgInfo.to = m_chatID;
    msgInfo.from = IMUSERID;
    msgInfo.msg = file;
    msgInfo.address = IMQTcpSocket->peerAddress().toString();

    QByteArray &byte = IMQPROTOCOL::getMsgQByteArray(msgInfo);
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
        int btn = QMessageBox::information(this, tr("��Ƶ����"), tr("����%1(%2)����Ƶ����").arg(m_chatName).arg(address), QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes)
        {
            if (m_videoChat == NULL)
            {
                m_videoChat = new VideoChatPanel(m_chatID + "(" + m_chatName + ")");
                m_videoChat->show();
                m_videoChat->setAddress(address);   //�õ��Է���ip��ַ
                m_videoChat->setIsTransfer(true);   //���Լ�������ͷ���ݴ�����Է�
                //��ʾ�Է������Ѿ����������Ƶ�����öԷ���ʼ��������
                MsgInfo msgInfo;
                msgInfo.msgType = MsgType::VIDEOCHATACCEPT;
                msgInfo.to = m_chatID;
                msgInfo.from = IMUSERID;
                msgInfo.address = IMQTcpSocket->peerAddress().toString();
                QByteArray &byte = IMQPROTOCOL::getMsgQByteArray(msgInfo);
                IMQTcpSocket->write(byte);
            }
        }
        else
        {
            //�ܽ�Ӧ�ô�������
        }
    }
    else if (info.msgType == MsgType::VIDEOCHATACCEPT)
    {
        m_videoChat->setIsTransfer(true);
    }
}

