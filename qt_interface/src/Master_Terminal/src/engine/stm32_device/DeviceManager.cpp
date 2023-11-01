#include "DeviceManager.h"
#include "../../app_settings.h"

#define LIN_STATUS_OFF                    (uint8_t)0x00
#define LIN_STATUS_ON                     (uint8_t)0x0F

#define IS_VALIDATION_MODE  (targetDeviceData.deviceModel.lin_mode &   (uint8_t)(LIN_STATUS_ON << 4))
#define LIN_VALIDATION_ON   targetDeviceData.deviceModel.lin_mode |=  (uint8_t)(LIN_STATUS_ON << 4);
#define LIN_VALIDATION_OFF  targetDeviceData.deviceModel.lin_mode &=~ (uint8_t)(LIN_STATUS_ON << 4);

/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/
void DeviceManager::reset(){
    for(size_t i = 0; i < sizeof(DeviceModel) ; i++){
        targetDeviceData.data[i] = 0xFF;
    }
}
void DeviceManager::init(const QByteArray &_init_data){
    // this is needed if new firmware modes were added, but still not supported by interface
    const uint32_t actual_init_length = _init_data.length();
    const QByteArray temp_init_data = _init_data.mid(0, actual_init_length);

    for(size_t i = 0; i < actual_init_length; i++){
        targetDeviceData.data[i] = temp_init_data.at(i);
    }

    emit changed();
    emit memchip_changed();
}

// Discard model
void DeviceManager::fill_OvrSts_from_DscModel(){
    m_DiscardIdModel.fill_OverrideStatus(&m_OverrideStatus);
}
void DeviceManager::update_DscModel_from_OvrSts(){
    m_DiscardIdModel.update_model_from_OverrideStatus(&m_OverrideStatus);
}



// Override filter model
void DeviceManager::fill_OvrSts_from_OvrModel(){
    m_OverrideFilterModel.fill_OverrideStatus(&m_OverrideStatus);
}
void DeviceManager::update_OvrModel_from_OvrSts(){
    m_OverrideFilterModel.update_model_from_OverrideStatus(&m_OverrideStatus);
}


/********************************************************************
 *
 *
 *                     Class setters/getters
 *
 *
********************************************************************/
const int DeviceManager::memchip_code() const{
    return targetDeviceData.deviceModel.memChipModel;
}

int DeviceManager::get_harware_scanner_filter_value(const int byte_n, bool isLowerBound){
    if(byte_n > 3) return 0;
    const int struct_pos = isLowerBound ? 23 : 27;
    int device_data_pos = struct_pos + byte_n;
    return targetDeviceData.data[device_data_pos];
}

bool DeviceManager::lin_validation() const{
    if(IS_VALIDATION_MODE){
        return true;
    }
    else return false;
}

bool DeviceManager::lin_mode_gateway() const{
    if(targetDeviceData.deviceModel.lin_mode & LIN_MODE_GATEWAY){
        return true;
    }
    else return false;
}

bool DeviceManager::lin_mode_filter() const{
    if(targetDeviceData.deviceModel.lin_mode & LIN_MODE_FILTER){
        return true;
    }
    else return false;
}

bool DeviceManager::lin_mode_scanner() const{
    if(targetDeviceData.deviceModel.lin_mode & LIN_MODE_SCANNER){
        return true;
    }
    else return false;
}

bool DeviceManager::lin_mode_device() const{
    if(targetDeviceData.deviceModel.lin_mode & LIN_MODE_DEVICE){
        return true;
    }
    else return false;
}

int DeviceManager::lin_poll_period() const{
    return m_lin_poll_period;
}

void DeviceManager::set_lin_poll_period(int new_value){
    if(m_lin_poll_period == new_value) return;
    m_lin_poll_period = new_value;
    emit lin_pp_changed();
}


