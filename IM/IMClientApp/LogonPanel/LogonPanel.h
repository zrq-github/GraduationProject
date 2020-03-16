/*
** ��¼����
*/

#ifndef LOGONPANEL_H
#define LOGONPANEL_H

#include <QDialog>
#include "logonpanel_global.h"
namespace Ui 
{ 
    class LogonPanel; 
};
class QTcpSocket;

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
    void readLocalSettings();
    void writeLocalSettings();

    void bindSigns();
private slots:
    void slot_btnLogon_clicked();     //��¼��ť_����¼�
    void slot_btnRegister_clicked();
    void slot_btnForgetPaswd_clicked();
private:
    Ui::LogonPanel *ui;
    QTcpSocket *socket;
protected:
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LOGONPANEL_H
