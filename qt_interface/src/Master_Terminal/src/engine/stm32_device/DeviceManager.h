#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

/***********************************************************************
 *
 *
 * DeviceManager is a class designed to handle all supported device modes
 *
 * Based on the structures imported form the firmware C code
 *
 *
 ************************************************************************/

#include <QObject>
#include <QDebug>
#include "OverrideStatus.h"
#include "Lin_filter.h"
#include "QML_Model/QDiscardId_ModelProperty.h"
#include "QML_Model/QOverrideFilter_ModelProperty.h"
#include "QML_Model/QLinConfigProperty_BaudRate.h"
#include "QML_Model/QLinConfigProperty_FilterPreset.h"
#include "QML_Model/QLinOverrideFilter_ModelProperty.h"

//======================= Exported from 'C' ============================
typedef enum  : uint8_t {
    DEVICE_OPERATION_MODE_DEFAULT = (uint8_t)0xFF,
    DEVICE_OPERATION_MODE_ON = (uint8_t)0x01,
    DEVICE_OPERATION_MODE_OFF = (uint8_t)0x02,
    DEVICE_OPERATION_MODE_REV = (uint8_t)0x03,   // Reverse CAN1 and CAN2
    DEVICE_OPERATION_MODE_CIRCULAR_REV = (uint8_t)0x04,
    DEVICE_OPERATION_MODE_CIRCULAR = (uint8_t)0x05,
    DEVICE_OPERATION_MODE_FILTR_UPD = (uint8_t)0x06,
    DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD = (uint8_t)0x07,
    DEVICE_OPERATION_MODE_CDC_TRACE_FIXED_THRESHOLD = (uint8_t)0x08} eDeviceFunctionMode;

    /* this is needed for interface application for a correct command set */
typedef enum  : uint8_t{
    MEMCHIP_MODEL_DEFAULT = (uint8_t)0xFF,
    MEMCHIP_MODEL_MX25L323 = (uint8_t)0x01,
    MEMCHIP_MODEL_M45PE16 = (uint8_t)0x02,
    MEMCHIP_MODEL_MX25L16 = (uint8_t)0x03 } eMemChipModel;


typedef struct DeviceModel{
    eMemChipModel memChipModel;
    eDeviceFunctionMode canGatewayMode;
    eDeviceFunctionMode can2GatewayMode; // OBSOLETE
    eDeviceFunctionMode calibratorFilterMode;
    eDeviceFunctionMode canOverrideMode;
    eDeviceFunctionMode canScannerMode;
    eDeviceFunctionMode can2ScannerMode;
    eDeviceFunctionMode memoryProgramingMode;
    eDeviceFunctionMode canInjectionMode;
    uint8_t val_BTR_PSC;
    uint8_t val_BTR_BS1;
    uint8_t val_BTR_BS2;
    uint8_t val_BTR_SJW;
    eDeviceFunctionMode customBTR;
    uint8_t val_BTR_PSC_2;
    uint8_t val_BTR_BS1_2;
    uint8_t val_BTR_BS2_2;
    uint8_t val_BTR_SJW_2;
    eDeviceFunctionMode customBTR_2;
    eDeviceFunctionMode canInjectionMode_CDC;
    eDeviceFunctionMode canInjection_CDC_threshold_mode;
    uint8_t canInjection_CDC_threshold_value;
    eDeviceFunctionMode scanner_hardware_filter;
    uint8_t lower_hw_filter_b0;
    uint8_t lower_hw_filter_b1;
    uint8_t lower_hw_filter_b2;
    uint8_t lower_hw_filter_b3;
    uint8_t higher_hw_filter_b0;
    uint8_t higher_hw_filter_b1;
    uint8_t higher_hw_filter_b2;
    uint8_t higher_hw_filter_b3;

    uint8_t lin_baudrate_preset;
    uint8_t lin_mode;
    uint8_t lin_filter;
} DeviceModel; //creating new type

