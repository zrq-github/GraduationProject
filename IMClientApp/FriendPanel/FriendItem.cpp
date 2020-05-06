#include "FriendItem.h"
#include "ui_FriendItemWidget.h"
#include "QBaseUi/QImageLable.h"
#include "AppSettings/AppPath.h"
#include"QtUITool/QImageTool.h"
#include <QLineEdit>

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
