#pragma once

#include <QWidget>
namespace Ui { class AnyChatSDKTest; };

class AnyChatSDKTest : public QWidget
{
    Q_OBJECT

public:
    AnyChatSDKTest(QWidget *parent = Q_NULLPTR);
    ~AnyChatSDKTest();

private:
    Ui::AnyChatSDKTest *ui;
    QString szCoreSDKPath;

    void initAnyChat();
private slots:
    void on_btnConnect_clicked();
};
