#ifndef FileServerPanel_H
#define FileServerPanel_H

#include <QDialog>
#include <QTime>
#include "chatpanel_global.h"

namespace Ui { class FileServerPanel; };
class QFile;
class QTcpServer;
class QTcpSocket;

class CHATPANEL_EXPORT FileServerPanel : public QDialog
{
    Q_OBJECT

public:
     explicit FileServerPanel(QWidget *parent = Q_NULLPTR);
    ~FileServerPanel();

    void initSrv();
    void refused();
    void setAcceptID(QString userID);
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::FileServerPanel *ui;

    qint16 tPort;
    QTcpServer *tSrv;
    QString fileName;
    QString theFileName;
    QFile *locFile;         //待发送的文件

    qint64 totalBytes;      //总共需发送的字节数
    qint64 bytesWritten;    //已发送字节数
    qint64 bytesTobeWrite;  //待发送的字节数
    qint64 payloadSize;     //被初始化一个常量
    QByteArray outBlock;    //缓存一次发送的数据

    QTcpSocket *clntConn;   //客服端连接的套接字

    QTime time;
    QString m_userID;
private slots:
    void sndMsg();
    void updClntProgress(qint64 numBytes);

    void on_btnOpen_clicked();
    void on_btnSend_clicked();
    void on_btnClose_clicked();

};

#endif