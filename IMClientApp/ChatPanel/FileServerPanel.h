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
    QFile *locFile;         //�����͵��ļ�

    qint64 totalBytes;      //�ܹ��跢�͵��ֽ���
    qint64 bytesWritten;    //�ѷ����ֽ���
    qint64 bytesTobeWrite;  //�����͵��ֽ���
    qint64 payloadSize;     //����ʼ��һ������
    QByteArray outBlock;    //����һ�η��͵�����

    QTcpSocket *clntConn;   //�ͷ������ӵ��׽���

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