#include "FriendListView.h"
#include <QPainter>
#include "DataCenter/BaseDataType.h"

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

FriendListView::FriendListView(QObject *parent)
    : QObject(parent)
{
}

FriendListView::~FriendListView()
{
}

FriendItemDelegate::FriendItemDelegate(QObject * parent)
{

}

void FriendItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole + 1);
        UserInfo &itemData = var.value<UserInfo>();

        // item 矩形区域
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);

        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());

        // 鼠标悬停或者选中时改变背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->setPen(QPen(QColor("#ebeced")));
            painter->setBrush(QColor("#ebeced"));
            painter->drawPath(path);
        }
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        }

        // 绘制头像
        QRectF iconRect = QRect(rect.left() + 5, rect.top() + 5, 40, 40);
        painter->drawImage(iconRect, QImage(itemData.imgPath));
        
        //绘制名字
        QRectF nameRect = QRect(iconRect.right() + 5, iconRect.top(), rect.width() - 10 - iconRect.width(), 20);
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Microsoft Yahei", 10));
        painter->drawText(nameRect, itemData.name);

        //绘制个性签名
        QRectF signRect = QRect(nameRect.left(), nameRect.bottom() + 0, rect.width() - 10 - iconRect.width(), 20);
        painter->setPen(QPen(Qt::gray));
        painter->drawText(signRect, itemData.sign);

        painter->restore();
    }
}

QSize FriendItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    return QSize(option.rect.width(), 50);
}