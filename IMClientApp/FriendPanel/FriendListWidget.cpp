#include "FriendListWidget.h"
#include "QBaseUi/QImageLable.h"
#include "AppSettings/AppPath.h"
#include"QtUITool/QImageTool.h"
#include <QLineEdit>
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include "DataCenter/BaseDataType.h"
#include <QDebug>

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

void FriendItem::setData(UserInfo & userInfo)
{
    //if (userInfo.id != nullptr)
    //    this->m_userInfo.id = userInfo.id;
    //if (userInfo.imgPath != nullptr)
    //    this->m_userInfo.imgPath = userInfo.imgPath;
    //if (userInfo.name != nullptr)
    //    this->m_userInfo.name = userInfo.name;
    this->m_userInfo = userInfo;

    m_labHead->setPixmap(QImageTool::generatePixmap(m_userInfo.imgPath, 100));
    m_labName->setText(QString(m_userInfo.name));
    m_labSign->setText(QString(m_userInfo.sign));
}

void FriendItem::setHead(QString path)
{
    m_userInfo.imgPath = path;
    m_labHead->setPixmap(QImageTool::generatePixmap(path, 100));
}

void FriendItem::setHead(QPixmap pixmap)
{
    m_labHead->setPixmap(pixmap);
}

void FriendItem::setName(QString name)
{
    m_userInfo.name = name;
    m_labName->setText(QString(name));
}

void FriendItem::setSign(QString sign)
{
    m_userInfo.sign = sign;
    m_labSign->setText(QString(sign));
}

void FriendItem::setWarn(bool warn)
{
    if (warn)
        m_labWarn->show();
    else
        m_labWarn->hide();
}

UserInfo & FriendItem::getUserInfo()
{
    // TODO: �ڴ˴����� return ���
    return m_userInfo;
}

void FriendItem::createUi()
{
    m_labHead = new QLabel(this);
    m_labHead->setGeometry(10, 10, 50, 50);
    m_labHead->setScaledContents(true);
    m_labHead->setPixmap(QImageTool::generatePixmap(IMPATH::ImgPath("img_logon_default_head.png"), 100));

    m_labName = new QLabel(this);
    m_labName->setGeometry(70, 10, 100, 20);
    m_labName->setText(QString("�������"));

    m_labSign = new QLabel(this);
    m_labSign->setGeometry(70, 40, 100, 20);
    m_labSign->setText(QString("��ļ��"));

    m_labWarn = new QLabel(this);
    m_labWarn->setGeometry(140, 30, 15, 15);
    m_labWarn->setStyleSheet(
        "background-color:red;"
    );
    m_labWarn->setFrameStyle(QFrame::Box | QFrame::Raised);
}

FriendListWidget::FriendListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // ȥ��itemѡ��ʱ�����߱߿�  
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//ˮƽ�������ر�  
    this->initMenu();

    //this->setStyleSheet("QListWidget{ background:white; color:black; border:none; } "
    //    "QListWidget::item{ border:none; height: 100px; }"
    //    "QListWidget::item:hover{ background:rgb(252,240,193) } "
    //    "QListWidget::item:selected{ background:rgb(252,233,161); color:black; }");
    this->initTest();
}

FriendListWidget::~FriendListWidget()
{
}

void FriendListWidget::initTest()
{
    addGroup("�ҵĺ���");
    addGroup("������");

    UserInfo info;
    info.id = QString("1");
    info.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info.name = QString("����һ��");
    info.sign = QString("�ҽ����������ɷ���");
    addFriend(info, QString("�ҵĺ���"));

    UserInfo info1;
    info1.id = QString("2");
    info1.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info1.name = QString("���Ƕ���");
    info1.sign = QString("�Һܿ�ʼ�������Ƕ���");
    addFriend(info1, QString("�ҵĺ���"));

    UserInfo info2;
    info2.id = QString("3");
    info2.imgPath = IMPATH::ImgPath("img_logon_default_head.png");
    info2.name = QString("��������");
    info2.sign = QString("�б������������");
    addFriend(info2, QString("������"));
}

void FriendListWidget::addGroup(QString groupName)
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(AppPath::ImgPath("arrow_normal.png")),groupName,this);
    newItem->setSizeHint(QSize(this->width(), 25)); //���ø߶ȡ����
    this->addItem(newItem);
    groupMap.insert(newItem, newItem);
    isHideMap.insert(newItem, true);  //���ø�������״̬ 
    m_groupHash.insert(groupName, newItem);
}

