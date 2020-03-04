#pragma once
/*
** 好友界面
*/

#include "friendpanel_global.h"
#include <QToolBox>  
#include <QMap>

class BuddyWidget;

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
    void addFriend(QWidget *page, QString id, QString name, QString sign, QString headPath);     //添加好友
    void addGroup(QString groupName);

    bool eventFilter(QObject *obj, QEvent *event);
private:
    QMap<QString, QWidget*> *listGroup;         //分组列表
    QMap<QString, QString>   *list;             //好友在哪个分组中

    void init();
signals:
    void childClick(QString &id,QString &name);      //自定义子空间点击事件

private slots:
    void slotAddFriend();
    void slotAddGroup();    //添加组
};
