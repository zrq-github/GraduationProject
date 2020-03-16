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
    :QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);        // ȥ��itemѡ��ʱ�����߱߿�  
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//ˮƽ�������ر�  
    createUi();
}

FriendPanel::~FriendPanel()
{
}

void FriendPanel::createUi()
{
    groupNameEdit = new QLineEdit;
    slotAddGroup();
}



void FriendPanel::slotAddGroup()
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(QString::fromUtf8("../Images/arrowRight")), "δ����");    //����һ��Item
    newItem->setSizeHint(QSize(this->width(), 25));//���ÿ�ȡ��߶�
    this->addItem(newItem);         //�ӵ�QListWidget��
    groupMap.insert(newItem, newItem);//�ӵ�����groupMap�key��value��Ϊ��
    isHideMap.insert(newItem, true);  //���ø�������״̬

    BuddyWidget *buddy = new BuddyWidget;   //����һ���Լ��������Ϣ��
    buddy->m_headPath = ":/head";                          //����ͷ��·��
    buddy->m_name->setText("��ңʥ��");                  //�����û���
    buddy->m_sign->setText("��ͨ�׵����ԣ�����̵ļ�����");   //���ø���ǩ��

    QListWidgetItem *newItem1 = new QListWidgetItem();       //����һ��newItem
    this->addItem(newItem1);
    this->setItemWidget(newItem1, buddy);
}

void FriendPanel::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //������������к��Ѻ��������
    {
        groupMap.remove(item);   //�Ƴ�
        delete item;   //ɾ��
    }
    isHideMap.remove(currentItem); //�Ƴ�
}

void FriendPanel::slotAddBuddy()
{
    BuddyWidget *buddy = new BuddyWidget;   //����һ���Լ��������Ϣ��
    buddy->m_headPath = ":/head";                          //����ͷ��·��
    buddy->m_name->setText("��ңʥ��");                  //�����û���
    buddy->m_sign->setText("��ͨ�׵����ԣ�����̵ļ�����");   //���ø���ǩ��
    QList<QListWidgetItem*> tem = groupMap.keys(currentItem);//��ǰ���Ӧ��������鱾��ͺ��ѣ����Ƹ�tem
    //�ؼ�����
    QListWidgetItem *newItem = new QListWidgetItem();       //����һ��newItem
    this->insertItem(row(currentItem) + tem.count(), newItem); //����newItem���뵽����
    this->setItemWidget(newItem, buddy); //��buddy������newItem
    groupMap.insert(newItem, currentItem);   //�ӽ�������keyΪ���ѣ�valueΪ��
    if (isHideMap.value(currentItem))          //������������أ���ӽ�ȥ�ĺ�������Ϊ����
        newItem->setHidden(true);
    else                                      //���򣬸ú�������Ϊ��ʾ
        newItem->setHidden(false);
}

void FriendPanel::slotDelBuddy()
{
    groupMap.remove(currentItem);  //�Ƴ��ú���
    delete currentItem;            //ɾ��
}