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
class VerificationCodeLabel;
class QLabel;
class QLineEdit;
class QPushButton;

class VerifyWidget :public QDialog
{
    Q_OBJECT
public:
    VerifyWidget(QWidget *parent = Q_NULLPTR);
    ~VerifyWidget();
public:
    bool eventFilter(QObject *object, QEvent *event);
private:
    void createUI();
    void bindSlots();
    VerificationCodeLabel *m_verifyLab;
    QLineEdit *m_verifyEdit;
    QPushButton *m_verifyBtn;
    QLabel *m_verifyState;
private slots:
    void slot_verifyBtn_clicked();
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
    int verifyState = 0;
private:
    void creatUI();
    void readLocalSettings();
    void writeLocalSettings();

    void bindSigns();
private slots:
    void on_btnLogon_clicked();                 //��¼��ť
    void on_btnRegister_clicked();              //ע��
    void on_btnForgetPasw_clicked();           //��������
    void on_btnNetSet_clicked();                //��������

    void slotLogonSucceed();
    void slotServerConnected();
    void slotServerData();

    void slotSocketError(QAbstractSocket::SocketError);
private:
    Ui::LogonPanel *ui;
    QMovie *movie;
    VerifyWidget *m_verifyWidget;
protected:
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // LOGONPANEL_H
