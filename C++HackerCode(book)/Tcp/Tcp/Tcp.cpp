// Tcp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#pragma comment (lib, "ws2_32")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    sockaddr_in sockaddr;
    sockaddr.sin_family = PF_INET;
    sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sockaddr.sin_port = htons(827);
    
    bind(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));
    
    listen(s, 1);
    
    SOCKADDR clientAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clientSock;
    clientSock = accept(s, (SOCKADDR*)&clientAddr, &nSize);
    
    send(clientSock, "hello client \r\n", strlen("hello client \r\n") + sizeof(char), NULL);
    
    closesocket(clientSock);
    closesocket(s);
    
    WSACleanup();
    return 0;
}
