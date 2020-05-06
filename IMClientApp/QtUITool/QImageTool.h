#ifndef QIMAGETOOL_H
#define QIMAGETOOL_H
/**
 * 主要对图片的一些操作
 */
#include <QObject>
class QImageTool : public QObject
{
    Q_OBJECT
public:
    QImageTool(QObject *parent);
    ~QImageTool();
    

    /**
     * 压缩图片为指定宽高
     */
    static  QPixmap scaledPixmap(const QPixmap &src, int width, int height);


    /**
     * 圆角图片
     * src 原图片
     * radius 图片半径
     */
    static QPixmap generatePixmap(const QPixmap &src, const int &radius);
};
#endif