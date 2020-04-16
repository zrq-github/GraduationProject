#pragma once

#include <QDialog>
namespace Ui { class RegisterPanel; };

class RegisterPanel : public QDialog
{
    Q_OBJECT

public:
    RegisterPanel(QWidget *parent = Q_NULLPTR,int type=0);  //0ΪĬ��,1Ϊ��������
    ~RegisterPanel();
private:
    void bindSigns();
    void changeUi();

    bool verifyAccount(QString strId);   //��֤�˺��Ƿ���Ϲ淶
    bool verifyAccountPawd(QString strPawd);    //��֤�����Ƿ���Ϲ淶
private slots:
    void slot_btnRegister_clicked();
private:
    Ui::RegisterPanel *ui;
    int m_type;
};
