#include "CDC_Driver.h"


/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/


/********************************************************************
 *
 *
 *                     COM-port connect/disconnect
 *
 *
********************************************************************/

int CDC_Driver::connection_status() const{
    return static_cast<int>(m_connection_status);
}

bool CDC_Driver::isConnected()const{
    if(m_connection_status == App_settings::ConnectionStatus::Connected) return true;
    else return false;
}

void CDC_Driver::setConnection_status(App_settings::ConnectionStatus newConnection_status){
    m_connection_status = newConnection_status;
    emit connection_status_changed();
}


/********************************************************************
 *
 *
 *                     Exchange data IO
 *
 *
********************************************************************/

/********************************************************************
 *
 *
 *                    Asynchronous mode
 *
 *
********************************************************************/

/* flag */
bool CDC_Driver::asynch_read() const{
    return m_asynch_read;
}

void CDC_Driver::setAsynch_read(bool newAsynch_read){
    m_asynch_read = newAsynch_read;
    emit async_read_changed();
}

/********************************************************************
 *
 *
 *                    Debug and print
 *
 *
********************************************************************/
// External objects interaction
void CDC_Driver::set_data(const QString &_string){
    if(m_pConsole != nullptr)
        m_pConsole->set_cdc_string(_string);
}

void CDC_Driver::print_data(const QString &_string){
    if(m_pConsole != nullptr)
        m_pConsole->append_cdc_string(_string);
}


/********************************************************************
 *
 *
 *                    Connection settings
 *
 *
********************************************************************/

int CDC_Driver::maxRxBytes_per_request() const{return m_pSerialPortConfig->max_recieve_data_per_request();}
int CDC_Driver::maxTxBytes_per_request() const{return m_pSerialPortConfig->max_transmit_data_per_request();}
int CDC_Driver::trialsOnBusyResponse() const{return m_pSerialPortConfig->Cdc_busy_cmd_trials();}
int CDC_Driver::read_timeout()const{return m_pSerialPortConfig->Cdc_read_timeout();}
void CDC_Driver::set_custom_read_timeout(const int _timeout){
    m_pSerialPortConfig->setCdc_read_timeout(_timeout);
}

/********************************************************************
 *
 *
 *                     Class Setters/getters
 *
 *
********************************************************************/

QSerialPortConfig *CDC_Driver::pSerialPortConfig() const{
    return m_pSerialPortConfig;
}

void CDC_Driver::setPSerialPortConfig(QSerialPortConfig *newPSerialPortConfig){
    m_pSerialPortConfig = newPSerialPortConfig;
}

Console *CDC_Driver::pConsole() const{
    return m_pConsole;
}

void CDC_Driver::setPConsole(Console *newPConsole){
    m_pConsole = newPConsole;
}
