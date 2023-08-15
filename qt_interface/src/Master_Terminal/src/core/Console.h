#ifndef CONSOLE_H
#define CONSOLE_H

/***********************************************************************
 *
 *
 * This class is designed to expose target device properties on a display
 *
 *
 ************************************************************************/

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <iostream>
#include <QDate>
#include "../app_settings.h"

class CDC_Driver;


class Console : public QObject{
    Q_OBJECT
    /* BASE_MAIN TEXT_EDIT com-port terminal service information (connection errors, port number, etc) */
    Q_PROPERTY(QString cached_cdc_string READ Cdc_string WRITE set_cdc_string NOTIFY cdc_new_string)
    /* MANUAL_OVERRIDE TEXT_EDIT Manual override incoming data) */
    Q_PROPERTY(QString cached_manual_override_string READ Manual_override WRITE set_manual_override NOTIFY manual_override_new_string)
    Q_PROPERTY(QString cached_manual_override_string_hex READ Manual_override_string_hex NOTIFY manual_override_new_string)

    /*** FIRMWARE UPDATE TEXT_EDIT ***/
    Q_PROPERTY(QString firmware_update READ firmware_update WRITE set_firmware_update NOTIFY firmware_update_new_string)

    /* CONNECTION STATUS & COLOR Connection status and button color */
    Q_PROPERTY(QStringList connection_status_description READ Connection_status_description NOTIFY connection_status_description_changed)

    /* is Connected? */
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connection_status_description_changed)


public:
    explicit Console(QObject *parent = nullptr): QObject(parent){
        m_Connection_status_description.append("Disconnected");
        m_Connection_status_description.append(App_settings::CONNECT_BUTTON_DISCONNECTED);
    };
    ~Console(){};


    //============================== Init and reset =================================
    /*** CONNECTION STATUS & COLOR ***/
    void set_connection_status_description(int _status);

    /******* BASE_MAIN TEXT_EDIT *****/
    Q_INVOKABLE void reset_cdc_string(){set_cdc_string("");};

    /*** MANUAL_OVERRIDE TEXT_EDIT ***/
    Q_INVOKABLE void reset_manual_override_string(){set_manual_override(""); setManual_override_string_hex("");};


    //============================== Setters/getters =================================
    /******* is Connected? ********/
    bool isConnected () const{return(connection_status == App_settings::ConnectionStatus::Connected);};
    /*** FIRMWARE UPDATE TEXT_EDIT ***/
    Q_INVOKABLE void reset_firmware_update_string(){set_firmware_update("");};


    //======================== Class setters/getters =================================
    const QStringList &Connection_status_description() const;
    /*** CDC Driver ***/
    CDC_Driver *pCdc_driver() const;
    void setPCdc_driver(CDC_Driver *newPCdc_driver);

    const QString &Cdc_string() const;
    void set_cdc_string(const QString &_string);
    void append_cdc_string(const QString &_string);
    const QString &firmware_update() const;
    void set_firmware_update(const QString &_string);
    const QString &Manual_override() const;
    void set_manual_override(const QString &_string);
    void append_manual_override(const QString &_string);

    const QString &Manual_override_string_hex() const;
    void setManual_override_string_hex(const QString &newManual_override_string_hex);


public slots:
    void append_firmware_update(const QString &_string);
    void read_serialport_and_append_data();

signals:
    /******* BASE_MAIN TEXT_EDIT *****/
    void cdc_new_string();

    /*** MANUAL_OVERRIDE TEXT_EDIT ***/
    void manual_override_new_string();

    /*** FIRMWARE UPDATE TEXT_EDIT ***/
    void firmware_update_new_string();

    /*** CONNECTION STATUS & COLOR ***/
    void connection_status_description_changed();

private:
    CDC_Driver *m_pCdc_driver = nullptr;
    void append_string(const QString &_string , QString *target, int max_cache);

    /******* BASE_MAIN TEXT_EDIT *****/
    QString m_Cdc_string = "";

    /*** MANUAL_OVERRIDE TEXT_EDIT ***/
    QString m_Manual_override_string = "";
    QString m_Manual_override_string_hex = "";

    /*** FIRMWARE UPDATE TEXT_EDIT ***/
    QString m_Firmware_update_string = "";

    /*** CONNECTION STATUS & COLOR ***/
    QStringList m_Connection_status_description; // The first string is a cnnection status, the second string is a button color code

    /* is Connected? */
    App_settings::ConnectionStatus connection_status = App_settings::ConnectionStatus::Disconnected;

    constexpr const static int max_cdc_cache = 64*32;
    constexpr const static int max_manual_override_cache = 64*64;
    constexpr const static int max_firmware_update_cache = 64*32;
};

#endif // CONSOLE_H
