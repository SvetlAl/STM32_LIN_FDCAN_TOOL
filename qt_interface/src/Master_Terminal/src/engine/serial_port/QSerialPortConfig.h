#ifndef QSERIALPORTCONFIG_H
#define QSERIALPORTCONFIG_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif

#include "QSerialPortConfigProperty.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "SerialConfig_Preset.h"


class QSerialPortConfig: public QObject{
    Q_OBJECT
    Q_PROPERTY(QSerialPortConfigProperty_PortNumber* portnames READ portnames CONSTANT )
    Q_PROPERTY(QSerialPortConfigProperty_BaudRate* baudrate READ baudrate CONSTANT )
    Q_PROPERTY(QSerialPortConfigProperty_Parity* parity READ parity CONSTANT )
    Q_PROPERTY(QSerialPortConfigProperty_DataBits* databits READ databits CONSTANT )
    Q_PROPERTY(QSerialPortConfigProperty_StopBits* stopbits READ stopbits CONSTANT )
    Q_PROPERTY(QSerialPortConfigProperty_FlowControl* flowcontrol READ flowcontrol CONSTANT )

    Q_PROPERTY(int Cdc_write_timeout READ Cdc_write_timeout WRITE setCdc_write_timeout NOTIFY Cdc_write_timeoutChanged)
    Q_PROPERTY(int Cdc_read_timeout READ Cdc_read_timeout WRITE setCdc_read_timeout NOTIFY Cdc_read_timeoutChanged)
    Q_PROPERTY(int Cdc_cmd_process_timeout READ Cdc_cmd_process_timeout WRITE setCdc_cmd_process_timeout NOTIFY Cdc_cmd_process_timeoutChanged)
    Q_PROPERTY(int Cdc_Jni_drv_timeout READ Cdc_Jni_drv_timeout WRITE setCdc_Jni_drv_timeout NOTIFY Cdc_Jni_drv_timeoutChanged)
    Q_PROPERTY(int Cdc_busy_cmd_trials READ Cdc_busy_cmd_trials WRITE setCdc_busy_cmd_trials NOTIFY Cdc_busy_cmd_trialsChanged)
    Q_PROPERTY(int max_recieve_data_per_request READ max_recieve_data_per_request WRITE setMax_recieve_data_per_request NOTIFY max_recieve_data_per_requestChanged)
    Q_PROPERTY(int max_transmit_data_per_request READ max_transmit_data_per_request WRITE setMax_transmit_data_per_request NOTIFY max_transmit_data_per_requestChanged)

    Q_PROPERTY(QString filename_recieved READ filename_recieved WRITE setFilename_recieved NOTIFY filename_recievedChanged)
    Q_PROPERTY(QString filename_to_send READ filename_to_send WRITE setFilename_to_send NOTIFY filename_to_sendChanged)
    Q_PROPERTY(QString filename_scan_recieved READ filename_scan_recieved WRITE setFilename_scan_recieved NOTIFY filename_scan_recievedChanged)
    Q_PROPERTY(QString filename_script_to_send READ filename_script_to_send WRITE setFilename_script_to_send NOTIFY filename_script_to_sendChanged)


public:
    explicit QSerialPortConfig(QObject *parent = nullptr): QObject(parent){};
    ~QSerialPortConfig(){ }

    virtual SerialConfig_Preset make_preset(){return SerialConfig_Preset{"",0,0,0,0,0,0,0,0,0,0,0,0,0,"","","",""};};
    virtual void set_preset(const SerialConfig_Preset& _preset){};
    virtual void refresh_ports(){};

    Q_INVOKABLE void refresh(){
        refresh_ports();
    }

    Q_INVOKABLE void print();

    QSerialPortConfigProperty_PortNumber *portnames(){return &m_portnames;};
    QSerialPortConfigProperty_BaudRate *baudrate(){return &m_baudrate;};
    QSerialPortConfigProperty_Parity *parity(){return &m_parity;};
    QSerialPortConfigProperty_DataBits *databits(){return &m_databits;};
    QSerialPortConfigProperty_StopBits *stopbits(){return &m_stopbits;};
    QSerialPortConfigProperty_FlowControl *flowcontrol(){return &m_flowcontrol;};

