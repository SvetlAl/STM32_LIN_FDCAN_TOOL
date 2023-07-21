#include "DeviceManager.h"

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

/************************************************************************
 *
 *
 *                               Override status
 *
 *
 * **********************************************************************/
const QByteArray DeviceManager::getOvrFilterData() const{
    return m_OverrideStatus.getRawData();
}




/************************************************************************
 *
 *
 *                               Discard model
 *
 *
 * **********************************************************************/

void DeviceManager::fill_OvrSts_from_DscModel(){
    m_DiscardIdModel.fill_OverrideStatus(&m_OverrideStatus);
}
void DeviceManager::update_DscModel_from_OvrSts(){
    m_DiscardIdModel.update_model_from_OverrideStatus(&m_OverrideStatus);
}



/************************************************************************
 *
 *
 *                          Override filter model
 *
 *
 * **********************************************************************/

void DeviceManager::fill_OvrSts_from_OvrModel(){
    m_OverrideFilterModel.fill_OverrideStatus(&m_OverrideStatus);
}
void DeviceManager::update_OvrModel_from_OvrSts(){
    m_OverrideFilterModel.update_model_from_OverrideStatus(&m_OverrideStatus);
}


