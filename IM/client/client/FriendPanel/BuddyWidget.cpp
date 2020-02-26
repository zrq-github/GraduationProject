#include "BuddyWidget.h"
#include <QPainter>  
#include <QVBoxLayout>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

BuddyWidget::BuddyWidget(QWidget *parent)
    : QWidget(parent)
{
    m_headPath = "../Images/background.png";
    this->setWindowFlags(Qt::SplashScreen);
    createUi();
}

BuddyWidget::~BuddyWidget()
{
}

void BuddyWidget::createUi()
{
    //创建头像
    labHead = new QLabel(this);
    labHead->setFixedSize(40, 40);
    labHead->setPixmap(QPixmap(m_headPath));
    //设置名字和个性设置
    m_name = new QLabel(this);
    m_name->setText(QString::fromUtf8("这个人没有名字"));
    m_sign = new QLabel(this);
    m_sign->setText("这个人很懒，什么都没有留下");
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    m_sign->setPalette(color);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(m_name);
    VLayout->addWidget(m_sign);
    //布局设置
    QHBoxLayout *Hlayout = new QHBoxLayout;
    Hlayout->setGeometry(QRect(0, 0, 0, 0));
    Hlayout->setSizeConstraint(QLayout::SetFixedSize);
    Hlayout->addWidget(labHead);
    Hlayout->addLayout(VLayout);

    setLayout(Hlayout);
}

void BuddyWidget::setData(QString & name, QString & sign, QString & headPath)
{
    m_name->setText(name);
    m_sign->setText(sign);
    labHead->setPixmap(headPath);
}

bool BuddyWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == labHead)
    {
        if (event->type() == QEvent::Paint)
        {
            QPainter painter(labHead);
            painter.drawPixmap(labHead->rect(), QPixmap(m_headPath));
        }
    }
    return QWidget::eventFilter(obj, event);
}