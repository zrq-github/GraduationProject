#ifndef FRIENDLISTWIDGET_H_
#define FRIENDLISTWIDGET_H_

#include <QListWidget>
#include "DataCenter/BaseDataType.h"
#include "friendpanel_global.h"

class QLabel;
class QMenu;

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    FriendItem(QWidget *parent = Q_NULLPTR);
    ~FriendItem();

    void setData(UserInfo &userInfo);
    void setHead(QString path/*img path*/);
    void setHead(QPixmap pixmap);   //����������ÿ��������⣬�Ȳ�Ҫ����
    void setName(QString name);
    void setSign(QString sign);
    void setWarn(bool warn);

    UserInfo & getUserInfo();
private:
    void createUi();

    QLabel *m_labHead;
    QLabel *m_labName;
    QLabel *m_labSign;
    QLabel *m_labWarn;
    UserInfo m_userInfo;
};

class FRIENDPANEL_EXPORT FriendListWidget : public QListWidget
{
    Q_OBJECT

public:
    FriendListWidget(QWidget *parent);
    ~FriendListWidget();

    void initTest();
    void addGroup(QString groupName="δ����");
    void addFriend(UserInfo info, QString groupName);
private:
    void initMenu();    //��ʼ���˵�
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    QMenu *blankMenu;   //����հ��ϵĲ˵�  
    QMenu *groupMenu;   //������ϵĲ˵�  
    QMenu *personMenu;  //������ϵĲ˵�  

    QHash<QString, QListWidgetItem*> m_groupHash;     //QString ����  QListWidgetItem �����  ��������Ӧ��item

    QMap<QListWidgetItem*, QListWidgetItem*> groupMap;   // �� - key:��(��+������) value:��  
    QMap<QListWidgetItem*, bool> isHideMap;//�����жϸ����Ƿ�������

    QLineEdit *groupNameEdit;//������֣���������ʱ����Ҫ�õ�  
    QListWidgetItem *currentItem;//��ǰ���� 
signals:
    void signUserInfo(UserInfo &);

private slots :
    void slotAddGroup();    //�����
    void slotDelGroup();   //ɾ����  
    void slotAddBuddy();   //��Ӻ���  
    void slotDelBuddy();   //ɾ������  
    void slotRename();     //��������  
    void slotRenameEditFshed();//�������  
};
#endif
