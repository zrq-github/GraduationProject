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
    //����ͷ��
    head = new QLabel(this);
    head->setFixedSize(40, 40);
    head->setPixmap(QPixmap(headPath));
    //�������ֺ͸�������
    name = new QLabel(this);
    name->setText(QString::fromUtf8("�����û������"));
    sign = new QLabel(this);
    sign->setText("����˺�����ʲô��û������");
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    sign->setPalette(color);

    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(name);
    VLayout->addWidget(sign);
    //��������
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