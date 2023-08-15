#include "Console.h"
#include <QRegularExpression>
#include "../engine/command_manager/StringConvertor.h"
#include "../engine/serial_port/CDC_Driver.h"




/********************************************************************
 *
 *
 *                    Init and reset
 *
 *
********************************************************************/

/****************************************************/
/**************** Connection status *****************/
/****************************************************/


void Console::set_connection_status_description(int _status){
    if(_status < 0x00 | _status > 0x02) return;
    App_settings::ConnectionStatus status = static_cast<App_settings::ConnectionStatus>(_status);
    switch (status)
    {
    case App_settings::ConnectionStatus::Disconnected:
        m_Connection_status_description.removeAt(0);
        m_Connection_status_description.insert(0, "Disconnected");
        m_Connection_status_description.removeAt(1);
        m_Connection_status_description.insert(1, App_settings::CONNECT_BUTTON_DISCONNECTED);
        break;
    case App_settings::ConnectionStatus::Connected:
        m_Connection_status_description.removeAt(0);
        m_Connection_status_description.insert(0, "Connected");
        m_Connection_status_description.removeAt(1);
        m_Connection_status_description.insert(1, App_settings::CONNECT_BUTTON_CONNECTED);
        break;
    case App_settings::ConnectionStatus::Failed:
        m_Connection_status_description.removeAt(0);
        m_Connection_status_description.insert(0, "Failed");
        m_Connection_status_description.removeAt(1);
        m_Connection_status_description.insert(1, App_settings::CONNECT_BUTTON_FAILED);
        break;
    default:
        break;
    }
    connection_status = status;
    emit connection_status_description_changed();
}


/********************************************************************
 *
 *
 *                    Slots
 *
 *
********************************************************************/


void Console::append_firmware_update(const QString &_string){
    append_string(_string, &m_Firmware_update_string, max_firmware_update_cache);
    emit firmware_update_new_string();
}

/****************************************************/
/****** Asynchronous Serial Port Read  **************/
/****************************************************/

void Console::read_serialport_and_append_data(){
    if(m_pCdc_driver == nullptr) return;
    if((m_pCdc_driver->getQASerialPortPtr() == nullptr) & (m_pCdc_driver->getQSerialPortPtr() != nullptr)){
        const QByteArray _data = m_pCdc_driver->getQSerialPortPtr()->readAll();
        this->append_manual_override(QString(_data));
    }
#ifdef ANDROID_V
    else if((m_pCdc_driver->getQASerialPortPtr() != nullptr) & (m_pCdc_driver->getQSerialPortPtr() == nullptr)){
        const QByteArray _data = m_pCdc_driver->getQASerialPortPtr()->readAll();
        this->append_manual_override(QString(_data));
    }
#endif
    else return;
}

/********************************************************************
 *
 *
 *                    Setters/getters
 *
 *
********************************************************************/


/********************************************************************
 *
 *
 *                    Class setters/getters
 *
 *
********************************************************************/

const QStringList &Console::Connection_status_description() const{
    return m_Connection_status_description;
}
/****************************************************/
/************* Manual override data *****************/
/****************************************************/

const QString &Console::Manual_override() const{
    return m_Manual_override_string;
}

void Console::set_manual_override(const QString &_string){
    m_Manual_override_string = _string;
    setManual_override_string_hex(StringConvertor::asciiToHex(m_Manual_override_string));
    emit manual_override_new_string();
}

void Console::append_manual_override(const QString &_string){
    append_string(_string, &m_Manual_override_string, max_manual_override_cache);
    setManual_override_string_hex(StringConvertor::asciiToHex(m_Manual_override_string));
    emit manual_override_new_string();
}

const QString &Console::Manual_override_string_hex() const{
    return m_Manual_override_string_hex;
}

void Console::setManual_override_string_hex(const QString &newManual_override_string_hex){
    m_Manual_override_string_hex = newManual_override_string_hex;
}

/****************************************************/
/************* Firmware update data *****************/
/****************************************************/

const QString &Console::firmware_update() const{
    return m_Firmware_update_string;
}

void Console::set_firmware_update(const QString &_string){
    m_Firmware_update_string = _string;
    emit firmware_update_new_string();
}

CDC_Driver *Console::pCdc_driver() const{
    return m_pCdc_driver;
}

void Console::setPCdc_driver(CDC_Driver *newPCdc_driver){
    m_pCdc_driver = newPCdc_driver;
}

/****************************************************/
/***************** CDC status data ******************/
/****************************************************/
const QString &Console::Cdc_string() const{
    return m_Cdc_string;
}

void Console::set_cdc_string(const QString &_string){
    m_Cdc_string = _string;
    emit cdc_new_string();
}

void Console::append_cdc_string(const QString &_string){
    append_string(_string, &m_Cdc_string, max_cdc_cache);
    emit cdc_new_string();
}


/********************************************************************
 *
 *
 *                   Private class service function
 *
 *
********************************************************************/

void Console::append_string(const QString &_string , QString *target, int max_cache){
    int new_string_length = _string.size() + 1;

    int current_cache_length = target->length();

    int predicted_cache_length = new_string_length + current_cache_length;

    if(predicted_cache_length >= max_cache){
        int trim_length = predicted_cache_length - max_cache;

        QString temp_left = target->left(trim_length-1);
        int new_line_char_count = temp_left.count('\n');

        trim_length += new_line_char_count;
        target->remove(0, trim_length-1);
        target->squeeze();
    }
    *target = *target + _string + '\n';
}