void DeviceManager::update_lin_filter(bool dir_mosi, QByteArray _data){
    uint8_t *lin_ptr = (dir_mosi) ? mosi_filter.data : miso_filter.data;
    uint8_t pos = 0;
    while(pos < sizeof(lin_filter_raw)){
        *lin_ptr++ = _data[pos++];
    }
    refresh_lin_filter(dir_mosi);
}
void DeviceManager::refresh_lin_filter(bool dir_mosi){
    uint8_t *lin_ptr = (dir_mosi) ? mosi_filter.data : miso_filter.data;
    uint8_t model_item_num = (dir_mosi) ? 0 : 1;
    uint8_t model_byte_pos = 0;
    uint8_t filter_byte_pos = 4;

    m_OverrideLINFilterModel.set_byte0_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte1_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte2_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte3_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte4_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte5_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte6_value(model_item_num, QString::number(lin_ptr[filter_byte_pos++], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos++));
    m_OverrideLINFilterModel.set_byte7_value(model_item_num, QString::number(lin_ptr[filter_byte_pos], 16).toUpper());
    m_OverrideLINFilterModel.enable_byte0(model_item_num, (lin_ptr[1] >> model_byte_pos));
    m_OverrideLINFilterModel.set_str_id_value(model_item_num, QString::number(lin_ptr[0], 16).toUpper());
}

lin_filter_raw *DeviceManager::get_refreshed_filter_ptr(bool dir_mosi){
    uint8_t model_item_num = (dir_mosi) ? 0 : 1;
    lin_filter_raw *filter_ptr = (dir_mosi) ? &mosi_filter : &miso_filter;
    m_OverrideLINFilterModel.set_lin_filter_values(model_item_num, filter_ptr);
    return filter_ptr;
}

void DeviceManager::set_lin_validation(bool new_value){
    if(lin_validation() == new_value) return;
    if(new_value == false){
        LIN_VALIDATION_OFF;
    }
    else{
        LIN_VALIDATION_ON;
    }
    emit changed();
}

int DeviceManager::lin_mode() const{
    uint8_t mode = targetDeviceData.deviceModel.lin_mode;
    mode &= ~0xF0;
    return mode;
}


void DeviceManager::set_lin_mode(int new_value){
    uint8_t new_mode = new_value &~0xF0;
    if(new_mode == (targetDeviceData.deviceModel.lin_mode &~ 0xF0)) return;
    targetDeviceData.deviceModel.lin_mode &=~ 0x0F;
    targetDeviceData.deviceModel.lin_mode |= new_mode;
    emit changed();
}



QString DeviceManager::str_scanner_hardware_filter_lwr() const{
    QString result;
    result.reserve(8);
    result.append(QString::number(targetDeviceData.deviceModel.lower_hw_filter_b3, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.lower_hw_filter_b2, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.lower_hw_filter_b1, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.lower_hw_filter_b0, 16).rightJustified(2, '0'));
    return result;
}
QString DeviceManager::str_scanner_hardware_filter_hgr() const{
    QString result;
    result.reserve(8);
    result.append(QString::number(targetDeviceData.deviceModel.higher_hw_filter_b3, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.higher_hw_filter_b2, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.higher_hw_filter_b1, 16).rightJustified(2, '0'));
    result.append(QString::number(targetDeviceData.deviceModel.higher_hw_filter_b0, 16).rightJustified(2, '0'));
    return result;
}

void DeviceManager::set_str_scanner_hardware_filter_lwr(const QString new_value){
    QString temp_value = new_value;

    // Remove "0x" from the beginning if present
    if (temp_value.startsWith("0x")) {
        temp_value = temp_value.mid(2);
    }
    bool ok;
    uint32_t value = temp_value.toUInt(&ok, 16);
    if (ok) {
        targetDeviceData.deviceModel.lower_hw_filter_b3 = (value >> 24) & 0xFF;
        targetDeviceData.deviceModel.lower_hw_filter_b2 = (value >> 16) & 0xFF;
        targetDeviceData.deviceModel.lower_hw_filter_b1 = (value >> 8) & 0xFF;
        targetDeviceData.deviceModel.lower_hw_filter_b0 = value & 0xFF;
        emit changed();
    }

}

