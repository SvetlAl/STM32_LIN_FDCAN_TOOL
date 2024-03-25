/****************************************************************
* 			Vehicle handler
*
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*
* 02.03.2023 typedef struct odometerCounter_LC300 - fixed padding
*
* 23.04.2023 Reference 0 km/h and test value for WINGLE7
*****************************************************************/

#include "vehicle.h"

#ifndef SUPPORT_SPEEDO_CALIBRATOR
//===============================================================================================
//=============================== Global var & setters/getters ==================================
//===============================================================================================
static VehicleStructData theVehicle;

static void initVehicle(VehicleStruct *vehicle, uint8_t mode);

uint8_t *get_vehicle_settings_data(void){
	return &theVehicle.data[0];
}

//===============================================================================================
//=================================== Vehicle access functions ==================================
//===============================================================================================
uint32_t vehicle_startup_settings(void){
	return theVehicle._vehicleStruct.startup_settings;
}

uint16_t vehicle_model(void){
	return VEHICLE_MODEL(theVehicle);
}
uint8_t vehicle_modes(void){
	return VEHICLE_MODES(theVehicle);
}
uint8_t vehicle_odo_mlt(void){
	return ODO_MLT(theVehicle);
}
uint8_t vehicle_spd_mlt(void){
	return SPEED_MLT(theVehicle);
}
uint8_t vehicle_crs_mlt(void){
	return CRUISE_MLT(theVehicle);
}
uint8_t vehicle_tyr_thr(void){
	return TYRES_THRESHOLD(theVehicle);
}
uint32_t vehicle_spd_id(void){
	return SPEEDOMETER_ID(theVehicle);
}
uint32_t vehicle_odo_id(void){
	return ODOMETER_ID(theVehicle);
}
uint32_t vehicle_crs_id(void){
	return CRUISE_ID(theVehicle);
}
uint32_t vehicle_ext_id(void){
	return EXTRAS_ID(theVehicle);
}
void vehicle_calibrate_spd(can_message *msg, uint8_t _odo_mlt){
	CALIBRATE_SPEEDOMETER(theVehicle, msg, _odo_mlt);
}
void vehicle_calibrate_odo(can_message *msg, uint8_t _odo_mlt){
	CALIBRATE_ODOMETER(theVehicle, msg, _odo_mlt);
}
void vehicle_calibrate_crs(can_message *msg){
	CALIBRATE_CRUISE(theVehicle, msg);
}
void vehicle_calibrate_ext(can_message *msg){
	CALIBRATE_EXTRAS(theVehicle, msg);
}

#ifdef SUPPORT_FDCAN
void fdcan_vehicle_calibrate_spd(uint8_t *msg, uint16_t data_sz, uint8_t _odo_mlt){
	FDCAN_CALIBRATE_SPEEDOMETER(msg, data_sz, _odo_mlt);
}
void fdcan_vehicle_calibrate_odo(uint8_t *msg, uint16_t data_sz, uint8_t _odo_mlt){
	FDCAN_CALIBRATE_ODOMETER(msg, data_sz,_odo_mlt);
}
void fdcan_vehicle_calibrate_crs(uint8_t *msg, uint16_t data_sz){
	FDCAN_CALIBRATE_CRUISE(msg, data_sz);
}
void fdcan_vehicle_calibrate_ext(uint32_t id, uint8_t *msg_data){
	FDCAN_CALIBRATE_EXTRAS(id, msg_data);
}
#endif // SUPPORT_FDCAN

void vehicle_set_model  (uint16_t val, uint8_t mode){
	theVehicle._vehicleStruct.model = (uint16_t)val;
	initVehicle(&theVehicle._vehicleStruct, mode);
}
void vehicle_set_modes  (uint8_t val){
	theVehicle._vehicleStruct.modes = val;
}
void vehicle_set_odo_mlt(uint8_t val){
	theVehicle._vehicleStruct.odometer_mlt = val;
}
void vehicle_set_spd_mlt(uint8_t val){
	theVehicle._vehicleStruct.speedometer_mlt = val;
}
void vehicle_set_crs_mlt(uint8_t val){
	theVehicle._vehicleStruct.cruise_mlt = val;
}
void vehicle_set_tyr_thr(uint8_t val){
	theVehicle._vehicleStruct.tyres_threshold = val;
}

//===============================================================================================
//=================================== Dummy functions ===========================================
//===============================================================================================
//static can_message dummy_SpeedOdo(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
static can_message dummy_Cruise(can_message *msg, uint8_t _cruise_mlt);
static can_message dummy_Extras(can_message *msg, uint8_t _mlt);

