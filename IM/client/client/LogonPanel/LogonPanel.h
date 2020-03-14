/*
** ��¼����
*/

#ifndef LOGONPANEL_H
#define LOGONPANEL_H

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

#include <QDialog>
#include "logonpanel_global.h"
namespace Ui { class LogonPanel; };
class QTcpSocket;

class LOGONPANEL_EXPORT LogonPanel : public QDialog
{
    Q_OBJECT
public:
    LogonPanel(QWidget *parent = Q_NULLPTR);
    ~LogonPanel();
protected:
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;       //��ʾ�����Ƿ������������ƶ�
    QPoint  m_lastPos;              //��һ�ε����λ��

    QString m_user = "user";        //��ʼ���û���
    QString m_pswd = "12345";       //��ʼ�����룬δ���ܵ�

    int m_tryCount = 0;             //�Դ����

    bool m_encrypt = false;         //�Ƿ����
private:
    void readLocalSettings();
    void writeLocalSettings();
    bool verifyID(QString &id,QString &pasw);       //��֤�˺������Ƿ���ȷ
    void bindSigns();


    QString encrypt(const QString& str);    //�ַ�������MD5
private slots:
    void slot_btnLogon_clicked();     //��¼��ť_����¼�
    void slotSocketRead();
    void slotSocketConnected();       //���������ӳɹ�ִ��
public:


    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::LogonPanel *ui;
    QTcpSocket *socket;
};

#endif // LOGONPANEL_H
