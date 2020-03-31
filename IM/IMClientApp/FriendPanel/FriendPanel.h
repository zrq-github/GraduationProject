#pragma once

#include <QWidget>
#include "FriendModel.h"
#include "friendpanel_global.h"
namespace Ui { class FriendPanel; };

class FRIENDPANEL_EXPORT FriendPanel : public QWidget
{
    Q_OBJECT

public:
    FriendPanel(QWidget *parent = Q_NULLPTR);
    ~FriendPanel();

    void initFriendData(QVector<FriendDataPtr> &data);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
signals:
    void signCreateChatPanel(QString id, QString name);
private slots:
    void slotAddGroup(bool isAdd);
private:
    void bindSigns();
    void createUi();
private:
    Ui::FriendPanel *ui;

    FriendModel *m_pModel;
    FriendView  *m_pView;
};
