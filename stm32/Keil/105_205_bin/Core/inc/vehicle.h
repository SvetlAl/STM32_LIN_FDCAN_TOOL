#ifndef VEHICLE_H_INCLUDED
#define VEHICLE_H_INCLUDED

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
#include "device_model.h"

#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif

#include "can.h"
//#include "string_convertor.h"

#define UNUSED(x) (void)(x)


#define VEHICLE_MODEL(vhcl) (uint16_t) (vhcl._vehicleStruct.model)

#define VEHICLE_MODES(vhcl) (uint8_t) (vhcl._vehicleStruct.modes)

#define ODO_MLT(vhcl) (uint8_t) (vhcl._vehicleStruct.odometer_mlt)
#define SPEED_MLT(vhcl) (uint8_t) (vhcl._vehicleStruct.speedometer_mlt)
#define CRUISE_MLT(vhcl) (uint8_t) (vhcl._vehicleStruct.cruise_mlt)
#define TYRES_THRESHOLD(vhcl) (uint8_t) (vhcl._vehicleStruct.tyres_threshold)

#define SPEEDOMETER_ID(vhcl) (uint32_t) (vhcl._vehicleStruct.id_speedometer)
#define ODOMETER_ID(vhcl) (uint32_t) (vhcl._vehicleStruct.id_odometer)
#define CRUISE_ID(vhcl) (uint32_t) (vhcl._vehicleStruct.id_cruise)
#define EXTRAS_ID(vhcl) (uint32_t) (vhcl._vehicleStruct.id_speedometer_extra)

#define CALIBRATE_SPEEDOMETER(vhcl, msg, odo_mlt) (vhcl._vehicleStruct.calibrate_speedometer(msg, vhcl._vehicleStruct.speedometer_mlt, odo_mlt))
#define CALIBRATE_ODOMETER(vhcl, msg, odo_mlt) (vhcl._vehicleStruct.calibrate_odometer(msg, vhcl._vehicleStruct.speedometer_mlt, odo_mlt))
#define CALIBRATE_CRUISE(vhcl, msg) (vhcl._vehicleStruct.calibrate_cruise(msg, vhcl._vehicleStruct.cruise_mlt))
#define CALIBRATE_EXTRAS(vhcl, msg) (vhcl._vehicleStruct.calibrate_extra(msg, vhcl._vehicleStruct.tyres_threshold))


/***************************************************
****************************************************
************* Standart format defs  ****************
****************************************************
***************************************************/


#define VEHICLE_OK 		0
#define VEHICLE_FAIL 	1

#define VEHICLE_INIT_PRESET 		1
#define VEHICLE_INIT_DEFAULT 		2

#define NO_CALIBRATION_RATIO 					(uint8_t)((uint8_t)0x64)

//#define STATUS_STRING_LENGTH 						64
#define VEHICLE_STATUS_SETTINGS_LENGTH	8

#define STARTUP_SETTINGS_DEFAULT				0x00
#define STARTUP_SETTINGS_IWDG						0x01


#define CALIBRATOR_DEFAULT_MODE         0x00
#define CALIBRATOR_ODO_FREEZE_MODE      0x01
#define CALIBRATOR_TEST_MODE            0x02

#define SPEEDOMETER_TEST_VALUE          0x2C
#define SPEEDOMETER_TEST_VALUE_GW       0x2C // 0x9C
#define SPEEDOMETER_TEST_VALUE_DR       0x9C

#define MODEL_TOYOTA_LC300              0x0000
#define MODEL_TOYOTA_LC150              0x0001
#define MODEL_TOYOTA_HILUX              0x0002
#define MODEL_TOYOTA_TUNDRA_2008        0x0003
#define MODEL_GREAT_WALL_WINGLE7        0x0004
#define MODEL_DODGE_RAM_2013            0x0005
#define MODEL_ISUZU_DMAX_MUX            0x0006
#define MODEL_LAND_ROVER_DEFENDER_2022  0x0007
#define MODEL_MITSUBISHI_L200           0x0008
#define MODEL_MITSUBISHI_PAJERO_SPORT   0x0009
#define MODEL_GREAT_WALL_POER           0x000A
#define MODEL_TOYOTA_LC200              0x000B
#define MODEL_LEXUS_LX570               0x000C
#define MODEL_TOYOTA_TUNDRA_2022        0x000D
#define MODEL_TANK_300                  0x000E
#define MODEL_TOYOTA_SEQUOIA_2022       0x000F
#define MODEL_HONDA_CRV_III             0x0010
#define MODEL_FORD_TRANSIT_2020         0x0011
#define MODEL_NISSAN_PATROL_2020        0x0012
#define MODEL_EXTRA_I                   0x0013
#define MODEL_EXTRA_II                  0x0014
#define MODEL_EXTRA_III                 0x0015

#define MODEL_COUNT                     0x0016

/***************************************************
****************************************************
************* Vehicle structure ********************
****************************************************
***************************************************/

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
	
	can_message (*calibrate_speedometer)(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
	can_message (*calibrate_odometer)(can_message *msg, uint8_t _speedometer_mlt, uint8_t odometer_mlt);
	can_message (*calibrate_cruise)(can_message *msg, uint8_t _cruise_mlt);
	can_message (*calibrate_extra)(can_message *msg, uint8_t _mlt);
} VehicleStruct; //creating new type

typedef union VehicleStructData{
	VehicleStruct _vehicleStruct;
	uint8_t data[sizeof(VehicleStruct)];
}VehicleStructData;

//=================== Load and init functions ===================================
VehicleStructData loadVehicle(uint8_t *buf);
void initVehicleSettings(VehicleStructData *vhcl);
void initVehicle(VehicleStruct *vehicle, uint8_t mode);

//=========================== Dummy functions ===================================
can_message dummy_SpeedOdo(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message dummy_Cruise(can_message *msg, uint8_t _cruise_mlt);
can_message dummy_Extras(can_message *msg, uint8_t _mlt);

//=============================== Checksums =====================================


/***************************************************
****************************************************
************* Standart format functions ************
****************************************************
***************************************************/


can_message calibrateSpeedOdo_MODEL_EXTRA_I(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_MODEL_EXTRA_I(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_MODEL_EXTRA_I(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_MODEL_EXTRA_II(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_MODEL_EXTRA_II(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_MODEL_EXTRA_II(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_MODEL_EXTRA_III(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_MODEL_EXTRA_III(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_MODEL_EXTRA_III(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _cruise_mlt);


/***************************************************
****************************************************
************* Vehicle specific defs ****************
****************************************************
***************************************************/


#endif /* VEHICLE_H_INCLUDED */
