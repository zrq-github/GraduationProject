#ifndef AppSettings_H
#define AppSettings_H

/*
** Ӧ��������Ϣ�Ķ�д(����ģʽ)
*/

#include "appsettings_global.h"
#include <QSettings>

#define IMSettings AppSettings::getInstance()

class APPSETTINGS_EXPORT AppSettings
{
public:
    static AppSettings &getInstance();

    QVariant getSetting(QString key);
    QVariant getSetting(QString group, QString key);
    void setSetting(QString key, QVariant value);
    void setSetting(QString group,QString key, QVariant value);

    //IM��װ
    QVariant getLogonSettings(QString key);
    void setLogonSettings(QString key, QVariant value);
private:
    AppSettings();
private:
    virtual void init();

    static AppSettings *m_appSettings;
    static QSettings *m_settings;
};
#endif