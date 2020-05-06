#ifndef FRIENDLISTVIEW_H_
#define FRIENDLISTVIEW_H_
/**
 * ����modle/view����ƺ��ѽ���
 */
 /**
  * ��ʱûʹ��
  */
#include <QObject>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QListView>

class FriendItemDelegate :public QStyledItemDelegate
{
public:
    FriendItemDelegate(QObject *parent = nullptr);
    
    void paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const Q_DECL_OVERRIDE;
};

class FriendListView : public QObject
{
    Q_OBJECT

public:
    FriendListView(QObject *parent);
    ~FriendListView();
};

#endif