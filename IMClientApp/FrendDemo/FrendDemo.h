#pragma once
/*
* Model/view ∫√”—¡–±ÌDemo
*/

#include <QtWidgets/QWidget>
#include "ui_FrendDemo.h"

#include <QMetaType>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QListView>
typedef struct {
    QString iconPath;
    QString singer;
    QString songsNb;
} MuItemData;
Q_DECLARE_METATYPE(MuItemData)

class ItemDelegate :public QStyledItemDelegate
{
public:
    ItemDelegate(QObject *parent = nullptr);
    
    void paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
    QStyleOptionViewItem *m_option;
};

class ItemModel :public QStandardItemModel
{
public:
    ItemModel(QObject *parent = nullptr);
};

class ItemView :public QListView
{
//public:
//    ItemView(QObject *parent = nullptr);

};

class FrendDemo : public QWidget
{
    Q_OBJECT

public:
    FrendDemo(QWidget *parent = Q_NULLPTR);

    void createUi();
private:
    Ui::FrendDemoClass ui;
    ItemView *view;
    ItemModel *model;
    ItemDelegate *itemDelegate;
};
