/*
** 登录界面
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
    bool    m_moving = false;       //表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;              //上一次的鼠标位置
private:
    void readLocalSettings();
    void writeLocalSettings();

    void bindSigns();
private slots:
    void slot_btnLogon_clicked();               //登录按钮
    void slot_btnRegister_clicked();            //注册
    void slot_btnForgetPaswd_clicked();         //忘记密码
    void slot_btnNetSet_clicked();              //网络设置

    void slotServerConnected();
    void slotServerData();
private:
    Ui::LogonPanel *ui;
protected:
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LOGONPANEL_H
