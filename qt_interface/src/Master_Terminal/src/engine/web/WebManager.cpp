#include "WebManager.h"

WebManager::WebManager(QObject *parent) : QObject(parent){
    m_pDownloader = new Downloader();
    connect(m_pDownloader, &Downloader::onReady, this, &WebManager::downloadFinished);
    connect(m_pDownloader, &Downloader::onError, this, &WebManager::resetOnError);
}

void WebManager::resetOnError(){
    QString error = m_pDownloader->popErrorString();
    m_pConsole->append_cdc_string("Web download failed: " + error);
    if(m_RequestTarget == DeviceUpdate){
        m_pConsole->append_firmware_update("Web download failed: " + error);
    }
    m_RequestTarget = DefaultValue;
}

void WebManager::downloadFinished(){
    switch(m_RequestTarget){
    case DeviceVersionInfo:
        m_RequestTarget = DefaultValue;
        m_pConsole->append_cdc_string("Device version downloaded...");
        emit deviceVersionInfoDownloaded();
        break;
    case DeviceUpdate:{
        m_RequestTarget = DefaultValue;
        emit deviceUpdateDownloaded("Download complete.");
        break;
    }
    case DeviceCodeOverride:
        m_RequestTarget = DefaultValue;
        m_pConsole->append_cdc_string("Code override data downloaded...");
        emit deviceCodeOverrideDownloaded();
        break;
    default:
        break;
    }
}

VersionManager *WebManager::pVersionManager() const{
    return m_pVersionManager;
}

void WebManager::setVersionManager(VersionManager *newPVersionManager){
    m_pVersionManager = newPVersionManager;
    connect(this, &WebManager::deviceVersionInfoDownloaded, m_pVersionManager, &VersionManager::handleDeviceVersionInfo);
}

WebConfig *WebManager::pWebConfig() const{
    return m_pWebConfig;
}

void WebManager::setWebConfig(WebConfig *newPWebConfig){
    m_pWebConfig = newPWebConfig;
}


Console *WebManager::pConsole() const{
    return m_pConsole;
}

void WebManager::setConsole(Console *newPConsole){
    m_pConsole = newPConsole;
}

CommandManager *WebManager::pCommandManager() const{
    return m_pCommandManager;
}
void WebManager::setCommandManager(CommandManager *newCommandManager){
    m_pCommandManager = newCommandManager;
    connect(this, &WebManager::deviceUpdateDownloaded, m_pCommandManager, &CommandManager::startWebUpdate);
}


bool WebManager::put_up_download(int _rq_target_value){
    RequestTarget rq_target_value = static_cast<RequestTarget>(_rq_target_value);
    if(isDownloaderBusy() | (rq_target_value == DefaultValue)) return false;
    m_RequestTarget = rq_target_value;

    switch(rq_target_value){
    case DeviceVersionInfo:
        m_pDownloader->setDownloadPath(App_settings::VERSION_INFO_CACHE_PATH);
        m_pDownloader->getData(m_pWebConfig->version_info_url());
        break;
    case DeviceUpdate:{
        m_pConsole->append_firmware_update("Downloading new firmware " + m_pWebConfig->update_url() + pVersionManager()->hardware_device_model_name() + ".bin");
        connect(this, &WebManager::deviceUpdateDownloaded, m_pConsole, &Console::append_firmware_update);

        m_pDownloader->setDownloadPath(App_settings::UPDATE_CACHE_PATH);
        m_pDownloader->getData(m_pWebConfig->update_url() + pVersionManager()->hardware_device_model_name() + ".bin");
        break;
    }
    case DeviceCodeOverride:
        m_pDownloader->setDownloadPath(App_settings::CODE_OVERRIDE_CACHE_PATH);
        m_pDownloader->getData(m_pWebConfig->code_override_url());
        break;
    default:
        break;
    }
    return true;
}

