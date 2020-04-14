/*
** ��¼����
*/

#ifndef LOGONPANEL_H
#define LOGONPANEL_H

#include <QDialog>
#include "logonpanel_global.h"
#include <QtNetwork/QTcpSocket>
namespace Ui 
{ 
    class LogonPanel; 
};

class LOGONPANEL_EXPORT LogonPanel : public QDialog
{
    Q_OBJECT
public:
    LogonPanel(QWidget *parent = Q_NULLPTR);
    ~LogonPanel();

private:
    bool    m_moving = false;       //��ʾ�����Ƿ������������ƶ�
    QPoint  m_lastPos;              //��һ�ε����λ��
private:
    void creatUI();
    void readLocalSettings();
    void writeLocalSettings();

    void bindSigns();
private slots:
    void slot_btnLogon_clicked();               //��¼��ť
    void slot_btnRegister_clicked();            //ע��
    void slot_btnForgetPaswd_clicked();         //��������
    void slot_btnNetSet_clicked();              //��������

    void slotServerConnected();
    void slotServerData();

    void slotSocketError(QAbstractSocket::SocketError);
private:
    Ui::LogonPanel *ui;
protected:
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LOGONPANEL_H
