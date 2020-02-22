/*
** 登录界面
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
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;       //表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;              //上一次的鼠标位置

    QString m_user = "user";        //初始化用户名
    QString m_pswd = "12345";       //初始化密码，未加密的

    int m_tryCount = 0;             //试错次数

    bool m_encrypt = false;         //是否加密
private:
    void    readSettings();         //读取设置,从注册表(或者从本地配置）
    void    writeSettings();        //写入设置,从注册表(或者从本地配置)

    QString encrypt(const QString& str);    //字符串加密MD5
private slots:
    void on_btnLogon_clicked();     //登录按钮_点击事件
public:
    LogonPanel(QWidget *parent = Q_NULLPTR);
    ~LogonPanel();

    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::LogonPanel *ui;
};

#endif // LOGONPANEL_H
