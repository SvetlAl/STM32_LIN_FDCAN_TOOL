#include "CommandManager.h"


/******************************************************************************************/
/*                               Connect/disconnect                                       */
/******************************************************************************************/

bool CommandManager::connect(){
    if(!m_pCDC_drv->isConnected()){
       m_pCDC_drv->init();
       bool connected = m_pCDC_drv->connect();
       if(connected) {
           getAndInitCurrentVehicleStatus();
           getAndInitHardwareVersion();
           getAndInitDevSoftware();
           updateDeviceStatus();
           resetAndroidCmdBuffer();
           //stop_asynch_read(0);
           //stop_asynch_read(1);
           //stop_asynch_read(2);
       }
       QObject::connect(m_pCDC_drv, &CDC_Driver::async_read_changed, this, &CommandManager::refreshAsynchRead);
       return connected;

    }
    else return true;
};

bool CommandManager::disconnect(){
    if(m_pCDC_drv->isConnected()){
        bool disconnected = m_pCDC_drv->disconnect();
        if(disconnected) {
            reset_all_on_disconnect();
        }
        return false;
    }
    else return false;
};

bool CommandManager::connect_switch(){
    if(!m_pCDC_drv->isConnected()){
        return connect();
    }
    else{
        return disconnect();
    }
};

bool CommandManager::isConnected(){
    return m_pCDC_drv->isConnected();
}

/******************************************************************************************/
/*                               Initialization                                           */
/******************************************************************************************/


void CommandManager::reset_vehicleNames_Model(){
    m_vehicles_model.clear();
};
void CommandManager::init_vehicleNames_Model(){
    m_vehicles_model.init();
};

void CommandManager::init_driver(){
    if(m_pCDC_drv != nullptr)
        m_pCDC_drv->init();
}

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

bool CommandManager::isAsynchRead() {
    return m_pCDC_drv->asynch_read();
}

void CommandManager::start_asynch_read(int mode){
    if(mode == CDC_Driver::AsynchReadToScanner){
        QObject::connect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::onCanScannerDataRecieved);
        QObject::connect(this, &CommandManager::asynchronousDataIn, m_pBusManager, &BusManager::processIncomingData);
    }

    else if(mode == CDC_Driver::AsynchReadToLinScanner){
        QObject::connect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::onCanScannerDataRecieved);
        QObject::connect(this, &CommandManager::asynchronousDataIn, m_pBusManager, &BusManager::processLinIncomingData);
    }

    else if(mode == CDC_Driver::AsynchReadInjectionMode){
        QObject::connect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::readInjectionModeRequest);
    }
    m_pCDC_drv->startAsynchReading(mode); emit asynchReadChanged();
};
void CommandManager::stop_asynch_read(int mode){
    m_pCDC_drv->stopAsynchReading(mode); emit asynchReadChanged();

    if(mode == CDC_Driver::AsynchReadToScanner){
        QObject::disconnect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::onCanScannerDataRecieved);
        QObject::disconnect(this, &CommandManager::asynchronousDataIn, m_pBusManager, &BusManager::processIncomingData);
    }
    else if(mode == CDC_Driver::AsynchReadToLinScanner){
        QObject::disconnect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::onCanScannerDataRecieved);
        QObject::disconnect(this, &CommandManager::asynchronousDataIn, m_pBusManager, &BusManager::processLinIncomingData);
    }
    else if(mode == CDC_Driver::AsynchReadInjectionMode){
        QObject::disconnect(m_pCDC_drv, &CDC_Driver::async_data_passover, this, &CommandManager::readInjectionModeRequest);
        setCdc_pending_flag(false);
    }
};

/******************************************************************************************/
/*                               Raw data handling                                        */
/******************************************************************************************/

/* O into memchip */
bool CommandManager::writeRawData(uint32_t address, const QByteArray &data, bool append){
    if(data.size() == 0) return true;
    if(m_pDeviceManager == nullptr) return false;
    uint8_t option = (append) ? 0x00 : 0xFF;

    m_cmdConstructor.constructCmd(ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP, address, data.size(), option);

    /****************************************************/
    m_pConsole->append_firmware_update(m_cmdConstructor.cmd_string());

    int memory_chip_timeout = data.size()/16;
    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, false, memory_chip_timeout);

