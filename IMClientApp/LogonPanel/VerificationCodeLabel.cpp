#include "VerificationCodeLabel.h"
#include <QDebug>

VerificationCodeLabel::VerificationCodeLabel(QWidget *parent)
    : QLabel(parent)
{
    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());
    colorArray = new QColor[letter_number];
    verificationCode = new QChar[letter_number];
    noice_point_number = this->width();

    produceVerificationCode();//产生4个不同的字符
    produceRandomColor();//产生4个不同的颜色
}

VerificationCodeLabel::~VerificationCodeLabel()
{
}

QString VerificationCodeLabel::getVerify()
{
    QString code = "";
    for (int i = 0; i < letter_number; ++i)
    {
        code += verificationCode[i];
    }

    return code;
}

void VerificationCodeLabel::refreshVerify()
{
    produceVerificationCode();//产生4个不同的字符
    produceRandomColor();//产生4个不同的颜色
    update();
}

void VerificationCodeLabel::paintEvent(QPaintEvent * event)
{
    qDebug() << "调用labe 重绘事件";

    QPainter painter(this);
    QPoint p;
    painter.fillRect(this->rect(), Qt::white);
    //绘制验证码 
    for (int i = 0; i < letter_number; ++i)
    {
        p.setX(i*(this->width() / letter_number) + this->width() / 8);
        p.setY(this->height() / 1.5);

        painter.setPen(colorArray[i]);
        QFont font;
        font.setPixelSize(30);
        painter.setFont(font);
        painter.drawText(p, QString(verificationCode[i]));
    }
    //绘制噪点
    for (int j = 0; j < noice_point_number; ++j)
    {
        p.setX(qrand() % this->width());
        p.setY(qrand() % this->height());
        painter.setPen(colorArray[j % 4]);
        painter.drawPoint(p);
    }
    return;
}

void VerificationCodeLabel::mousePressEvent(QMouseEvent * ev)
{
    this->refreshVerify();
}

void VerificationCodeLabel::produceVerificationCode()
{
    for (int i = 0; i < letter_number; ++i)
    {
        verificationCode[i] = produceRandomLetter();
    }
    return;
}

QChar VerificationCodeLabel::produceRandomLetter()
{
    QChar c;
    int flag = qrand() % letter_number;
    switch (flag)
    {
    case 0:
        c = '0' + qrand() % 10;
        break;
    case 1:
        c = 'A' + qrand() % 26;
        break;
    case 2:
        c = 'a' + qrand() % 26;
        break;
    default:
        c = '0' + qrand() % 10;
        break;
    }
    return c;
  
    return QChar();
}

void VerificationCodeLabel::produceRandomColor()
{
    for (int i = 0; i < letter_number; ++i)
    {
        colorArray[i]= QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    }
    return;
}
