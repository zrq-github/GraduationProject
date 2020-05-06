#include "FriendListWidget.h"
#include "QBaseUi/QImageLable.h"
#include "AppSettings/AppPath.h"
#include"QtUITool/QImageTool.h"
#include <QLineEdit>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include "DataCenter/BaseDataType.h"
#include <QDebug>

#pragma execution_character_set("utf-8")

FriendItem::FriendItem(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    setFixedSize(160, 70);
    createUi();
}

FriendItem::~FriendItem()
{
    delete m_labHead;
    delete m_labName;
    delete m_labSign;
}

void FriendItem::setData(UserInfo & userInfo)
{
    //if (userInfo.id != nullptr)
    //    this->m_userInfo.id = userInfo.id;
    //if (userInfo.imgPath != nullptr)
    //    this->m_userInfo.imgPath = userInfo.imgPath;
    //if (userInfo.name != nullptr)
    //    this->m_userInfo.name = userInfo.name;
    this->m_userInfo = userInfo;

    m_labHead->setPixmap(QImageTool::generatePixmap(m_userInfo.imgPath, 100));
    m_labName->setText(QString(m_userInfo.name));
    m_labSign->setText(QString(m_userInfo.sign));
}

void FriendItem::setHead(QString path)
{
    m_userInfo.imgPath = path;
    m_labHead->setPixmap(QImageTool::generatePixmap(path, 100));
}

void FriendItem::setHead(QPixmap pixmap)
{
    m_labHead->setPixmap(pixmap);
}

void FriendItem::setName(QString name)
{
    m_userInfo.name = name;
    m_labName->setText(QString(name));
}

void FriendItem::setSign(QString sign)
{
    m_userInfo.sign = sign;
    m_labSign->setText(QString(sign));
}

void FriendItem::setWarn(bool warn)
{
    if (warn)
        m_labWarn->show();
    else
        m_labWarn->hide();
}

UserInfo & FriendItem::getUserInfo()
{
    // TODO: 在此处插入 return 语句
    return m_userInfo;
}

void FriendItem::createUi()
{
    m_labHead = new QLabel(this);
    m_labHead->setGeometry(10, 10, 50, 50);
    m_labHead->setScaledContents(true);
    m_labHead->setPixmap(QImageTool::generatePixmap(IMPATH::ImgPath("img_logon_default_head.png"), 100));

    m_labName = new QLabel(this);
    m_labName->setGeometry(70, 10, 100, 20);
    m_labName->setText(QString("你的名字"));

    m_labSign = new QLabel(this);
    m_labSign->setGeometry(70, 40, 100, 20);
    m_labSign->setText(QString("你的简介"));

    m_labWarn = new QLabel(this);
    m_labWarn->setGeometry(140, 30, 15, 15);
    m_labWarn->setStyleSheet(
        "background-color:red;"
    );
    m_labWarn->setFrameStyle(QFrame::Box | QFrame::Raised);
}

FriendListWidget::FriendListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框  
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条关闭  
    this->initMenu();

    //this->setStyleSheet("QListWidget{ background:white; color:black; border:none; } "
    //    "QListWidget::item{ border:none; height: 100px; }"
    //    "QListWidget::item:hover{ background:rgb(252,240,193) } "
    //    "QListWidget::item:selected{ background:rgb(252,233,161); color:black; }");
    this->initTest();
}

FriendListWidget::~FriendListWidget()
{
}

void FriendListWidget::initTest()
{
    addGroup("我的好友");
    addGroup("黑名单");

    UserInfo info;
    info.id = QString("1");
    info.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info.name = QString("我是一号");
    info.sign = QString("我骄傲，我自由放纵");
    addFriend(info, QString("我的好友"));

    UserInfo info1;
    info1.id = QString("2");
    info1.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info1.name = QString("我是二号");
    info1.sign = QString("我很开始啦，我是二号");
    addFriend(info1, QString("我的好友"));

    UserInfo info2;
    info2.id = QString("3");
    info2.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info2.name = QString("我是三号");
    info2.sign = QString("有本事你就拉黑我");
    addFriend(info2, QString("黑名单"));
}

