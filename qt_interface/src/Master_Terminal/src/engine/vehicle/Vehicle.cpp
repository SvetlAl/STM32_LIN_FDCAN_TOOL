#include "Vehicle.h"


/********************************************************************
 *
 *
 *                     Initialization
 *
 *
********************************************************************/

void Vehicle::init_with_response_bytes(const QByteArray &response_bytes){
    uint16_t prev_model = model();

    for (size_t i = 0; i < RESPONSE_LENGTH_CURRENT_STATUS_STRING_HEX; i++){
        m_pUnionVehicleStructData.data[i] = response_bytes[i];
    }
    if(prev_model != model()) initNewModel();
    else{
        emit modes_changed();
        emit speedometer_mlt_changed();
        emit odometer_mlt_changed();
        emit cruise_mlt_changed();
        emit tyres_threshold_changed();
    }
}

void Vehicle::initNewModel() {
    switch(model()){
    case MODEL_TOYOTA_LC300:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("TOYOTA_LC300");
        break;
    case MODEL_TOYOTA_LC150:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("TOYOTA_LC150");
        break;
    case MODEL_TOYOTA_HILUX:
        is_speedometer_mlt_available = false;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("TOYOTA_HILUX");
        break;
    case MODEL_TOYOTA_TUNDRA_2008:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("TUNDRA_2008");
        break;
    case MODEL_GREAT_WALL_WINGLE7:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = false;
        is_tyres_threshold_available = false;
        set_modelName("GREAT_WALL_WINGLE7");
        break;
    case MODEL_DODGE_RAM_2013:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("DODGE_RAM_2013");
        break;
    case MODEL_ISUZU_DMAX_MUX:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("ISUZU_DMAX_MUX");
        break;
    case MODEL_LAND_ROVER_DEFENDER_2022:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("LAND_ROVER_DEFENDER_22");
        break;
    case MODEL_MITSUBISHI_L200:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = false;
        is_tyres_threshold_available = false;
        set_modelName("MITSUBISHI_L200");
        break;
    case MODEL_MITSUBISHI_PAJERO_SPORT:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = false;
        is_tyres_threshold_available = false;
        set_modelName("MITSUBISHI_PAJERO_SPORT");
        break;
    case MODEL_GREAT_WALL_POER:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("GREAT_WALL_POER");
        break;
    case MODEL_TOYOTA_LC200:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("TOYOTA_LC200");
        break;
    case MODEL_LEXUS_LX570:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = false;
        set_modelName("LEXUS_LX570");
        break;
    case MODEL_TOYOTA_TUNDRA_2022:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("TOYOTA_TUNDRA_22");
        break;
    case MODEL_TANK_300:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("TANK_300");
        break;   
    case MODEL_TOYOTA_SEQUOIA_2022:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("TOYOTA_SEQUOIA_22");
        break;
    case MODEL_HONDA_CRV_III:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("HONDA_CRV_III");
        break;
    case MODEL_FORD_TRANSIT_2020:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("FORD_TRANSIT_20");
        break;
    case MODEL_EXTRA_I:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("EXTRA_I");
        break;
    case MODEL_EXTRA_II:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("EXTRA_II");
        break;
    case MODEL_EXTRA_III:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("EXTRA_III");
        break;
    case MODEL_NISSAN_PATROL_2020:
        is_speedometer_mlt_available = true;
        is_odometer_mlt_available = true;
        is_cruise_mlt_available = true;
        is_tyres_threshold_available = true;
        set_modelName("NISSAN_PTRL_20");
        break;
    default:
        is_speedometer_mlt_available = false;
        is_odometer_mlt_available = false;
        is_cruise_mlt_available = false;
        is_tyres_threshold_available = false;
        set_modelName("");
    }
    // all_changed();
}

void Vehicle::reset(){
    set_model(0xFFFF);
    set_modelName("");

    set_modes(0);
    set_speedometer_mlt(0);
    set_odometer_mlt(0);
    set_cruise_mlt(0);
    set_tyres_threshold(0);
    set_id_speedometer(0);
    set_id_speedometer_extra(0);
    set_id_odometer(0);
    set_id_cruise(0);
}

/********************************************************************
 *
 *
 *                     Signals
 *
 *
********************************************************************/

void Vehicle::all_changed(){
    emit model_name_changed();
    emit model_changed();
    emit modes_changed();
    emit speedometer_mlt_changed();
    emit odometer_mlt_changed();
    emit cruise_mlt_changed();
    emit tyres_threshold_changed();
    emit is_speedometer_mlt_availableChanged();
    emit is_odometer_mlt_availableChanged();
    emit is_cruise_mlt_availableChanged();
    emit is_tyres_threshold_availableChanged();
   // emit id_speedometer_changed();
    //emit id_speedometer_extra_changed();
    //emit id_odometer_changed();
    //emit id_cruise_changed();
}