/****************************************************/
    m_pConsole->append_firmware_update(response);

     if(!CommandConstructor::isResponseOk(QString::fromUtf8(response))){
         return false;
     }

     int max_tx_bytes = m_pCDC_drv->maxTxBytes_per_request();
     int temp_length = data.size();
     int pos = 0;

     while(temp_length >= max_tx_bytes){
         sendRawData(data.mid(pos, max_tx_bytes));
         temp_length -= max_tx_bytes;
         pos += max_tx_bytes;
     }

     if((temp_length != 0) & (temp_length < max_tx_bytes)){
         sendRawData(data.mid(pos, temp_length));
     }

     response = waitAndReadResponse(memory_chip_timeout/64);
     if(!CommandConstructor::isResponseOk(QString::fromUtf8(response))){
         return false;
     }
     else
         return true;
}   

bool CommandManager::writeRawData(uint32_t address, const QString &value, bool sendFromFile, bool append){
    if(!sendFromFile){

        writeRawData(address, value.toUtf8(), append);
     //   writeRawData(address, value, append);
        return true;
    }
    else{
        /*
        int line_count = m_FlashSpiModel.length();
        if(line_count==0) return false;
    */
        QFile flashFile(value);
        bool open = flashFile.open(QFile::ReadOnly);
        qDebug() << flashFile.fileName();
        if(!open) return false;
        QByteArray data;
        QDataStream stream(&flashFile);

        qint64 dataLength = flashFile.size();
        data.resize(dataLength);
        int bytesRead = stream.readRawData(data.data(), dataLength);
        if(bytesRead != dataLength){
            qDebug() << "bytesRead != dataLength";
            qDebug() << bytesRead;
            qDebug() << dataLength;

            flashFile.close();
            return false;
        }

        flashFile.close();
        if(writeRawData(address, data, append) == true)
        return true;
        else return false;
    }
}


bool CommandManager::sendRawData(const QByteArray &data) const{
    return m_pCDC_drv->writeData(data);
}

/* I */
QByteArray CommandManager::waitAndReadResponse(int timeout){
    QByteArray response = m_pCDC_drv->readData(timeout);
    return response;
}



/******************************************************************************************/
/*                               Exchange commands                                        */
/******************************************************************************************/

//======================== exchange_cmd_string ==================================

QString CommandManager::exchange_cmd_string(QString _output_cmd, bool print, bool handle){
    if(!m_pCDC_drv->isConnected()){
        reset_all_on_disconnect();
        return "";
    }
    QString output_string = "";

    if(handle){
        int trials = m_pCDC_drv->trialsOnBusyResponse();
        do{
            output_string =  QString::fromUtf8(m_pCDC_drv->exchange_data(_output_cmd.toUtf8()));
            if(!CommandConstructor::isResponseBusy(output_string)){
                break;
            }
        }
        while(trials--);
    }
    else output_string =  QString::fromUtf8(m_pCDC_drv->exchange_data(_output_cmd.toUtf8()));

    if(print){
        m_pConsole->append_manual_override(output_string);
    }
    return output_string;
};


//======================== exchange_cmd_string_HEX ==================================

QByteArray CommandManager::exchange_cmd_string_HEX(const QByteArray& _cmd_2_send, QByteArray *_cmd_output, bool handle, int timeout){
    #ifndef ANDROID_V
    if(!m_pCDC_drv->isConnected()){
        reset_all_on_disconnect();
        return "";
    }
    if(handle){
        int trials = m_pCDC_drv->trialsOnBusyResponse();
        do{
            *_cmd_output =  m_pCDC_drv->exchange_data(_cmd_2_send, timeout);
            if(!CommandConstructor::isResponseBusy(QString::fromUtf8(*_cmd_output))){
                break;
            }
        }
        while(trials--);
       // if(CommandConstructor::isResponseBusy(QString::fromUtf8(*_cmd_output)))
        return *_cmd_output;
    }
    else{
        *_cmd_output =  m_pCDC_drv->exchange_data(_cmd_2_send, timeout);
        return *_cmd_output;
    }
    #endif
#ifdef ANDROID_V
    if(!m_pCDC_drv->isConnected()){
        reset_all_on_disconnect();
        return "";
    }
    if(handle){
        int trials = m_pCDC_drv->trialsOnBusyResponse();
        do{
            *_cmd_output =  m_pCDC_drv->exchange_data(_cmd_2_send, timeout);
            if(!CommandConstructor::isResponseBusy(QString::fromUtf8(*_cmd_output))){
                break;
            }
         //   _cmd_output->clear();
        }
        while(trials--);
       // if(CommandConstructor::isResponseBusy(QString::fromUtf8(*_cmd_output)))
        return *_cmd_output;
    }
    else{
        *_cmd_output =  m_pCDC_drv->exchange_data(_cmd_2_send, timeout);
        return *_cmd_output;
    }
#endif
};



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

