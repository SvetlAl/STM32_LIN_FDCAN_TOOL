#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "../../app_settings.h"

#include <QObject>
#include <QDebug>

#include "../../core/VersionManager.h"
#include "CommandConstructor.h"
#include "./src/core/Console.h"
#include "./src/engine/vehicle/Vehicle.h"
#include "./src/engine/vehicle/QML_Model/QVehicle_ModelProperty.h"
#include "../serial_port/QSerialPortConfig.h"
#include "../serial_port/CDC_Driver.h"
#include "../memory/MemoryManager.h"
#include "../stm32_device/DeviceManager.h"

#if defined(PC_WINDOWS) || defined(PC_LINUX)
    #include "../serial_port/CDC_PC_Driver.h"
#elif defined(ANDROID_V)
    #include "../serial_port/CDC_JNI_Driver.h"
#else
     #error "Either PC_V or ANDROID_V must be defined."
#endif

class CommandManager : public QObject{
    Q_OBJECT
    /******************************************************************************************/
    /*                     Supported vehicle models                                           */
    /******************************************************************************************/
    Q_PROPERTY(QVehicleNames_ModelProperty* vehicleNames_Model READ vehicleNames_Model CONSTANT )

    /******************************************************************************************/
    /*                           Flags                                                        */
    /******************************************************************************************/
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectStatusChanged)
    Q_PROPERTY(bool AsynchRead READ isAsynchRead NOTIFY asynchReadChanged)