#include "Commands/user_cmd.h"

#ifdef MEMCHIP_NOR_FLASH
#include "Flash_memchip/flash_nor_mem_chip_spi.h"
#endif
#ifdef MEMCHIP_NAND_FLASH
#include "Flash_memchip/flash_nand_mem_chip_spi.h"
#endif

#define NO_CALIBRATION_RATIO          (uint8_t)((uint8_t)0x64)




/***************************************************
****************************************************
************* Standart format vars *****************
****************************************************
***************************************************/
/** 
* brief  Init loaded data 
* param 
* param  
* retval Startup Settings
*/	
uint32_t initVehicleSettings(void){
	if(theVehicle._vehicleStruct.model < MODEL_COUNT){
		initVehicle(&theVehicle._vehicleStruct, VEHICLE_INIT_PRESET);
	}
	
	else if(theVehicle._vehicleStruct.model >= MODEL_COUNT){
		theVehicle._vehicleStruct.model = MODEL_TOYOTA_LC300;
		initVehicle(&theVehicle._vehicleStruct, VEHICLE_INIT_DEFAULT);
	}
	
	if(theVehicle._vehicleStruct.startup_settings & STARTUP_SETTINGS_IWDG){
		#ifndef DEBUG_MODE
		return (uint32_t)STARTUP_SETTINGS_IWDG;
		#endif
	}
	
	return OPERATION_OK;
}


static can_message dummy_SpeedOdo(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	UNUSED(msg);
	UNUSED(_speedometer_mlt);
	UNUSED(_odometer_mlt);
	return *msg;
}

static can_message dummy_Cruise(can_message *msg, uint8_t _cruise_mlt){
	UNUSED(_cruise_mlt);
	UNUSED(msg);
	return *msg;
}

static can_message dummy_Extras(can_message *msg, uint8_t _mlt){
	UNUSED(_mlt);
	UNUSED(msg);
	return *msg;
}
#ifdef SUPPORT_FDCAN
static void dummy_fdcan_calibrate_speedometer    (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
  UNUSED(siz);
	UNUSED(msg_data);
	UNUSED(_speedometer_mlt);
	UNUSED(_odometer_mlt);
}
static void dummy_fdcan_calibrate_odometer       (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
UNUSED(siz);
	UNUSED(msg_data);
	UNUSED(_speedometer_mlt);
	UNUSED(_odometer_mlt);
}
static void dummy_fdcan_calibrate_cruise         (uint8_t *msg_data, uint8_t siz, uint8_t _cruise_mlt){
  UNUSED(siz);
	UNUSED(msg_data);
	UNUSED(_cruise_mlt);
}
static void dummy_fdcan_calibrate_extra          (uint8_t *msg, uint32_t id, uint8_t _threshold_mlt){
	UNUSED(msg);
	UNUSED(id);
	UNUSED(_threshold_mlt);
}
#endif // SUPPORT_FDCAN

/**
* brief  Init vehicle settings
* param  Vehicle data ref
* param  mode: default or loaded from a memory chip
* retval 
*/
void initVehicle(VehicleStruct *vehicle, uint8_t mode){
	UNUSED(mode);
	vehicle->startup_settings = STARTUP_SETTINGS_DEFAULT;
	vehicle->modes = 0x00;
	
	/*********** DEFAULT ****************/
	vehicle->id_speedometer = 0xFFF;
	vehicle->id_speedometer_extra = 0xFFF;
	vehicle->id_odometer = 0xFFF;
	vehicle->id_cruise = 0xFFF;
	
	vehicle->speedometer_mlt = 0x64;
	vehicle->odometer_mlt = 0x64;
	vehicle->cruise_mlt = 0x64;
	vehicle->tyres_threshold = 0x64;
	
	vehicle->calibrate_speedometer = &dummy_SpeedOdo;
	vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
	vehicle->calibrate_cruise = &dummy_Cruise;
	vehicle->calibrate_extra = &dummy_Extras;
#ifdef SUPPORT_FDCAN
	vehicle->fdcan_calibrate_speedometer = &dummy_fdcan_calibrate_speedometer;
	vehicle->fdcan_calibrate_odometer = &dummy_fdcan_calibrate_odometer;
	vehicle->fdcan_calibrate_cruise = &dummy_fdcan_calibrate_cruise;
	vehicle->fdcan_calibrate_extra = &dummy_fdcan_calibrate_extra;
#endif
}

#endif /* SUPPORT_SPEEDO_CALIBRATOR */