//======================== readMemoryData ==================================




/******************************************************************************************/
/*                               Vehicle related commands                                 */
/******************************************************************************************/

bool CommandManager::setAndSaveVehicleModel(uint16_t model_code){
    m_cmdConstructor.constructCmd(ELP_VEHICLE_SET_MODEL, (uint32_t)model_code);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));

    if(!CommandConstructor::isResponseOk(response)) return false;
    return saveVehicleStatus(true);
};

void CommandManager::updateVehicleStatus(){
    m_cmdConstructor.constructCmd(ELPR_VEHICLE_GET_CURRENT_STATUS);

    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response);

    if(response.length() != RESPONSE_LENGTH_CURRENT_STATUS_STRING_HEX){
        return;
    }
    m_cmdConstructor.translateVehicleStatus(response, *m_pVehicle);
};

bool CommandManager::saveVehicleStatus(bool initNewModel){
    uint16_t model_code = m_pVehicle->model();
    m_cmdConstructor.constructCmd(ELP_VEHICLE_SAVE_STATUS);

    const int custom_timeout = m_pCDC_drv->read_timeout();
    if(m_pDeviceManager->memchip_code() == eMemChipModel::MEMCHIP_MODEL_M45PE16){
        int temp_custom_timeout = App_settings::m_45pe16_memchip_save_timeout;
        m_pCDC_drv->set_custom_read_timeout(temp_custom_timeout);
    }
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    m_pCDC_drv->set_custom_read_timeout(custom_timeout);

    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    getAndInitCurrentVehicleStatus();

    if(m_pVehicle->model() != model_code){
        if(initNewModel)return true;
        else return false;
    }
    if(initNewModel)return false;
    else return true;
};

void CommandManager::getAndInitCurrentVehicleStatus(){
    m_cmdConstructor.constructCmd(ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));

    if(response.length() != RESPONSE_LENGTH_CURRENT_STATUS_STRING_ASCII) return;
    m_cmdConstructor.translateVehicleStatus(response, *m_pVehicle);
};

bool CommandManager::setCalibratorValue(uint32_t property, uint32_t value){
    if((property < ELP_VEHICLE_SET_SPEEDOMETER_MLT) | (property > ELP_VEHICLE_SET_MODE))
        return false;
    m_cmdConstructor.constructCmd(property, (uint32_t)value);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));

    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    return true;
};


/******************************************************************************************/
/*                               Device version related commands                          */
/******************************************************************************************/

void CommandManager::getAndInitHardwareVersion(){
    m_cmdConstructor.constructCmd(ELP_VEHICLE_GET_DEV_MODEL);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(response.length() != RESPONSE_LENGTH_GET_DEV_MODEL) return;
    m_pVersions->setHardware_device_model(response);
    //console_print(response);
};

void CommandManager::getAndInitDevSoftware(){
    m_cmdConstructor.constructCmd(ELP_VEHICLE_GET_SW_VERSION);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(response.length() != RESPONSE_LENGTH_GET_SW_VERSION) return;
    m_pVersions->setCurrent_device_version(response);
    //console_print(response);
};

void CommandManager::resetAndroidCmdBuffer(){
    m_cmdConstructor.constructCmd(ELP_VEHICLE_GET_DEV_MODEL);
    int count = 100;
    QString response ="";
    while((count-- > 0) & (response.length() != RESPONSE_LENGTH_GET_DEV_MODEL)){
        response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()), false, false);
    }
}

/******************************************************************************************/
/*                               Device modes and override filters                        */
/******************************************************************************************/

bool CommandManager::startCDC_CAN_Injection(uint8_t value){
    m_cmdConstructor.constructCmd(ELP_DEVICE_SET_MODE, Enm_canInjectionMode_CDC, value);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    else{
        start_asynch_read(CDC_Driver::AsynchReadInjectionMode);
        return true;
    }
}

void CommandManager::updateDeviceStatus(){
    m_cmdConstructor.constructCmd(ELPR_DEVICE_GET_CURRENT_STATUS);

    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response);
    //if(response.length() != DeviceManager::data_struct_size) return;
    if(m_pDeviceManager != nullptr) m_pDeviceManager->init(response);
};

