#ifndef QIMAGETOOL_H
#define QIMAGETOOL_H
/**
 * ��Ҫ��ͼƬ��һЩ����
 */
#include <QObject>
class QImageTool : public QObject
{
    Q_OBJECT
public:
    QImageTool(QObject *parent);
    ~QImageTool();
    

    /**
     * ѹ��ͼƬΪָ�����
     */
    static  QPixmap scaledPixmap(const QPixmap &src, int width, int height);


    /**
     * Բ��ͼƬ
     * src ԭͼƬ
     * radius ͼƬ�뾶
     */
    static QPixmap generatePixmap(const QPixmap &src, const int &radius);
};
#endif