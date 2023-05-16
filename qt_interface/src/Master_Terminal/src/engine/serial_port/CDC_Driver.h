#ifndef CDC_DRIVER_H
#define CDC_DRIVER_H

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
        AsynchReadToScanner = 1
    };



    /******************************************************************************************/
    /*                                     Initialization                                     */
    /******************************************************************************************/

    virtual bool init(){return RESULT_OK;};

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               Synchronous work                                         */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                                  Connect/disconnect                                    */
    /******************************************************************************************/
    virtual bool connect(){return RESULT_OK;};
    virtual bool disconnect(){return RESULT_OK;};
    int connection_status() const;
    bool isConnected()const;
    void setConnection_status(App_settings::ConnectionStatus newConnection_status);

    /******************************************************************************************/
    /*                                  Data exchange, I/O                                    */
    /******************************************************************************************/

    virtual QByteArray exchange_data(const QByteArray &cmd, int custom_timeout = 0){return cmd;};

    virtual bool writeData(const QByteArray &data) {return RESULT_OK;}
    virtual QByteArray readData(int timeout = 0) {return QByteArray();}

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               Asynchronous work                                        */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                                      Start/stop                                        */
    /******************************************************************************************/

    virtual void startAsynchReading(int mode){}
    virtual void stopAsynchReading(int mode){}
    /* flag */
    bool asynch_read() const;
    void setAsynch_read(bool newAsynch_read);

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               External objects interaction                             */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                                   Data print                                           */
    /******************************************************************************************/

    void set_data(const QString &_string);
    void print_data(const QString &_string);

    /******************************************************************************************/
    /*                                        Settings                                        */
    /******************************************************************************************/

    int maxRxBytes_per_request()const;
    int maxTxBytes_per_request()const;
    int trialsOnBusyResponse()const;

    /******************************************************************************************/
    /*                                      Setters/getters                                   */
    /******************************************************************************************/
    Console *pConsole() const;
    void setPConsole(Console *newPConsole);

    QSerialPortConfig *pSerialPortConfig() const;
    void setPSerialPortConfig(QSerialPortConfig *newPSerialPortConfig);

//    BusManager *pBusManager() const;
//    void setPBusManager(BusManager *newPBusManager);

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
//    BusManager *m_pBusManager = nullptr;

    App_settings::ConnectionStatus m_connection_status = App_settings::ConnectionStatus::Disconnected;

    QMetaObject::Connection conn;
};

#endif // CDC_DRIVER_H
