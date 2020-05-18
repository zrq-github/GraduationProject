#include "LogRecord.h"
#include <imagehlp.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

LogRecord::LogRecord()
{
    //��ʼ��
    memset(m_strLogPath, 0, MAX_STR_LEN);
    memset(m_strCurLogName, 0, MAX_STR_LEN);
    m_pFileStream = NULL;
    //����Ĭ�ϵ�д��־����
    m_nLogLevel = EnumLogLevel::LOGLEVELNORMAL;
    //��ʼ���ٽ�������
    InitializeCriticalSection(&m_cs);
    //������־�ļ���
    GenerateLogName();
}

LogRecord::LogRecord(const char * strLogPath, EnumLogLevel nLogLevel) :m_nLogLevel(nLogLevel)
{
    //��ʼ��
    m_pFileStream = NULL;
    strcpy(m_strLogPath, strLogPath);
    InitializeCriticalSection(&m_cs);
    CreateLogPath();
    GenerateLogName();
}

LogRecord::~LogRecord()
{
    //�ͷ��ٽ���
    DeleteCriticalSection(&m_cs);
    //�ر��ļ���
    if (m_pFileStream)
        fclose(m_pFileStream);
}
//д�ؼ���Ϣ�ӿ�
void LogRecord::TraceKeyInfo(const char * strInfo, ...)
{
    if (!strInfo)
        return;
    char pTemp[MAX_STR_LEN] = { 0 };
    strcpy(pTemp, GetCurrentTime());
    strcat(pTemp, KEYINFOPREFIX);
    //��ȡ�ɱ��β�
    va_list arg_ptr = NULL;
    va_start(arg_ptr, strInfo);
    vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
    va_end(arg_ptr);
    //д��־�ļ�
    Trace(pTemp);
    arg_ptr = NULL;
}

void LogRecord::TraceError(const char * strInfo, ...)
{//д������Ϣ
    //�жϵ�ǰ��д��־����������Ϊ��д��־��������
    if (m_nLogLevel >= EnumLogLevel::LOGLEVELSTOP)
        return;
    if (!strInfo)
        return;
    char pTemp[MAX_STR_LEN] = { 0 };
    strcpy(pTemp, GetCurrentTime());
    strcat(pTemp, ERRORPREFIX);
    va_list arg_ptr = NULL;
    va_start(arg_ptr, strInfo);
    vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
    va_end(arg_ptr);
    Trace(pTemp);
    arg_ptr = NULL;
}

void LogRecord::TraceWarning(const char * strInfo, ...)
{//д������Ϣ
    //�жϵ�ǰ��д��־����������Ϊֻд������Ϣ��������
    if (m_nLogLevel >= EnumLogLevel::LOGLEVELNORMAL)
        return;
    if (!strInfo)
        return;
    char pTemp[MAX_STR_LEN] = { 0 };
    strcpy(pTemp, GetCurrentTime());
    strcat(pTemp, WARNINGPREFIX);
    va_list arg_ptr = NULL;
    va_start(arg_ptr, strInfo);
    vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
    va_end(arg_ptr);
    Trace(pTemp);
    arg_ptr = NULL;
}
//дһ����Ϣ
void LogRecord::TraceInfo(const char * strInfo, ...)
{
    //�жϵ�ǰ��д��־����������ֻд����;�����Ϣ��������
    if (m_nLogLevel >= EnumLogLevel::LOGLEVELMID)
        return;
    if (!strInfo)
        return;
    char pTemp[MAX_STR_LEN] = { 0 };
    strcpy(pTemp, GetCurrentTime());
    strcat(pTemp, INFOPREFIX);
    va_list arg_ptr = NULL;
    va_start(arg_ptr, strInfo);
    vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
    va_end(arg_ptr);
    Trace(pTemp);
    arg_ptr = NULL;
}

void LogRecord::SetLogLevel(EnumLogLevel nLevel)
{//����д��־����
    m_nLogLevel = nLevel;
}

void LogRecord::Trace(const char * strInfo)
{//д�ļ�����
    if (!strInfo)
        return;
    try
    {
        //�����ٽ���
        EnterCriticalSection(&m_cs);
        //���ļ���û�д򿪣������´�
        if (!m_pFileStream)
        {
            char temp[1024] = { 0 };
            strcat(temp, m_strLogPath);
            strcat(temp, m_strCurLogName);
            m_pFileStream = fopen(temp, "a+");
            if (!m_pFileStream)
            {
                return;
            }
        }
        //д��־��Ϣ���ļ���
        fprintf(m_pFileStream, "%s\n", strInfo);
        fflush(m_pFileStream);
        //�뿪�ٽ���
        LeaveCriticalSection(&m_cs);
    }
    //�������쳣�������뿪�ٽ�������ֹ����
    catch (...)
    {
        LeaveCriticalSection(&m_cs);
    }
}
//��ȡϵͳ��ǰʱ��
char * LogRecord::GetCurrentTime()
{
    time_t curTime;
    struct tm * pTimeInfo = NULL;
    time(&curTime);
    pTimeInfo = localtime(&curTime);
    char temp[MAX_STR_LEN] = { 0 };
    sprintf(temp, "%02d:%02d:%02d", pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
    char * pTemp = temp;
    return pTemp;
}

void LogRecord::GenerateLogName()
{
    time_t curTime;
    struct tm * pTimeInfo = NULL;
    time(&curTime);
    pTimeInfo = localtime(&curTime);
    char temp[1024] = { 0 };
    //��־�������磺2013-01-01.log
    sprintf(temp, "%04d-%02d-%02d.log", pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday);
    if (0 != strcmp(m_strCurLogName, temp))
    {
        strcpy(m_strCurLogName, temp);
        if (m_pFileStream)
            fclose(m_pFileStream);
        char temp[1024] = { 0 };
        strcat(temp, m_strLogPath);
        strcat(temp, m_strCurLogName);
        //��׷�ӵķ�ʽ���ļ���
        m_pFileStream = fopen(temp, "a+");
    }
}


void LogRecord::CreateLogPath()
{
    if (0 != strlen(m_strLogPath))
    {
        strcat(m_strLogPath, "\\");
    }
    MakeSureDirectoryPathExists(m_strLogPath);
}