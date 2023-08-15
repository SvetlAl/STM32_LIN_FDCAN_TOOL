#include "WebConfig.h"

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

WebConfig_Preset WebConfig::make_preset(){
    return WebConfig_Preset(
        m_version_info_url,
        m_update_url,
        m_code_override_url
    );
}

void WebConfig::set_preset(const WebConfig_Preset& _preset){
    setVersion_info_url(_preset.getVersion_info_url());
    setUpdate_url(_preset.getUpdate_url());
    setCode_override_url(_preset.getUpdate_url());
}

/********************************************************************
 *
 *
 *                     Class setters/getters
 *
 *
********************************************************************/

const QString &WebConfig::version_info_url() const{
    return m_version_info_url;
}

void WebConfig::setVersion_info_url(const QString &newVersion_info_url){
    if (m_version_info_url == newVersion_info_url)
        return;
    m_version_info_url = newVersion_info_url;
    emit version_info_urlChanged();
}

const QString &WebConfig::update_url() const{
    return m_update_url;
}

void WebConfig::setUpdate_url(const QString &newUpdate_url){
    if (m_update_url == newUpdate_url)
        return;
    m_update_url = newUpdate_url;
    emit update_urlChanged();
}

const QString &WebConfig::code_override_url() const{
    return m_code_override_url;
}

void WebConfig::setCode_override_url(const QString &newCode_override_url){
    if (m_code_override_url == newCode_override_url)
        return;
    m_code_override_url = newCode_override_url;
    emit code_override_urlChanged();
}



