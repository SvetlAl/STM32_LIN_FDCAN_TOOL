#ifndef WEBCONFIG_PRESET_H
#define WEBCONFIG_PRESET_H

#include <stdlib.h>
#include <iostream>
#include "../../app_settings.h"


#ifdef QT_IN_USE
class WebConfig_Preset{
public:
    explicit WebConfig_Preset() = default;
     WebConfig_Preset(
             QString _version_info_url,
             QString _update_url,
             QString _code_override_url):
         version_info_url(_version_info_url),
         update_url(_update_url),
         code_override_url(_code_override_url){}

    ~WebConfig_Preset() = default;

     friend QDataStream& operator >>( QDataStream& d, WebConfig_Preset& wcp);
     friend QDataStream& operator << (QDataStream& d, const WebConfig_Preset& wcp);

    const QString &getVersion_info_url() const;
    const QString &getUpdate_url() const;
    const QString &getCode_override_url() const;

private:
    QString version_info_url = App_settings::DEFAULT_VERSION_INFO_ADDRESS;
    QString update_url = App_settings::DEFAULT_UPDATE_ADDRESS;
    QString code_override_url = App_settings::DEFAULT_CODE_OVERRIDE_ADDRESS;
};

QDataStream& operator << (QDataStream& d, const WebConfig_Preset& wcp);
QDataStream& operator >> (QDataStream& d, WebConfig_Preset& wcp);

#endif

#ifndef QT_IN_USE
#include "../../engine/file_manager/SimpleSerializer.h"
using namespace std;

class WebConfig_Preset{
public:
    explicit WebConfig_Preset() = default;
     WebConfig_Preset(
             string _version_info_url,
             string _update_url,
             string _code_override_url):
         version_info_url(_version_info_url),
         update_url(_update_url),
         code_override_url(_code_override_url){}

    ~WebConfig_Preset() = default;


    std::ostream& serialize (std::ostream &out){
        out << bits(this->version_info_url);
        out << bits(this->update_url);
        out << bits(this->code_override_url);
        return out;
    }

    std::istream& serialize(std::istream &in){
        in >> bits(this->version_info_url);
        in >> bits(this->update_url);
        in >> bits(this->code_override_url);
        return in;
    }


    const string &getVersion_info_url() const;
    const string &getUpdate_url() const;
    const string &getCode_override_url() const;

private:
    string version_info_url = App_settings::DEFAULT_VERSION_INFO_ADDRESS;
    string update_url = App_settings::DEFAULT_UPDATE_ADDRESS;
    string code_override_url = App_settings::DEFAULT_CODE_OVERRIDE_ADDRESS;
};

#endif

#endif // WEBCONFIG_PRESET_H
