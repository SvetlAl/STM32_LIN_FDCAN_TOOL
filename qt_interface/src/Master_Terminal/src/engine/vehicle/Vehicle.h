#ifndef VEHICLE_H
#define VEHICLE_H

/***********************************************************************
 *
 *
 * Vehicle class incapsulates vehicle data (imported from the firmware project)
 *
 *
 *
 *
 ************************************************************************/

#include <QObject>
#include <QDebug>
#include "../../app_settings.h"


/*************** Exported from 'C' **********************/


typedef struct VehicleStruct{
    uint16_t model;

    uint8_t startup_settings;
    uint8_t modes;

    uint8_t speedometer_mlt;
    uint8_t odometer_mlt;
    uint8_t cruise_mlt;
    uint8_t tyres_threshold;

    uint32_t id_speedometer;
    uint32_t id_speedometer_extra;
    uint32_t id_odometer;
    uint32_t id_cruise;
} VehicleStruct;

typedef union unionVehicleStructData{
    VehicleStruct _vehicleStruct;
    uint8_t data[sizeof(VehicleStruct)];
}unionVehicleStructData;


class Vehicle : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString model_name READ model_name NOTIFY model_name_changed)
    Q_PROPERTY(int model READ model WRITE set_model NOTIFY model_changed)
    Q_PROPERTY(int modes READ modes WRITE set_modes NOTIFY modes_changed)
    /*** Modes ***/
    Q_PROPERTY(bool isOdoFreeze READ isOdoFreeze NOTIFY modes_changed)
    Q_PROPERTY(bool isTestMode READ isTestMode NOTIFY modes_changed)

    Q_PROPERTY(int speedometer_mlt READ speedometer_mlt WRITE set_speedometer_mlt NOTIFY speedometer_mlt_changed)
    Q_PROPERTY(int odometer_mlt READ odometer_mlt WRITE set_odometer_mlt NOTIFY odometer_mlt_changed)
    Q_PROPERTY(int cruise_mlt READ cruise_mlt WRITE set_cruise_mlt NOTIFY cruise_mlt_changed)
    Q_PROPERTY(int tyres_threshold READ tyres_threshold WRITE set_tyres_threshold NOTIFY tyres_threshold_changed)
    Q_PROPERTY(int id_speedometer READ id_speedometer WRITE set_id_speedometer NOTIFY id_speedometer_changed)
    Q_PROPERTY(int id_speedometer_extra READ id_speedometer_extra WRITE set_id_speedometer_extra NOTIFY id_speedometer_extra_changed)
    Q_PROPERTY(int id_odometer READ id_odometer WRITE set_id_odometer NOTIFY id_odometer_changed)
    Q_PROPERTY(int id_cruise READ id_cruise WRITE set_id_cruise NOTIFY id_cruise_changed)

    Q_PROPERTY(bool is_speedometer_mlt_available READ speedometer_mlt_available MEMBER is_speedometer_mlt_available NOTIFY is_speedometer_mlt_availableChanged)
    Q_PROPERTY(bool is_odometer_mlt_available READ odometer_mlt_available MEMBER is_odometer_mlt_available NOTIFY is_odometer_mlt_availableChanged)
    Q_PROPERTY(bool is_cruise_mlt_available READ cruise_mlt_available MEMBER is_cruise_mlt_available NOTIFY is_cruise_mlt_availableChanged)
    Q_PROPERTY(bool is_tyres_threshold_available READ tyres_threshold_available MEMBER is_tyres_threshold_available NOTIFY is_tyres_threshold_availableChanged)


