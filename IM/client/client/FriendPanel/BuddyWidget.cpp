#include "BuddyWidget.h"
#include <QPainter>  
#include <QVBoxLayout>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

BuddyWidget::BuddyWidget(QWidget *parent)
    : QWidget(parent)
{
    //赋初值
    m_id = "1234";
    m_headPath = "../Images/background.png";
    this->setWindowFlags(Qt::SplashScreen);
    createUi();
}

BuddyWidget::~BuddyWidget()
{
}

QString BuddyWidget::getID()
{
    return m_id;
}

QString BuddyWidget::getName()
{
    return labName->text();
}

QString BuddyWidget::getSign()
{
    return labSign->text();
}

void BuddyWidget::setID(QString id)
{
    m_id = id;
}

void BuddyWidget::setName(QString name)
{
    this->labName->setText(name);
}

void BuddyWidget::setSign(QString sign)
{
    this->labSign->setText(sign);
}

void BuddyWidget::createUi()
{
    //创建头像
    labHead = new QLabel(this);
    labHead->setFixedSize(40, 40);
    labHead->setPixmap(QPixmap(m_headPath));
    //设置名字和个性设置
    labName = new QLabel(this);
    labName->setText(QString::fromUtf8("这个人没有名字"));
    labSign = new QLabel(this);
    labSign->setText("这个人很懒，什么都没有留下");
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    labSign->setPalette(color);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(labName);
    VLayout->addWidget(labSign);
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
    labName->setText(name);
    labSign->setText(sign);
    labHead->setPixmap(headPath);
}

void BuddyWidget::mouseReleaseEvent(QMouseEvent * event)
{

    return QWidget::mouseReleaseEvent(event);
}
