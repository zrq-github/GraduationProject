#include "FriendPanel.h"
#include "ui_FriendPanel.h"
#include <QListWidget>
#include "FriendListView.h"
#include "FriendListWidget.h"
#include "DataCenter/BaseDataType.h"
#include "AppSettings/AppPath.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif
FriendPanel::FriendPanel(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::FriendPanel();
    ui->setupUi(this);

    this->createUi();
    //this->friendInit();
}

FriendPanel::~FriendPanel()
{
    delete ui;
}

void FriendPanel::createUi()
{
    //ui->listView->setStyleSheet("background-color:transparent");//背景透明
    //ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
    //ui->listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条

    //friendListView = new FriendListView(this);
    //m_pModel = new QStandardItemModel(this);
    //m_pDelegate = new FriendItemDelegate(this);
    //ui->listView->setItemDelegate(m_pDelegate);
    //ui->listView->setModel(m_pModel);
    FriendListWidget *w = new FriendListWidget(this);
    ui->verticalLayout->addWidget(w);
}

void FriendPanel::friendInit()
{
    QStandardItem *pItem1 = new QStandardItem;
    UserInfo userInfo1;
    userInfo1.id = 1;
    userInfo1.name = QString("我是一号");
    userInfo1.sign = QString("我就是这么自由潇洒");
    userInfo1.imgPath = AppPath::ImgPath("CustomerService.png");
    pItem1->setData(QVariant::fromValue(userInfo1), Qt::UserRole + 1);
    m_pModel->appendRow(pItem1);

    QStandardItem *pItem2 = new QStandardItem;
    UserInfo userInfo2;
    userInfo2.id = 2;
    userInfo2.name = QString("我是二号");
    userInfo2.sign = QString("自由放纵");
    userInfo2.imgPath = AppPath::ImgPath("img_logon_default_head.png");
    pItem2->setData(QVariant::fromValue(userInfo2), Qt::UserRole + 1);
    m_pModel->appendRow(pItem2);

    QStandardItem *pItem3 = new QStandardItem;
    UserInfo userInfo3;
    userInfo3.id = 3;
    userInfo3.name = QString("我是三号");
    userInfo3.sign = QString("我是网易云");
    userInfo3.imgPath = AppPath::ImgPath("logo.ico");
    pItem3->setData(QVariant::fromValue(userInfo3), Qt::UserRole + 1);
    m_pModel->appendRow(pItem3);

}
