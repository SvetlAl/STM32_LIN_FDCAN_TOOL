#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include "CoreStatus.h"
#include "VersionManager.h"
#include "../app_settings.h"
#include "../engine/web/WebConfig.h"
#include "../engine/serial_port/QSerialPortConfig.h"
#include "design/Appdesign.h"
#include "user_profile/Userprofile.h"

class Core : public QObject{
    Q_OBJECT

public:

    explicit Core(QObject *parent = nullptr);
    ~Core();

    void init_folders();
    void init();

    enum LoaderMode {
        LmUserProfile = 0,
        LmAppDesign = 1,
        LmCoreStatus = 2
    };


    //===================== Design values setters/getters ============================
    Q_INVOKABLE int getDesignValue_int(const QString _assignment, const QString _item_element, const QString _name){
        return m_pAappdesign->getIntValue(_assignment, _item_element, _name);}

    Q_INVOKABLE QString getDesignValue_string(const QString _assignment, const QString _item_element, const QString _name){
        return m_pAappdesign->getStringValue(_assignment, _item_element, _name);}

    Q_INVOKABLE float getDesignValue_float(const QString _assignment, const QString _item_element, const QString _name){
        return m_pAappdesign->getFloatValue(_assignment, _item_element, _name);}


    Q_INVOKABLE void setDesignValue_int(const QString _assignment, const QString _item_element, const QString _name, int _value){
        m_pAappdesign->setIntValue(_assignment, _item_element, _name, _value);
    }
    Q_INVOKABLE void setDesignValue_string(const QString _assignment, const QString _item_element, const QString _name, QString _value){
        m_pAappdesign->setStringValue(_assignment, _item_element, _name, _value);
    }
    Q_INVOKABLE void setDesignValue_float(const QString _assignment, const QString _item_element, const QString _name, float _value){
        m_pAappdesign->setFloatValue(_assignment, _item_element, _name, _value);
    }

    //===================== User profile setters/getters ============================
    Q_INVOKABLE QString getUserProfileValue(int _val);
    Q_INVOKABLE void setUserProfileValue(int _val, QString _str);
    Q_INVOKABLE void deleteUserProfile(QString _username);
    Q_INVOKABLE void createUserProfile();
    Q_INVOKABLE void setUserProfile(QString _username);
    Q_INVOKABLE bool validateUserProfile();
    Q_INVOKABLE QStringList makeUserList();
    Q_INVOKABLE QStringList makeUserLanguagesList();

    //============================= Design Preset ===================================
    Q_INVOKABLE void setDesignSizePreset(int _val);

    //================= Profile/Design/Core status save/load ========================
    Q_INVOKABLE void saveSetting(int _mode);
    Q_INVOKABLE bool loadSetting(QString _username, int _mode);

    /*************** Serial Port Preset ***********/
    Q_INVOKABLE void saveSerialPortPreset();
    Q_INVOKABLE bool loadSerialPortPreset();
    /*************** WebConfig ***********/
    Q_INVOKABLE void saveWebConfigPreset();
    Q_INVOKABLE bool loadWebConfigPreset();

    /*************** Test ***********/
    Q_INVOKABLE void test_print(){
        m_pAappdesign->print();
    }

    /************************* Setters/Getters **************************/
    QSerialPortConfig *getSerialport_config() const;
    void setSerialport_config(QSerialPortConfig *newPtr_serialport_config);
    void setWebConfig(WebConfig *newPWebConfig);
    void setVersionManager(VersionManager *newPVersionManager);

signals:
    void userProfileChanged();
    void appDesignChanged();

private:
    QString fullpath = "";
    void initUserProfile();
    void initAppDesign(); 

    void saveUserProfile();
    void saveAppDesign();
    void saveCoreStatus();

    bool loadUserProfile(QString _username);
    bool loadAppDesign(QString _username);
    bool loadCoreStatus();

    CoreStatus m_core_status;

    AppDesign* m_pAappdesign;
    UserProfile* m_pUser_profile;
    WebConfig* m_pWebConfig;
    QSerialPortConfig* m_pSerialport_config;
    VersionManager *m_pVersionManager = nullptr;
};


Q_DECLARE_METATYPE(Core);
#endif // CORE_H
