#include "FileServerPanel.h"
#include "ui_FileServerPanel.h"

#include <QFile>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "DataCenter/IMQTcpWord.h"
#include "DataCenter/BaseDataType.h"
#include "DataCenter/DataCenter.h"
#include "DataCenter/DataAnalysis.h"
#include <QByteArray>
#include <QHostAddress>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

FileServerPanel::FileServerPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::FileServerPanel();
    ui->setupUi(this);

    tPort = 5555;
    tSrv = new QTcpServer(this);
    connect(tSrv, SIGNAL(newConnection()), this, SLOT(sndMsg()));

    initSrv();
}

FileServerPanel::~FileServerPanel()
{
    delete ui;
}

void FileServerPanel::initSrv()
{
    payloadSize = 64 * 1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesTobeWrite = 0;

    ui->labStatus->setText(tr("请选择要传送的文件"));
    ui->progressBar->reset();
    ui->btnOpen->setEnabled(true);
    ui->btnSend->setEnabled(false);

    tSrv->close();
}

void FileServerPanel::refused()
{
    tSrv->close();
    ui->labStatus->setText(tr("对方拒绝接收！"));
}

void FileServerPanel::closeEvent(QCloseEvent *)
{
    on_btnClose_clicked();
}

void FileServerPanel::sndMsg()
{  //用户确认后,
    ui->btnSend->setEnabled(false);
    clntConn = tSrv->nextPendingConnection();   //拿到连接方的socket
    connect(clntConn, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));

    ui->labStatus->setText(tr("开始传送文件 %1 ！").arg(theFileName));

    locFile = new QFile(fileName);
    if (!locFile->open((QFile::ReadOnly))) {
        QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件 %1:\n%2").arg(fileName).arg(locFile->errorString()));
        return;
    }
    totalBytes = locFile->size();   //计算文件的总大小
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    time.start();  // 开始计时
    QString curFile = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
    sendOut << qint64(0) << qint64(0) << curFile;
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);  
    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));    //包头包含发送数据的大小
    bytesTobeWrite = totalBytes - clntConn->write(outBlock);                    //待发送的字节=总字节-发送缓冲区的字节
    outBlock.resize(0); //缓冲区清0
}

void FileServerPanel::updClntProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += (int)numBytes;
    if (bytesTobeWrite > 0) {
        outBlock = locFile->read(qMin(bytesTobeWrite, payloadSize));
        bytesTobeWrite -= (int)clntConn->write(outBlock);
        outBlock.resize(0);
    }
    else {
        locFile->close();
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->labStatus->setText(tr("已发送 %1MB (%2MB/s) \n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
        .arg(bytesWritten / (1024 * 1024))
        .arg(speed * 1000 / (1024 * 1024), 0, 'f', 2)
        .arg(totalBytes / (1024 * 1024))
        .arg(useTime / 1000, 0, 'f', 0)
        .arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));

    if (bytesWritten == totalBytes) 
    {
        locFile->close();
        tSrv->close();
        ui->labStatus->setText(tr("传送文件 %1 成功").arg(theFileName));
    }
}


void FileServerPanel::on_btnOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
        ui->labStatus->setText(tr("要传送的文件为：%1 ").arg(theFileName));
        ui->btnSend->setEnabled(true);
        ui->btnOpen->setEnabled(false);
    }
}

void FileServerPanel::on_btnSend_clicked()
{
    QString sIP = IMQTcpSocket->peerAddress().toString();

    if (!tSrv->listen(IMQTcpSocket->peerAddress(), tPort))//开始监听
    {
        qDebug() << tSrv->errorString();
        close();
        return;
    }
    ui->labStatus->setText(tr("等待对方接收... ..."));

    UserInfoPtr &userInfo = DataCenterInst.getMyInfo();
    MsgInfo info(MsgType::FILENAME, userInfo->id, m_userID, fileName, sIP, tPort);
    QByteArray byte = DataAnalysis::byteFromMsgInfo(info);
    IMQTcpSocket->write(byte);
    IMQTcpSocket->flush();
}

void FileServerPanel::on_btnClose_clicked()
{
    if (tSrv->isListening())
    {
        tSrv->close();
        //if (locFile->isOpen())
        //    locFile->close();
        clntConn->abort();
    }
    this->close();
}

void FileServerPanel::setAcceptID(QString userID)
{
    m_userID = userID;
}