void CommandManager::saveDeviceStatus(){
    m_cmdConstructor.constructCmd(ELP_DEVICE_SAVE_STATUS);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(!CommandConstructor::isResponseOk(response)){
        return;
    }
    updateDeviceStatus();
};


bool CommandManager::set_LIN_validation(bool value){
    uint8_t val_to_set = m_pDeviceManager->lin_mode();
    val_to_set &= ~0xF0;
    uint8_t val_to_renew = value ? 0xF0 : 0x00;
    val_to_set |= val_to_renew;
    return setDeviceValue(32, val_to_set); // lin_mode
}

bool CommandManager::set_LIN_mode(int value, bool _set){
    uint8_t validation_hb = m_pDeviceManager->lin_validation() ? 0xF0 : 0x00;
    uint8_t val_to_set = m_pDeviceManager->lin_mode() ; //
    uint8_t _mode = value &~ 0xF0;
    if(_set){
        val_to_set |= _mode;
    }
    else val_to_set &= ~_mode;
    val_to_set |= validation_hb;
    if(value == LIN_MODE_DEVICE) updateLIN_poll_period();
    return setDeviceValue(32, val_to_set); // lin_mode
}

void CommandManager::refresh_LIN_poll_period(uint16_t value){
    bool res = set_LIN_poll_period(value);
    if(res)updateLIN_poll_period();
}

bool CommandManager::set_LIN_poll_period(uint16_t value){
    m_cmdConstructor.constructCmd(ELP_LIN_POLL_PERIOD, (uint32_t)value);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    qDebug() << m_cmdConstructor.cmd_string();
    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    return true;
}

bool CommandManager::get_LIN_filter(bool dir_mosi){
    if(dir_mosi){
        m_cmdConstructor.constructCmd(ELPR_LIN_GET_MOSI_FILTER);
    }
    else{
        m_cmdConstructor.constructCmd(ELPR_LIN_GET_MISO_FILTER);
    }
    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, false, 10);
    if(response.size() == sizeof(lin_filter_raw)){
        m_pDeviceManager->update_lin_filter(dir_mosi, response);
        return true;
    }
    else return false;

}
bool CommandManager::set_LIN_filter(bool dir_mosi){
    lin_filter_raw* filter_ptr = m_pDeviceManager->get_refreshed_filter_ptr(dir_mosi);
    m_cmdConstructor.constructCmd(ELP_LIN_SET_FILTER, dir_mosi, filter_ptr);
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    return true;
}


void CommandManager::updateLIN_poll_period(){
    m_cmdConstructor.constructCmd(ELPR_LIN_GET_POLL_PERIOD);

    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, false, 10);
    int result = (uint16_t)response[1] | (uint16_t)(response[0] << 8);
    m_pDeviceManager->set_lin_poll_period(result);
};


bool CommandManager::setDeviceValue(uint32_t property, uint8_t value){ 
    if(property > DeviceManager::data_struct_size)
        return false;

    m_cmdConstructor.constructCmd(ELP_DEVICE_SET_MODE, property, value);

    qDebug() << m_cmdConstructor.cmd_string();

    if(property == 19){ // CDC INJECTION
        sendRawData(m_cmdConstructor.cmd_string());
        return true;
    }
    QString response = exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
    if(!CommandConstructor::isResponseOk(response)){
        return false;
    }
    updateDeviceStatus();
    return true;
};

void CommandManager::refresh_hardware_scanner_filters(bool isLowerThresh){
    for(int bytecount = 0; bytecount < 4; bytecount++){
        uint8_t value = (uint8_t)pDeviceManager()->get_harware_scanner_filter_value(bytecount, isLowerThresh);
        int position = isLowerThresh ? DeviceModelProperties::Enm_lower_hw_filter_b0 + bytecount :
                                       DeviceModelProperties::Enm_higher_hw_filter_b0 + bytecount;

        m_cmdConstructor.constructCmd(ELP_DEVICE_SET_MODE, position, value);
        exchange_cmd_string(QString::fromUtf8(m_cmdConstructor.cmd_string()));
        //setDeviceValue(position, value);
    }
    updateDeviceStatus();
}

