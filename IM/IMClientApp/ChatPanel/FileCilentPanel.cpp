#include "FileCilentPanel.h"
#include "ui_FileCilentPanel.h"
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

FileCilentPanel::FileCilentPanel(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::FileCilentPanel();
    ui->setupUi(this);

    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tClnt = new QTcpSocket(this);
    tPort = 5555;
    connect(tClnt, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(tClnt, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErr(QAbstractSocket::SocketError)));
}

FileCilentPanel::~FileCilentPanel()
{
    delete ui;
}

void FileCilentPanel::setHostAddr(QHostAddress addr)
{
    hostAddr = addr;
    newConn();
}

void FileCilentPanel::setFileName(QString name)
{
    locFile = new QFile(name);
}

void FileCilentPanel::closeEvent(QCloseEvent *)
{
    on_btnClose_clicked();
}

void FileCilentPanel::newConn()
{
    blockSize = 0;
    tClnt->abort();
    tClnt->connectToHost(hostAddr, tPort);
    time.start();
}

void FileCilentPanel::readMsg()
{
    QDataStream in(tClnt);
    in.setVersion(QDataStream::Qt_4_7);

    float useTime = time.elapsed();

    if (bytesReceived <= sizeof(qint64) * 2) {
        if ((tClnt->bytesAvailable() >= sizeof(qint64) * 2) && (fileNameSize == 0))
        {
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }
        if ((tClnt->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)) {
            in >> fileName;
            bytesReceived += fileNameSize;

            if (!locFile->open(QFile::WriteOnly)) {
                QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件 %1:\n%2.").arg(fileName).arg(locFile->errorString()));
                return;
            }
        }
        else {
            return;
        }
    }
    if (bytesReceived < totalBytes) {
        bytesReceived += tClnt->bytesAvailable();
        inBlock = tClnt->readAll();
        locFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->labStatus->setText(tr("已接收 %1MB (%2MB/s) \n共%3MB 已用时：%4秒\n估计剩余时间：%5秒")
        .arg(bytesReceived / (1024 * 1024))
        .arg(speed * 1000 / (1024 * 1024), 0, 'f', 2)
        .arg(totalBytes / (1024 * 1024))
        .arg(useTime / 1000, 0, 'f', 0)
        .arg(totalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));

    if (bytesReceived == totalBytes)
    {
        locFile->close();
        tClnt->close();
        ui->labStatus->setText(tr("接收文件 %1 完毕").arg(fileName));
    }
}

void FileCilentPanel::displayErr(QAbstractSocket::SocketError sockErr)
{
    switch (sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError: break;
    default: qDebug() << tClnt->errorString();
    }
}

void FileCilentPanel::on_btnCancle_clicked()
{
    tClnt->abort();
    if (locFile->isOpen())
        locFile->close();
}

void FileCilentPanel::on_btnClose_clicked()
{
    tClnt->abort();
    if (locFile->isOpen())
        locFile->close();
    close();
}
