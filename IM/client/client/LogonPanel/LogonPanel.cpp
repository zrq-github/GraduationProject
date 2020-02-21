#include "LogonPanel.h"
#include "ui_LogonPanel.h"

namespace IM
{
    LogonPanel::LogonPanel(QWidget *parent)
        :QDialog(parent)
    {
        if (ui != NULL)
        {
            ui->setupUi(this);
        }
    }

}