bool CommandManager::updateOverrideActiveFilters(){
    if(!isConnected()) return false;
    m_cmdConstructor.constructCmd(ELPR_OVR_FLTR_GET_FILTER_NUMS);
    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, false, 100);
    if(response.size() ==4){
        m_pDeviceManager->refreshActiveFilters(response);
        m_pDeviceManager->update_DscModel_from_OvrSts();
        m_pDeviceManager->update_DscModel_from_OvrSts();
        return true;
    }
    return false;
}


bool CommandManager::updateOverrideStatus(){
    if(!isConnected()) return false;
    m_cmdConstructor.constructCmd(ELPR_OVR_FLTR_GET_CURRENT_STATUS);
    sendRawData(m_cmdConstructor.cmd_string());
    QByteArray ovr_status = waitAndReadResponse(1000);

    int trials = 10;
    while(trials-- & (ovr_status.size() < DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH) ){
        QByteArray part = waitAndReadResponse(1000);
        ovr_status.append(part);
    }
    if(ovr_status.size() == DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH){
        m_pDeviceManager->refreshOverrideStatus(ovr_status);
        m_pDeviceManager->update_DscModel_from_OvrSts();
        m_pDeviceManager->update_DscModel_from_OvrSts();
        return true;
    }
    return false;
}

bool CommandManager::sendOverrideFilterConfiguration(){
    if(!isConnected()) return false;
    if(m_pDeviceManager == nullptr) return false;
    m_cmdConstructor.constructCmd(ELP_UPDATE_OVR_FILTERS);
    const QByteArray data = m_pDeviceManager->getOvrFilterData();

    int memory_chip_timeout = data.size()/16;

    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, false, memory_chip_timeout);

    if(!CommandConstructor::isResponseOk(QString::fromUtf8(response))){
        return false;
    }

    int max_tx_bytes = m_pCDC_drv->maxTxBytes_per_request();
    int temp_length = data.size();
    int pos = 0;

    while(temp_length >= max_tx_bytes){
        sendRawData(data.mid(pos, max_tx_bytes));
        temp_length -= max_tx_bytes;
        pos += max_tx_bytes;
    }

    if((temp_length != 0) & (temp_length < max_tx_bytes)){
        sendRawData(data.mid(pos, temp_length));
    }

    response = waitAndReadResponse(memory_chip_timeout/64);
    if(!CommandConstructor::isResponseOk(QString::fromUtf8(response))){
        return false;
    }
    else{
        return true;
    }
}




/******************************************************************************************/
/*                               Update procedure                                         */
/******************************************************************************************/

void CommandManager::startWebUpdate(){
    m_pConsole->append_firmware_update("Download completed. Starting Flash programming.");
    //================ Model Code ==============================
    char device_code = m_pVersions->hardware_device_model_code();
    QString qdevice_code= QChar(device_code);
    m_pConsole->append_firmware_update("Device code: " + qdevice_code);

    // 0x03E7FC BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR
    uint32_t size_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR, device_code);
    // 0x02EE00
    uint32_t firmware_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_UPDATE_PROGRAMM_ADDR, device_code);

    uint32_t write_result;
    write_result = update_procedure_start(App_settings::UPDATE_CACHE_PATH, firmware_address, size_address);
    if(write_result == 0) return;

    uint32_t verify_result = update_procedure_verifyData(App_settings::UPDATE_CACHE_PATH, firmware_address);

    if(verify_result != 0){
        m_pConsole->append_firmware_update("Verification OK: power down and reset the device.");
    }
    else m_pConsole->append_firmware_update("Verification Failed: " + QString::number(verify_result));
}


//========================= RECOVERY ===================================

void CommandManager::startEmerencyProgramm(const QString &_filename){
    m_pConsole->append_firmware_update("Update procedure: " + _filename);

    //================ Model Code ==============================
    char device_code = m_pVersions->hardware_device_model_code();
    QString qdevice_code= QChar(device_code);
    m_pConsole->append_firmware_update("Device code: " + qdevice_code);

    // 0x02EDFC BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR
    uint32_t size_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR, device_code);
    // 0x01F400
    uint32_t firmware_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, device_code);

    uint32_t write_result;
    write_result = update_procedure_start(_filename, firmware_address, size_address);
    if(write_result == 0) return;

    uint32_t verify_result = update_procedure_verifyData(_filename, firmware_address);

    if(verify_result != 0){
        m_pConsole->append_firmware_update("Verification OK: power down and reset the device.");
    }
    else m_pConsole->append_firmware_update("Verification Failed: " + QString::number(verify_result));
}


