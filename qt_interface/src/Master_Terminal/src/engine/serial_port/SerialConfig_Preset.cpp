#include "SerialConfig_Preset.h"

#ifdef QT_IN_USE

/********************************************************************
 *
 *
 *                    Class setters/getters
 *
 *
********************************************************************/

const QString &SerialConfig_Preset::getPortname() const{
    return portname;
}

int SerialConfig_Preset::getBaudrate() const{
    return baudrate;
}

int SerialConfig_Preset::getParity() const{
    return parity;
}

int SerialConfig_Preset::getDatabits() const{
    return databits;
}

int SerialConfig_Preset::getStopbits() const{
    return stopbits;
}

int SerialConfig_Preset::getFlowcontrol() const{
    return flowcontrol;
}

int SerialConfig_Preset::getCustom_baudrate() const{
    return custom_baudrate;
}

int SerialConfig_Preset::getWrite_timeout() const{
    return write_timeout;
}

int SerialConfig_Preset::getRead_timeout() const{
    return read_timeout;
}

int SerialConfig_Preset::getCmd_process_timeout() const{
    return cmd_process_timeout;
}

int SerialConfig_Preset::getJni_drv_timeout() const{
    return jni_drv_timeout;
}

int SerialConfig_Preset::getBusy_cmd_trials() const{
    return busy_cmd_trials;
}

int SerialConfig_Preset::getMax_tx_bytes_per_request() const{
    return max_tx_bytes_per_request;
}

int SerialConfig_Preset::getMax_rx_bytes_per_request() const{
    return max_rx_bytes_per_request;
}

const QString &SerialConfig_Preset::getFilename_recieved() const{
    return filename_recieved;
}

const QString &SerialConfig_Preset::getFilename_to_send() const{
    return filename_to_send;
}

const QString &SerialConfig_Preset::getFilename_scan_recieved() const{
    return filename_scan_recieved;
}

const QString &SerialConfig_Preset::getFilename_script_to_send() const{
    return filename_script_to_send;
}

/********************************************************************
 *
 *
 *                     Operators
 *
 *
********************************************************************/

QDataStream& operator << (QDataStream& d, const SerialConfig_Preset& scp){
    d << scp.portname;
    d << scp.baudrate;
    d << scp.parity;
    d << scp.databits;
    d << scp.stopbits;
    d << scp.flowcontrol;
    d << scp.custom_baudrate;

    d << scp.write_timeout;
    d << scp.read_timeout;
    d << scp.cmd_process_timeout;
    d << scp.jni_drv_timeout;
    d << scp.busy_cmd_trials;
    d << scp.max_rx_bytes_per_request;
    d << scp.max_tx_bytes_per_request;

    d << scp.filename_recieved;
    d << scp.filename_to_send;
    d << scp.filename_scan_recieved;
    d << scp.filename_script_to_send;
    return d;
}

QDataStream& operator >> (QDataStream& d, SerialConfig_Preset& scp){
    d >> scp.portname;
    d >> scp.baudrate;
    d >> scp.parity;
    d >> scp.databits;
    d >> scp.stopbits;
    d >> scp.flowcontrol;
    d >> scp.custom_baudrate;

    d >> scp.write_timeout;
    d >> scp.read_timeout;
    d >> scp.cmd_process_timeout;
    d >> scp.jni_drv_timeout;
    d >> scp.busy_cmd_trials;
    d >> scp.max_rx_bytes_per_request;
    d >> scp.max_tx_bytes_per_request;

    d >> scp.filename_recieved;
    d >> scp.filename_to_send;
    d >> scp.filename_scan_recieved;
    d >> scp.filename_script_to_send;
    return d;
}


#endif

#ifndef QT_IN_USE

const string &SerialConfig_Preset::getPortname() const
{
    return portname;
}

int SerialConfig_Preset::getBaudrate() const
{
    return baudrate;
}

int SerialConfig_Preset::getParity() const
{
    return parity;
}

int SerialConfig_Preset::getDatabits() const
{
    return databits;
}

int SerialConfig_Preset::getStopbits() const
{
    return stopbits;
}

int SerialConfig_Preset::getFlowcontrol() const
{
    return flowcontrol;
}

int SerialConfig_Preset::getCustom_baudrate() const
{
    return custom_baudrate;
}

int SerialConfig_Preset::getWrite_timeout() const
{
    return write_timeout;
}

int SerialConfig_Preset::getRead_timeout() const
{
    return read_timeout;
}

int SerialConfig_Preset::getCmd_process_timeout() const
{
    return cmd_process_timeout;
}

int SerialConfig_Preset::getJni_drv_timeout() const
{
    return jni_drv_timeout;
}

int SerialConfig_Preset::getBusy_cmd_trials() const
{
    return busy_cmd_trials;
}

int SerialConfig_Preset::getMax_tx_bytes_per_request() const
{
    return max_tx_bytes_per_request;
}

int SerialConfig_Preset::getMax_rx_bytes_per_request() const
{
    return max_rx_bytes_per_request;
}

const string &SerialConfig_Preset::getFilename_recieved() const
{
    return filename_recieved;
}

const string &SerialConfig_Preset::getFilename_to_send() const
{
    return filename_to_send;
}

const string &SerialConfig_Preset::getFilename_scan_recieved() const
{
    return filename_scan_recieved;
}

const string &SerialConfig_Preset::getFilename_script_to_send() const
{
    return filename_script_to_send;
}

#endif
