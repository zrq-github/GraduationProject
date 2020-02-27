#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include "friendpanel_global.h"

class FRIENDPANEL_EXPORT BuddyWidget : public QWidget
{
    Q_OBJECT

public:
    BuddyWidget(QWidget *parent = Q_NULLPTR);
    ~BuddyWidget();
public:
    QLabel *labHead;  //头像

    QLabel *m_id;       //用户id
    QLabel *m_name;     //用户名  
    QLabel *m_sign;     //个性签名
    QString m_headPath; //头像路径
    bool    isOnLine;
public:

private:
    void createUi();
    void setData(QString &name, QString &sign, QString &headPath);
    void mouseReleaseEvent(QMouseEvent *event); 

signals:
    void signMouseRelease();
};