//========================= OVERRIDE ===================================

void CommandManager::startFileUpdate(const QString &_filename){
    m_pConsole->append_firmware_update("Update procedure: " + _filename);
    //================ Model Code ==============================
    char device_code = m_pVersions->hardware_device_model_code();
    QString qdevice_code= QChar(device_code);
    m_pConsole->append_firmware_update("Device code: " + qdevice_code);

    // 0x03E7FC BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR
    uint32_t size_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR, device_code);
    // 0x02EE00
    uint32_t firmware_address = m_cmdConstructor.getMemchipAddress(CommandConstructor::MemChipAddress::BOOTLOADER_UPDATE_PROGRAMM_ADDR, device_code);

    uint32_t write_result;
    write_result = update_procedure_start(_filename, firmware_address, size_address);
    if(write_result == 0) return;

    uint32_t verify_result = update_procedure_verifyData(_filename, firmware_address);

    if(verify_result != 0){
        m_pConsole->append_firmware_update("Verification OK: power down and reset the device.");
    }
    else m_pConsole->append_firmware_update("Verification Failed: " + QString::number(verify_result));
}




/******************************************************************************************/
/******************************************************************************************/
/*                                                                                        */
/*                               Setters/getters                                          */
/*                                                                                        */
/******************************************************************************************/
/******************************************************************************************/


void CommandManager::setPSerialPortConfig(QSerialPortConfig *newPSerialPortConfig){
    if(m_pCDC_drv!= nullptr)
        m_pCDC_drv->setPSerialPortConfig(newPSerialPortConfig);
}

Console *CommandManager::pConsole() const{
    return m_pConsole;
}

void CommandManager::setPConsole(Console *newPConsole){
    m_pConsole = newPConsole;
    m_pCDC_drv->setPConsole(newPConsole);
}

VersionManager *CommandManager::Versions() const{
    return m_pVersions;
}

void CommandManager::setVersions(VersionManager *newPVersions){
    m_pVersions = newPVersions;
}

Vehicle *CommandManager::vehicle() const{
    return m_pVehicle;
}

void CommandManager::setVehicle(Vehicle *newPVehicle){
    m_pVehicle = newPVehicle;
}


void CommandManager::console_print(const QString _data){
    if(m_pConsole != nullptr){
        m_pConsole->append_cdc_string(_data);
    }
}

BusManager *CommandManager::pBusManager() const
{
    return m_pBusManager;
}

void CommandManager::setPBusManager(BusManager *newPBusManager)
{
    m_pBusManager = newPBusManager;
 //   if(pCDC_drv()!=nullptr)m_pCDC_drv->setPBusManager(m_pBusManager);
}

CDC_Driver *CommandManager::pCDC_drv() const{
    return m_pCDC_drv;
}

DeviceManager *CommandManager::pDeviceManager() const
{
    return m_pDeviceManager;
}

void CommandManager::setDeviceManager(DeviceManager *newPDeviceManager){
    m_pDeviceManager = newPDeviceManager;
}

MemoryManager *CommandManager::pMemoryManager() const{
    return m_pMemoryManager;
}

void CommandManager::setPMemoryManager(MemoryManager *newPMemoryManager){
    m_pMemoryManager = newPMemoryManager;
}














/***************************************************************************/
/******************************** Private **********************************/
/***************************************************************************/

uint32_t CommandManager::update_procedure_getFileSize(QString path){
    m_pConsole->append_firmware_update("Local file: " + path);
    QFile firmware(path);
    bool open = firmware.open(QFile::ReadOnly);
    if(!open){
        m_pConsole->append_firmware_update("Update failed: error opening the file.");
        firmware.close();
        return 0;
    }
    uint32_t file_size = firmware.size();
    firmware.close();
    return file_size;
}


