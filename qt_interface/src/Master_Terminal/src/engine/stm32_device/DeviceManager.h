#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QDebug>
#include "OverrideStatus.h"
#include "QML_Model/QDiscardId_ModelProperty.h"
#include "QML_Model/QOverrideFilter_ModelProperty.h"
//#include "../../core/Console.h"



//======================= Exported from 'C' ============================
typedef enum  : uint8_t {
    DEVICE_OPERATION_MODE_DEFAULT = (uint8_t)0xFF,
    DEVICE_OPERATION_MODE_ON = (uint8_t)0x01,
    DEVICE_OPERATION_MODE_OFF = (uint8_t)0x02,
    DEVICE_OPERATION_MODE_REV = (uint8_t)0x03,
    DEVICE_OPERATION_MODE_CIRCULAR_REV = (uint8_t)0x04,
    DEVICE_OPERATION_MODE_CIRCULAR = (uint8_t)0x05,
    DEVICE_OPERATION_MODE_FILTR_UPD = (uint8_t)0x06} eDeviceFunctionMode;

    /* this is needed for interface application for a correct command set */
typedef enum  : uint8_t{
    MEMCHIP_MODEL_DEFAULT = (uint8_t)0xFF,
    MEMCHIP_MODEL_MX25L323 = (uint8_t)0x01,
    MEMCHIP_MODEL_M45PE16 = (uint8_t)0x02,
    MEMCHIP_MODEL_MX25L16 = (uint8_t)0x03 } eMemChipModel;


typedef struct DeviceModel{
    eMemChipModel memChipModel;
    eDeviceFunctionMode canGatewayMode;
    eDeviceFunctionMode can2GatewayMode;
    eDeviceFunctionMode calibratorFilterMode;
    eDeviceFunctionMode canOverrideMode;
    eDeviceFunctionMode canScannerMode;
    eDeviceFunctionMode can2ScannerMode;
    eDeviceFunctionMode memoryProgramingMode;
    eDeviceFunctionMode canInjectionMode;
} DeviceModel;

enum DeviceModelProperties{
    Enm_memChipModel = 0,
    Enm_canGatewayMode = 1,
    Enm_can2GatewayMode = 2,
    Enm_calibratorFilterMode = 3,
    Enm_canOverrideMode = 4,
    Enm_canScannerMode = 5,
    Enm_can2ScannerMode = 6,
    Enm_memoryProgramingMode = 7,
    Enm_canInjectionMode = 8,
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
    Q_PROPERTY(QString memchip_name READ memchip_name NOTIFY memchip_changed)


    /******************************************************************************************/
    /*                              CAN override configuration                                */
    /******************************************************************************************/
    //=========== Discard Id model ===========
    Q_PROPERTY(QDiscardId_ModelProperty* DiscardIdModel READ DiscardIdModel CONSTANT)

    //=========== Override Filters ===========
    Q_PROPERTY(QOverrideFilter_ModelProperty* OverrideFilterModel READ OverrideFilterModel CONSTANT)



public:
    explicit DeviceManager(QObject *parent = 0) : QObject(parent){
        reset();
    }
    ~DeviceManager() {};

    void reset(){
        for(size_t i = 0; i < sizeof(DeviceModel) ; i++){
            targetDeviceData.data[i] = 0xFF;
        }
    }
    constexpr static const int data_struct_size = sizeof(DeviceModel);

    void init(const QByteArray &_init_data){
        for(size_t i = 0; i < sizeof(DeviceModel); i++){
            targetDeviceData.data[i] = _init_data.at(i);
        }
        emit changed();
        emit memchip_changed();
    }

    int memoryPrograming_Mode() const { return targetDeviceData.deviceModel.memoryProgramingMode; }
    int canGateway_Mode() const { return targetDeviceData.deviceModel.canGatewayMode; }
    int calibratorFilter_Mode() const { return targetDeviceData.deviceModel.calibratorFilterMode; }
    int canOverride_Mode() const { return targetDeviceData.deviceModel.canOverrideMode; }
    int canScanner_Mode() const { return targetDeviceData.deviceModel.canScannerMode; }
    int can2Scanner_Mode() const { return targetDeviceData.deviceModel.can2ScannerMode; }
    int canInjection_Mode() const { return targetDeviceData.deviceModel.canInjectionMode; }

    void setCanInjection_Mode(int value);
    void setCanGateway_Mode(int value);
    void setCalibratorFilter_Mode(int value);
    void setCanOverride_Mode(int value);
    void setCanScanner_Mode(int value);
    void setCan2Scanner_Mode(int value);

    const QString memchip_name() const;

    const int memchip() const{ return targetDeviceData.deviceModel.memChipModel;}

    /************************************************************************
     *
     *
     *                               Override status
     *
     *
     * **********************************************************************/
    const QByteArray getOvrFilterData() const;


    /************************************************************************
     *
     *
     *                               Discard model
     *
     *
     * **********************************************************************/

    QDiscardId_ModelProperty *DiscardIdModel(){return &m_DiscardIdModel;}

    Q_INVOKABLE void fill_OvrSts_from_DscModel();
    Q_INVOKABLE void update_DscModel_from_OvrSts();



    /************************************************************************
     *
     *
     *                          Override filter model
     *
     *
     * **********************************************************************/
    QOverrideFilter_ModelProperty *OverrideFilterModel(){return &m_OverrideFilterModel;}

    Q_INVOKABLE void fill_OvrSts_from_OvrModel();
    Q_INVOKABLE void update_OvrModel_from_OvrSts();


signals:
    void changed();
    void memchip_changed();

public slots:
    void refreshOverrideStatus(const QByteArray& data){
        m_OverrideStatus.init_OverrideStatuswithRawData(data);
    }

    void refreshActiveFilters(const QByteArray& data){
        m_OverrideStatus.setActiveFilters(data);
    }
private:
    uDeviceModel targetDeviceData;
    OverrideStatus m_OverrideStatus;

    QDiscardId_ModelProperty m_DiscardIdModel;
    QOverrideFilter_ModelProperty m_OverrideFilterModel;
};




#endif // DEVICEMANAGER_H
