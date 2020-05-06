#include "QImageTool.h"
#include <QPixmap>
#include <QPainter>
#include <QDebug>

QImageTool::QImageTool(QObject *parent)
    : QObject(parent)
{
}

QImageTool::~QImageTool()
{
}

QPixmap QImageTool::scaledPixmap(const QPixmap & src, int width, int height)
{
    return src.scaled(width, (height == 0 ? width : height),
        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QPixmap QImageTool::generatePixmap(const QPixmap & src, const int & radius)
{
    // 无效图片不处理
    if (src.isNull()) {
        qDebug() << QString::fromLocal8Bit("QImageTool 无效图片");
        return src;
    }
    // 压缩图片
    QPixmap pixmap = scaledPixmap(src, radius * 2, radius * 2);

    QPixmap dest(2 * radius, 2 * radius);
    dest.fill(Qt::transparent);
    QPainter painter(&dest);
    // 抗锯齿 + 平滑边缘处理
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // 裁剪为圆角
    QPainterPath path;
    path.addEllipse(0, 0, 2 * radius, 2 * radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 2 * radius, 2 * radius, pixmap);

    qDebug() << QString::fromLocal8Bit("QImageTool 处理圆角完成");
    return dest;
}