enum DeviceModelProperties{
    Enm_memChipModel = 0,
    Enm_canGatewayMode = 1,
    Enm_can2GatewayMode = 2, // OBSOLETE
    Enm_calibratorFilterMode = 3,
    Enm_canOverrideMode = 4,
    Enm_canScannerMode = 5,
    Enm_can2ScannerMode = 6,
    Enm_memoryProgramingMode = 7,
    Enm_canInjectionMode = 8, // not tested properly
    Enm_val_BTR_PSC = 9,
    Enm_val_BTR_BS1 = 10,
    Enm_val_BTR_BS2 = 11,
    Enm_val_BTR_SJW = 12,
    Enm_customBTR = 13,
    Enm_val_BTR_PSC_2 = 14,
    Enm_val_BTR_BS1_2 = 15,
    Enm_val_BTR_BS2_2 = 16,
    Enm_val_BTR_SJW_2 = 17,
    Enm_customBTR_2 = 18,
    Enm_canInjectionMode_CDC = 19,
    Enm_canInjection_CDC_threshold_mode = 20,
    Enm_canInjection_CDC_threshold_value = 21,
    Enm_scanner_hardware_filter = 22,
    Enm_lower_hw_filter_b0 = 23,
    Enm_lower_hw_filter_b1 = 24,
    Enm_lower_hw_filter_b2 = 25,
    Enm_lower_hw_filter_b3 = 26,
    Enm_higher_hw_filter_b0 = 27,
    Enm_higher_hw_filter_b1 = 28,
    Enm_higher_hw_filter_b2 = 29,
    Enm_higher_hw_filter_b3 = 30,
    Enm_lin_baudrate_preset = 31,
    Enm_lin_mode = 32,
    Enm_lin_filter = 33
};

typedef union uDeviceModel{
    DeviceModel deviceModel;
    uint8_t data[sizeof(DeviceModel)];
}uDeviceModel;




class DeviceManager : public QObject{
    Q_OBJECT
    Q_PROPERTY(int canGateway_Mode READ canGateway_Mode WRITE setCanGateway_Mode NOTIFY changed)
    Q_PROPERTY(int calibratorFilter_Mode READ calibratorFilter_Mode WRITE setCalibratorFilter_Mode NOTIFY changed)
    Q_PROPERTY(int canOverride_Mode READ canOverride_Mode WRITE setCanOverride_Mode NOTIFY changed)
    Q_PROPERTY(int canScanner_Mode READ canScanner_Mode WRITE setCanScanner_Mode NOTIFY changed)
    Q_PROPERTY(int can2Scanner_Mode READ can2Scanner_Mode WRITE setCan2Scanner_Mode NOTIFY changed)
    Q_PROPERTY(int memoryPrograming_Mode READ memoryPrograming_Mode NOTIFY changed)
    Q_PROPERTY(int canInjection_Mode READ canInjection_Mode NOTIFY changed)
    Q_PROPERTY(int customBTR_Mode READ customBTR_Mode WRITE setCustomBTR_Mode NOTIFY changed)
    Q_PROPERTY(int val_BTR_PSC READ val_BTR_PSC WRITE setVal_BTR_PSC NOTIFY changed)
    Q_PROPERTY(int val_BTR_BS1 READ val_BTR_BS1 WRITE setVal_BTR_BS1 NOTIFY changed)
    Q_PROPERTY(int val_BTR_BS2 READ val_BTR_BS2 WRITE setVal_BTR_BS2 NOTIFY changed)
    Q_PROPERTY(int val_BTR_SJW READ val_BTR_SJW WRITE setVal_BTR_SJW NOTIFY changed)
    Q_PROPERTY(int customBTR_Mode_2 READ customBTR_Mode_2 WRITE setCustomBTR_Mode_2 NOTIFY changed)
    Q_PROPERTY(int val_BTR_PSC_2 READ val_BTR_PSC_2 WRITE setVal_BTR_PSC_2 NOTIFY changed)
    Q_PROPERTY(int val_BTR_BS1_2 READ val_BTR_BS1_2 WRITE setVal_BTR_BS1_2 NOTIFY changed)
    Q_PROPERTY(int val_BTR_BS2_2 READ val_BTR_BS2_2 WRITE setVal_BTR_BS2_2 NOTIFY changed)
    Q_PROPERTY(int val_BTR_SJW_2 READ val_BTR_SJW_2 WRITE setVal_BTR_SJW_2 NOTIFY changed)
    Q_PROPERTY(int canInjection_Mode_CDC READ canInjection_Mode_CDC NOTIFY changed)
    Q_PROPERTY(QString memchip_name READ memchip_name NOTIFY memchip_changed)
    Q_PROPERTY(int cdc_injection_threshold_mode READ cdc_injection_threshold_mode WRITE set_cdc_injection_threshold_mode NOTIFY changed)
    Q_PROPERTY(int cdc_injection_threshold_value READ cdc_injection_threshold_value WRITE set_cdc_injection_threshold_value NOTIFY changed)
    Q_PROPERTY(int scanner_hardware_filter READ scanner_hardware_filter WRITE set_scanner_hardware_filter NOTIFY changed)
    Q_PROPERTY(QString str_scanner_hardware_filter_lwr READ str_scanner_hardware_filter_lwr WRITE set_str_scanner_hardware_filter_lwr NOTIFY changed)
    Q_PROPERTY(QString str_scanner_hardware_filter_hgr READ str_scanner_hardware_filter_hgr WRITE set_str_scanner_hardware_filter_hgr NOTIFY changed)

