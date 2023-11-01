#ifndef CDC_DRIVER_H
#define CDC_DRIVER_H

/***********************************************************************
 *
 *
 * CDC Driver describes main COM-port library functions:
 *
 * Modes:
 *        read to the console
 *        read to a scanner
 *        read data for CAN message trace injection
 *
 * Main functions:
 *        read incoming data
 *        (exchange) send data and then read a response
 *        send data
 *
 *
 *
 ************************************************************************/

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif
#include <QThread>
#include "QSerialPortConfig.h"
#include "../../core/Console.h"
#include "../androidserial/QASerialPort.h"
#include "../bus/BusManager.h"
#include <QSerialPort>


class CDC_Driver: public QObject{
Q_OBJECT
public:
    CDC_Driver(QObject * parent = nullptr): QObject(parent){
    };
    ~CDC_Driver(){
    };

    enum {
        AsynchReadToConsole = 0,
        AsynchReadToScanner = 1,
        AsynchReadInjectionMode = 2,
        AsynchReadToLinScanner = 3
    };

    //==================================== init =====================================
    virtual bool init(){return RESULT_OK;};


    //======================== COM-port connect/disconnect ==========================
    virtual bool connect(){return RESULT_OK;};
    virtual bool disconnect(){return RESULT_OK;};
    int connection_status() const;
    bool isConnected()const;
    void setConnection_status(App_settings::ConnectionStatus newConnection_status);


    //============================== Exchange data IO ===============================
    // Synch.mode: Send data and then read a response
    virtual QByteArray exchange_data(const QByteArray &cmd, int custom_timeout = 0){return cmd;};
    // send data
    virtual bool writeData(const QByteArray &data) {return RESULT_OK;}
    // read incoming data
    virtual QByteArray readData(int timeout = 0) {return QByteArray();}


    //============================= Asynchronous mode ===============================
    virtual void startAsynchReading(int mode){}
    virtual void stopAsynchReading(int mode){}
    /* flag */
    bool asynch_read() const;
    void setAsynch_read(bool newAsynch_read);


    //============================= Debug and print =================================
    void set_data(const QString &_string);
    void print_data(const QString &_string);


    //============================= Connection settings =============================
    int maxRxBytes_per_request()const;
    int maxTxBytes_per_request()const;
    int trialsOnBusyResponse()const;
    int read_timeout()const;
    void set_custom_read_timeout(const int _timeout);


    //========================= Class Setters/getters  ==============================
    Console *pConsole() const;
    void setPConsole(Console *newPConsole);

    QSerialPortConfig *pSerialPortConfig() const;
    void setPSerialPortConfig(QSerialPortConfig *newPSerialPortConfig);

    virtual QASerialPort *getQASerialPortPtr(){return nullptr;}
    virtual QSerialPort *getQSerialPortPtr(){return nullptr;}

signals:
    void connection_status_changed();
    void async_read_changed();
    void async_data_passover(const QByteArray arr);


protected:
    bool m_asynch_read = false;
    QSerialPortConfig * m_pSerialPortConfig;

    Console *m_pConsole = nullptr;

    App_settings::ConnectionStatus m_connection_status = App_settings::ConnectionStatus::Disconnected;

    QMetaObject::Connection conn;
};

#endif // CDC_DRIVER_H
