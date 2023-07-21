#ifndef SERIALCONFIG_PRESET_H
#define SERIALCONFIG_PRESET_H

#include <stdlib.h>
#include <iostream>
#include "../../app_settings.h"


#ifdef QT_IN_USE
class SerialConfig_Preset{
public:
    explicit SerialConfig_Preset() = default;
     SerialConfig_Preset(QString _portname,
                         int _baudrate,
                         int _parity,
                         int _databits,
                         int _stopbits,
                         int _flowcontrol,
                         int _custom_baudrate,

                         int _write_timeout,
                         int _read_timeout,
                         int _cmd_process_timeout,
                         int _jni_drv_timeout,
                         int _busy_cmd_trials,
                         int _max_tx_bytes_per_request,
                         int _max_rx_bytes_per_request,

                         QString _filename_recieved,
                         QString _filename_to_send,
                         QString _filename_scan_recieved,
                         QString _filename_script_to_send):

         portname(_portname),
         baudrate(_baudrate),
         parity(_parity),
         databits(_databits),
         stopbits(_stopbits),
         flowcontrol(_flowcontrol),
         custom_baudrate(_custom_baudrate),

         write_timeout(_write_timeout),
         read_timeout(_read_timeout),
         cmd_process_timeout(_cmd_process_timeout),
         jni_drv_timeout(_jni_drv_timeout),
         busy_cmd_trials(_busy_cmd_trials),
         max_tx_bytes_per_request(_max_tx_bytes_per_request),
         max_rx_bytes_per_request(_max_rx_bytes_per_request),

         filename_recieved(_filename_recieved),
         filename_to_send(_filename_to_send),
         filename_scan_recieved(_filename_scan_recieved),
         filename_script_to_send(_filename_script_to_send)

     {}

    ~SerialConfig_Preset() = default;

     friend QDataStream& operator >>( QDataStream& d, SerialConfig_Preset& scp);
     friend QDataStream& operator << (QDataStream& d, const SerialConfig_Preset& scp);


    const QString &getPortname() const;
    int getBaudrate() const;
    int getParity() const;
    int getDatabits() const;
    int getStopbits() const;
    int getFlowcontrol() const;
    int getCustom_baudrate() const;

    int getWrite_timeout() const;
    int getRead_timeout() const;
    int getCmd_process_timeout() const;
    int getJni_drv_timeout() const;
    int getBusy_cmd_trials() const;

    int getMax_tx_bytes_per_request() const;
    int getMax_rx_bytes_per_request() const;

    const QString &getFilename_recieved() const;
    const QString &getFilename_to_send() const;
    const QString &getFilename_scan_recieved() const;
    const QString &getFilename_script_to_send() const;

private:
    QString portname;
    int baudrate;
    int parity;
    int databits;
    int stopbits;
    int flowcontrol;
    int custom_baudrate;

    int write_timeout;
    int read_timeout;
    int cmd_process_timeout;
    int jni_drv_timeout;
    int busy_cmd_trials;
    int max_rx_bytes_per_request;
    int max_tx_bytes_per_request;

    QString filename_recieved;
    QString filename_to_send;
    QString filename_scan_recieved;
    QString filename_script_to_send;
};

QDataStream& operator << (QDataStream& d, const SerialConfig_Preset& scp);
QDataStream& operator >> (QDataStream& d, SerialConfig_Preset& scp);

#endif
#ifndef QT_IN_USE
#include "../../engine/file_manager/SimpleSerializer.h"

using namespace std;

class SerialConfig_Preset{
public:
    explicit SerialConfig_Preset() = default;
     SerialConfig_Preset(string _portname,
                         int _baudrate,
                         int _parity,
                         int _databits,
                         int _stopbits,
                         int _flowcontrol,
                         int _custom_baudrate,

                         int _write_timeout,
                         int _read_timeout,
                         int _cmd_process_timeout,
                         int _jni_drv_timeout,
                         int _busy_cmd_trials,
                         int _max_tx_bytes_per_request,
                         int _max_rx_bytes_per_request,

                         string _filename_recieved,
                         string _filename_to_send,
                         string _filename_scan_recieved,
                         string _filename_script_to_send):

