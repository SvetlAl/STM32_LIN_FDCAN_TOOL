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
#include "QML_Model/QFDCAN_OverrideFilter_ModelProperty.h"
#include "QML_Model/QLinConfigProperty_BaudRate.h"
#include "QML_Model/QLinConfigProperty_FilterPreset.h"
#include "QML_Model/QLinOverrideFilter_ModelProperty.h"
#include "FD_CAN_settings.h"

//======================= Exported from 'C' ============================
typedef enum: uint8_t {
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
typedef enum: uint8_t{
  MEMCHIP_MODEL_DEFAULT = (uint8_t)0xFF,
  MEMCHIP_MODEL_MX25L323 = (uint8_t)0x01,
  MEMCHIP_MODEL_M45PE16 = (uint8_t)0x02,
  MEMCHIP_MODEL_MX25L16 = (uint8_t)0x03,
  MEMCHIP_MODEL_MX35LF1GE4A = (uint8_t)0x04,
  MEMCHIP_MODEL_W25Q16 = (uint8_t)0x05
} eMemChipModel;


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
    uint8_t can_periph_freq;

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
    Enm_lin_filter = 33,
    Enm_can_periph_freq = 34
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


    // FD CAN
    Q_PROPERTY(int val_FDCAN_freq READ val_FDCAN_freq WRITE setVal_FDCAN_freq NOTIFY changed)


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

    /******************************************************************************************/
    /*                            FDCAN override configuration                                */
    /******************************************************************************************/
    //=========== Override Filters ===========
    Q_PROPERTY(QFDCAN_OverrideFilter_ModelProperty* FdcanOverrideFilterModel READ FdcanOverrideFilterModel CONSTANT)




public:
    explicit DeviceManager(QObject *parent = 0) : QObject(parent){
        reset();
        connect(this, &DeviceManager::changed, this, &DeviceManager::refreshLIN);
    }
    ~DeviceManager() {};
    constexpr static const int data_struct_size = sizeof(DeviceModel);
    constexpr static const int nand_write_timeout = 50;

    //===================================== init ======================================
    void reset();
    void init(const QByteArray &_init_data);
    // Discard model
    Q_INVOKABLE void fill_OvrSts_from_DscModel();
    Q_INVOKABLE void update_DscModel_from_OvrSts();
    // Override filter model
    Q_INVOKABLE void fill_OvrSts_from_OvrModel();
    Q_INVOKABLE void update_OvrModel_from_OvrSts();
    //===================================== FD CAN ====================================
    Q_INVOKABLE void fdcan_fill_OvrSts_from_OvrModel();
    Q_INVOKABLE void fdcan_update_OvrModel_from_OvrSts();
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
    int val_FDCAN_freq() const { return targetDeviceData.deviceModel.can_periph_freq; }





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
    void setVal_FDCAN_freq(int new_value);




    const int memchip_code() const;
    const QString memchip_name() const;
    const int memchip() const{ return targetDeviceData.deviceModel.memChipModel;}
    bool isMemchipNand()const;

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

    // FDCAN Override filter model
    QFDCAN_OverrideFilter_ModelProperty *FdcanOverrideFilterModel(){return &m_FdcanOverrideFilterModel;}
    const QByteArray getFdcanOvrFilterData() const;


signals:
    void changed();
    void memchip_changed();
    void lin_pp_changed();
    void canfd_settings_changed();

public slots:
    void refreshOverrideStatus(const QByteArray& data){
        m_OverrideStatus.init_OverrideStatuswithRawData(data);
    }

    void refreshFdcanOverrideStatus(const QByteArray& data){
        m_FdcanOverrideStatus.init_OverrideStatuswithRawData(data);
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

    // FD CAN
    QFDCAN_OverrideFilter_ModelProperty m_FdcanOverrideFilterModel;
    FDCAN_OverrideStatus m_FdcanOverrideStatus;





    //===============================================================================================================
    //===============================================================================================================
    //============================================== CAN FD =========================================================
    //===============================================================================================================
    //===============================================================================================================

    FD_CAN_settings m_CANFD_settings;
    //============================================== CAN 1  =========================================================
    Q_PROPERTY(int canfd1_nbtr_psc   READ canfd1_nbtr_psc   WRITE set_canfd1_nbtr_psc   NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_nbtr_tseg1 READ canfd1_nbtr_tseg1 WRITE set_canfd1_nbtr_tseg1 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_nbtr_tseg2 READ canfd1_nbtr_tseg2 WRITE set_canfd1_nbtr_tseg2 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_nbtr_sjw   READ canfd1_nbtr_sjw   WRITE set_canfd1_nbtr_sjw   NOTIFY canfd_settings_changed)

    Q_PROPERTY(int canfd1_dbtr_psc   READ canfd1_dbtr_psc   WRITE set_canfd1_dbtr_psc   NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_dbtr_tseg1 READ canfd1_dbtr_tseg1 WRITE set_canfd1_dbtr_tseg1 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_dbtr_tseg2 READ canfd1_dbtr_tseg2 WRITE set_canfd1_dbtr_tseg2 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd1_dbtr_sjw   READ canfd1_dbtr_sjw   WRITE set_canfd1_dbtr_sjw   NOTIFY canfd_settings_changed)


    Q_PROPERTY(bool canfd1_ASM       READ canfd1_ASM        WRITE set_canfd1_ASM        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_DAR       READ canfd1_DAR        WRITE set_canfd1_DAR        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_FDOE      READ canfd1_FDOE       WRITE set_canfd1_FDOE       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_BRSE      READ canfd1_BRSE       WRITE set_canfd1_BRSE       NOTIFY canfd_settings_changed)

    Q_PROPERTY(bool canfd1_PXHD      READ canfd1_PXHD       WRITE set_canfd1_PXHD       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_EFBI      READ canfd1_EFBI       WRITE set_canfd1_EFBI       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_TXP       READ canfd1_TXP        WRITE set_canfd1_TXP        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd1_NISO      READ canfd1_NISO       WRITE set_canfd1_NISO       NOTIFY canfd_settings_changed)


    //============================================== CAN 2  =========================================================
    Q_PROPERTY(int canfd2_nbtr_psc   READ canfd2_nbtr_psc   WRITE set_canfd2_nbtr_psc   NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_nbtr_tseg1 READ canfd2_nbtr_tseg1 WRITE set_canfd2_nbtr_tseg1 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_nbtr_tseg2 READ canfd2_nbtr_tseg2 WRITE set_canfd2_nbtr_tseg2 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_nbtr_sjw   READ canfd2_nbtr_sjw   WRITE set_canfd2_nbtr_sjw   NOTIFY canfd_settings_changed)

    Q_PROPERTY(int canfd2_dbtr_psc   READ canfd2_dbtr_psc   WRITE set_canfd2_dbtr_psc   NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_dbtr_tseg1 READ canfd2_dbtr_tseg1 WRITE set_canfd2_dbtr_tseg1 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_dbtr_tseg2 READ canfd2_dbtr_tseg2 WRITE set_canfd2_dbtr_tseg2 NOTIFY canfd_settings_changed)
    Q_PROPERTY(int canfd2_dbtr_sjw   READ canfd2_dbtr_sjw   WRITE set_canfd2_dbtr_sjw   NOTIFY canfd_settings_changed)


    Q_PROPERTY(bool canfd2_ASM       READ canfd2_ASM        WRITE set_canfd2_ASM        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_DAR       READ canfd2_DAR        WRITE set_canfd2_DAR        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_FDOE      READ canfd2_FDOE       WRITE set_canfd2_FDOE       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_BRSE      READ canfd2_BRSE       WRITE set_canfd2_BRSE       NOTIFY canfd_settings_changed)

    Q_PROPERTY(bool canfd2_PXHD      READ canfd2_PXHD       WRITE set_canfd2_PXHD       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_EFBI      READ canfd2_EFBI       WRITE set_canfd2_EFBI       NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_TXP       READ canfd2_TXP        WRITE set_canfd2_TXP        NOTIFY canfd_settings_changed)
    Q_PROPERTY(bool canfd2_NISO      READ canfd2_NISO       WRITE set_canfd2_NISO       NOTIFY canfd_settings_changed)

 public:
    //============================================== CAN 1  =========================================================
    int canfd1_nbtr_psc()const  {return m_CANFD_settings.bitrate_psc  (FDCAN1_E);}
    int canfd1_nbtr_tseg1()const{return m_CANFD_settings.bitrate_tseg1(FDCAN1_E);}
    int canfd1_nbtr_tseg2()const{return m_CANFD_settings.bitrate_tseg2(FDCAN1_E);}
    int canfd1_nbtr_sjw()const  {return m_CANFD_settings.bitrate_sjw  (FDCAN1_E);}

    int canfd1_dbtr_psc()const  {return m_CANFD_settings.bitrate_psc  (FDCAN1_E, false);}
    int canfd1_dbtr_tseg1()const{return m_CANFD_settings.bitrate_tseg1(FDCAN1_E, false);}
    int canfd1_dbtr_tseg2()const{return m_CANFD_settings.bitrate_tseg2(FDCAN1_E, false);}
    int canfd1_dbtr_sjw()const  {return m_CANFD_settings.bitrate_sjw  (FDCAN1_E, false);}

    bool canfd1_ASM()const       {return m_CANFD_settings.ASM (FDCAN1_E);}
    bool canfd1_DAR()const       {return m_CANFD_settings.DAR (FDCAN1_E);}
    bool canfd1_FDOE()const      {return m_CANFD_settings.FDOE(FDCAN1_E);}
    bool canfd1_BRSE()const      {return m_CANFD_settings.BRSE(FDCAN1_E);}
    bool canfd1_PXHD()const      {return m_CANFD_settings.PXHD(FDCAN1_E);}
    bool canfd1_EFBI()const      {return m_CANFD_settings.EFBI(FDCAN1_E);}
    bool canfd1_TXP()const       {return m_CANFD_settings.TXP (FDCAN1_E);}
    bool canfd1_NISO()const      {return m_CANFD_settings.NISO(FDCAN1_E);}

    void set_canfd1_nbtr_psc  (uint8_t val){m_CANFD_settings.set_bitrate_psc  (FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_nbtr_tseg1(uint8_t val){m_CANFD_settings.set_bitrate_tseg1(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_nbtr_tseg2(uint8_t val){m_CANFD_settings.set_bitrate_tseg2(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_nbtr_sjw  (uint8_t val){m_CANFD_settings.set_bitrate_sjw  (FDCAN1_E, val); emit canfd_settings_changed();}

    void set_canfd1_dbtr_psc  (uint8_t val){m_CANFD_settings.set_bitrate_psc  (FDCAN1_E, val, false); emit canfd_settings_changed();}
    void set_canfd1_dbtr_tseg1(uint8_t val){m_CANFD_settings.set_bitrate_tseg1(FDCAN1_E, val, false); emit canfd_settings_changed();}
    void set_canfd1_dbtr_tseg2(uint8_t val){m_CANFD_settings.set_bitrate_tseg2(FDCAN1_E, val, false); emit canfd_settings_changed();}
    void set_canfd1_dbtr_sjw  (uint8_t val){m_CANFD_settings.set_bitrate_sjw  (FDCAN1_E, val, false); emit canfd_settings_changed();}

    void set_canfd1_ASM   (bool val){m_CANFD_settings.setASM (FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_DAR   (bool val){m_CANFD_settings.setDAR (FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_FDOE  (bool val){m_CANFD_settings.setFDOE(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_BRSE  (bool val){m_CANFD_settings.setBRSE(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_PXHD  (bool val){m_CANFD_settings.setPXHD(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_EFBI  (bool val){m_CANFD_settings.setEFBI(FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_TXP   (bool val){m_CANFD_settings.setTXP (FDCAN1_E, val); emit canfd_settings_changed();}
    void set_canfd1_NISO  (bool val){m_CANFD_settings.setNISO(FDCAN1_E, val); emit canfd_settings_changed();}

    //============================================== CAN 2  =========================================================
    int canfd2_nbtr_psc()const  {return m_CANFD_settings.bitrate_psc  (FDCAN2_E);}
    int canfd2_nbtr_tseg1()const{return m_CANFD_settings.bitrate_tseg1(FDCAN2_E);}
    int canfd2_nbtr_tseg2()const{return m_CANFD_settings.bitrate_tseg2(FDCAN2_E);}
    int canfd2_nbtr_sjw()const  {return m_CANFD_settings.bitrate_sjw  (FDCAN2_E);}

    int canfd2_dbtr_psc()const  {return m_CANFD_settings.bitrate_psc  (FDCAN2_E, false);}
    int canfd2_dbtr_tseg1()const{return m_CANFD_settings.bitrate_tseg1(FDCAN1_E, false);}
    int canfd2_dbtr_tseg2()const{return m_CANFD_settings.bitrate_tseg2(FDCAN2_E, false);}
    int canfd2_dbtr_sjw()const  {return m_CANFD_settings.bitrate_sjw  (FDCAN2_E, false);}

    bool canfd2_ASM()const       {return m_CANFD_settings.ASM (FDCAN2_E);}
    bool canfd2_DAR()const       {return m_CANFD_settings.DAR (FDCAN2_E);}
    bool canfd2_FDOE()const      {return m_CANFD_settings.FDOE(FDCAN2_E);}
    bool canfd2_BRSE()const      {return m_CANFD_settings.BRSE(FDCAN2_E);}
    bool canfd2_PXHD()const      {return m_CANFD_settings.PXHD(FDCAN2_E);}
    bool canfd2_EFBI()const      {return m_CANFD_settings.EFBI(FDCAN2_E);}
    bool canfd2_TXP()const       {return m_CANFD_settings.TXP (FDCAN2_E);}
    bool canfd2_NISO()const      {return m_CANFD_settings.NISO(FDCAN2_E);}

    void set_canfd2_nbtr_psc  (uint8_t val){m_CANFD_settings.set_bitrate_psc  (FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_nbtr_tseg1(uint8_t val){m_CANFD_settings.set_bitrate_tseg1(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_nbtr_tseg2(uint8_t val){m_CANFD_settings.set_bitrate_tseg2(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_nbtr_sjw  (uint8_t val){m_CANFD_settings.set_bitrate_sjw  (FDCAN2_E, val); emit canfd_settings_changed();}

    void set_canfd2_dbtr_psc  (uint8_t val){m_CANFD_settings.set_bitrate_psc  (FDCAN2_E, val, false); emit canfd_settings_changed();}
    void set_canfd2_dbtr_tseg1(uint8_t val){m_CANFD_settings.set_bitrate_tseg1(FDCAN2_E, val, false); emit canfd_settings_changed();}
    void set_canfd2_dbtr_tseg2(uint8_t val){m_CANFD_settings.set_bitrate_tseg2(FDCAN2_E, val, false); emit canfd_settings_changed();}
    void set_canfd2_dbtr_sjw  (uint8_t val){m_CANFD_settings.set_bitrate_sjw  (FDCAN2_E, val, false); emit canfd_settings_changed();}

    void set_canfd2_ASM   (bool val){m_CANFD_settings.setASM (FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_DAR   (bool val){m_CANFD_settings.setDAR (FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_FDOE  (bool val){m_CANFD_settings.setFDOE(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_BRSE  (bool val){m_CANFD_settings.setBRSE(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_PXHD  (bool val){m_CANFD_settings.setPXHD(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_EFBI  (bool val){m_CANFD_settings.setEFBI(FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_TXP   (bool val){m_CANFD_settings.setTXP (FDCAN2_E, val); emit canfd_settings_changed();}
    void set_canfd2_NISO  (bool val){m_CANFD_settings.setNISO(FDCAN2_E, val); emit canfd_settings_changed();}

    void refresh_fdcan_settings(const QByteArray& _data){m_CANFD_settings.init(_data); emit canfd_settings_changed();}
    const QByteArray read_fdcan_settings()const         {return m_CANFD_settings.raw_data();}

};




#endif // DEVICEMANAGER_H