uint32_t CommandManager::update_procedure_verifyData(QString path, int firmware_address){
    m_pConsole->append_firmware_update("Verifying data...");
    QFile firmware(path);
    bool open = firmware.open(QFile::ReadOnly);
    if(!open) {
        m_pConsole->append_firmware_update("Verification failed: error opening the file.");
        firmware.close();
        return 0;
    }

    //=================================
    //============ Verify =============
    QByteArray verification_data;
    QDataStream stream(&firmware);

    qint64 dataLength = firmware.size();
    verification_data.resize(dataLength);
    int bytesRead = stream.readRawData(verification_data.data(), dataLength);
    firmware.close();
    if(bytesRead != dataLength){
        m_pConsole->append_firmware_update("Verification failed: programmed data length mismatch.");
        return 0;
    }

    else{
#ifdef ANDROID_V
        int max_rx_bytes = 64;
#endif
#ifndef ANDROID_V
       // int max_rx_bytes = m_pCDC_drv->maxRxBytes_per_request();
        int max_rx_bytes = 64;
#endif

        int temp_length = dataLength;
        int addr_counter = firmware_address;

        QByteArray data_for_verification;
        QByteArray buffer;

        while(temp_length >= max_rx_bytes){
            buffer.resize(max_rx_bytes);
            m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, max_rx_bytes);
            exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false);

            temp_length -= max_rx_bytes;
            addr_counter += max_rx_bytes;
            data_for_verification.append(buffer);
            buffer.clear();
        }

        buffer.resize(temp_length);
        m_cmdConstructor.constructCmd(ELP_CMD_SPI_MEMCHIP_READ, addr_counter, temp_length);
        exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &buffer, false);
        data_for_verification.append(buffer);

        qDebug() << "data_for_verification" <<  data_for_verification.size();
        qDebug() << "verification_data" << verification_data.size();

        data_for_verification.resize(dataLength);
        for(size_t i = 0; i < dataLength; i++){
            if(data_for_verification.at(i) != verification_data.at(i)){
                m_pConsole->append_firmware_update("Verification failed: data mismatch. Position: " + QString::number(i));
                return 0;
            }
        }
        return dataLength;
    }
    return dataLength;
}


uint32_t CommandManager::update_procedure_start(QString file_path, int firmware_address, int firmware_sz_address){

    //================ File size ==============================
    uint32_t file_size = update_procedure_getFileSize(file_path);
    if(file_size == 0){
        m_pConsole->append_firmware_update("Failed: the file is empty or not found");
    }
    QString file_size_str = QString::number(file_size);
    m_pConsole->append_firmware_update("File size: " + file_size_str);
    m_pConsole->append_firmware_update("Device: " + m_pVersions->hardware_device_model_name());

    if(file_size > App_settings::MAX_FIRMWARE_SIZE){
        m_pConsole->append_firmware_update("Update failed: the file size exceeds max. supported size.");
        return 0;
    }

    //=======================================================================
    //==== Construct QString from firmware address and size address =========
    //=======================================================================

    QString firmware_address_str = StringConvertor::uint32_t_to_QString_as_HEX(firmware_address);
    QString size_address_str = StringConvertor::uint32_t_to_QString_as_HEX(firmware_sz_address);

    m_pConsole->append_firmware_update("Memchip firmware address: " + firmware_address_str);
    m_pConsole->append_firmware_update("Memchip size address: " + size_address_str);

    //=======================================================================
    //========================= Erase area  =================================
    //=======================================================================
    uint32_t size_to_erase = App_settings::MAX_FIRMWARE_SIZE;
    uint32_t start_address_to_erase = firmware_address;

    m_cmdConstructor.constructCmd(ELP_ERASE_AREA, start_address_to_erase, size_to_erase+4);
    m_pConsole->append_firmware_update("Erasing : " + m_cmdConstructor.cmd_string());

    uint32_t memory_chip_timeout = size_to_erase/8;
    QByteArray response;
    exchange_cmd_string_HEX(m_cmdConstructor.cmd_string(), &response, true, memory_chip_timeout);

    if(CommandConstructor::isResponseOk(QString::fromUtf8(response))){
        m_pConsole->append_firmware_update("Erase OK: " + m_cmdConstructor.cmd_string());
    }
    else{
        m_pConsole->append_firmware_update("Erase failed: " + m_cmdConstructor.cmd_string());
        return 0;
    }

    //=======================================================================
    //=================== Writing firmware and its size  ====================
    //=======================================================================

    QByteArray firmware_size_in_hex;
    firmware_size_in_hex.resize(4);
    int j = 3;
    for(int i=0; i < 4; i++){
        firmware_size_in_hex[i] = (uint8_t)(file_size >> j*8);
        j--;
    }

    bool result;
    m_pConsole->append_firmware_update("Writing firmware...");
    result = writeRawData(firmware_address, file_path, true, true);
    if(result){
        m_pConsole->append_firmware_update("Writing firmware OK.");
    }
    else{
        m_pConsole->append_firmware_update("Writing firmware FAILED.");
        return 0;
    }
    m_pConsole->append_firmware_update("Appending a file size...");

    result = writeRawData(firmware_sz_address, firmware_size_in_hex, true);

    m_pConsole->append_firmware_update(QString::number(firmware_sz_address, 16));
    m_pConsole->append_firmware_update(QString::fromUtf8(firmware_size_in_hex)); /* 4E 50 NP in Android */


    if(result){
        m_pConsole->append_firmware_update("Appending a file size OK.");
    }
    else{
        m_pConsole->append_firmware_update("Appending a file size FAILED.");
        return 0;
    }
    return file_size;
}

