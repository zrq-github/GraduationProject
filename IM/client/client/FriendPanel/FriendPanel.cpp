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
    setFocusPolicy(Qt::NoFocus);        // ȥ��itemѡ��ʱ�����߱߿�  
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

bool FriendPanel::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QList<BuddyWidget*> &child = this->findChildren<BuddyWidget*>();
        for (BuddyWidget *i : child)
        {
            if (obj == i)
            {
                //�����﷢�͵���¼�
                emit this->childClick(i->getID(), i->getName());
                return false;
            }
        }
        return true;
    }

    return false;
}

void FriendPanel::slotAddFriend()
{

}

void FriendPanel::slotAddGroup()
{
    BuddyWidget *a1 = new BuddyWidget;
    a1->setName("һ�Ż�");
    BuddyWidget *a2 = new BuddyWidget;
    a2->setName("���Ż�");
    a1->installEventFilter(this);
    a2->installEventFilter(this);
    QWidget *widget = new QWidget;
    
    //��������
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setGeometry(QRect(0,0,0,0));
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setSpacing(0);
    layout->addWidget(a1);
    layout->addWidget(a2);
    widget->setLayout(layout);

    addItem(widget, "asd");
}


