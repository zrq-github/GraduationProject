#pragma once
/*
** ���ѽ���
*/

#include "friendpanel_global.h"
#include <QToolBox>  
#include <QMap>

class BuddyWidget;

class FRIENDPANEL_EXPORT FriendPanel :public QToolBox
{
    Q_OBJECT

public: 
    explicit FriendPanel(QWidget *parent= Q_NULLPTR);
    ~FriendPanel();
private:
    void createUi();
    void binSlots();
public:
    void addFriend(QWidget *page, QString id, QString name, QString sign, QString headPath);     //��Ӻ���
    void addGroup(QString groupName);

    bool eventFilter(QObject *obj, QEvent *event);
private:
    QMap<QString, QWidget*> *listGroup;         //�����б�
    QMap<QString, QString>   *list;             //�������ĸ�������

    void init();
signals:
    void childClick(QString &id,QString &name);      //�Զ����ӿռ����¼�

private slots:
    void slotAddFriend();
    void slotAddGroup();    //�����
};
