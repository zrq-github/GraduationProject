#pragma once
/*
** 
*/

#include <QWidget>
#include "im_global.h"
namespace Ui { class IM; };

class IM_EXPORT IM : public QWidget
{
    Q_OBJECT

public:
    IM(QWidget *parent = Q_NULLPTR);
    ~IM();

protected:
    void mousePressEvent(QMouseEvent *event);       //��������϶����ڵ�����¼�����
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;           //��ʾ�����Ƿ������������ƶ�
    QPoint  m_lastPos;                  //��һ�ε����λ��
private:
    Ui::IM *ui;
    void createUi();
};