void  CommandManager::reset_all_on_disconnect(){
    if(m_pVehicle != nullptr)m_pVehicle->reset();
    if(m_pVersions != nullptr)m_pVersions->resetOnDisconnect();
    if(m_pDeviceManager != nullptr) m_pDeviceManager->reset();
    stop_asynch_read(0);
    stop_asynch_read(1);
    stop_asynch_read(2);
    stop_asynch_read(3);
}

/******************************************************************************************/
/*                               Cdc injection                                            */
/******************************************************************************************/

bool CommandManager::CDC_Injection_data_send_procedure(uint32_t length){
    if(cdc_stop_flag()){
        setCdc_stop_flag(false);
        sendStopCmdCdcInjection();
        return false;
    }

    const uint32_t stop_cmd = 0xFFFFFFFF;
    if(length == stop_cmd){
        stop_asynch_read(CDC_Driver::AsynchReadInjectionMode);
        setCdc_injection_pos(0);
        return false;
    }

    int max_pos = m_pBusManager->CanBusTraceModel()->count() -1;
    int requested_msgs_to_send = length;
    int pos = cdc_injection_pos();

    if(pos >= max_pos){
        if(!cdc_circular()){
            sendStopCmdCdcInjection();
            setCdc_injection_pos(0);
            return true;
        }
    }
    const QByteArray data_to_send = m_pBusManager->CanBusTraceModel()->get_raw_data_for_cdc(&pos, requested_msgs_to_send, cdc_circular());

    int max_tx_bytes = m_pCDC_drv->maxTxBytes_per_request();
    int temp_length = data_to_send.size();
    int bytes_pos = 0;

    while(temp_length >= max_tx_bytes){
        sendRawData(data_to_send.mid(bytes_pos, max_tx_bytes));
        temp_length -= max_tx_bytes;
        bytes_pos += max_tx_bytes;
    }

    if((temp_length != 0) & (temp_length < max_tx_bytes)){
        sendRawData(data_to_send.mid(bytes_pos, temp_length));
    }

    setCdc_injection_pos(pos);
    return true;
}


void CommandManager::sendStopCmdCdcInjection(){
    const QByteArray data_to_send = CanBusItem::makeInvalidByteArray();
    sendRawData(data_to_send);
}



/******************************************************************************************/
/*                               Setters/Getters                                          */
/******************************************************************************************/

int CommandManager::cdc_injection_pos() const{
    return m_cdc_injection_pos;
}

void CommandManager::setCdc_injection_pos(int newCdc_injection_pos){
    if (m_cdc_injection_pos == newCdc_injection_pos)
        return;
    m_cdc_injection_pos = newCdc_injection_pos;
    emit cdc_injection_posChanged();
}

void CommandManager::resetCdc_injection_pos(){
    setCdc_injection_pos(0);
}


bool CommandManager::cdc_circular() const{
    return m_cdc_circular;
}

void CommandManager::setCdc_circular(bool newCdc_circular){
    if (m_cdc_circular == newCdc_circular)
        return;
    m_cdc_circular = newCdc_circular;
    emit cdc_circularChanged();
}

void CommandManager::resetCdc_circular(){
    setCdc_circular(false);
}

bool CommandManager::cdc_stop_flag() const{
    return m_cdc_stop_flag;
}

void CommandManager::setCdc_stop_flag(bool newCdc_stop_flag){
    m_cdc_stop_flag = newCdc_stop_flag;
    emit cdc_stop_timeoutChanged();
}

bool CommandManager::cdc_pending_flag() const{
    return m_cdc_pending_flag;
}
void CommandManager::setCdc_pending_flag(bool newCdc_pending_flag){
    m_cdc_pending_flag = newCdc_pending_flag;
    emit cdc_pendingChanged();
}