void DeviceManager::set_str_scanner_hardware_filter_hgr(const QString new_value){
    QString temp_value = new_value;
    // Remove "0x" from the beginning if present
    if (temp_value.startsWith("0x")) {
        temp_value = temp_value.mid(2);
    }
    bool ok;
    uint32_t value = temp_value.toUInt(&ok, 16);
    if (ok) {
        targetDeviceData.deviceModel.higher_hw_filter_b3 = (value >> 24) & 0xFF;
        targetDeviceData.deviceModel.higher_hw_filter_b2 = (value >> 16) & 0xFF;
        targetDeviceData.deviceModel.higher_hw_filter_b1 = (value >> 8) & 0xFF;
        targetDeviceData.deviceModel.higher_hw_filter_b0 = value & 0xFF;
    }
    emit changed();
}


void DeviceManager::set_scanner_hardware_filter(int value){
    targetDeviceData.deviceModel.scanner_hardware_filter = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::set_cdc_injection_threshold_mode(int value){
    targetDeviceData.deviceModel.canInjection_CDC_threshold_mode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}
void DeviceManager::set_cdc_injection_threshold_value(int value){
    targetDeviceData.deviceModel.canInjection_CDC_threshold_value = value;
    emit changed();
}

void DeviceManager::setCanInjection_Mode(int value){
    targetDeviceData.deviceModel.canInjectionMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCanInjection_Mode_CDC(int value){
    targetDeviceData.deviceModel.canInjectionMode_CDC = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCanGateway_Mode(int value){
    if ((targetDeviceData.deviceModel.canGatewayMode == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.canGatewayMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCalibratorFilter_Mode(int value){
    if ((targetDeviceData.deviceModel.calibratorFilterMode == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.calibratorFilterMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCanOverride_Mode(int value){
    if ((targetDeviceData.deviceModel.canOverrideMode == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.canOverrideMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCanScanner_Mode(int value){
    if ((targetDeviceData.deviceModel.canScannerMode == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.canScannerMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCan2Scanner_Mode(int value){
    if ((targetDeviceData.deviceModel.can2ScannerMode == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.can2ScannerMode = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCustomBTR_Mode(int value){
    if ((targetDeviceData.deviceModel.customBTR == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.customBTR = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}
//===========
void DeviceManager::setVal_BTR_PSC(int value){
    targetDeviceData.deviceModel.val_BTR_PSC = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_BS1(int value){
    targetDeviceData.deviceModel.val_BTR_BS1 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_BS2(int value){
    targetDeviceData.deviceModel.val_BTR_BS2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_SJW(int value){
    targetDeviceData.deviceModel.val_BTR_SJW = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setCustomBTR_Mode_2(int value){
    if ((targetDeviceData.deviceModel.customBTR_2 == value) | (value > DEVICE_OPERATION_MODE_OFF) | (value < DEVICE_OPERATION_MODE_ON))
        return;
    targetDeviceData.deviceModel.customBTR_2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}
//===========
void DeviceManager::setVal_BTR_PSC_2(int value){
    targetDeviceData.deviceModel.val_BTR_PSC_2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_BS1_2(int value){
    targetDeviceData.deviceModel.val_BTR_BS1_2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_BS2_2(int value){
    targetDeviceData.deviceModel.val_BTR_BS2_2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

void DeviceManager::setVal_BTR_SJW_2(int value){
    targetDeviceData.deviceModel.val_BTR_SJW_2 = static_cast<eDeviceFunctionMode>(value);
    emit changed();
}

const QString DeviceManager::memchip_name() const{
    switch(targetDeviceData.deviceModel.memChipModel){
    case MEMCHIP_MODEL_MX25L323:
        return "MX25L323";
        break;
    case MEMCHIP_MODEL_M45PE16:
        return "M45PE16";
        break;
    case MEMCHIP_MODEL_MX25L16:
        return "MX25L16";
        break;
    case MEMCHIP_MODEL_DEFAULT:
    default:
        return "no memchip info";
    }
}

//Override status
const QByteArray DeviceManager::getOvrFilterData() const{
    return m_OverrideStatus.getRawData();
}