    // LIN
    Q_PROPERTY(bool lin_validation READ lin_validation WRITE set_lin_validation NOTIFY changed)
    Q_PROPERTY(int lin_mode READ lin_mode WRITE set_lin_mode NOTIFY changed)
    Q_PROPERTY(bool lin_mode_gateway READ lin_mode_gateway NOTIFY changed)
    Q_PROPERTY(bool lin_mode_filter  READ lin_mode_filter  NOTIFY changed)
    Q_PROPERTY(bool lin_mode_scanner READ lin_mode_scanner NOTIFY changed)
    Q_PROPERTY(bool lin_mode_device  READ lin_mode_device  NOTIFY changed)

    Q_PROPERTY(int lin_poll_period READ lin_poll_period WRITE set_lin_poll_period NOTIFY lin_pp_changed)

    Q_PROPERTY(QLinConfigProperty_BaudRate* lin_baudrate READ lin_baudrate CONSTANT )
    Q_PROPERTY(QLinConfigProperty_FilterPreset* lin_filter_preset READ lin_filter_preset CONSTANT )



    /******************************************************************************************/
    /*                              CAN override configuration                                */
    /******************************************************************************************/
    //=========== Discard Id model ===========
    Q_PROPERTY(QDiscardId_ModelProperty* DiscardIdModel READ DiscardIdModel CONSTANT)

    //=========== Override Filters ===========
    Q_PROPERTY(QOverrideFilter_ModelProperty* OverrideFilterModel READ OverrideFilterModel CONSTANT)

    /******************************************************************************************/
    /*                              LIN override configuration                                */
    /******************************************************************************************/

    //=========== Override Filters ===========
    Q_PROPERTY(QLinOverrideFilter_ModelProperty* OverrideLINFilterModel READ OverrideLINFilterModel CONSTANT)



public:
    explicit DeviceManager(QObject *parent = 0) : QObject(parent){
        reset();
        connect(this, &DeviceManager::changed, this, &DeviceManager::refreshLIN);
    }
    ~DeviceManager() {};
    constexpr static const int data_struct_size = sizeof(DeviceModel);

    //===================================== init ======================================
    void reset();
    void init(const QByteArray &_init_data);
    // Discard model
    Q_INVOKABLE void fill_OvrSts_from_DscModel();
    Q_INVOKABLE void update_DscModel_from_OvrSts();
    // Override filter model
    Q_INVOKABLE void fill_OvrSts_from_OvrModel();
    Q_INVOKABLE void update_OvrModel_from_OvrSts();

    //============================== Class setters/getters=============================
    int memoryPrograming_Mode() const { return targetDeviceData.deviceModel.memoryProgramingMode; }
    int canGateway_Mode() const { return targetDeviceData.deviceModel.canGatewayMode; }
    int calibratorFilter_Mode() const { return targetDeviceData.deviceModel.calibratorFilterMode; }
    int canOverride_Mode() const { return targetDeviceData.deviceModel.canOverrideMode; }
    int canScanner_Mode() const { return targetDeviceData.deviceModel.canScannerMode; }
    int can2Scanner_Mode() const { return targetDeviceData.deviceModel.can2ScannerMode; }
    int canInjection_Mode() const { return targetDeviceData.deviceModel.canInjectionMode; }
    int customBTR_Mode() const { return targetDeviceData.deviceModel.customBTR; }
    int val_BTR_PSC() const { return targetDeviceData.deviceModel.val_BTR_PSC; }
    int val_BTR_BS1() const { return targetDeviceData.deviceModel.val_BTR_BS1; }
    int val_BTR_BS2() const { return targetDeviceData.deviceModel.val_BTR_BS2; }
    int val_BTR_SJW() const { return targetDeviceData.deviceModel.val_BTR_SJW; }
    int customBTR_Mode_2() const { return targetDeviceData.deviceModel.customBTR_2; }
    int val_BTR_PSC_2() const { return targetDeviceData.deviceModel.val_BTR_PSC_2; }
    int val_BTR_BS1_2() const { return targetDeviceData.deviceModel.val_BTR_BS1_2; }
    int val_BTR_BS2_2() const { return targetDeviceData.deviceModel.val_BTR_BS2_2; }
    int val_BTR_SJW_2() const { return targetDeviceData.deviceModel.val_BTR_SJW_2; }
    int canInjection_Mode_CDC() const { return targetDeviceData.deviceModel.canInjectionMode_CDC; }
    int cdc_injection_threshold_mode() const { return targetDeviceData.deviceModel.canInjection_CDC_threshold_mode; }
    int cdc_injection_threshold_value() const { return targetDeviceData.deviceModel.canInjection_CDC_threshold_value; }
    int scanner_hardware_filter() const { return targetDeviceData.deviceModel.scanner_hardware_filter; }
    QString str_scanner_hardware_filter_lwr() const;
    QString str_scanner_hardware_filter_hgr() const;
    bool lin_validation() const;
    int lin_mode() const;
    bool lin_mode_gateway() const;
    bool lin_mode_filter() const;
    bool lin_mode_scanner() const;
    bool lin_mode_device() const;
    int lin_poll_period() const;




