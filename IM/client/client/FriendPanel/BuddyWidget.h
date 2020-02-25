#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include "friendpanel_global.h"

class FRIENDPANEL_EXPORT BuddyWidget : public QWidget
{
    Q_OBJECT

public:
    QLabel *head;  //ͷ��  
    QLabel *name;  //�û���  
    QLabel *sign;  //����ǩ��  
    QString headPath;//ͷ��·��
public:
    BuddyWidget(QWidget *parent = Q_NULLPTR);
    ~BuddyWidget();
private:

    void createUi();

    bool eventFilter(QObject *obj, QEvent *event);//�¼�������  
};
