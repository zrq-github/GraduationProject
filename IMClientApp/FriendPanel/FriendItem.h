#pragma once

#include <QWidget>
#include "friendpanel_global.h"
namespace Ui { class FriendItem; };

class QLabel;

class FRIENDPANEL_EXPORT FriendItem : public QWidget
{
    Q_OBJECT

public:
    FriendItem(QWidget *parent = Q_NULLPTR);
    ~FriendItem();

private:
    void createUi();

    QLabel *m_labHead;
    QLabel *m_labName;
    QLabel *m_labSign;
    QLabel *m_labWarn;
};
