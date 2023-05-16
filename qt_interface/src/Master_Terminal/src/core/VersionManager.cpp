#include "VersionManager.h"
#include <QFile>


void VersionManager::setCurrent_device_version(const QString &init_string){
    m_current_device_version = Version(init_string, static_cast <int>(Version::VerDesignCode::Device));
    emit current_device_versionChanged();
}

void VersionManager::setHardware_device_model(const QString &init_string){
    m_hardware_device_model_name = init_string.left(init_string.size() - 1);
    m_hardware_device_model_code = init_string.back().toLatin1();
    emit hardware_device_modelChanged();
}


void VersionManager::handleDeviceVersionInfo(){
    QFile file(App_settings::VERSION_INFO_CACHE_PATH);
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly)){
        m_pConsole->append_cdc_string("Click \"Update\" button to refresh version data.");
        return;
    }
    data = file.readAll();
    file.close();
    parseVersionInfo(data);
    m_available_interface_version = findLatestVersion(Version::VerDesignCode::Interface);
    m_available_device_version = findLatestVersion(Version::VerDesignCode::Device);
    fillCurrentVersionInfo(Version::VerDesignCode::Interface);

    if(isInterfaceInfoAppended) printInterfaceVersions();
    if(m_current_device_version.isValid() & m_pConsole->isConnected()) printDeviceVersions();
    emit isNewHardwareApplicationAvailableChanged();

}

char VersionManager::hardware_device_model_code() const{
    return m_hardware_device_model_code;
}

void VersionManager::parseVersionInfo(const QByteArray &data){
    versions_from_server.clear();
    const auto _c_newline = ""; //'\n';

    QList<QByteArray> lines = data.split('\n');

    for (int i = 0; i < lines.size(); i++) {
        QByteArray line = lines.at(i).trimmed();

        if (line == "[version]") {
            i++;

            line = lines.at(i).trimmed();

            int tmp_design_code = (line == "[device]") ? static_cast<int>(Version::VerDesignCode::Device) :
                                   (line == "[interface]") ? static_cast<int>(Version::VerDesignCode::Interface):
                                                             static_cast<int>(Version::VerDesignCode::Invalid);


            i++;
            line = lines.at(i).trimmed();
            QString tmp_init_string = QString::fromUtf8(line);
            QSharedPointer<Version> tmp_version(new Version(tmp_init_string, tmp_design_code));
            i++;
            line = lines.at(i).trimmed();

            if (line == "[description]") {
                i++;
                line = lines.at(i).trimmed();
            }
            /******************* Description **************************/
            QString tmp_description = "";
            if (line == "[Russian]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "[English]") {
                    line = lines.at(i).trimmed();
                    if(CurrentLanguage() == "Russian") tmp_description.append(QString::fromUtf8(line) + _c_newline);
                    i++;
                }
            }
            line = lines.at(i).trimmed();

            if (line == "[English]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "[errata]") {
                    line = lines.at(i).trimmed();

                    if(CurrentLanguage() == "English"){
                        tmp_description.append(QString::fromUtf8(line) + _c_newline);
                    }
                    i++;
                }
            }
            tmp_version.data()->setDescription(tmp_description);

            line = lines.at(i).trimmed();
            /******************* Errata **************************/
            if (line == "[errata]") {
                i++;
                line = lines.at(i).trimmed();
            }

            QString tmp_errata = "";
            if (line == "[Russian]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "[English]") {
                    line = lines.at(i).trimmed();
                    if(CurrentLanguage() == "Russian") tmp_errata.append(QString::fromUtf8(line) + _c_newline);
                    i++;
                }
            }

            line = lines.at(i).trimmed();
            if (line == "[English]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "[extra]") {
                    line = lines.at(i).trimmed();
                    if(CurrentLanguage() == "English") tmp_errata.append(QString::fromUtf8(line) + _c_newline);
                    i++;
                }
            }
            tmp_version.data()->setErrata(tmp_errata);
            line = lines.at(i).trimmed();

            /******************* Extra **************************/
            if (line == "[extra]") {
                i++;
                line = lines.at(i).trimmed();
            }

            QString tmp_extra = "";
            if (line == "[Russian]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "[English]") {
                    line = lines.at(i).trimmed();
                    if(CurrentLanguage() == "Russian") tmp_extra.append(QString::fromUtf8(line) + _c_newline);
                    i++;
                }
            }
            line = lines.at(i).trimmed();
            if (line == "[English]") {
                i++;
                while (i < lines.size() && lines.at(i).trimmed() != "") {
                    line = lines.at(i).trimmed();
                    if(CurrentLanguage() == "English") tmp_extra.append(QString::fromUtf8(line) + _c_newline);
                    i++;
                }
            }
            tmp_version.data()->setExtra(tmp_extra);

            versions_from_server.append(tmp_version);
        }
    }
