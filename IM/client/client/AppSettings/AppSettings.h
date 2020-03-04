#pragma once
/*
** 应用配置信息的读写(单例模式)
*/

#include "appsettings_global.h"
#include <QSettings>

#define appSettingsInstance AppSettings::getInstance()

class APPSETTINGS_EXPORT AppSettings
{
public:
    static AppSettings &getInstance();
    static QVariant getSetting(QString key);
    static QVariant getSetting(QString group,QString key);
    static void setSetting(QString key, QVariant value);
    static void setSetting(QString group,QString key, QVariant value);
private:
    AppSettings();
private:
    static void init();
    static AppSettings *m_appSettings;
    static QSettings *m_settings;
};
