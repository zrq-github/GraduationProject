#include "ChatPanel.h"
#include "ui_ChatPanel.h"
#include <QLineEdit>
#include <QDateTime>
#include <QDebug>

QString ChatPanel::getTitle()
{
    return ui->labName->text();
}

void ChatPanel::closeEvent(QCloseEvent * event)
{//�ر�ǰ�����ź�
    emit signClose(m_chatID);
}

ChatPanel::ChatPanel(QString meID, QString id,QString name, QWidget *parent)
    : QWidget(parent)
{
    this->m_chatID = id;
    this->m_chatName = name;
    this->m_meID = meID;
    ui = new Ui::ChatPanel();
    ui->setupUi(this);
    createUi();
    binSlots();
}

ChatPanel::~ChatPanel()
{
    delete ui;
}

void ChatPanel::createUi()
{
    ui->textEdit->setReadOnly(true);
}

void ChatPanel::binSlots()
{

    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slot_btnSend_click()));    //�����ı��¼�
}

void ChatPanel::dealMessage(QString & sendId, QString & time, QString & data)
{
    QString qstr = sendId + " " + time + "\n" + data + "\n";
    ui->textEdit->append(qstr);
}

//void ChatPanel::dealMessage(QNChatMessage * messageW, QListWidgetItem * item, QString text, QString time, QNChatMessage::User_Type type)
//{
//    messageW->setFixedWidth(this->width());
//    QSize size = messageW->fontRect(text);
//    item->setSizeHint(size);
//    item->setSelected(false);
//    messageW->setText(text, time, size, type);
//    ui->listWidget->setItemWidget(item, messageW);
//}
//
//void ChatPanel::dealMessageTime(QString curMsgTime)
//{   //���������Ϣ���һ����,��ʵ��ʱ��
//    bool isShowTime = false;
//    if (ui->listWidget->count() > 0) {
//        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
//        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
//        int lastTime = messageW->time().toInt();
//        int curTime = curMsgTime.toInt();
//        qDebug() << "curTime lastTime:" << curTime - lastTime;
//        isShowTime = ((curTime - lastTime) > 60); // ������Ϣ���һ����
////        isShowTime = true;
//    }
//    else {
//        isShowTime = true;
//    }
//
//    if (isShowTime) {
//        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
//        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);
//
//        QSize size = QSize(this->width(), 40);
//        itemTime->setFlags(itemTime->flags()  & ~Qt::ItemIsSelectable);
//
//        messageTime->resize(size);
//        itemTime->setSizeHint(size);
//        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
//        ui->listWidget->setItemWidget(itemTime, messageTime);
//    }
//}

void ChatPanel::slot_btnSend_click()
{
    //�õ��ı�
    QString msg = ui->editSend->toPlainText();
    ui->editSend->setText("");
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss");

    dealMessage(m_meID, current_date, msg);
}