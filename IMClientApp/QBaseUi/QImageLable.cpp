#include "QImageLable.h"
#include <QPainter>
#include <QDebug>

QImageLable::QImageLable(QWidget *parent)
    : QLabel(parent)
{

}

QImageLable::QImageLable(const QPixmap & pixmap, QWidget *parent /* = Q_NULLPTR */)
    :QLabel(parent)
{
    setScaledContents(true);
    setPixmap(pixmap);

}

QImageLable::QImageLable(const QPixmap & pixmap, const int & radius, QWidget *parent /* = Q_NULLPTR */)
{
    QPixmap &pix = generatePixmap(pixmap, radius);
    QImageLable(pix, parent);
}

QPixmap QImageLable::scaledPixmap(const QPixmap & src, int width, int height)
{
    return src.scaled(width, (height == 0 ? width : height),
        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

QPixmap QImageLable::generatePixmap(const QPixmap & src, const int & radius)
{
    // ��ЧͼƬ������
    if (src.isNull()) {
        qDebug() << QString::fromLocal8Bit("QImageTool ��ЧͼƬ");
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

    qDebug() << QString::fromLocal8Bit("QImageTool ����Բ�����");
    return dest;
}

QImageLable::~QImageLable()
{
    
}
