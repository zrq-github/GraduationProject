#include "FriendPanel.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QLineEdit>
#include <QMouseEvent>
#include "BuddyWidget.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


FriendPanel::FriendPanel(QWidget * parent)
    :QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);        // 去除item选中时的虚线边框  
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭  
    createUi();
}

FriendPanel::~FriendPanel()
{
}

void FriendPanel::createUi()
{
    groupNameEdit = new QLineEdit;
    slotAddGroup();
}



void FriendPanel::slotAddGroup()
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(QString::fromUtf8("../Images/arrowRight")), "未命名");    //创建一个Item
    newItem->setSizeHint(QSize(this->width(), 25));//设置宽度、高度
    this->addItem(newItem);         //加到QListWidget中
    groupMap.insert(newItem, newItem);//加到容器groupMap里，key和value都为组
    isHideMap.insert(newItem, true);  //设置该组隐藏状态

    BuddyWidget *buddy = new BuddyWidget;   //创建一个自己定义的信息类
    buddy->m_headPath = ":/head";                          //设置头像路径
    buddy->m_name->setText("逍遥圣帝");                  //设置用户名
    buddy->m_sign->setText("用通俗的语言，讲深刻的技术。");   //设置个性签名

    QListWidgetItem *newItem1 = new QListWidgetItem();       //创建一个newItem
    this->addItem(newItem1);
    this->setItemWidget(newItem1, buddy);
}

void FriendPanel::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //遍历该组的所有好友和自身的组
    {
        groupMap.remove(item);   //移除
        delete item;   //删除
    }
    isHideMap.remove(currentItem); //移除
}

void FriendPanel::slotAddBuddy()
{
    BuddyWidget *buddy = new BuddyWidget;   //创建一个自己定义的信息类
    buddy->m_headPath = ":/head";                          //设置头像路径
    buddy->m_name->setText("逍遥圣帝");                  //设置用户名
    buddy->m_sign->setText("用通俗的语言，讲深刻的技术。");   //设置个性签名
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//当前组对应的项（包括组本身和好友）复制给tem
    //关键代码
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    this->insertItem(row(currentItem) + tem.count(), newItem); //将该newItem插入到后面
    this->setItemWidget(newItem, buddy); //将buddy赋给该newItem
    groupMap.insert(newItem, currentItem);   //加进容器，key为好友，value为组
    if (isHideMap.value(currentItem))          //如果该组是隐藏，则加进去的好友设置为隐藏
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示
        newItem->setHidden(false);
}

void FriendPanel::slotDelBuddy()
{
    groupMap.remove(currentItem);  //移除该好友
    delete currentItem;            //删除
}