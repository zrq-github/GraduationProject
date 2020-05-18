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
#include "DataCenter/BaseDataType.h"
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
    this->disconnect();
    delete ui;
}

void ChatPanel::createUi()
{
    ui->textEdit->setReadOnly(true);
    ui->labName->setText(QString("%1(%2)").arg(m_chatName, m_chatID));

    ui->btnSendFile->setIcon(QIcon(IMPATH::ImgPath("floder.png", "Resources//FileIcon")));


    ui->btnSendFile->setIconSize(QSize(20, 20));
    qDebug() << IMPATH::ImgPath("img_btn_video_chat.png");
    ui->btnVideoChat->setIcon(QIcon(IMPATH::ImgPath("img_btn_video_chat.png")));
    ui->btnVideoChat->setIconSize(QSize(20, 20));
}

void ChatPanel::binSign()
{
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //�����ı��¼�
    connect(&IMQTcpWord::getInstance(), &IMQTcpWord::signFileName, this, &ChatPanel::slotSaveFile); //��������ļ�
    connect(&IMQTcpWord::getInstance(), &IMQTcpWord::signVideoChat, this, &ChatPanel::slotVidelChat);//������Ƶ����
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
        //�ܽ�Ӧ�ô��������
    }
}

void ChatPanel::slot_btnSend_click()
{
    UserInfoPtr myInfo = DataCenterInst.getMyInfo();    //�õ����˵���Ϣ
    //�õ��ı�
    QString strMsg = ui->editSend->toPlainText();
    ui->editSend->setText("");
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");
    dealMessage(myInfo->id, current_date, strMsg);//ui����

    //��װ
    MsgInfo msgInfo(MsgType::USERMSG, myInfo->id, m_chatID, strMsg);
    QByteArray byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void ChatPanel::on_btnSendFile_clicked()
{
    fileSrv = new FileServerPanel(this);

    fileSrv->initSrv();
    fileSrv->setAcceptID(m_chatID);
    fileSrv->show();
    
}

void ChatPanel::on_btnVideoChat_clicked()
{
    if (m_videoChat == NULL)
    {
        m_videoChat = new VideoChatPanel(m_chatID + "(" + m_chatName + ")");
    }
    m_videoChat->show();

    UserInfoPtr &userInfo = DataCenterInst.getMyInfo();
    MsgInfo msgInfo(MsgType::VIDEOCHAT, userInfo->id, m_chatID, QString::number(MsgType::VIDEOCHATACCEPT), IMQTcpSocket->peerAddress().toString());

    QByteArray &byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void ChatPanel::slotSaveFile(MsgInfo msgInfo)
{
    this->hasPendingFile(msgInfo.from, msgInfo.address, nullptr, msgInfo.msg);
}

void ChatPanel::slotSendFile(QString file)
{
    MsgInfo msgInfo;// (MsgType::FILENAME, IMUSERID, m_chatID, file, IMQTcpSocket->peerAddress().toString());

    QByteArray &byte = DataAnalysis::byteFromMsgInfo(msgInfo);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
    //emit signSendFile(byte);
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

                UserInfoPtr userInfo = DataCenterInst.getMyInfo();
                MsgInfo msgInfo(MsgType::VIDEOCHATACCEPT, userInfo->id, m_chatID,
                    QString::number(MsgType::VIDEOCHATACCEPT), IMQTcpSocket->peerAddress().toString());

                QByteArray byte = DataAnalysis::byteFromMsgInfo(msgInfo);
                IMQTcpSocket->write(byte);
            }
        }
    }
    else if (info.msgType == MsgType::VIDEOCHATACCEPT)
    {//������Ƶ�����¼�
        m_videoChat->setIsTransfer(true);
    }
    else if (info.msgType == MsgType::VIDEOCHATREFUSE)
    {//�ܽ�Ӧ�ô��������

    }
}
