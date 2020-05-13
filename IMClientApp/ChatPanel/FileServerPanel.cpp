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

    ui->labStatus->setText(tr("��ѡ��Ҫ���͵��ļ�"));
    ui->progressBar->reset();
    ui->btnOpen->setEnabled(true);
    ui->btnSend->setEnabled(false);

    tSrv->close();
}

void FileServerPanel::refused()
{
    tSrv->close();
    ui->labStatus->setText(tr("�Է��ܾ����գ�"));
}

void FileServerPanel::closeEvent(QCloseEvent *)
{
    on_btnClose_clicked();
}

void FileServerPanel::sndMsg()
{  //�û�ȷ�Ϻ�,
    ui->btnSend->setEnabled(false);
    clntConn = tSrv->nextPendingConnection();   //�õ����ӷ���socket
    connect(clntConn, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));

    ui->labStatus->setText(tr("��ʼ�����ļ� %1 ��").arg(theFileName));

    locFile = new QFile(fileName);
    if (!locFile->open((QFile::ReadOnly))) {
        QMessageBox::warning(this, tr("Ӧ�ó���"), tr("�޷���ȡ�ļ� %1:\n%2").arg(fileName).arg(locFile->errorString()));
        return;
    }
    totalBytes = locFile->size();   //�����ļ����ܴ�С
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    time.start();  // ��ʼ��ʱ
    QString curFile = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
    sendOut << qint64(0) << qint64(0) << curFile;
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);  
    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));    //��ͷ�����������ݵĴ�С
    bytesTobeWrite = totalBytes - clntConn->write(outBlock);                    //�����͵��ֽ�=���ֽ�-���ͻ��������ֽ�
    outBlock.resize(0); //��������0
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
    ui->labStatus->setText(tr("�ѷ��� %1MB (%2MB/s) \n��%3MB ����ʱ:%4��\n����ʣ��ʱ�䣺%5��")
        .arg(bytesWritten / (1024 * 1024))
        .arg(speed * 1000 / (1024 * 1024), 0, 'f', 2)
        .arg(totalBytes / (1024 * 1024))
        .arg(useTime / 1000, 0, 'f', 0)
        .arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));

    if (bytesWritten == totalBytes) 
    {
        locFile->close();
        tSrv->close();
        ui->labStatus->setText(tr("�����ļ� %1 �ɹ�").arg(theFileName));
    }
}


void FileServerPanel::on_btnOpen_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
        ui->labStatus->setText(tr("Ҫ���͵��ļ�Ϊ��%1 ").arg(theFileName));
        ui->btnSend->setEnabled(true);
        ui->btnOpen->setEnabled(false);
    }
}

void FileServerPanel::on_btnSend_clicked()
{
    QString sIP = IMQTcpSocket->peerAddress().toString();

    if (!tSrv->listen(IMQTcpSocket->peerAddress(), tPort))//��ʼ����
    {
        qDebug() << tSrv->errorString();
        close();
        return;
    }
    ui->labStatus->setText(tr("�ȴ��Է�����... ..."));

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
