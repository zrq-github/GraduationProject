#pragma once
/*
** 好友界面
*/

#include "friendpanel_global.h"
#include <QListWidget>  

class FRIENDPANEL_EXPORT FriendPanel :public QListWidget
{
    Q_OBJECT

public: 
    explicit FriendPanel(QWidget *parent= Q_NULLPTR);
    ~FriendPanel();
private:
    void createUi();
public:

    QMap<QListWidgetItem*, QListWidgetItem*> groupMap;   // 组容器 - key:
    QMap<QListWidgetItem*, bool> isHideMap;//用来判断该组是否隐藏了

    QLineEdit *groupNameEdit;       //组的名字，重命名的时候需要用到  
    QListWidgetItem *currentItem;   //当前的项  

public slots:
    void slotAddGroup();    //添加组  
    void slotDelGroup();    //删除组  
    void slotAddBuddy();    //添加好友  
    void slotDelBuddy();    //删除好友 
};
