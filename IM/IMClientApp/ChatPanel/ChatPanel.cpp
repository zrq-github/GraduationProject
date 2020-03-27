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
#include "Base/IMQJson.h"
#include "Base/DeftData.h"
#include "IMQTcpWord/IMQTcpWord.h"
#include <QMessageBox>

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

void ChatPanel::slotSendFile(QString file)
{
    QByteArray byte = IMQJson::getQJsonFile(MsgType::FILENAME, m_chatID, IMUSERID, IMQTcpSocket->localAddress().toString(), file);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
    //emit signSendFile(byte);
}

void ChatPanel::slotSaveFile(QByteArray)
{
}
