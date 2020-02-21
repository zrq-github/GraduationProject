#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_clientApp.h"

class clientApp : public QMainWindow
{
    Q_OBJECT

public:
    clientApp(QWidget *parent = Q_NULLPTR);

private:
    Ui::clientAppClass ui;
};
