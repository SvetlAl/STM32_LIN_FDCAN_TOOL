#include "QSerialPortConfig.h"



void QSerialPortConfig::print(){
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Port number: " + m_portnames.get_current_name() + ": ");
    QDEBUG_OUT(m_portnames.get_current_name());
    DEBUG_OUT_POD(m_portnames.get_current_value());
    DEBUG_OUT_POD(m_portnames.getCurrentIndex());
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Baud rate: " + m_baudrate.get_current_name() + ": ");
    DEBUG_OUT_POD(m_baudrate.get_current_value());
    DEBUG_OUT_POD(m_baudrate.getCurrentIndex());
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Parity: " + m_parity.get_current_name() + ": ");
    DEBUG_OUT_POD(m_parity.get_current_value());
    DEBUG_OUT_POD(m_parity.getCurrentIndex());
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Data bits: " + m_databits.get_current_name() + ": ");
    DEBUG_OUT_POD(m_databits.get_current_value());
    DEBUG_OUT_POD(m_databits.getCurrentIndex());
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Stop bits: " + m_stopbits.get_current_name() + ": ");
    DEBUG_OUT_POD(m_stopbits.get_current_value());
    DEBUG_OUT_POD(m_stopbits.getCurrentIndex());
    QDEBUG_OUT("*****************************************************");
    QDEBUG_OUT("Flow control: " + m_flowcontrol.get_current_name() + ": ");
    DEBUG_OUT_POD(m_flowcontrol.get_current_value());
    DEBUG_OUT_POD(m_flowcontrol.getCurrentIndex());
}

int QSerialPortConfig::Cdc_write_timeout() const
{
    return m_Cdc_write_timeout;
}

void QSerialPortConfig::setCdc_write_timeout(int newCdc_write_timeout)
{
    if (m_Cdc_write_timeout == newCdc_write_timeout)
        return;
    m_Cdc_write_timeout = newCdc_write_timeout;
    emit Cdc_write_timeoutChanged();
}

int QSerialPortConfig::Cdc_read_timeout() const
{
    return m_Cdc_read_timeout;
}

void QSerialPortConfig::setCdc_read_timeout(int newCdc_read_timeout)
{
    if (m_Cdc_read_timeout == newCdc_read_timeout)
        return;
    m_Cdc_read_timeout = newCdc_read_timeout;
    emit Cdc_read_timeoutChanged();
}

int QSerialPortConfig::Cdc_cmd_process_timeout() const
{
    return m_Cdc_cmd_process_timeout;
}

void QSerialPortConfig::setCdc_cmd_process_timeout(int newCdc_cmd_process_timeout)
{
    if (m_Cdc_cmd_process_timeout == newCdc_cmd_process_timeout)
        return;
    m_Cdc_cmd_process_timeout = newCdc_cmd_process_timeout;
    emit Cdc_cmd_process_timeoutChanged();
}

int QSerialPortConfig::Cdc_Jni_drv_timeout() const
{
    return m_Cdc_Jni_drv_timeout;
}

void QSerialPortConfig::setCdc_Jni_drv_timeout(int newCdc_Jni_drv_timeout)
{
    if (m_Cdc_Jni_drv_timeout == newCdc_Jni_drv_timeout)
        return;
    m_Cdc_Jni_drv_timeout = newCdc_Jni_drv_timeout;
    emit Cdc_Jni_drv_timeoutChanged();
}

int QSerialPortConfig::Cdc_busy_cmd_trials() const
{
    return m_Cdc_busy_cmd_trials;
}

void QSerialPortConfig::setCdc_busy_cmd_trials(int newCdc_busy_cmd_trials)
{
    if (m_Cdc_busy_cmd_trials == newCdc_busy_cmd_trials)
        return;
    m_Cdc_busy_cmd_trials = newCdc_busy_cmd_trials;
    emit Cdc_busy_cmd_trialsChanged();
}

int QSerialPortConfig::max_recieve_data_per_request() const
{
    return m_max_recieve_data_per_request;
}

void QSerialPortConfig::setMax_recieve_data_per_request(int newMax_recieve_data_per_request)
{
    if (m_max_recieve_data_per_request == newMax_recieve_data_per_request)
        return;
    m_max_recieve_data_per_request = newMax_recieve_data_per_request;
    emit max_recieve_data_per_requestChanged();
}

int QSerialPortConfig::max_transmit_data_per_request() const
{
    return m_max_transmit_data_per_request;
}

void QSerialPortConfig::setMax_transmit_data_per_request(int newMax_transmit_data_per_request)
{
    if (m_max_transmit_data_per_request == newMax_transmit_data_per_request)
        return;
    m_max_transmit_data_per_request = newMax_transmit_data_per_request;
    emit max_transmit_data_per_requestChanged();
}

const QString &QSerialPortConfig::filename_recieved() const
{
    return m_filename_recieved;
}

void QSerialPortConfig::setFilename_recieved(const QString &newFilename_recieved)
{
    if (m_filename_recieved == newFilename_recieved)
        return;
    m_filename_recieved = newFilename_recieved;
    emit filename_recievedChanged();
}

const QString &QSerialPortConfig::filename_to_send() const
{
    return m_filename_to_send;
}

void QSerialPortConfig::setFilename_to_send(const QString &newFilename_to_send)
{
    if (m_filename_to_send == newFilename_to_send)
        return;
    m_filename_to_send = newFilename_to_send;
    emit filename_to_sendChanged();
}

const QString &QSerialPortConfig::filename_scan_recieved() const
{
    return m_filename_scan_recieved;
}

void QSerialPortConfig::setFilename_scan_recieved(const QString &newFilename_scan_recieved)
{
    if (m_filename_scan_recieved == newFilename_scan_recieved)
        return;
    m_filename_scan_recieved = newFilename_scan_recieved;
    emit filename_scan_recievedChanged();
}

const QString &QSerialPortConfig::filename_script_to_send() const
{
    return m_filename_script_to_send;
}

void QSerialPortConfig::setFilename_script_to_send(const QString &newFilename_script_to_send)
{
    if (m_filename_script_to_send == newFilename_script_to_send)
        return;
    m_filename_script_to_send = newFilename_script_to_send;
    emit filename_script_to_sendChanged();
}
