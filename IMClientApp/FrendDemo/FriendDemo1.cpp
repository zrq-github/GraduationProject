#include "FriendDemo1.h"
#include "ui_FriendDemo1.h"
#include <QPainter>

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

personListBuddy::personListBuddy(QWidget *parent) :
    QWidget(parent)
{
    initUi();
}
//��ʼ��Ui  
void personListBuddy::initUi()
{
    //��ʼ��  
    head = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    //����ͷ���С  
    head->setFixedSize(40, 40);
    head->setText("123123");
    //��������
    name->setText("name");
    //���ø���ǩ������Ϊ��ɫ  
    QPalette color;
    color.setColor(QPalette::Text, Qt::gray);
    sign->setPalette(color);
    sign->setText("sign");
    //����  
    head->move(7, 7);
    name->move(54, 10);
    sign->move(54, 27);
    sign->setText("bbb");
    //װ���¼�������  
    head->installEventFilter(this);
}
//�¼�����������Ҫ��Ϊ����ͼƬ�ܹ�ȫ�������head����  
bool personListBuddy::eventFilter(QObject *obj, QEvent *event)
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

personList::personList(QListWidget *parent) :
    QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // ȥ��itemѡ��ʱ�����߱߿�  
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//ˮƽ�������ر�  
    initMenu();

    this->setStyleSheet("QListWidget{ background:white; color:black; border:none; } "
        "QListWidget::item{ border:none; height: 54px; }"
        "QListWidget::item:hover{ background:rgb(252,240,193) } "
        "QListWidget::item:selected{ background:rgb(252,233,161); color:black; }"
        "QScrollBar:vertical { background:transparent; width:9px; margin: 0px 0px 2px 0px;}"
        "QScrollBar::handle:vertical { background: rgb(195, 195, 195); min-height: 20px; border-radius: 3px; } "
        "QScrollBar::handle:vertical:hover{ background:rgba(0,0,0,30%); } "
        "QScrollBar::add-line:vertical { height: 0px; subcontrol-position: bottom; subcontrol-origin: margin; }"
        "QScrollBar::sub-line:vertical { height: 0px; subcontrol-position: top; subcontrol-origin: margin; }"
    );
}
//��ʼ���˵�  
void personList::initMenu()
{
    //��ʼ����  
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
//������¼�  
void personList::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event); // ��������û���mousePressEvent��item��select����첻��Ӧ,���ø��࣬��QSS��Ч����ΪQSS���ڸ���QListWidget����������Ӵ��ڣ��������ϲ㴰�ڣ��Ǹ����ڸ������ϵģ��������ڸ����ڲ�����Ϣ  
    //��ֹһ���������������item�������������item��հ״�ʱ��ָ����item��currentItem����������item  
    if (groupNameEdit->isVisible() && !(groupNameEdit->rect().contains(event->pos())))
    {
        if (groupNameEdit->text() != NULL)
            currentItem->setText(groupNameEdit->text());
        groupNameEdit->setText("");
        groupNameEdit->hide();
    }
    currentItem = this->itemAt(mapFromGlobal(QCursor::pos()));//���λ�õ�Item�������Ҽ��������ȡ  
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
            currentItem->setIcon(QIcon(":/arrowDown"));
        }
        else                                                             //������ǰ����ʾ��������  
        {
            foreach(QListWidgetItem* subItem, groupMap.keys(currentItem))//������Ķ�Ӧ�����������ͺ��ѣ�  
                if (subItem != currentItem)                                 //�������Ļ������д���  
                {
                    subItem->setHidden(true);                            //����ȫ������  
                }
            isHideMap.insert(currentItem, true);                          //���ø���Ϊ����״̬  
            currentItem->setIcon(QIcon(":/arrowRight"));
        }
    }
}
//�˵��¼���Ϊ����ʾ�˵����������Ҽ���Ӧ��������¼�mousePressEvent������contextMenuEvent  
void personList::contextMenuEvent(QContextMenuEvent *event)
{
    QListWidget::contextMenuEvent(event);           //���û����¼�  
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
//�����  
void personList::slotAddGroup()
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/arrowRight"), "δ����");    //����һ��Item  
    newItem->setSizeHint(QSize(this->width(), 25));//���ÿ�ȡ��߶�  
    this->addItem(newItem);         //�ӵ�QListWidget��  
    groupMap.insert(newItem, newItem);//�ӵ�����groupMap�key��value��Ϊ��  
    isHideMap.insert(newItem, true);  //���ø�������״̬  
    groupNameEdit->raise();
    groupNameEdit->setText(tr("δ����")); //����Ĭ������  
    groupNameEdit->selectAll();        //����ȫѡ  
    groupNameEdit->setGeometry(this->visualItemRect(newItem).left() + 15, this->visualItemRect(newItem).top() + 1, this->visualItemRect(newItem).width(), this->visualItemRect(newItem).height() - 2);//���ֵ�λ��  
    groupNameEdit->show();              //��ʾ  
    groupNameEdit->setFocus();          //��ȡ����  
    currentItem = newItem;     // ��ΪҪ��group���������Ե�ǰ��currentItem��Ϊ��group  
}
//ɾ����  
void personList::slotDelGroup()
{
    foreach(QListWidgetItem* item, groupMap.keys(currentItem))  //������������к��Ѻ��������  
    {
        groupMap.remove(item);   //�Ƴ�  
        delete item;   //ɾ��  
    }
    isHideMap.remove(currentItem); //�Ƴ�  
}
//������  
void personList::slotRename()
{
    groupNameEdit->raise();
    groupNameEdit->setGeometry(this->visualItemRect(currentItem).left() + 15, this->visualItemRect(currentItem).top() + 1, this->visualItemRect(currentItem).width(), this->visualItemRect(currentItem).height() - 2);//���ֵ�λ��  
    groupNameEdit->setText(currentItem->text());   //��ȡ����������  
    groupNameEdit->show();                        //��ʾ  
    groupNameEdit->selectAll();                   //ȫѡ  
    groupNameEdit->setFocus();                        //��ȡ����  
}

//��Ӻ��ѣ���Ҫ��Ϊ�˲��Թ��ܣ�ʵ�ʹ�������Ըĳɶ�̬��ȡ���ݿ������Ӻ���  
void personList::slotAddBuddy()
{
    personListBuddy *buddy = new personListBuddy();   //����һ���Լ��������Ϣ��  
    buddy->headPath = ":/head";                          //����ͷ��·��  
    buddy->name->setText("��ңʥ��");                  //�����û���  
    buddy->sign->setText("��ͨ�׵����ԣ�����̵ļ�����");   //���ø���ǩ��  
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
//ɾ������  
void personList::slotDelBuddy()
{
    groupMap.remove(currentItem);  //�Ƴ��ú���  
    delete currentItem;            //ɾ��  
}
//���������  
void personList::slotRenameEditFshed()
{
    if (groupNameEdit->text() != NULL)      //����������༭��Ϊ��  
        currentItem->setText(groupNameEdit->text());  //��������  
    groupNameEdit->setText("");
    groupNameEdit->hide();  //�����������༭��  
}


FriendDemo1::FriendDemo1(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::FriendDemo1();
    ui->setupUi(this);
    creatUi();
}

FriendDemo1::~FriendDemo1()
{
    delete ui;
}

void FriendDemo1::creatUi()
{
    buddy = new personListBuddy(this);
    buddy->setGeometry(10, 10, 100, 100);
}