public:
    explicit CommandManager(QObject *parent = nullptr): QObject(parent){
    #ifdef USB_CDC_INTERFACE
        #if defined(PC_WINDOWS) || defined(PC_LINUX)
        m_pCDC_drv = new CDC_PC_Driver(this);
        #elif defined(ANDROID_V)
        m_pCDC_drv = new CDC_JNI_Driver(this);
        #else
             #error "Either PC_V or ANDROID_V must be defined."
        #endif
    #endif
    };
    ~CommandManager(){};


    /******************************************************************************************/
    /*                               Connect/disconnect                                       */
    /******************************************************************************************/

    Q_INVOKABLE bool connect();
    Q_INVOKABLE bool disconnect();
    Q_INVOKABLE bool connect_switch(); // switch connect/disconnect
    bool isConnected();

    /******************************************************************************************/
    /*                               Initialization                                           */
    /******************************************************************************************/

    void init_driver();
    Q_INVOKABLE void reset_vehicleNames_Model();
    Q_INVOKABLE void init_vehicleNames_Model();

    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               General IO procedures                                    */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/


    /******************************************************************************************/
    /*                               Asynchronous reading                                     */
    /******************************************************************************************/

    Q_INVOKABLE bool isAsynchRead();
    Q_INVOKABLE void start_asynch_read(int mode);
    Q_INVOKABLE void stop_asynch_read(int mode);


    /******************************************************************************************/
    /*                               Raw data handling                                        */
    /******************************************************************************************/

    /* O */
    Q_INVOKABLE bool writeRawData(uint32_t address, const QByteArray &data, bool append = false);
    Q_INVOKABLE bool writeRawData(uint32_t address, const QString &value, bool sendFromFile, bool append); // from file
    // writeRawData ==> sendRawData
    bool sendRawData(const QByteArray &data) const;
    /* I */
    Q_INVOKABLE QByteArray waitAndReadResponse(int timeout);

    /******************************************************************************************/
    /*                               Exchange commands                                        */
    /******************************************************************************************/

    Q_INVOKABLE QString exchange_cmd_string(QString _output_cmd, bool print = false, bool handle = true);
    QByteArray exchange_cmd_string_HEX(const QByteArray& _cmd_2_send, QByteArray *_cmd_output, bool handle = true, int timeout = 0);



    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               Designated functions                                     */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    /******************************************************************************************/
    /*                               Device memory                                            */
    /******************************************************************************************/

    Q_INVOKABLE bool readMemoryData(int address, int transaction_length){
    #ifndef ANDROID_V
        int max_rx_bytes = m_pCDC_drv->maxRxBytes_per_request();

        int temp_length = transaction_length;

        int addr_counter = address;

        QByteArray buffer;

        while(temp_length > max_rx_bytes){
            buffer.resize(max_rx_bytes);
            m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, max_rx_bytes);
            exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false, 100);

            bool result = m_pMemoryManager->parseByteArray(addr_counter, buffer, max_rx_bytes);
            if(!result) return false;
            temp_length -= max_rx_bytes;
            addr_counter += max_rx_bytes;
            buffer.clear();
        }

        buffer.resize(temp_length);
        m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, temp_length);
        exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false, 100);
        m_pMemoryManager->parseByteArray(addr_counter, buffer, temp_length);
        return true;
    #endif
    #ifdef ANDROID_V
        int max_rx_bytes = 64; //m_pCDC_drv->maxRxBytes_per_request();
        int temp_length = transaction_length;
        int addr_counter = address;

        QByteArray buffer;

        while(temp_length > max_rx_bytes){
            buffer.resize(max_rx_bytes);
            m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, max_rx_bytes);
            exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false, 100);

            bool result = m_pMemoryManager->parseByteArray(addr_counter, buffer, max_rx_bytes);
            if(!result) return false;
            temp_length -= max_rx_bytes;
            addr_counter += max_rx_bytes;
            buffer.clear();
        }
        buffer.resize(temp_length);
        m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, temp_length);
        exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false, 100);
        m_pMemoryManager->parseByteArray(addr_counter, buffer, temp_length);
        return true;
    #endif
    }

    /******************************************************************************************/
    /*                               Vehicle related commands                                 */
    /******************************************************************************************/

    Q_INVOKABLE bool setAndSaveVehicleModel(uint16_t model_code);
    Q_INVOKABLE void updateVehicleStatus();
    Q_INVOKABLE bool saveVehicleStatus(bool initNewModel);
    void getAndInitCurrentVehicleStatus();

    Q_INVOKABLE bool setCalibratorValue(uint32_t property, uint32_t value);

    /******************************************************************************************/
    /*                               Device version related commands                          */
    /******************************************************************************************/

    void getAndInitDevSoftware();
    void getAndInitHardwareVersion();
    void resetAndroidCmdBuffer();

    /******************************************************************************************/
    /*                               Device modes and override filters                        */
    /******************************************************************************************/

    Q_INVOKABLE void updateDeviceStatus(); // calibrator, scanner, gateway
    Q_INVOKABLE void saveDeviceStatus(); // device status and override filters
    Q_INVOKABLE bool setDeviceValue(uint32_t property, uint8_t value);


    Q_INVOKABLE bool updateOverrideStatus();
    Q_INVOKABLE bool updateOverrideActiveFilters();
    Q_INVOKABLE bool sendOverrideFilterConfiguration();


 //   Q_INVOKABLE bool removeOverrideEntry(uint8_t override_method); // TODO deprecate
 //   Q_INVOKABLE bool addDiscardEntry(uint8_t can, QString can_id); // TODO deprecate
 //   Q_INVOKABLE bool addOverrideFilterEntry(uint8_t can, QString can_id, uint8_t ovr_fltr_msk, const QByteArray &msgdata); // TODO deprecate

 //   Q_INVOKABLE bool setOverrideStatusValue(uint32_t property, uint8_t value);

    /******************************************************************************************/
    /*                               Update procedure                                         */
    /******************************************************************************************/

    Q_INVOKABLE void startWebUpdate();
    Q_INVOKABLE void startEmerencyProgramm(const QString &_filename);
    Q_INVOKABLE void startFileUpdate(const QString &_filename);



    /******************************************************************************************/
    /******************************************************************************************/
    /*                                                                                        */
    /*                               Setters/getters                                          */
    /*                                                                                        */
    /******************************************************************************************/
    /******************************************************************************************/

    void setPSerialPortConfig(QSerialPortConfig *newPSerialPortConfig);

    //=================================
    Vehicle *vehicle() const;
    void setVehicle(Vehicle *newPVehicle);
    //=================================
    Console *pConsole() const;
    void setPConsole(Console *newPConsole);
    //=================================
    VersionManager *Versions() const;
    void setVersions(VersionManager *newPVersions);
    //=================================
    MemoryManager *pMemoryManager() const;
    void setPMemoryManager(MemoryManager *newPMemoryManager);
    //=================================
    DeviceManager *pDeviceManager() const;
    void setDeviceManager(DeviceManager *newPDeviceManager);
    //=================================
    BusManager *pBusManager() const;
    void setPBusManager(BusManager *newPBusManager);

    CDC_Driver *pCDC_drv() const;

    /****** Vehicle Model ************/

    QVehicleNames_ModelProperty *vehicleNames_Model(){return &m_vehicles_model;}




public slots:
    void onCanScannerDataRecieved(const QByteArray _data){
        // записать в буфер
        // начать обработку
        //qDebug() << QString(_data);
        emit asynchronousDataIn(_data);
    }

    void refreshAsynchRead(){
        emit asynchReadChanged();
    }

signals:
    void asynchronousDataIn(const QByteArray _data);
    void connectStatusChanged();
    void asynchReadChanged();

private:
    /* unused */
    void console_print(const QString _data);
    CDC_Driver *m_pCDC_drv = nullptr;
    Console *m_pConsole = nullptr;
    Vehicle *m_pVehicle = nullptr;
    VersionManager *m_pVersions = nullptr;
    MemoryManager *m_pMemoryManager = nullptr;
    DeviceManager *m_pDeviceManager = nullptr;
    BusManager *m_pBusManager = nullptr;

    CommandConstructor m_cmdConstructor;
    void reset_all_on_disconnect();

    QVehicleNames_ModelProperty m_vehicles_model;

    uint32_t update_procedure_start(QString file_path, int firmware_address, int firmware_sz_address);
    uint32_t update_procedure_getFileSize(QString path);
    uint32_t update_procedure_verifyData(QString path, int firmware_address);
};


// Q_DECLARE_METATYPE(CommandManager);
#endif // COMMANDMANAGER_H
