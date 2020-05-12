#ifndef REGISTERPANEL_H_
#define REGISTERPANEL_H_

#include <QDialog>
#include <QTcpSocket>
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

    bool verifyAccount(QString strId);          //验证账号是否符合规范
    bool verifyAccountPawd(QString strPawd);    //验证密码是否符合规范
private slots:
    void slot_btnRegister_clicked();
    void slot_sockt_readData();
private:
    Ui::RegisterPanel *ui;
    int m_type;
    QTcpSocket *m_socket;
};

#endif