void FriendListWidget::addGroup(QString groupName)
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(AppPath::ImgPath("arrow_normal.png")),groupName,this);
    newItem->setSizeHint(QSize(this->width(), 25)); //设置高度、宽度
    this->addItem(newItem);
    groupMap.insert(newItem, newItem);
    isHideMap.insert(newItem, true);  //设置该组隐藏状态 
    m_groupHash.insert(groupName, newItem);
}

void FriendListWidget::addFriend(UserInfo info, QString groupName)
{
    FriendItem *buddy = new FriendItem(this);
    buddy->setData(info);
    buddy->setWarn(false);

    QListWidgetItem* groupItem = m_groupHash.value(groupName);

    QList<QListWidgetItem*> tem = groupMap.keys(groupItem);//当前组对应的项（包括组本身和好友）复制给tem  
    //关键代码  
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem 
    newItem->setSizeHint(buddy->size());
    this->insertItem(row(groupItem) + tem.count(), newItem); //将该newItem插入到后面  
    this->setItemWidget(newItem, buddy); //将buddy赋给该newItem  
    groupMap.insert(newItem, groupItem);   //加进容器，key为好友，value为组  
    if (isHideMap.value(groupItem))          //如果该组是隐藏，则加进去的好友设置为隐藏  
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示  
        newItem->setHidden(false);
}

void FriendListWidget::initMenu()
{//初始化
    blankMenu = new QMenu();
    groupMenu = new QMenu();
    personMenu = new QMenu();
    groupNameEdit = new QLineEdit();
    QAction *addGroup = new QAction("添加分组", this);
    QAction *delGroup = new QAction("删除该组", this);
    QAction *rename = new QAction("重命名", this);
    QAction *addBuddy = new QAction("添加好友", this);
    QAction *delBuddy = new QAction("删除好友", this);
    //设置：  
    groupNameEdit->setParent(this);  //设置父类  
    groupNameEdit->hide(); //设置初始时隐藏  
    groupNameEdit->setPlaceholderText("未命名");//设置初始时的内容  
    //布局：  
    blankMenu->addAction(addGroup);
    groupMenu->addAction(delGroup);
    groupMenu->addAction(rename);
    groupMenu->addAction(addBuddy);
    personMenu->addAction(delBuddy);
    //信息槽：  
    connect(groupNameEdit, SIGNAL(editingFinished()), this, SLOT(slotRenameEditFshed()));
    connect(addGroup, SIGNAL(triggered()), this, SLOT(slotAddGroup()));
    connect(delGroup, SIGNAL(triggered()), this, SLOT(slotDelGroup()));
    connect(rename, SIGNAL(triggered()), this, SLOT(slotRename()));
    connect(addBuddy, SIGNAL(triggered()), this, SLOT(slotAddBuddy()));
    connect(delBuddy, SIGNAL(triggered()), this, SLOT(slotDelBuddy()));
}

void FriendListWidget::mousePressEvent(QMouseEvent * event)
{
    QListWidget::mousePressEvent(event); // 如果不调用基类mousePressEvent，item被select会半天不响应,调用父类，让QSS起效，因为QSS基于父类QListWidget，子类就是子窗口，就是最上层窗口，是覆盖在父窗口上的，所以先于父窗口捕获消息  
    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//鼠标位置的Item，不管右键左键都获取
    qDebug() << "execute mousePressEvent" << currentItem;
    if (currentItem == nullptr)
        return;

    if (groupNameEdit->isVisible() && !(groupNameEdit->rect().contains(event->pos())))
    {
        if (groupNameEdit->text() != NULL)
            currentItem->setText(groupNameEdit->text());
        groupNameEdit->setText("");
        groupNameEdit->hide();
    }

    if (event->button() == Qt::LeftButton && currentItem != NULL && currentItem == groupMap.value(currentItem))//如果点击的左键并且是点击的是组  
    {
        if (isHideMap.value(currentItem))                                  //如果先前是隐藏，则显示  
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）  
                if (subItem != currentItem)                                 //如果是组的话不进行处理  
                {
                    subItem->setHidden(false);                            //好友全部显示  
                }
            isHideMap.insert(currentItem, false);                          //设置该组为显示状态  
            //currentItem->setIcon(QIcon(":/arrowDown"));
        }
        else                                                             //否则，先前是显示，则隐藏  
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//遍历组的对应的项（包括自身和好友）  
                if (subItem != currentItem)                                 //如果是组的话不进行处理  
                {
                    subItem->setHidden(true);                            //好友全部隐藏  
                }
            isHideMap.insert(currentItem, true);                          //设置该组为隐藏状态  
            //currentItem->setIcon(QIcon(":/arrowRight"));
        }
    }

}

void FriendListWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    qDebug() << "execute mouseDoubleClickEvent" << currentItem;
    FriendItem *friendWidget = static_cast<FriendItem*> (this->itemWidget(currentItem));
    
    if (friendWidget != nullptr)
    {
        qDebug() << "execute mouseDoubleClickEvent" << friendWidget;
        emit signUserInfo(friendWidget->getUserInfo());
    }
}

void FriendListWidget::contextMenuEvent(QContextMenuEvent * event)
{
    if (currentItem == NULL)                           //如果点击到的是空白处  
    {
        blankMenu->exec(QCursor::pos());
        return;
    }
    if (currentItem == groupMap.value(currentItem))    // 如果点击到的是组  
        groupMenu->exec(QCursor::pos());
    else                                            //否则点击到的是好友  
        personMenu->exec(QCursor::pos());
}

void FriendListWidget::slotAddGroup()
{
    addGroup("nihao ");
    //QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/arrowRight"), "未命名");    //创建一个Item  

    //newItem->setSizeHint(QSize(this->width(), 25));//设置宽度、高度  
    //this->addItem(newItem);         //加到QListWidget中  
    //groupMap.insert(newItem, newItem);//加到容器groupMap里，key和value都为组  
    //isHideMap.insert(newItem, true);  //设置该组隐藏状态  
    //groupNameEdit->raise();
    //groupNameEdit->setText(tr("未命名")); //设置默认内容  
    //groupNameEdit->selectAll();        //设置全选  
    //groupNameEdit->setGeometry(this->visualItemRect(newItem).left() + 5, this->visualItemRect(newItem).top() + 1, this->visualItemRect(newItem).width(), this->visualItemRect(newItem).height() - 2);//出现的位置  
    //groupNameEdit->show();              //显示  
    //groupNameEdit->setFocus();          //获取焦点  
    //currentItem = newItem;     // 因为要给group命名，所以当前的currentItem设为该group  
}

void FriendListWidget::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //遍历该组的所有好友和自身的组  
    {
        groupMap.remove(item);   //移除  
        delete item;   //删除  
    }
    isHideMap.remove(currentItem); //移除  
}

void FriendListWidget::slotAddBuddy()
{

    qDebug() << "slotAddBuddy   " << currentItem;

    FriendItem *buddy = new FriendItem();   //创建一个自己定义的信息类 
    //buddy->headPath = ":/head";                          //设置头像路径  
    buddy->setName("默认好友");                  //设置用户名  
    buddy->setSign("用通俗的语言，讲深刻的技术。");   //设置个性签名  
    
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//当前组对应的项（包括组本身和好友）复制给tem  
    //关键代码  
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem 
    newItem->setSizeHint(buddy->size());
    this->insertItem(row(currentItem) + tem.count(), newItem); //将该newItem插入到后面  
    this->setItemWidget(newItem, buddy); //将buddy赋给该newItem  
    groupMap.insert(newItem, currentItem);   //加进容器，key为好友，value为组  
    if (isHideMap.value(currentItem))          //如果该组是隐藏，则加进去的好友设置为隐藏  
        newItem->setHidden(true);
    else                                      //否则，该好友设置为显示  
        newItem->setHidden(false);
}

void FriendListWidget::slotDelBuddy()
{
    groupMap.remove(currentItem);
    delete currentItem;
}

void FriendListWidget::slotRename()
{
    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(currentItem).left() + 15, this->visualItemRect(currentItem).top() + 1, this->visualItemRect(currentItem).width(), this->visualItemRect(currentItem).height() - 2);//出现的位置  
    groupNameEdit->setText(currentItem->text());   //获取该组名内容  
    groupNameEdit->show();                        //显示  
    groupNameEdit->selectAll();                   //全选  
    groupNameEdit->setFocus();                        //获取焦点  
}

void FriendListWidget::slotRenameEditFshed()
{
    if (groupNameEdit->text() != NULL)      //如果重命名编辑框不为空  
        currentItem->setText(groupNameEdit->text());  //更新组名  
    groupNameEdit->setText("");
    groupNameEdit->hide();  //隐藏重命名编辑框  
}

