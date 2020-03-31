#pragma once

#include <QAbstractListModel>
#include <QListView>
#include <QStyledItemDelegate>
#include "Base/DeftData.h"

class FriendDelegate :public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FriendDelegate(QStyledItemDelegate *parent = 0);
    ~FriendDelegate();
    //ÖØÐ´ÖØ»­º¯Êý
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class FriendModel : public QAbstractListModel
{
    Q_OBJECT

public:
    FriendModel(QObject *parent=Q_NULLPTR);
    ~FriendModel();
    
    void initData(QVector<FriendDataPtr> &itemData);

    QVariant data(const QModelIndex & index, int role=Qt::DisplayRole) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
private:
    QVector<FriendDataPtr> m_ItemData;
};

class FriendView :public QListView
{
    Q_OBJECT
public:
    FriendView(QWidget *parent = Q_NULLPTR);
    ~FriendView();
private:
    void bindSigns();
signals:
    void signCreateChatPanel(QString id, QString name);

private slots:
    void itemDoubleClicked(QModelIndex index);
};