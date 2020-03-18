#include "FriendModel.h"
#include <QIcon>
#include <QFile>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>
#include <QPainter>

FriendModel::FriendModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

FriendModel::~FriendModel()
{
}

void FriendModel::initData(QVector<FriendData*>& itemData)
{
    this->m_ItemData = itemData;
}

QVariant FriendModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (index.row() > m_ItemData.count()))
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return m_ItemData.at(index.row())->name;
    }
    if (role == Qt::DecorationRole)
    {
        QString localPath = ":/img/logo.ico";
        QPixmap pixmap;
        pixmap.load(localPath);
        return pixmap.scaled(QSize(50, 50), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    if (role == Qt::UserRole)
    {
        return m_ItemData.at(index.row())->id;
    }
    return QVariant();
}

int FriendModel::rowCount(const QModelIndex & parent) const
{
    return m_ItemData.size();
}

FriendView::FriendView(QWidget *parent /*= Q_NULLPTR*/)
    :QListView(parent)
{
    this->bindSigns();
}

FriendView::~FriendView()
{
}


void FriendView::bindSigns()
{
    connect(this, &FriendView::doubleClicked, this, &FriendView::itemDoubleClicked);
}

void FriendView::itemDoubleClicked(QModelIndex index)
{
    QString name = this->model()->data(index, Qt::DisplayRole).toString();
    QString id = this->model()->data(index, Qt::UserRole).toString();

    emit signCreateChatPanel(id, name);
}

FriendDelegate::FriendDelegate(QStyledItemDelegate *parent /* = 0 */)
    :QStyledItemDelegate(parent)
{

}

FriendDelegate::~FriendDelegate()
{
}

void FriendDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    const QPixmap &pixmap = qvariant_cast<QPixmap>(index.data(Qt::UserRole + 1));
    QRect pixmapRect = QRect(option.rect.topLeft(), QSize(50, 50));

    const QString &str = index.data(Qt::UserRole).toString();
    QFontMetrics font(painter->fontMetrics());
    QRect diplayRect = QRect(pixmapRect.topRight() + QPoint(20, 25), QSize(font.width(str), font.height()));
    painter->drawPixmap(pixmapRect, pixmap);
    painter->drawText(diplayRect, str);
}

QSize FriendDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(option.rect.width(), 50);
}
