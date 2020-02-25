#include "BuddyWidget.h"
#include <QPainter>  
#include <QVBoxLayout>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

BuddyWidget::BuddyWidget(QWidget *parent)
    : QWidget(parent)
{
    headPath = "../Images/background.png";
    createUi();
}

BuddyWidget::~BuddyWidget()
{
}

void BuddyWidget::createUi()
{
    //创建头像
    head = new QLabel(this);
    head->setFixedSize(40, 40);
    head->setPixmap(QPixmap(headPath));
    //设置名字和个性设置
    name = new QLabel(this);
    name->setText(QString::fromUtf8("这个人没有名字"));
    sign = new QLabel(this);
    sign->setText("这个人很懒，什么都没有留下");
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    sign->setPalette(color);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(name);
    VLayout->addWidget(sign);
    //布局设置
    QHBoxLayout *Hlayout = new QHBoxLayout;
    Hlayout->addWidget(head);
    Hlayout->addLayout(VLayout);

    setLayout(Hlayout);
}

bool BuddyWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == head)
    {
        if (event->type() == QEvent::Paint)
        {
            QPainter painter(head);
            painter.drawPixmap(head->rect(), QPixmap(headPath));
        }
    }
    return QWidget::eventFilter(obj, event);
}