void FriendListWidget::addFriend(UserInfo info, QString groupName)
{
    FriendItem *buddy = new FriendItem(this);
    buddy->setData(info);
    buddy->setWarn(false);

    QListWidgetItem* groupItem = m_groupHash.value(groupName);

    QList<QListWidgetItem*> tem = groupMap.keys(groupItem);//��ǰ���Ӧ��������鱾��ͺ��ѣ����Ƹ�tem  
    //�ؼ�����  
    QListWidgetItem *newItem = new QListWidgetItem();       //����һ��newItem 
    newItem->setSizeHint(buddy->size());
    this->insertItem(row(groupItem) + tem.count(), newItem); //����newItem���뵽����  
    this->setItemWidget(newItem, buddy); //��buddy������newItem  
    groupMap.insert(newItem, groupItem);   //�ӽ�������keyΪ���ѣ�valueΪ��  
    if (isHideMap.value(groupItem))          //������������أ���ӽ�ȥ�ĺ�������Ϊ����  
        newItem->setHidden(true);
    else                                      //���򣬸ú�������Ϊ��ʾ  
        newItem->setHidden(false);
}

void FriendListWidget::initMenu()
{//��ʼ��
    blankMenu = new QMenu();
    groupMenu = new QMenu();
    personMenu = new QMenu();
    groupNameEdit = new QLineEdit();
    QAction *addGroup = new QAction("��ӷ���", this);
    QAction *delGroup = new QAction("ɾ������", this);
    QAction *rename = new QAction("������", this);
    QAction *addBuddy = new QAction("��Ӻ���", this);
    QAction *delBuddy = new QAction("ɾ������", this);
    //���ã�  
    groupNameEdit->setParent(this);  //���ø���  
    groupNameEdit->hide(); //���ó�ʼʱ����  
    groupNameEdit->setPlaceholderText("δ����");//���ó�ʼʱ������  
    //���֣�  
    blankMenu->addAction(addGroup);
    groupMenu->addAction(delGroup);
    groupMenu->addAction(rename);
    groupMenu->addAction(addBuddy);
    personMenu->addAction(delBuddy);
    //��Ϣ�ۣ�  
    connect(groupNameEdit, SIGNAL(editingFinished()), this, SLOT(slotRenameEditFshed()));
    connect(addGroup, SIGNAL(triggered()), this, SLOT(slotAddGroup()));
    connect(delGroup, SIGNAL(triggered()), this, SLOT(slotDelGroup()));
    connect(rename, SIGNAL(triggered()), this, SLOT(slotRename()));
    connect(addBuddy, SIGNAL(triggered()), this, SLOT(slotAddBuddy()));
    connect(delBuddy, SIGNAL(triggered()), this, SLOT(slotDelBuddy()));
}

void FriendListWidget::mousePressEvent(QMouseEvent * event)
{
    QListWidget::mousePressEvent(event); // ��������û���mousePressEvent��item��select����첻��Ӧ,���ø��࣬��QSS��Ч����ΪQSS���ڸ���QListWidget����������Ӵ��ڣ��������ϲ㴰�ڣ��Ǹ����ڸ������ϵģ��������ڸ����ڲ�����Ϣ  
    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//���λ�õ�Item�������Ҽ��������ȡ
    qDebug() << "execute mousePressEvent" << currentItem;
    if (currentItem == nullptr)
        return;

    if (groupNameEdit->isVisible() && !(groupNameEdit->rect().contains(event->pos())))
    {
        if (groupNameEdit->text() != NULL)
            currentItem->setText(groupNameEdit->text());
        groupNameEdit->setText("");
        groupNameEdit->hide();
    }

    if (event->button() == Qt::LeftButton && currentItem != NULL && currentItem == groupMap.value(currentItem))//����������������ǵ��������  
    {
        if (isHideMap.value(currentItem))                                  //�����ǰ�����أ�����ʾ  
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//������Ķ�Ӧ�����������ͺ��ѣ�  
                if (subItem != currentItem)                                 //�������Ļ������д���  
                {
                    subItem->setHidden(false);                            //����ȫ����ʾ  
                }
            isHideMap.insert(currentItem, false);                          //���ø���Ϊ��ʾ״̬  
            //currentItem->setIcon(QIcon(":/arrowDown"));
        }
        else                                                             //������ǰ����ʾ��������  
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//������Ķ�Ӧ�����������ͺ��ѣ�  
                if (subItem != currentItem)                                 //�������Ļ������д���  
                {
                    subItem->setHidden(true);                            //����ȫ������  
                }
            isHideMap.insert(currentItem, true);                          //���ø���Ϊ����״̬  
            //currentItem->setIcon(QIcon(":/arrowRight"));
        }
    }

}

void FriendListWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    qDebug() << "execute mouseDoubleClickEvent" << currentItem;
    FriendItem *friendWidget = static_cast<FriendItem*> (this->itemWidget(currentItem));
    
    if (friendWidget != nullptr)
    {
        qDebug() << "execute mouseDoubleClickEvent" << friendWidget;
        emit signUserInfo(friendWidget->getUserInfo());
    }
}

void FriendListWidget::contextMenuEvent(QContextMenuEvent * event)
{
    if (currentItem == NULL)                           //�����������ǿհ״�  
    {
        blankMenu->exec(QCursor::pos());
        return;
    }
    if (currentItem == groupMap.value(currentItem))    // ��������������  
        groupMenu->exec(QCursor::pos());
    else                                            //�����������Ǻ���  
        personMenu->exec(QCursor::pos());
}

void FriendListWidget::slotAddGroup()
{
    addGroup("nihao ");
    //QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/arrowRight"), "δ����");    //����һ��Item  

    //newItem->setSizeHint(QSize(this->width(), 25));//���ÿ�ȡ��߶�  
    //this->addItem(newItem);         //�ӵ�QListWidget��  
    //groupMap.insert(newItem, newItem);//�ӵ�����groupMap�key��value��Ϊ��  
    //isHideMap.insert(newItem, true);  //���ø�������״̬  
    //groupNameEdit->raise();
    //groupNameEdit->setText(tr("δ����")); //����Ĭ������  
    //groupNameEdit->selectAll();        //����ȫѡ  
    //groupNameEdit->setGeometry(this->visualItemRect(newItem).left() + 5, this->visualItemRect(newItem).top() + 1, this->visualItemRect(newItem).width(), this->visualItemRect(newItem).height() - 2);//���ֵ�λ��  
    //groupNameEdit->show();              //��ʾ  
    //groupNameEdit->setFocus();          //��ȡ����  
    //currentItem = newItem;     // ��ΪҪ��group���������Ե�ǰ��currentItem��Ϊ��group  
}

void FriendListWidget::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //������������к��Ѻ��������  
    {
        groupMap.remove(item);   //�Ƴ�  
        delete item;   //ɾ��  
    }
    isHideMap.remove(currentItem); //�Ƴ�  
}

void FriendListWidget::slotAddBuddy()
{

    qDebug() << "slotAddBuddy   " << currentItem;

    FriendItem *buddy = new FriendItem();   //����һ���Լ��������Ϣ�� 
    //buddy->headPath = ":/head";                          //����ͷ��·��  
    buddy->setName("Ĭ�Ϻ���");                  //�����û���  
    buddy->setSign("��ͨ�׵����ԣ�����̵ļ�����");   //���ø���ǩ��  
    
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//��ǰ���Ӧ��������鱾��ͺ��ѣ����Ƹ�tem  
    //�ؼ�����  
    QListWidgetItem *newItem = new QListWidgetItem();       //����һ��newItem 
    newItem->setSizeHint(buddy->size());
    this->insertItem(row(currentItem) + tem.count(), newItem); //����newItem���뵽����  
    this->setItemWidget(newItem, buddy); //��buddy������newItem  
    groupMap.insert(newItem, currentItem);   //�ӽ�������keyΪ���ѣ�valueΪ��  
    if (isHideMap.value(currentItem))          //������������أ���ӽ�ȥ�ĺ�������Ϊ����  
        newItem->setHidden(true);
    else                                      //���򣬸ú�������Ϊ��ʾ  
        newItem->setHidden(false);
}

void FriendListWidget::slotDelBuddy()
{
    groupMap.remove(currentItem);
    delete currentItem;
}

void FriendListWidget::slotRename()
{
    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(currentItem).left() + 15, this->visualItemRect(currentItem).top() + 1, this->visualItemRect(currentItem).width(), this->visualItemRect(currentItem).height() - 2);//���ֵ�λ��  
    groupNameEdit->setText(currentItem->text());   //��ȡ����������  
    groupNameEdit->show();                        //��ʾ  
    groupNameEdit->selectAll();                   //ȫѡ  
    groupNameEdit->setFocus();                        //��ȡ����  
}

void FriendListWidget::slotRenameEditFshed()
{
    if (groupNameEdit->text() != NULL)      //����������༭��Ϊ��  
        currentItem->setText(groupNameEdit->text());  //��������  
    groupNameEdit->setText("");
    groupNameEdit->hide();  //�����������༭��  
}

