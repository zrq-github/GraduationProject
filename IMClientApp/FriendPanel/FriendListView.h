#ifndef FRIENDLISTVIEW_H_
#define FRIENDLISTVIEW_H_
/**
 * 采用modle/view来设计好友界面
 */
 /**
  * 暂时没使用
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