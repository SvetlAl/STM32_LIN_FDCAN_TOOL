#include "Core.h"
// #include "./../engine/file_manager/SimpleClassLoader.h"
#include "./../engine/file_manager/QClassLoader.h"
#include "../app_settings.h"
#include "./../engine/file_manager/FileManager.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "../engine/serial_port/SerialConfig_Preset.h"
#include "../engine/web/WebConfig_Preset.h"
#include <QDir>
#ifdef ANDROID_V
#include <QJniObject>
#include <QJniEnvironment>
#include <QtCore/private/qandroidextras_p.h>
#endif

Core::Core(QObject *parent)
    : QObject{parent}{
    m_pAappdesign = new AppDesign();
    m_pUser_profile = new UserProfile();
}

Core::~Core(){
    delete m_pAappdesign;
    delete m_pUser_profile;
}

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/



/********************************************************************/
/***                 General initialization                       ***/
/********************************************************************/

void Core::init(){
    init_folders();
    QClassLoader<CoreStatus> loader;
    QString filename = App_settings::APP_DIR + App_settings::APP_NAME + App_settings::APP_EXT;
    loader.setFilename(filename);
    loader.setDirname(App_settings::APP_DIR);

    if(!loader.assertFileExist()){
        m_core_status.setLast_used_profile(App_settings::DEFAULT_USERNAME);
        loader.saveClassInstance(m_core_status);
    }
    else m_core_status = loader.loadClassInstance();

    initUserProfile();
    initAppDesign();
};


/********************************************************************/
/***                 Sub-init: create the folders                 ***/
/********************************************************************/

void Core::init_folders(){
    QDir dir;
    QString fullpath = dir.absolutePath();

    if(QDir(fullpath + App_settings::USERPROFILES_DIR).exists()){
    }
    else{
        QDir().mkdir(fullpath + App_settings::USERPROFILES_DIR);
    }

    if(QDir(fullpath + App_settings::SERIALPORTCONFIG_DIR).exists()){
    }
    else{
        QDir().mkdir(fullpath + App_settings::SERIALPORTCONFIG_DIR);
    }

    if(QDir(fullpath + App_settings::WEBCONFIG_DIR).exists()){
    }
    else{
        QDir().mkdir(fullpath + App_settings::WEBCONFIG_DIR);
    }

    if(QDir(fullpath + App_settings::APPDESIGN_DIR).exists()){
    }
    else{
        QDir().mkdir(fullpath + App_settings::APPDESIGN_DIR);
    }
}

/********************************************************************/
/***                 Sub-init: User profile                       ***/
/********************************************************************/

void Core::initUserProfile(){
    QClassLoader<UserProfile> loader;
    loader.setFilename(App_settings::USERPROFILES_DIR + m_core_status.last_used_profile() + App_settings::USERPROFILES_EXT);
    loader.setDirname(App_settings::USERPROFILES_DIR);

    if(!loader.assertFileExist()){
        loader.saveClassInstance(*m_pUser_profile);
    }
    else *m_pUser_profile = loader.loadClassInstance();
};

/********************************************************************/
/***                 Sub-init: Application Design                 ***/
/********************************************************************/

void Core::initAppDesign(){
    QClassLoader<AppDesign> loader;
    loader.setFilename(App_settings::APPDESIGN_DIR + m_pUser_profile->m_name + App_settings::APPDESIGN_EXT);
    loader.setDirname(App_settings::APPDESIGN_DIR);

    if(!loader.assertFileExist()){
        DEBUG_OUT("Core::initAppDesign() нет файла ");
        m_pAappdesign->default_init();

#ifdef ANDROID_V
    m_pAappdesign->setSizePreset(AppDesign::SizePreset::Sp_XL);
#endif
        loader.saveClassInstance(*m_pAappdesign);
    }
    else{
        DEBUG_OUT("Core::initAppDesign() файл есть ")
        *m_pAappdesign = loader.loadClassInstance();
    }
};

/********************************************************************
 *
 *
 *                     User Profile
 *
 *
********************************************************************/

/********************************************************************/
/***            Sub-init: find all saved user profiles            ***/
/********************************************************************/

QStringList Core::makeUserList(){
    auto _list = FileManager<QString>::find_files_in_qdir(App_settings::USERPROFILES_DIR, App_settings::USERPROFILES_EXT, true);
    return _list;
}

/********************************************************************/
/*** Sub-init: find corresponding language settings for all users ***/
/********************************************************************/

QStringList Core::makeUserLanguagesList(){
    auto _list = FileManager<QString>::find_files_in_qdir(App_settings::USERPROFILES_DIR, App_settings::USERPROFILES_EXT, true);
    QStringList languageList;

    foreach(const auto username, _list){
        QClassLoader<UserProfile> loader;
        loader.setFilename(App_settings::USERPROFILES_DIR + username + App_settings::USERPROFILES_EXT);
        loader.setDirname(App_settings::USERPROFILES_DIR);
        UserProfile temp_p = loader.loadClassInstance();
        languageList.append(temp_p.getValue(UserProfile::ProfileMembers::Language));
    }
    return languageList;
}