         portname(_portname),
         baudrate(_baudrate),
         parity(_parity),
         databits(_databits),
         stopbits(_stopbits),
         flowcontrol(_flowcontrol),
         custom_baudrate(_custom_baudrate),

         write_timeout(_write_timeout),
         read_timeout(_read_timeout),
         cmd_process_timeout(_cmd_process_timeout),
         jni_drv_timeout(_jni_drv_timeout),
         busy_cmd_trials(_busy_cmd_trials),
         max_tx_bytes_per_request(_max_tx_bytes_per_request),
         max_rx_bytes_per_request(_max_rx_bytes_per_request),

         filename_recieved(_filename_recieved),
         filename_to_send(_filename_to_send),
         filename_scan_recieved(_filename_scan_recieved),
         filename_script_to_send(_filename_script_to_send)

     {}

    ~SerialConfig_Preset() = default;


    std::ostream& serialize (std::ostream &out){
        out << bits(this->portname);
        out << bits(this->baudrate);
        out << bits(this->parity);
        out << bits(this->databits);
        out << bits(this->stopbits);
        out << bits(this->flowcontrol);
        out << bits(this->custom_baudrate);

        out << bits(this->write_timeout);
        out << bits(this->read_timeout);
        out << bits(this->cmd_process_timeout);
        out << bits(this->jni_drv_timeout);
        out << bits(this->busy_cmd_trials);
        out << bits(this->max_rx_bytes_per_request);
        out << bits(this->max_tx_bytes_per_request);

        out << bits(this->filename_recieved);
        out << bits(this->filename_to_send);
        out << bits(this->filename_scan_recieved);
        out << bits(this->filename_script_to_send);
        return out;
    }

    std::istream& serialize(std::istream &in){
        in >> bits(this->portname);
        in >> bits(this->baudrate);
        in >> bits(this->parity);
        in >> bits(this->databits);
        in >> bits(this->stopbits);
        in >> bits(this->flowcontrol);
        in >> bits(this->custom_baudrate);

        in >> bits(this->write_timeout);
        in >> bits(this->read_timeout);
        in >> bits(this->cmd_process_timeout);
        in >> bits(this->jni_drv_timeout);
        in >> bits(this->busy_cmd_trials);
        in >> bits(this->max_rx_bytes_per_request);
        in >> bits(this->max_tx_bytes_per_request);

        in >> bits(this->filename_recieved);
        in >> bits(this->filename_to_send);
        in >> bits(this->filename_scan_recieved);
        in >> bits(this->filename_script_to_send);

        return in;
    }

    const string &getPortname() const;
    int getBaudrate() const;
    int getParity() const;
    int getDatabits() const;
    int getStopbits() const;
    int getFlowcontrol() const;
    int getCustom_baudrate() const;

    int getWrite_timeout() const;
    int getRead_timeout() const;
    int getCmd_process_timeout() const;
    int getJni_drv_timeout() const;
    int getBusy_cmd_trials() const;

    int getMax_tx_bytes_per_request() const;
    int getMax_rx_bytes_per_request() const;

    const string &getFilename_recieved() const;
    const string &getFilename_to_send() const;
    const string &getFilename_scan_recieved() const;
    const string &getFilename_script_to_send() const;

private:
    string portname;
    int baudrate;
    int parity;
    int databits;
    int stopbits;
    int flowcontrol;
    int custom_baudrate;

    int write_timeout;
    int read_timeout;
    int cmd_process_timeout;
    int jni_drv_timeout;
    int busy_cmd_trials;
    int max_rx_bytes_per_request;
    int max_tx_bytes_per_request;

    string filename_recieved;
    string filename_to_send;
    string filename_scan_recieved;
    string filename_script_to_send;
};

#endif

#endif // SERIALCONFIG_PRESET_H
