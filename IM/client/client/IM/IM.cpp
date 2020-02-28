#include "IM.h"
#include "ui_IM.h"
#include <QMoveEvent>
#include "IMTitleBarPanel.h"
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"
#include <QSplitter>

IM::IM(QWidget *parent)
    : QWidget(parent)
    , friendPanel(Q_NULLPTR)
    , chatPanel(Q_NULLPTR)
{
    ui = new Ui::IM();
    ui->setupUi(this);
    this->createUi();
    //this->setWindowFlags(Qt::FramelessWindowHint);      //无边框，但是在任务显示对话框标题
    this->binSlots();
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
    m_moving = false; //停止移动
}

void IM::createUi()
{
    IMTitleBarPanel *titleBar = new IMTitleBarPanel;
    ui->layoutTitleBar->addWidget(titleBar, 0, Qt::AlignLeft);
    friendPanel = new FriendPanel;
    chatPanel = new ChatPanel;

    QSplitter *splitterLMain = new QSplitter(Qt::Horizontal, 0);
    ui->horizontalLayout->addWidget(splitterLMain);

    QSplitter *splitterLeft = new QSplitter(splitterLMain);
    splitterLeft->setMinimumWidth(100);
    splitterLeft->setChildrenCollapsible(true);
    splitterLeft->addWidget(friendPanel);

    QSplitter *splitterRight = new QSplitter(splitterLMain);
    splitterRight->addWidget(chatPanel);

    splitterLMain->setStretchFactor(1, 3);
}

void IM::binSlots()
{
    connect(friendPanel, SIGNAL(childClick(QString&, QString&)),
        chatPanel, SLOT(slotChatterChange(QString&, QString&)));
}