public:
    explicit Vehicle(QObject *parent = nullptr): QObject(parent){
        set_model(0xFFFF);
    };
    ~Vehicle(){
    };

    //================================= static presets ==============================
    enum ModelBrand {
        Toyota = 0,
        GreatWall = 1,
        Dodge = 2,
        LandRover = 3,
        Mitsubishi = 4,
        Isuzu = 5,
        Lexus = 6,
        Tank = 7,
        Honda = 8,
        Ford = 9,
        Nissan = 10,
        Extra = 11,
        Default = 12
    };

    //==================================== init =====================================
    void init_with_response_bytes(const QByteArray &response_bytes);
    void initNewModel();
    void reset();

    //============================= Setters/Getters =================================
    const QString model_name() const {return m_modelName;};
    const uint16_t model() const {return m_VehicleStruct->model;};
    const uint8_t modes() const {return m_VehicleStruct->modes;};
    const uint8_t speedometer_mlt() const {return m_VehicleStruct->speedometer_mlt;};
    const uint8_t odometer_mlt() const {return m_VehicleStruct->odometer_mlt;};
    const uint8_t cruise_mlt() const {return m_VehicleStruct->cruise_mlt;};
    const uint8_t tyres_threshold() const {return m_VehicleStruct->tyres_threshold;};
    const uint32_t id_speedometer() const {return m_VehicleStruct->id_speedometer;};
    const uint32_t id_speedometer_extra() const {return m_VehicleStruct->id_speedometer_extra;};
    const uint32_t id_odometer() const {return m_VehicleStruct->id_odometer;};
    const uint32_t id_cruise() const {return m_VehicleStruct->id_cruise;};

    void set_model(const uint16_t _model) {m_VehicleStruct->model = _model; emit model_changed();};
    void set_modelName(const QString& _modelName) {m_modelName = _modelName; emit model_name_changed();};
    void set_modes(const uint16_t _modes) {m_VehicleStruct->modes = _modes; emit modes_changed();};
    void set_speedometer_mlt(uint8_t _speedometer_mlt)  {m_VehicleStruct->speedometer_mlt = _speedometer_mlt; emit speedometer_mlt_changed();};
    void set_odometer_mlt(uint8_t _odometer_mlt)  {m_VehicleStruct->odometer_mlt = _odometer_mlt; emit odometer_mlt_changed();};
    void set_cruise_mlt(uint8_t _cruise_mlt)  {m_VehicleStruct->cruise_mlt = _cruise_mlt; emit cruise_mlt_changed();};
    void set_tyres_threshold(uint8_t _tyres_threshold)  {m_VehicleStruct->tyres_threshold = _tyres_threshold; emit tyres_threshold_changed();};
    void set_id_speedometer(uint32_t _id_speedometer)  {m_VehicleStruct->id_speedometer = _id_speedometer; emit id_speedometer_changed();};
    void set_id_speedometer_extra(uint32_t _id_speedometer_extra)  {m_VehicleStruct->id_speedometer_extra = _id_speedometer_extra; emit id_speedometer_extra_changed();};
    void set_id_odometer(uint32_t _id_odometer)  {m_VehicleStruct->id_odometer = _id_odometer; emit id_odometer_changed();};
    void set_id_cruise(uint32_t _id_cruise)  {m_VehicleStruct->id_cruise = _id_cruise; emit id_cruise_changed();};

    /*** Modes ***/
    bool isOdoFreeze() const{return (m_VehicleStruct->modes & CALIBRATOR_ODO_FREEZE_MODE);}
    bool isTestMode() const{return (m_VehicleStruct->modes & CALIBRATOR_TEST_MODE);}

    bool speedometer_mlt_available() const {return is_speedometer_mlt_available;};
    bool odometer_mlt_available() const {return is_odometer_mlt_available;};
    bool cruise_mlt_available() const {return is_cruise_mlt_available;};
    bool tyres_threshold_available() const {return is_tyres_threshold_available;};

    /* emit all signals */
    void all_changed();
signals:

    void model_name_changed();
    void model_changed();
    void modes_changed();
    void speedometer_mlt_changed();
    void odometer_mlt_changed();
    void cruise_mlt_changed();
    void tyres_threshold_changed();
    void id_speedometer_changed();
    void id_speedometer_extra_changed();
    void id_odometer_changed();
    void id_cruise_changed();

    void is_speedometer_mlt_availableChanged();
    void is_odometer_mlt_availableChanged();
    void is_cruise_mlt_availableChanged();
    void is_tyres_threshold_availableChanged();

private:

    unionVehicleStructData m_pUnionVehicleStructData = {0};
    VehicleStruct *m_VehicleStruct = &m_pUnionVehicleStructData._vehicleStruct;

    QString m_modelName = "";

    bool is_speedometer_mlt_available = false;
    bool is_odometer_mlt_available = false;
    bool is_cruise_mlt_available = false;
    bool is_tyres_threshold_available = false;
};


//Q_DECLARE_METATYPE(Core);
#endif // VEHICLE_H
