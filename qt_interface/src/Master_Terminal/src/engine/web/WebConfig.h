#ifndef WEBCONFIG_H
#define WEBCONFIG_H

#include "../../app_settings.h"
#include <QDebug>
#include "WebConfig_Preset.h"



class WebConfig: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString version_info_url READ version_info_url WRITE setVersion_info_url NOTIFY version_info_urlChanged)
    Q_PROPERTY(QString update_url READ update_url WRITE setUpdate_url NOTIFY update_urlChanged)
    Q_PROPERTY(QString code_override_url READ code_override_url WRITE setCode_override_url NOTIFY code_override_urlChanged)

public:
    explicit WebConfig(QObject *parent = nullptr): QObject(parent){
        set_preset(WebConfig_Preset());
    };
    ~WebConfig(){ }

    WebConfig_Preset make_preset();
    void set_preset(const WebConfig_Preset& _preset);

    const QString &version_info_url() const;
    void setVersion_info_url(const QString &newVersion_info_url);
    const QString &update_url() const;
    void setUpdate_url(const QString &newUpdate_url);
    const QString &code_override_url() const;
    void setCode_override_url(const QString &newCode_override_url);

signals:
    void version_info_urlChanged();
    void update_urlChanged();
    void code_override_urlChanged();

private:
    QString m_version_info_url;// = App_settings::DEFAULT_VERSION_INFO_ADDRESS;
    QString m_update_url;// = App_settings::DEFAULT_UPDATE_ADDRESS;
    QString m_code_override_url;// = App_settings::DEFAULT_CODE_OVERRIDE_ADDRESS;

};


#endif // WEBCONFIG_H
