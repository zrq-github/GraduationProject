#ifndef FRIENDLISTWIDGET_H_
#define FRIENDLISTWIDGET_H_

#include <QListWidget>
#include "DataCenter/BaseDataType.h"
#include "friendpanel_global.h"

class QLabel;
class QMenu;

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    FriendItem(QWidget *parent = Q_NULLPTR);
    ~FriendItem();

    void setData(UserInfo &userInfo);
    void setHead(QString path/*img path*/);
    void setHead(QPixmap pixmap);   //这个函数调用可以有问题，先不要调用
    void setName(QString name);
    void setSign(QString sign);
    void setWarn(bool warn);

    UserInfo & getUserInfo();
private:
    void createUi();

    QLabel *m_labHead;
    QLabel *m_labName;
    QLabel *m_labSign;
    QLabel *m_labWarn;
    UserInfo m_userInfo;
};

class FRIENDPANEL_EXPORT FriendListWidget : public QListWidget
{
    Q_OBJECT

public:
    FriendListWidget(QWidget *parent);
    ~FriendListWidget();

    void initTest();
    void addGroup(QString groupName="未命名");
    void addFriend(UserInfo info, QString groupName);
private:
    void initMenu();    //初始化菜单
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    QMenu *blankMenu;   //点击空白上的菜单  
    QMenu *groupMenu;   //点击组上的菜单  
    QMenu *personMenu;  //点击人上的菜单  

    QHash<QString, QListWidgetItem*> m_groupHash;     //QString 组名  QListWidgetItem 组对象  组名所对应的item

    QMap<QListWidgetItem*, QListWidgetItem*> groupMap;   // 组 - key:项(组+好友项) value:组  
    QMap<QListWidgetItem*, bool> isHideMap;//用来判断该组是否隐藏了

    QLineEdit *groupNameEdit;//组的名字，重命名的时候需要用到  
    QListWidgetItem *currentItem;//当前的项 
signals:
    void signUserInfo(UserInfo &);

private slots :
    void slotAddGroup();    //添加组
    void slotDelGroup();   //删除组  
    void slotAddBuddy();   //添加好友  
    void slotDelBuddy();   //删除好友  
    void slotRename();     //重命名组  
    void slotRenameEditFshed();//命名完成  
};
#endif
