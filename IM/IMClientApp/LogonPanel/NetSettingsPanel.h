#pragma once

#include <QDialog>
#include "logonpanel_global.h"
namespace Ui { class NetSettingsPanel; };

class LOGONPANEL_EXPORT NetSettingsPanel : public QDialog
{
    Q_OBJECT

public:
    NetSettingsPanel(QWidget *parent = Q_NULLPTR);
    ~NetSettingsPanel();

private slots:
    void slotBtnSave();
private:
    void createUi();
    void bindSign();
    Ui::NetSettingsPanel *ui;
};
