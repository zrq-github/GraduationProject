#pragma once

#include <QtWidgets/QWidget>
#include "ui_UITest.h"

class UITest : public QWidget
{
    Q_OBJECT

public:
    UITest(QWidget *parent = Q_NULLPTR);

private:
    Ui::UITestClass ui;
};
