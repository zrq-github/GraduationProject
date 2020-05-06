#ifndef FRIENDPANEL_H_
#define FRIENDPANEL_H_
/**
 * ��ʱûʹ��
 */
#include <QListWidget>
#include "friendpanel_global.h"
namespace Ui { class FriendPanel; };
class FriendListView;
class QStandardItemModel;
class FriendItemDelegate;

class FRIENDPANEL_EXPORT  FriendPanel : public QWidget
{
    Q_OBJECT

public:
    FriendPanel(QWidget *parent = Q_NULLPTR);
    ~FriendPanel();


    QStandardItemModel *m_pModel;
    FriendItemDelegate *m_pDelegate;
private:
    void createUi();
    void friendInit();        //���Ժ���
    Ui::FriendPanel *ui;
    FriendListView *friendListView;
};

#endif