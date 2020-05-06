#pragma once

#include <QWidget>
#include <QLabel>  
#include <QEvent>  
#include <QListWidget>  
#include <QMenu>  
#include <QMouseEvent>  
#include <QLineEdit>  
namespace Ui { class FriendDemo1; };


//�Զ�����ϢItem��  
class personListBuddy : public QWidget
{
    Q_OBJECT
public:
    explicit personListBuddy(QWidget *parent = 0);
    void initUi();//��ʼ��Ui  
    QLabel *head;  //ͷ��  
    QLabel *name;  //�û���  
    QLabel *sign;  //����ǩ��  
    QString headPath;//ͷ��·��  
    bool eventFilter(QObject *obj, QEvent *event);//�¼�������  

signals:

public slots:

};

class personList : public QListWidget //�̳�QListWidget������ʹ���������Դ��ĺ�����������  
{
    Q_OBJECT
public:
    explicit personList(QListWidget *parent = 0);
     
    void contextMenuEvent(QContextMenuEvent*);//�˵��¼���Ϊ����ʾ�˵�  
    void initMenu();//��ʼ���˵�  
    QMenu *blankMenu;//����հ��ϵĲ˵�  
    QMenu *groupMenu;//������ϵĲ˵�  
    QMenu *personMenu;//������ϵĲ˵�  
    QMap<QListWidgetItem*, QListWidgetItem*> groupMap;   // ������ - key:�� value:��  
    QMap<QListWidgetItem*, bool> isHideMap;//�����жϸ����Ƿ�������

    QLineEdit *groupNameEdit;//������֣���������ʱ����Ҫ�õ�  
    QListWidgetItem *currentItem;//��ǰ����  
private:
    void mousePressEvent(QMouseEvent *event);//������¼� 
signals:

public slots:
    void slotAddGroup();   //�����  
    void slotDelGroup();   //ɾ����  
    void slotAddBuddy();   //��Ӻ���  
    void slotDelBuddy();   //ɾ������  
    void slotRename();     //��������  
    void slotRenameEditFshed();//�������  

};

class FriendDemo1 : public QWidget
{
    Q_OBJECT

public:
    FriendDemo1(QWidget *parent = Q_NULLPTR);
    ~FriendDemo1();

private:
    void creatUi();
    Ui::FriendDemo1 *ui;
    personListBuddy *buddy;
};
