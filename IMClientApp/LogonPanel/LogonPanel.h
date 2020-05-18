/*
** 登录界面
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
    bool    m_moving = false;       //表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;              //上一次的鼠标位置
    int verifyState = 0;
private:
    void creatUI();
    void readLocalSettings();
    void writeLocalSettings();

    void bindSigns();
private slots:
    void on_btnLogon_clicked();                 //登录按钮
    void on_btnRegister_clicked();              //注册
    void on_btnForgetPasw_clicked();           //忘记密码
    void on_btnNetSet_clicked();                //网络设置

    void slotLogonSucceed();
    void slotServerConnected();
    void slotServerData();

    void slotSocketError(QAbstractSocket::SocketError);
private:
    Ui::LogonPanel *ui;
    QMovie *movie;
    VerifyWidget *m_verifyWidget;
protected:
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // LOGONPANEL_H
