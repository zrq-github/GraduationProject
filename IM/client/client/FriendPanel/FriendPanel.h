#pragma once
/*
** ���ѽ���
*/

#include "friendpanel_global.h"
#include <QToolBox>  
#include <QMap>

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
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void childClick(QString &id,QString &name);      //�Զ����ӿռ����¼�
private slots:
    void slotAddGroup();    //������
};