/********************************************************************/
/***     Load a user profile, set user configuration presets      ***/
/********************************************************************/

void Core::setUserProfile(QString _username){
    if(loadUserProfile(_username)){
        if(loadAppDesign(_username)){
            m_core_status.setLast_used_profile(_username);
            saveCoreStatus();
        }
    }
}

bool Core::validateUserProfile(){
    return true;
}

/********************************************************************/
/**************     Create a new user profile      ******************/
/********************************************************************/
/* Assuming, that m_user_profile is already set with a new profile data */
void Core::createUserProfile(){
    QClassLoader<UserProfile> loader;
    loader.setFilename(App_settings::USERPROFILES_DIR + m_pUser_profile->m_name + App_settings::USERPROFILES_EXT);
    loader.setDirname(App_settings::USERPROFILES_DIR);

    if(!loader.assertFileExist()){
        loader.saveClassInstance(*m_pUser_profile);
        saveAppDesign();
        setUserProfile(m_pUser_profile->m_name);
    }
}

/********************************************************************/
/**************   Delete an existing user profile   *****************/
/********************************************************************/
void Core::deleteUserProfile(QString _username){
    /* delete current user */
    if(m_pUser_profile->m_name == App_settings::DEFAULT_USERNAME) return;
    else if(m_pUser_profile->m_name == _username){
        setUserProfile(App_settings::DEFAULT_USERNAME);
    }

    QString userprofile_path = App_settings::USERPROFILES_DIR + _username + App_settings::USERPROFILES_EXT;
    FileManager<QString>::deleteFile(userprofile_path);

    QString appdesign_path = App_settings::APPDESIGN_DIR + _username +
            App_settings::APPDESIGN_EXT;

    FileManager<QString>::deleteFile(appdesign_path);
}

/********************************************************************
 *
 *
 *                    Save/load functions
 *
 *
********************************************************************/

/********************************************************************/
/**************             General save            *****************/
/********************************************************************/

void Core::saveSetting(int _mode){
    switch(_mode){
    case LoaderMode::LmUserProfile:
        saveUserProfile();
        break;
    case LoaderMode::LmAppDesign:
        saveAppDesign();
        break;
    case LoaderMode::LmCoreStatus:
        saveCoreStatus();
        break;
    default:
        break;
    }
}

/********************************************************************/
/**************             General load            *****************/
/********************************************************************/

bool Core::loadSetting(QString _username, int _mode){
    switch(_mode){
    case LoaderMode::LmUserProfile:
        return loadUserProfile(_username);
        break;
    case LoaderMode::LmAppDesign:
        return loadAppDesign(_username);
        break;
    case LoaderMode::LmCoreStatus:
        return loadCoreStatus();
        break;
    default:
        return false;
        break;
    }
}

void Core::saveUserProfile(){
    QClassLoader<UserProfile> loader;
    loader.setFilename(App_settings::USERPROFILES_DIR + m_pUser_profile->m_name + App_settings::USERPROFILES_EXT);
    loader.setDirname(App_settings::USERPROFILES_DIR);
    loader.saveClassInstance(*m_pUser_profile);
}
void Core::saveAppDesign(){
    QClassLoader<AppDesign> loader;
    loader.setFilename(App_settings::APPDESIGN_DIR + m_pUser_profile->m_name + App_settings::APPDESIGN_EXT);
    loader.setDirname(App_settings::APPDESIGN_DIR);
    loader.saveClassInstance(*m_pAappdesign);
}
void Core::saveCoreStatus(){
    QClassLoader<CoreStatus> loader;
    QString filename = App_settings::APP_DIR + App_settings::APP_NAME + App_settings::APP_EXT;
    loader.setFilename(filename);
    loader.setDirname(App_settings::APP_DIR);
    loader.saveClassInstance(m_core_status);
}
bool Core::loadUserProfile(QString _username){
    QClassLoader<UserProfile> loader;
    loader.setFilename(App_settings::USERPROFILES_DIR + _username + App_settings::USERPROFILES_EXT);
    loader.setDirname(App_settings::USERPROFILES_DIR);
    if(loader.assertFileExist()){
        *m_pUser_profile = loader.loadClassInstance();
        if(m_pVersionManager != nullptr){
            m_pVersionManager->setCurrentLanguage(m_pUser_profile->m_language);
        }
        emit userProfileChanged();
        return true;
    }
    else{
        initUserProfile();
        emit userProfileChanged();
        return false;
    }
}
bool Core::loadAppDesign(QString _username){
    QClassLoader<AppDesign> loader;
    loader.setFilename(App_settings::APPDESIGN_DIR + _username + App_settings::APPDESIGN_EXT);
    loader.setDirname(App_settings::APPDESIGN_DIR);
    if(loader.assertFileExist()){
        DEBUG_OUT("loadAppDesign File exists")
        *m_pAappdesign = loader.loadClassInstance();
        emit appDesignChanged();
        return true;
    }
    else{
        DEBUG_OUT("loadAppDesign File doesnt exists")
        initAppDesign();
        emit appDesignChanged();
        return false;
    }
}
bool Core::loadCoreStatus(){
    QClassLoader<CoreStatus> loader;
    QString filename = App_settings::APP_DIR + App_settings::APP_NAME + App_settings::APP_EXT;
    loader.setFilename(filename);
    loader.setDirname(App_settings::APP_DIR);

    if(!loader.assertFileExist()){
        m_core_status.setLast_used_profile(App_settings::DEFAULT_USERNAME);
        loader.saveClassInstance(m_core_status);
        return true;
    }
    else{
        m_core_status = loader.loadClassInstance();
        return false;
    }
}

