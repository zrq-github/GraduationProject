#include "BuddyWidget.h"
#include <QPainter>  
#include <QVBoxLayout>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

BuddyWidget::BuddyWidget(QWidget *parent)
    : QWidget(parent)
{
    //����ֵ
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
    //����ͷ��
    labHead = new QLabel(this);
    labHead->setFixedSize(40, 40);
    labHead->setPixmap(QPixmap(m_headPath));
    //�������ֺ͸�������
    labName = new QLabel(this);
    labName->setText(QString::fromUtf8("�����û������"));
    labSign = new QLabel(this);
    labSign->setText("����˺�����ʲô��û������");
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    labSign->setPalette(color);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(labName);
    VLayout->addWidget(labSign);
    //��������
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