    const QString get_portname(){return m_portnames.get_current_name();};
    qint32 get_baudrate(){return m_baudrate.get_current_value();};
    QSerialPort::DataBits get_databits(){
        return qvariant_cast<QSerialPort::DataBits>(m_databits.current_item());
    };
    QSerialPort::Parity get_parity(){
        return qvariant_cast<QSerialPort::Parity>(m_parity.current_item());
    };
    QSerialPort::StopBits get_stopbits(){
        return qvariant_cast<QSerialPort::StopBits>(m_stopbits.current_item());
    };
    QSerialPort::FlowControl get_flowcontrol(){
        return qvariant_cast<QSerialPort::FlowControl>(m_flowcontrol.current_item());
    };

    int Cdc_write_timeout() const;
    void setCdc_write_timeout(int newCdc_write_timeout);
    int Cdc_read_timeout() const;
    void setCdc_read_timeout(int newCdc_read_timeout);
    int Cdc_cmd_process_timeout() const;
    void setCdc_cmd_process_timeout(int newCdc_cmd_process_timeout);
    int Cdc_Jni_drv_timeout() const;
    void setCdc_Jni_drv_timeout(int newCdc_Jni_drv_timeout);
    int Cdc_busy_cmd_trials() const;
    void setCdc_busy_cmd_trials(int newCdc_busy_cmd_trials);

    int max_recieve_data_per_request() const;
    void setMax_recieve_data_per_request(int newMax_recieve_data_per_request);
    int max_transmit_data_per_request() const;
    void setMax_transmit_data_per_request(int newMax_transmit_data_per_request);

    const QString &filename_recieved() const;
    void setFilename_recieved(const QString &newFilename_recieved);
    const QString &filename_to_send() const;
    void setFilename_to_send(const QString &newFilename_to_send);
    const QString &filename_scan_recieved() const;
    void setFilename_scan_recieved(const QString &newFilename_scan_recieved);
    const QString &filename_script_to_send() const;
    void setFilename_script_to_send(const QString &newFilename_script_to_send);

signals:
    void Cdc_write_timeoutChanged();
    void Cdc_read_timeoutChanged();
    void Cdc_cmd_process_timeoutChanged();
    void Cdc_Jni_drv_timeoutChanged();
    void Cdc_busy_cmd_trialsChanged();

    void max_recieve_data_per_requestChanged();
    void max_transmit_data_per_requestChanged();

    void filename_recievedChanged();
    void filename_to_sendChanged();
    void filename_scan_recievedChanged();
    void filename_script_to_sendChanged();

protected:
    QSerialPortConfigProperty_PortNumber m_portnames;
    QSerialPortConfigProperty_BaudRate m_baudrate;
    QSerialPortConfigProperty_Parity m_parity;
    QSerialPortConfigProperty_DataBits m_databits;
    QSerialPortConfigProperty_StopBits m_stopbits;
    QSerialPortConfigProperty_FlowControl m_flowcontrol;

#ifndef ANDROID_V
    int m_Cdc_write_timeout = 20; /* ms */
    int m_Cdc_read_timeout = 20; /* ms */
    int m_Cdc_cmd_process_timeout = 20; /* ms */
    int m_Cdc_Jni_drv_timeout = 100; /* ms */
    int m_Cdc_busy_cmd_trials = 5; /* count */

    int m_max_recieve_data_per_request = 64; /* bytes */
    int m_max_transmit_data_per_request = 64; /* bytes */
#endif
#ifdef ANDROID_V
    int m_Cdc_write_timeout = 50; /* ms */
    int m_Cdc_read_timeout = 50; /* ms */
    int m_Cdc_cmd_process_timeout = 75; /* ms */
    int m_Cdc_Jni_drv_timeout = 100; /* ms */
    int m_Cdc_busy_cmd_trials = 5; /* count */

    int m_max_recieve_data_per_request = 64; /* bytes */
    int m_max_transmit_data_per_request = 64; /* bytes */
#endif

    QString m_filename_recieved = "recieved.bin";
    QString m_filename_to_send = "to_send.bin";
    QString m_filename_scan_recieved = "scan.txt";
    QString m_filename_script_to_send = "script_to_send.txt";


private:
};


#endif // QSERIALPORTCONFIG_H
