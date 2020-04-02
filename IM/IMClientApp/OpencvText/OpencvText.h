#pragma once

#include <QtWidgets/QWidget>
#include "ui_OpencvText.h"

class OpencvText : public QWidget
{
    Q_OBJECT

public:
    OpencvText(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpencvTextClass ui;
};
