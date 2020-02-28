#pragma once
/*
** 好友界面
*/

#include "friendpanel_global.h"
#include <QToolBox>  
#include <QMap>

class FRIENDPANEL_EXPORT FriendPanel :public QToolBox
{
    Q_OBJECT

public: 
    explicit FriendPanel(QWidget *parent= Q_NULLPTR);
    ~FriendPanel();
private:
    void createUi();
    void binSlots();
public:
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void childClick(QString &id,QString &name);      //自定义子空间点击事件
private slots:
    void slotAddGroup();    //添加组
};