/*
    foreach (auto vers, versions_from_server) {
        vers.data()->print();
    }
*/
}

bool VersionManager::getIsInterfaceInfoAppended() const
{
    return isInterfaceInfoAppended;
}

void VersionManager::setIsInterfaceInfoAppended(bool newIsInterfaceInfoAppended)
{
    if (isInterfaceInfoAppended == newIsInterfaceInfoAppended)
        return;
    isInterfaceInfoAppended = newIsInterfaceInfoAppended;
    emit isInterfaceInfoAppendedChanged();
}

bool VersionManager::getIsDeviceInfoAppended() const
{
    return isDeviceInfoAppended;
}

void VersionManager::setIsDeviceInfoAppended(bool newIsDeviceInfoAppended)
{
    if (isDeviceInfoAppended == newIsDeviceInfoAppended)
        return;
    isDeviceInfoAppended = newIsDeviceInfoAppended;
    emit isDeviceInfoAppendedChanged();
}

bool VersionManager::getIsCriticalAlert() const
{
    return isCriticalAlert;
}

void VersionManager::setIsCriticalAlert(bool newIsCriticalAlert)
{
    if (isCriticalAlert == newIsCriticalAlert)
        return;
    isCriticalAlert = newIsCriticalAlert;
    emit isCriticalAlertChanged();
}

Version VersionManager::findLatestVersion(int _verDesignCode) const{
    Version result;
    foreach (auto vers, versions_from_server){
        if(vers.data()->getDesign_code() == static_cast<Version::VerDesignCode>(_verDesignCode)){
            if(result.getDate() <= vers.data()->getDate()) result = vers;
        }
    }
    return result;
}

void VersionManager::fillCurrentVersionInfo(int _verDesignCode){
    Version *p_vers = (_verDesignCode == Version::VerDesignCode::Interface) ? &m_current_interface_version : &m_current_device_version;
    foreach (auto vers, versions_from_server){
        if(vers.data()->getDesign_code() == static_cast<Version::VerDesignCode>(_verDesignCode)){
            if(p_vers->getDate() == vers.data()->getDate()) *p_vers = vers;
        }
    }
}


const QString &VersionManager::CurrentLanguage() const{
    return m_CurrentLanguage;
}

void VersionManager::setCurrentLanguage(const QString &newCurrentLanguage){
    m_CurrentLanguage = newCurrentLanguage;
}


void VersionManager::setConsole(Console *newPConsole){
    m_pConsole = newPConsole;
}