/********************************************************************/
/*************** Save/Load Serial Port preset ***********************/
/********************************************************************/

void Core::saveSerialPortPreset(){
    QClassLoader<SerialConfig_Preset> loader;
    loader.setFilename(App_settings::SERIALPORTCONFIG_DIR + m_pUser_profile->m_name + App_settings::SERIALPORTCONFIG_EXT);
    loader.setDirname(App_settings::SERIALPORTCONFIG_DIR);
    SerialConfig_Preset temp_preset = m_pSerialport_config->make_preset();
    loader.saveClassInstance(temp_preset);
}
bool Core::loadSerialPortPreset(){
    QClassLoader<SerialConfig_Preset> loader;
    loader.setFilename(App_settings::SERIALPORTCONFIG_DIR + m_pUser_profile->m_name + App_settings::SERIALPORTCONFIG_EXT);
    loader.setDirname(App_settings::SERIALPORTCONFIG_DIR);
    if(loader.assertFileExist()){
        m_pSerialport_config->set_preset(loader.loadClassInstance());
        return true;
    }
    else{
        return false;
    }
}

/********************************************************************/
/***************** Save/Load Serial WebConfig ***********************/
/********************************************************************/
void Core::saveWebConfigPreset(){
    QClassLoader<WebConfig_Preset> loader;
    loader.setFilename(App_settings::WEBCONFIG_DIR + m_pUser_profile->m_name + App_settings::WEBCONFIG_EXT);
    loader.setDirname(App_settings::WEBCONFIG_DIR);
    WebConfig_Preset temp_preset = m_pWebConfig->make_preset();
    loader.saveClassInstance(temp_preset);
}

bool Core::loadWebConfigPreset(){
    QClassLoader<WebConfig_Preset> loader;
    loader.setFilename(App_settings::WEBCONFIG_DIR + m_pUser_profile->m_name + App_settings::WEBCONFIG_EXT);
    loader.setDirname(App_settings::WEBCONFIG_DIR);
    if(loader.assertFileExist()){
        m_pWebConfig->set_preset(loader.loadClassInstance());
        return true;
    }
    else{
        return false;
    }
}


/********************************************************************
 *
 *
 *                    Class setters/getters
 *
 *
********************************************************************/
void Core::setVersionManager(VersionManager *newPVersionManager){
    m_pVersionManager = newPVersionManager;
    m_pVersionManager->setCurrentLanguage(m_pUser_profile->m_language);
}

void Core::setWebConfig(WebConfig *newPWebConfig){
    m_pWebConfig = newPWebConfig;
}

QSerialPortConfig *Core::getSerialport_config() const{
    return m_pSerialport_config;
}

void Core::setSerialport_config(QSerialPortConfig *newPtr_serialport_config){
    m_pSerialport_config = newPtr_serialport_config;
}


/********************************************************************/
/*****************          Design preset     ***********************/
/********************************************************************/

void Core::setDesignSizePreset(int _val){
    m_pAappdesign->setSizePreset(_val);
    emit appDesignChanged();
    saveSetting(LmAppDesign);
}


/********************************************************************/
/****************** User profile setters/getters ********************/
/********************************************************************/

QString Core::getUserProfileValue(int _val) {
    return m_pUser_profile->getValue(_val);}

void Core::setUserProfileValue(int _val, QString _str){
    m_pUser_profile->setValue(_val, _str);

    if( (_val == static_cast<int>(UserProfile::ProfileMembers::Language))  & (m_pVersionManager != nullptr)){
        m_pVersionManager->setCurrentLanguage(_str);
    }
    emit userProfileChanged();
}





