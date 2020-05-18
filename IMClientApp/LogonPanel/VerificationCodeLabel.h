#ifndef VERIFICATIONCODELABEL_H_
#define VERIFICATIONCODELABEL_H_

#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include "logonpanel_global.h"

class LOGONPANEL_EXPORT VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=nullptr);
    ~VerificationCodeLabel();

    QString getVerify();
    inline void refreshVerify();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev);
private:
    const int letter_number = 4;//产生字符的数量
    int noice_point_number=100;//噪点的数量
    void produceVerificationCode();//生成验证码
    QChar produceRandomLetter();//产生随机的字符
    void produceRandomColor();//产生随机的颜色

    QChar *verificationCode;
    QColor *colorArray;
};

#endif // !VERIFICATIONCODELABEL_H_