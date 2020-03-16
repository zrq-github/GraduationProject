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
    void slot_btnLogon_clicked();     //登录按钮_点击事件
    void slot_btnRegister_clicked();
    void slot_btnForgetPaswd_clicked();
private:
    Ui::LogonPanel *ui;
    QTcpSocket *socket;
protected:
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LOGONPANEL_H
