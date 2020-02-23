#pragma once

#include <QWidget>
#include "imtitlebarpanel_global.h"
namespace Ui { class IMTitleBarPanel; };

class IMTITLEBARPANEL_EXPORT IMTitleBarPanel : public QWidget
{
    Q_OBJECT

public:
    IMTitleBarPanel(QWidget *parent = Q_NULLPTR);
    ~IMTitleBarPanel();

private:
    Ui::IMTitleBarPanel *ui;
    void createUi();
};
