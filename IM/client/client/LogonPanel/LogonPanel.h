#pragma once

#include <QDialog>
#include "logonpanel_global.h"
namespace Ui { class LogonPanel; };

class LOGONPANEL_EXPORT LogonPanel : public QDialog
{
    Q_OBJECT

public:
    LogonPanel(QWidget *parent = Q_NULLPTR);
    ~LogonPanel();

private:
    Ui::LogonPanel *ui;
};
