#pragma once

#include "logonpanel_global.h"
#include <QtWidgets/qdialog.h>

namespace Ui
{
    class LogonClass;
}

namespace IM
{
    class LOGONPANEL_EXPORT LogonPanel:public QDialog
    {
        Q_OBJECT
    public:
        LogonPanel(QWidget *parent=Q_NULLPTR);
    private:
        Ui::LogonClass *ui;
    };

}
