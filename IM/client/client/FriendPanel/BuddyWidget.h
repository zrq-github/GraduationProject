#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include "friendpanel_global.h"

class FRIENDPANEL_EXPORT BuddyWidget : public QWidget
{
    Q_OBJECT

public:
    BuddyWidget(QWidget *parent = Q_NULLPTR);
    ~BuddyWidget();
public:
    QLabel *labHead;  //ͷ��

    QLabel *m_id;       //�û�id
    QLabel *m_name;     //�û���  
    QLabel *m_sign;     //����ǩ��
    QString m_headPath; //ͷ��·��
    bool    isOnLine;
public:

private:
    void createUi();
    void setData(QString &name, QString &sign, QString &headPath);
    void mouseReleaseEvent(QMouseEvent *event); 

signals:
    void signMouseRelease();
};
