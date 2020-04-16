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
    // ��ЧͼƬ������
    if (src.isNull()) {
        qDebug() << "QImageTool ��ЧͼƬ";
        return src;
    }
    // ѹ��ͼƬ
    QPixmap pixmap = scaledPixmap(src, radius * 2, radius * 2);

    QPixmap dest(2 * radius, 2 * radius);
    dest.fill(Qt::transparent);
    QPainter painter(&dest);
    // ����� + ƽ����Ե����
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // �ü�ΪԲ��
    QPainterPath path;
    path.addEllipse(0, 0, 2 * radius, 2 * radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 2 * radius, 2 * radius, pixmap);

    qDebug() << "QImageTool ����Բ�����";
    return dest;
}
