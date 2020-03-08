#include "AppSettings.h"

#include <QDir>
#include <QDebug>
#include <QCoreApplication>

AppSettings *AppSettings::m_appSettings = nullptr;
QSettings *AppSettings::m_settings = nullptr;

AppSettings &AppSettings::getInstance()
{
    if (m_appSettings == nullptr)
    {
        m_appSettings = new AppSettings();
        //��ʼ��
        init();
    }
    return *m_appSettings;
}

QVariant AppSettings::getSetting(QString key)
{
    return m_settings->value(key);
}

QVariant AppSettings::getSetting(QString group, QString key)
{
    return m_settings->value(group + "/" + key);
}

void AppSettings::setSetting(QString key, QVariant value)
{
    return m_settings->setValue(key, value);
}

void AppSettings::setSetting(QString group, QString key, QVariant value)
{
    return m_settings->setValue(group + "/" + key, value);
}

AppSettings::AppSettings()
{
}

void AppSettings::init()
{
    //������Ϣ����д��
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString fileName = "config.ini";
    m_settings = new QSettings(appDirPath + "/" + fileName, QSettings::IniFormat);
    //�ж������ļ��Ƿ����
    QFileInfo fileInfo(appDirPath + "/" + fileName);
    if (fileInfo.exists())
    {
        return;
    }
    else
    {   //��ʼ�������ļ�
        m_settings->setIniCodec("UTF-8");
        m_settings->beginGroup("LogonSettings");
        m_settings->setValue("lastLogonId", "");
        m_settings->setValue("lastLogonPswd", "");
        m_settings->setValue("rememberPswd",false);
        m_settings->endGroup();
    }
}
