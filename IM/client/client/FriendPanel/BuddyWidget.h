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

public:
    QString getID();
    QString getName();
    QString getSign();

    void setID(QString id);
    void setName(QString name);
    void setSign(QString sign);
private:
    QString m_id;       //�û�id
    QString m_headPath; //ͷ��·��

    QLabel *labHead;  //ͷ��
    QLabel *labName;     //�û���  
    QLabel *labSign;     //����ǩ��
    
    bool    isOnLine;
private:
    void createUi();
    void setData(QString &name, QString &sign, QString &headPath);
    void mouseReleaseEvent(QMouseEvent *event); 

signals:
    void signMouseRelease();
};
