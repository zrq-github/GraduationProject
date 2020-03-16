#pragma once
/*
** ���ѽ���
*/

#include "friendpanel_global.h"
#include <QListWidget>  

class FRIENDPANEL_EXPORT FriendPanel :public QListWidget
{
    Q_OBJECT

public: 
    explicit FriendPanel(QWidget *parent= Q_NULLPTR);
    ~FriendPanel();
private:
    void createUi();
public:

    QMap<QListWidgetItem*, QListWidgetItem*> groupMap;   // ������ - key:
    QMap<QListWidgetItem*, bool> isHideMap;//�����жϸ����Ƿ�������

    QLineEdit *groupNameEdit;       //������֣���������ʱ����Ҫ�õ�  
    QListWidgetItem *currentItem;   //��ǰ����  

public slots:
    void slotAddGroup();    //�����  
    void slotDelGroup();    //ɾ����  
    void slotAddBuddy();    //��Ӻ���  
    void slotDelBuddy();    //ɾ������ 
};
