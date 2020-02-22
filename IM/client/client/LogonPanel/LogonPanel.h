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

class LOGONPANEL_EXPORT LogonPanel : public QDialog
{
    Q_OBJECT

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
    void    readSettings();         //��ȡ����,��ע���(���ߴӱ������ã�
    void    writeSettings();        //д������,��ע���(���ߴӱ�������)

    QString encrypt(const QString& str);    //�ַ�������MD5
private slots:
    void on_btnLogon_clicked();     //��¼��ť_����¼�
public:
    LogonPanel(QWidget *parent = Q_NULLPTR);
    ~LogonPanel();

    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::LogonPanel *ui;
};

#endif // LOGONPANEL_H
