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
    :QToolBox(parent)
{
    setFocusPolicy(Qt::NoFocus);        // 去除item选中时的虚线边框  
    createUi();
    binSlots();
}

FriendPanel::~FriendPanel()
{
}

void FriendPanel::createUi()
{
    setGeometry(0, 0, 0, 0);
    slotAddGroup();
}

void FriendPanel::binSlots()
{
}



void FriendPanel::slotAddGroup()
{
    BuddyWidget *a1 = new BuddyWidget;
    BuddyWidget *a2 = new BuddyWidget;

    QWidget *widget = new QWidget;
    
    //布局设置
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setGeometry(QRect(0,0,0,0));
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);
    layout->addWidget(a1);
    layout->addWidget(a2);
    widget->setLayout(layout);

    addItem(widget, "asd");
}