void VersionManager::printInterfaceVersions(){
    fillCurrentVersionInfo(Version::VerDesignCode::Interface);
    VerInfoLanguage language = (CurrentLanguage()== "Russian") ? Russian : English;

    QStringList responseString;
    responseString.append(currentInterfaceVersion_ph[language]);
    responseString.append(m_current_interface_version.version_string());
    if(m_current_interface_version.isDescribed()){
        responseString.append(m_current_interface_version.getDescription());
        if(m_current_interface_version.getErrata().trimmed() != ""){
            setIsCriticalAlert(true);
            responseString.append(errorControl_ph[language]);
            responseString.append(m_current_interface_version.getErrata());
        }
        else setIsCriticalAlert(false);

        if(m_current_interface_version.getExtra().trimmed()!= ""){
            responseString.append("Extras: ");
            responseString.append(m_current_interface_version.getExtra());
        }
    }
    else responseString.append(infoVersionUnavailable_ph[language]);

    bool is_latest_available_version_initialized = m_available_interface_version.isValid();
    if(!is_latest_available_version_initialized){
        printResponse(responseString);
        return;
    }

    responseString.append("");
    bool isNewVersionAvailable = (m_available_interface_version > m_current_interface_version) ? true : false;
    if(!isNewVersionAvailable){
        printResponse(responseString);
        return;
    }

    responseString.append(availableInterfaceVersion_ph[language]);
    responseString.append(m_available_interface_version.version_string());
    if(m_available_interface_version.isDescribed()){
        responseString.append(m_available_interface_version.getDescription());

        if(m_available_interface_version.getErrata().trimmed() != ""){
            responseString.append(errorControl_ph[language]);
            responseString.append(m_available_interface_version.getErrata());
        }

        if(m_available_interface_version.getExtra().trimmed() != ""){
            responseString.append("Extras: ");
            responseString.append(m_available_interface_version.getExtra());
        }
    }
    else responseString.append(infoVersionUnavailable_ph[language]);

    printResponse(responseString);
    return;
}


void VersionManager::printDeviceVersions(){
    fillCurrentVersionInfo(Version::VerDesignCode::Device);

    VerInfoLanguage language = (CurrentLanguage()== "Russian") ? Russian : English;

    QStringList responseString;
    responseString.append(currentDeviceVersion_ph[language]);
    responseString.append(m_current_device_version.version_string());
    if(m_current_device_version.isDescribed()){
        responseString.append(m_current_device_version.getDescription());
        if(m_current_device_version.getErrata().trimmed() != ""){
            setIsCriticalAlert(true);
            responseString.append(errorControl_ph[language]);
            responseString.append(m_current_device_version.getErrata());
        }
        else setIsCriticalAlert(false);

        if(m_current_device_version.getExtra().trimmed() != ""){
            responseString.append("Extras: ");
            responseString.append(m_current_device_version.getExtra());
        }
    }
    else responseString.append(infoVersionUnavailable_ph[language]);

    bool is_latest_available_version_initialized = m_available_device_version.isValid();
    if(!is_latest_available_version_initialized){
        printResponse(responseString);
        return;
    }

    responseString.append("");
    bool isNewVersionAvailable = (m_available_device_version > m_current_device_version) ? true : false;
    if(!isNewVersionAvailable){
        printResponse(responseString);
        return;
    }

    responseString.append(availableDeviceVersion_ph[language]);
    responseString.append(m_available_device_version.version_string());
    if(m_available_device_version.isDescribed()){
        responseString.append(m_available_device_version.getDescription());

        if(m_available_device_version.getErrata().trimmed() != ""){
            responseString.append(errorControl_ph[language]);
            responseString.append(m_available_device_version.getErrata());
        }

        if(m_available_device_version.getExtra().trimmed() != ""){
            responseString.append("Extras: ");
            responseString.append(m_available_device_version.getExtra());
        }
    }
    else responseString.append(infoVersionUnavailable_ph[language]);



    printResponse(responseString);
    return;

}
void VersionManager::printOnUpdate(){
    printInterfaceVersions();
    if(m_pConsole->isConnected())
    printDeviceVersions();
}

void VersionManager::printResponse(const QStringList& list)const{
    foreach (const QString vers, list) {
        m_pConsole->append_cdc_string(vers);
    }
}


bool VersionManager::isNewHardwareApplicationAvailable(){
    if((m_pConsole == nullptr) | (m_pConsole->isConnected() != true)) return false;
    if(m_available_device_version > m_current_device_version)
        return true;
    else return false;}

