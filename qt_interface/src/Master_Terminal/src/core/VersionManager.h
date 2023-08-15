#ifndef VERSIONMANAHER_H
#define VERSIONMANAHER_H

/***********************************************************************
 *
 * Version Manager incapsulates a current interface and versions,
 * info about available newer versions on the Internet
 *
 * Info about possible critical errors
 * Info about a connected device hardware
 *
 * Main functions:
 * read available versions info,
 * display, if newer versions available
 * read and display hardware info
 *
 ************************************************************************/


#include "../app_settings.h"
#include <stdlib.h>
#include <QDebug>
#include <iostream>
#include "Version.h"
#include "Console.h"
#include "../app_settings.h"

class VersionManager: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString current_interface_version READ current_interface_version CONSTANT )
    Q_PROPERTY(QString current_device_version READ current_device_version NOTIFY current_device_versionChanged)
    Q_PROPERTY(QString hardware_device_model_name READ hardware_device_model_name NOTIFY hardware_device_modelChanged)

    Q_PROPERTY(bool isCriticalAlert READ getIsCriticalAlert WRITE setIsCriticalAlert NOTIFY isCriticalAlertChanged)
    Q_PROPERTY(bool isInterfaceInfoAppended READ getIsInterfaceInfoAppended WRITE setIsInterfaceInfoAppended NOTIFY isInterfaceInfoAppendedChanged)
    Q_PROPERTY(bool isDeviceInfoAppended READ getIsDeviceInfoAppended WRITE setIsDeviceInfoAppended NOTIFY isDeviceInfoAppendedChanged)

    Q_PROPERTY(bool isNewHardwareApplicationAvailable READ isNewHardwareApplicationAvailable NOTIFY isNewHardwareApplicationAvailableChanged)

public:
    explicit VersionManager(QObject *parent = nullptr): QObject(parent){};
    ~VersionManager(){ }

    //=========================== const presets ==============================
    enum VerInfoLanguage {
        English = 0,
        Russian = 1
    };

    static inline const QStringList currentInterfaceVersion_ph = {"******* Current Interface Version: ******",  "******* Текущая версия ПО интерфейса: *******"};
    static inline const QStringList currentDeviceVersion_ph = {"******* Current Device Version: ***",  "******* Текущая версия ПО устройства: *******"};
    static inline const QStringList availableInterfaceVersion_ph = {"******* New Interface Version available: *******",  "******* Доступна новая версия интерфейса: *******"};
    static inline const QStringList availableDeviceVersion_ph = {"******* New Device Version available: *******",  "******* Доступна новая версия устройства: *******"};
    static inline const QStringList infoVersionUnavailable_ph = {"Version info not found.",  "Информация о версии ПО не найдена."};
    static inline const QStringList errorControl_ph = {"Errata: ",  "Сведения об ошибках: "};

    //=========================== Init functions ==============================
    void setCurrent_device_version(const QString &init_string);
    void setHardware_device_model(const QString &init_string);
    void resetOnDisconnect(){
        m_current_device_version.resetOnDisconnect();
        m_hardware_device_model_name = "";
        m_hardware_device_model_code = NULL_MCODE;
        isCriticalAlert = false;
        isDeviceInfoAppended = false;
        emit current_device_versionChanged();
        emit hardware_device_modelChanged();
    }

    //========================= Print and display =============================
    Q_INVOKABLE void printInterfaceVersions();
    Q_INVOKABLE void printDeviceVersions();
    Q_INVOKABLE void printOnUpdate();
    void printResponse(const QStringList& list)const;

    //============================ Class service ==============================
    Version findLatestVersion(int _verDesignCode) const;
    void fillCurrentVersionInfo(int _verDesignCode);
    bool isNewHardwareApplicationAvailable();

    //========================= Class setters/getters =========================
    void setConsole(Console *newPConsole);
    const QString &CurrentLanguage() const;
    void setCurrentLanguage(const QString &newCurrentLanguage);
    char hardware_device_model_code() const;
    const QString current_interface_version () const {return m_current_interface_version.version_string();}
    const QString current_device_version () const{return m_current_device_version.version_string();}
    const QString &hardware_device_model_name() const{ return m_hardware_device_model_name;};
    bool getIsInterfaceInfoAppended() const;
    bool getIsCriticalAlert() const;
    void setIsCriticalAlert(bool newIsCriticalAlert);
    void setIsInterfaceInfoAppended(bool newIsInterfaceInfoAppended);
    bool getIsDeviceInfoAppended() const;
    void setIsDeviceInfoAppended(bool newIsDeviceInfoAppended);


public slots:
    void handleDeviceVersionInfo();

signals:
    void current_device_versionChanged();
    void hardware_device_modelChanged();

    void isCriticalAlertChanged();

    void isInterfaceInfoAppendedChanged();
    void isDeviceInfoAppendedChanged();
    void isNewHardwareApplicationAvailableChanged();

private:
    QList< QSharedPointer<Version> > versions_from_server;

    Version m_current_interface_version = Version(App_settings::INTERFACE_VERSION, Version::VerDesignCode::Interface);
    Version m_available_interface_version;

    /* 1.02.02.22 */
    Version m_current_device_version;
    Version m_available_device_version;

    /* SIGMA, TEC, Starline 2CAN */
    QString m_hardware_device_model_name = "";
    char m_hardware_device_model_code = NULL_MCODE;


    Console *m_pConsole;
    QString m_CurrentLanguage = "English";

    void parseVersionInfo(const QByteArray &data);

    /* User alert values */
    bool isCriticalAlert = false;
    bool isInterfaceInfoAppended = false;
    bool isDeviceInfoAppended = false;
};


#endif // VERSIONMANAHER_H
