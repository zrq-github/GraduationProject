#ifndef FileCilentPanel_H
#define FileCilentPanel_H

#include <QDialog>
#include <QTextCharFormat>
#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>

class QTcpSocket;
namespace Ui { class FileCilentPanel; };

class FileCilentPanel : public QDialog
{
    Q_OBJECT

public:
    explicit FileCilentPanel(QWidget *parent=Q_NULLPTR);
    ~FileCilentPanel();

    void setHostAddr(QHostAddress addr);    //获取发送端IP地址
    void setFileName(QString name);         //获取文件保存路径
    void setAcceptID(QString userID);
protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::FileCilentPanel *ui;

    QTcpSocket *tClnt;
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;

    qint64 totalBytes;      //需要接受的总字节数
    qint64 bytesReceived;   //已接受的字节数
    qint64 fileNameSize;    //文件的大小
    QString fileName;       //文件的名字
    QFile *locFile;         //当前文件的路径
    QByteArray inBlock;     //接受缓存区

    QTime time;
    QString m_userID;
private slots:
    void newConn();
    void readMsg();
    void displayErr(QAbstractSocket::SocketError sockErr);
    void on_btnCancle_clicked();
    void on_btnClose_clicked();
};
#endif