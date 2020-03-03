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
        //初始化
        init();
    }
    return *m_appSettings;
}

QVariant AppSettings::getSetting(QString key)
{
    return m_settings->value(key);
}

void AppSettings::setSetting(QString key, QVariant value)
{
    return m_settings->setValue(key, value);
}

AppSettings::AppSettings()
{
}

void AppSettings::init()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString fileName = "config.ini";

    //判断配置文件是否存在
    QFileInfo fileInfo(appDirPath + "/" + fileName);
    if (fileInfo.exists())
    {
        return;
    }
    else
    {   //初始化配置文件
        m_settings = new QSettings(appDirPath + "/" + fileName, QSettings::IniFormat);
        m_settings->setIniCodec("UTF-8");

        m_settings->beginGroup("SQL-Standard");
        m_settings->setValue("hostName", "127.0.0.1");
    }
}
