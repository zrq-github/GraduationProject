#pragma once

#include <QtWidgets/QWidget>
#include "ui_IMClientApp.h"

class FriendPanel;

class IMClientApp : public QWidget
{
    Q_OBJECT

public:
    IMClientApp(QWidget *parent = Q_NULLPTR);
private:
    void bindSigns();
    void createUi();
private:
    Ui::IMClientAppClass ui;
    FriendPanel *friendPanel;
};
