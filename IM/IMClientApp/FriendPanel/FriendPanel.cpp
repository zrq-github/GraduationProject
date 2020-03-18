#include "FriendPanel.h"
#include "ui_FriendPanel.h"
#include <QListView>
#include <QVBoxLayout>
#include "FriendModel.h"
#include <QToolBox>

FriendPanel::FriendPanel(QWidget *parent)
    : QWidget(parent)
    , m_pModel(Q_NULLPTR)
    , m_pView(Q_NULLPTR)
{
    ui = new Ui::FriendPanel();
    ui->setupUi(this);

    QVector<FriendData*> *data = new QVector<FriendData *>;
    for (int i = 0; i < 10; i++)
    {
        FriendData *d = new FriendData;
        d->id = QString::number(i);
        d->name = QString::number(i);
        data->append(d);
    }

    m_pModel = new FriendModel(this);
    m_pModel->initData(*data);
    m_pView = new FriendView(this);
    m_pView->setModel(m_pModel);

    createUi();
    bindSigns();
}

FriendPanel::~FriendPanel()
{
    delete ui;
}

void FriendPanel::contextMenuEvent(QContextMenuEvent * event)
{
}

void FriendPanel::slotAddGroup(bool isAdd)
{
}

void FriendPanel::bindSigns()
{
    connect(m_pView, &FriendView::signCreateChatPanel, this, &FriendPanel::signCreateChatPanel);    //×ª·¢ÐÅºÅ
}

void FriendPanel::createUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setGeometry(QRect(0, 0, 0, 0));
    mainLayout->setMargin(0);

    mainLayout->addWidget(m_pView);

    this->setLayout(mainLayout);
}

