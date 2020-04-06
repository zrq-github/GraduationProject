#include "AnyChatSDKTest.h"
#include "ui_AnyChatSDKTest.h"
#include <windows.h>
#include <BRAnyChatCoreSDK.h>
#include <cstring>

#pragma comment(lib,"BRAnyChatCore.lib")

AnyChatSDKTest::AnyChatSDKTest(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::AnyChatSDKTest();
    ui->setupUi(this);

    szCoreSDKPath = QCoreApplication::applicationDirPath();

    initAnyChat();
}

AnyChatSDKTest::~AnyChatSDKTest()
{
    delete ui;
}

void AnyChatSDKTest::initAnyChat()
{
    ulong dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY;
        //| BRAC_FUNC_CHKDEPENDMODULE | BRAC_FUNC_AUDIO_VOLUMECALC
        //| BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN;

    BRAC_InitSDK((HWND)this->winId(), dwFuncMode);
}

void AnyChatSDKTest::on_btnConnect_clicked()
{//连接服务器
    //DWORD port = 8900;
    //LPCTSTR lpctStr = (LPCTSTR)"127.0.0.1";
    DWORD port = 8906;
    LPCTSTR lpctStr = (LPCTSTR)"demo.anychat.cn";
    BRAC_Connect(lpctStr, port);
    BRAC_Login((LPCTSTR)"zrq", (LPCTSTR)"", 0);
    BRAC_EnterRoom(1, (LPCTSTR)"",0);
    int a = 0;
}