    Q_INVOKABLE int get_harware_scanner_filter_value(const int byte_n, bool isLowerBound);

    void setCanInjection_Mode(int value);
    void setCanGateway_Mode(int value);
    void setCalibratorFilter_Mode(int value);
    void setCanOverride_Mode(int value);
    void setCanScanner_Mode(int value);
    void setCan2Scanner_Mode(int value);
    void setCustomBTR_Mode(int value);
    void setVal_BTR_PSC(int value);
    void setVal_BTR_BS1(int value);
    void setVal_BTR_BS2(int value);
    void setVal_BTR_SJW(int value);
    void setCustomBTR_Mode_2(int value);
    void setVal_BTR_PSC_2(int value);
    void setVal_BTR_BS1_2(int value);
    void setVal_BTR_BS2_2(int value);
    void setVal_BTR_SJW_2(int value);
    void setCanInjection_Mode_CDC(int value);
    void set_cdc_injection_threshold_mode(int value);
    void set_cdc_injection_threshold_value(int value);
    void set_scanner_hardware_filter(int value);
    void set_str_scanner_hardware_filter_lwr(const QString new_value);
    void set_str_scanner_hardware_filter_hgr(const QString new_value);
    void set_lin_validation(bool new_value);
    void set_lin_mode(int new_value);
    void set_lin_poll_period(int new_value);




    const int memchip_code() const;
    const QString memchip_name() const;
    const int memchip() const{ return targetDeviceData.deviceModel.memChipModel;}

    // Override status
    const QByteArray getOvrFilterData() const;

    // Discard model
    QDiscardId_ModelProperty *DiscardIdModel(){return &m_DiscardIdModel;}

    // Override filter model
    QOverrideFilter_ModelProperty *OverrideFilterModel(){return &m_OverrideFilterModel;}

    // Override LIN filter model
    QLinOverrideFilter_ModelProperty *OverrideLINFilterModel(){return &m_OverrideLINFilterModel;}

    QLinConfigProperty_BaudRate *lin_baudrate(){return &m_lin_baudrate;};
    QLinConfigProperty_FilterPreset *lin_filter_preset(){return &m_lin_filter_preset;};

    // Lin misc
    void update_lin_filter(bool dir_mosi, QByteArray _data);
    lin_filter_raw *get_refreshed_filter_ptr(bool dir_mosi);



signals:
    void changed();
    void memchip_changed();
    void lin_pp_changed();

public slots:
    void refreshOverrideStatus(const QByteArray& data){
        m_OverrideStatus.init_OverrideStatuswithRawData(data);
    }

    void refreshActiveFilters(const QByteArray& data){
        m_OverrideStatus.setActiveFilters(data);
    }
    void refreshLIN(){
        uint8_t cur_filter_preset = targetDeviceData.deviceModel.lin_filter;
        uint8_t cur_baudrate_preset = targetDeviceData.deviceModel.lin_baudrate_preset;
        m_lin_filter_preset.setCurrentIndex(cur_filter_preset);
        m_lin_baudrate.setCurrentIndex(cur_baudrate_preset);
    }

protected:
    QLinConfigProperty_BaudRate m_lin_baudrate;
    QLinConfigProperty_FilterPreset m_lin_filter_preset;

private:
    void refresh_lin_filter(bool dir_mosi);

    uDeviceModel targetDeviceData;
    OverrideStatus m_OverrideStatus;

    QDiscardId_ModelProperty m_DiscardIdModel;
    QOverrideFilter_ModelProperty m_OverrideFilterModel;

    QLinOverrideFilter_ModelProperty m_OverrideLINFilterModel;

    lin_filter_raw mosi_filter;
    lin_filter_raw miso_filter;

    int m_lin_poll_period = 0;
};




#endif // DEVICEMANAGER_H
