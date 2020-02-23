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
    void mousePressEvent(QMouseEvent *event);       //用于鼠标拖动窗口的鼠标事件操作
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    m_moving = false;           //表示窗口是否在鼠标操作下移动
    QPoint  m_lastPos;                  //上一次的鼠标位置
private:
    Ui::IM *ui;
    void createUi();
};
