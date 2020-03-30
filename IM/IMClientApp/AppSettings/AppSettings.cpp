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

QString AppSettings::getUserID()
{
    return m_userID;
}

void AppSettings::setUserID(QString id)
{
    this->m_userID = id;
}

QString AppSettings::getUserName()
{
    return m_userName;
}

void AppSettings::setUserName(QString name)
{
    this->m_userName = name;
}

QVariant AppSettings::getLogonSettings(QString key/*userID, userPswd,isRemember,*/)
{
    QString group = "LogonSettings";
    return getSetting(group, key);
}

void AppSettings::setLogonSettings(QString key,QVariant value)
{
    QString group = "LogonSettings";
    setSetting(group, key,value);
}

AppSettings::AppSettings()
{
    this->init();
}

void AppSettings::init()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString fileName = "config.ini";
    m_settings = new QSettings(appDirPath + "/" + fileName, QSettings::IniFormat);
    //判断配置文件是否存在
    QFileInfo fileInfo(appDirPath + "/" + fileName);
    if (fileInfo.exists())
    {
        return;
    }
    else
    {   //初始化配置文件
        m_settings->setIniCodec("UTF-8");
        //初始化登录设置
        m_settings->beginGroup("LogonSettings");
        m_settings->setValue("userID", "");
        m_settings->setValue("userPswd", "");
        m_settings->setValue("isRemember", false);
        m_settings->endGroup();
        //初始化服务器设置
        m_settings->beginGroup("server");
        m_settings->setValue("name", "servername");
        m_settings->setValue("ip", "127.0.0.0");
        m_settings->setValue("port", 1200);
        m_settings->endGroup();
    }
}
