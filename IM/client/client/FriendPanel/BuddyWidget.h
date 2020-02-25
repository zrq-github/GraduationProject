#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include "friendpanel_global.h"

class FRIENDPANEL_EXPORT BuddyWidget : public QWidget
{
    Q_OBJECT

public:
    QLabel *head;  //头像  
    QLabel *name;  //用户名  
    QLabel *sign;  //个性签名  
    QString headPath;//头像路径
public:
    BuddyWidget(QWidget *parent = Q_NULLPTR);
    ~BuddyWidget();
private:

    void createUi();

    bool eventFilter(QObject *obj, QEvent *event);//事件过滤器  
};
