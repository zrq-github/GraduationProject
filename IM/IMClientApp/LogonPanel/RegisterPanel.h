#pragma once

#include <QDialog>
namespace Ui { class RegisterPanel; };

class RegisterPanel : public QDialog
{
    Q_OBJECT

public:
    RegisterPanel(QWidget *parent = Q_NULLPTR,int type=0);  //0为默认,1为忘记密码
    ~RegisterPanel();
private:
    void bindSigns();
    void changeUi();
private slots:
    void slot_btnRegister_clicked();
private:
    Ui::RegisterPanel *ui;
    int m_type;
};
