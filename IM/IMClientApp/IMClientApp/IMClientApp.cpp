#include "IMClientApp.h"
#include "LogonPanel/LogonPanel.h"
#include <QHBoxLayout>
#include "FriendPanel/FriendPanel.h"
#include "ChatPanel/ChatPanel.h"

IMClientApp::IMClientApp(QWidget *parent)
    : QWidget(parent)
    , m_friendPanel(Q_NULLPTR)
    , m_hashFriendPanel(Q_NULLPTR)
{
    ui.setupUi(this);
    //��ʼ������
    m_hashFriendPanel = new QHash<QString, ChatPanel *>;
    createUi();
    bindSigns();
}

void IMClientApp::bindSigns()
{
    connect(m_friendPanel, &FriendPanel::signCreateChatPanel, this, &IMClientApp::slotCreateChatPanel);
}

void IMClientApp::slotCreateChatPanel(QString id, QString name)
{
    //����֮ǰ���жϸ�������Ƿ����
    if (m_hashFriendPanel->value(id)!=nullptr)
    {
        return;
    }
    ChatPanel *chat = new ChatPanel(id,name);
    connect(chat, &ChatPanel::signClose, this, &IMClientApp::slotDeletChatPanel);
    chat->setWindowTitle(name + "(" + id + ")");
    chat->show();
    m_hashFriendPanel->insert(id, chat);
}

void IMClientApp::createUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    m_friendPanel = new FriendPanel(this);
    layout->addWidget(m_friendPanel);
    this->setLayout(layout);
}

void IMClientApp::slotDeletChatPanel(QString id)
{
    QHash<QString, ChatPanel *>::iterator it = m_hashFriendPanel->find(id);
    if (it != m_hashFriendPanel->end())
    {
        ChatPanel* cp = it.value();
        delete cp;
        cp = Q_NULLPTR;
        m_hashFriendPanel->erase(it);
    }
}
