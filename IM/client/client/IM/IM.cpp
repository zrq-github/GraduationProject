#include "IM.h"
#include "ui_IM.h"
#include <QMoveEvent>
#include "IMTitleBarPanel/IMTitleBarPanel.h"

IM::IM(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::IM();
    ui->setupUi(this);
    this->createUi();
    //this->setWindowFlags(Qt::FramelessWindowHint);      //�ޱ߿򣬵�����������ʾ�Ի������
}

IM::~IM()
{
    delete ui;
}

void IM::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mousePressEvent(event);
}

void IM::mouseMoveEvent(QMouseEvent * event)
{
    if (m_moving && (event->buttons() && Qt::LeftButton)
        && (event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void IM::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event);
    m_moving = false; //ֹͣ�ƶ�
}

void IM::createUi()
{
    IMTitleBarPanel *titleBar = new IMTitleBarPanel;
    ui->layoutTitleBar->addWidget(titleBar, 0, Qt::AlignLeft);
}

