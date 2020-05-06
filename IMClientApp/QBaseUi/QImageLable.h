#ifndef QIMAGELABLE_H_
#define QIMAGELABLE_H_
/**
 * 展示图片用的label 提供圆角方案 
 * 
 */
#include <QLabel>
#include "qbaseui_global.h"

class QBASEUI_EXPORT QImageLable : public QLabel
{
    Q_OBJECT

public:
    QImageLable(QWidget *parent = Q_NULLPTR);
    QImageLable(const QPixmap & pixmap, QWidget *parent = Q_NULLPTR);
    QImageLable(const QPixmap & pixmap, const int & radius,QWidget *parent = Q_NULLPTR);

    QPixmap scaledPixmap(const QPixmap &src, int width, int height);
    QPixmap generatePixmap(const QPixmap &src, const int &radius);

    ~QImageLable();
private:
};
#endif
