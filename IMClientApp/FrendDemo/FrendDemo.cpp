#include "FrendDemo.h"
#include <QPainter>
#include <QDebug>

FrendDemo::FrendDemo(QWidget *parent)
    : QWidget(parent)
    ,itemDelegate(nullptr)
    ,view(nullptr)
    ,model(nullptr)
{
    ui.setupUi(this);
    this->createUi();
}

ItemDelegate::ItemDelegate(QObject * parent)
    :QStyledItemDelegate(parent)
{
    
}

const QStringList icons = {
    ":/res/1.PNG", ":/Resources/qq.png", ":/Resources/qq.png",
    ":/Resources/qq.png", ":/Resources/qq.png", ":/Resources/qq.png",
};
const QStringList singers = {
    "MC-Hotdog", "李荣浩", "Author",
    "PACT", "杨千嬅", "张震岳",
};

void ItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

    if (index.isValid()) {
        qDebug() << index;
        painter->save();
        QVariant var = index.data(Qt::UserRole + 1);
        MuItemData itemData = var.value<MuItemData>();

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

        // 绘制图片，歌手，数量位置区域
        QRectF iconRect = QRect(rect.left() + 5, rect.top() + 5, 40, 40);
        QRectF singerRect = QRect(iconRect.right() + 5, iconRect.top(), rect.width() - 10 - iconRect.width(), 20);
        QRectF songNbRect = QRect(singerRect.left(), singerRect.bottom() + 5, rect.width() - 10 - iconRect.width(), 20);

        painter->drawImage(iconRect, QImage(itemData.iconPath));
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Microsoft Yahei", 10));
        painter->drawText(singerRect, itemData.singer);

        painter->setPen(QPen(Qt::gray));
        painter->drawText(songNbRect, itemData.songsNb);

        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)

    return QSize(option.rect.width(), 50);
}

void FrendDemo::createUi()
{
    model = new ItemModel();

    //初始化数据
    for (int i = 0; i < icons.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        MuItemData itemData;
        itemData.singer = singers.at(i);
        itemData.songsNb = QString::number(i * i) + "首";
        itemData.iconPath = icons.at(i);
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
        model->appendRow(pItem);
    }

    itemDelegate = new ItemDelegate(this);

    ui.listView->setItemDelegate(itemDelegate);
    ui.listView->setModel(model);
}

//ItemView::ItemView(QObject * parent)
//    :QListView(parent)
//{
//}

ItemModel::ItemModel(QObject * parent)
    : QStandardItemModel(parent)
{
}
