#include "WebConfig_Preset.h"

#ifdef QT_IN_USE

/********************************************************************
 *
 *
 *                    Class Setters/Getters
 *
 *
********************************************************************/

const QString &WebConfig_Preset::getVersion_info_url() const{
    return version_info_url;
}

const QString &WebConfig_Preset::getUpdate_url() const{
    return update_url;
}

const QString &WebConfig_Preset::getCode_override_url() const{
    return code_override_url;
}


/********************************************************************
 *
 *
 *                    Operators
 *
 *
********************************************************************/
QDataStream& operator << (QDataStream& d, const WebConfig_Preset& wcp){
    d << wcp.version_info_url;
    d << wcp.update_url;
    d << wcp.code_override_url;
    return d;
}

QDataStream& operator >> (QDataStream& d, WebConfig_Preset& wcp){
    d >> wcp.version_info_url;
    d >> wcp.update_url;
    d >> wcp.code_override_url;
    return d;
}

#endif

















// OBSOLETE
#ifndef QT_IN_USE

const string &WebConfig_Preset::getVersion_info_url() const
{
    return version_info_url;
}

const string &WebConfig_Preset::getUpdate_url() const
{
    return update_url;
}

const string &WebConfig_Preset::getCode_override_url() const
{
    return code_override_url;
}

#endif
