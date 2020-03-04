#include "FriendPanel.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QLineEdit>
#include <QMouseEvent>
#include "BuddyWidget.h"
#include <QPushButton>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif


FriendPanel::FriendPanel(QWidget * parent)
    :QToolBox(parent)
    , listGroup(new QMap<QString, QWidget*>)
    , list(new QMap<QString, QString>)
{
    //setFocusPolicy(Qt::NoFocus);        // 去除item选中时的虚线边框  
    createUi();
    binSlots();

    init();
}

FriendPanel::~FriendPanel()
{
}

void FriendPanel::createUi()
{
    setGeometry(0, 0, 0, 0);

}

void FriendPanel::binSlots()
{
    
}

void FriendPanel::addFriend(QWidget *page, QString id, QString name, QString sign, QString headPath)
{
    BuddyWidget *widget = new BuddyWidget;
    widget->installEventFilter(this);
    widget->setName(name);
    widget->setID(id);
    widget->setSign(sign);

    QLayout *layout = page->findChild<QLayout*>("layout");
    layout->addWidget(widget);
}

void FriendPanel::addGroup(QString groupName)
{
    QWidget *page = new QWidget;
    page->setGeometry(0, 0, 0, 0);
    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setObjectName("layout");
    layout->setMargin(0);
    layout->setGeometry(QRect(0, 0, 0, 0));
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    page->setLayout(layout);

    //QPushButton *btn1 = new QPushButton(page);
    //QPushButton *btn2 = new QPushButton(page);
    //layout->addWidget(btn1);
    //layout->addWidget(btn2);

    listGroup->insert(groupName, page);
    addItem(page, groupName);
}

bool FriendPanel::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QList<BuddyWidget*> &child = this->findChildren<BuddyWidget*>();
        for (BuddyWidget *i : child)
        {
            if (obj == i)
            {
                //在这里发送点击事件
                emit this->childClick(i->getID(), i->getName());
                return true;
            }
        }
        return false;
    }

    return false;
}

void FriendPanel::init()
{
    addGroup("好友分类一");
    addFriend(listGroup->value("好友分类一"), "001", "懒人一号", "这人什么都没有写", "");
    addFriend(listGroup->value("好友分类一"), "002", "懒人二号", "这人什么都没有写", "");
}

void FriendPanel::slotAddFriend()
{

}

void FriendPanel::slotAddGroup()
{
}


