#pragma once

#include <QWidget>
namespace Ui { class IMTitleBarPanel; };

class IMTitleBarPanel : public QWidget
{
    Q_OBJECT

public:
    IMTitleBarPanel(QWidget *parent = Q_NULLPTR);
    ~IMTitleBarPanel();

private:
    Ui::IMTitleBarPanel *ui;
    void createUi();
};
