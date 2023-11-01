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
#define MODEL_TANK_500                  0x0013
#define MODEL_EXTRA_I                   0x0014
#define MODEL_EXTRA_II                  0x0015
#define MODEL_EXTRA_III                 0x0016

#define MODEL_COUNT                     0x0017

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
uint8_t calculateToyotaCheckSum(can_message *msg);
uint8_t calculateTank300CheckSum(can_message *msg);

/***************************************************
****************************************************
************* Standart format functions ************
****************************************************
***************************************************/

can_message calibrateSpeedOdo_TOYOTA_LC300(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_TOYOTA_LC300(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_TOYOTA_LC150(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

can_message calibrateSpeedOdo_TUNDRA_2008(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

can_message calibrateSpeedOdo_GREAT_WALL_WINGLE7(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

can_message calibrateSpeedOdo_DODGE_RAM_2013(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_DODGE_RAM_2013(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_ISUZU_DMAX_MUX(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_ISUZU_DMAX_MUX(can_message *msg, uint8_t _cruise_mlt);
can_message calibrateExtras_ISUZU_DMAX_MUX(can_message *msg, uint8_t _mlt);

can_message calibrateSpeedOdo_LAND_ROVER_DEFENDER_2022(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_LAND_ROVER_DEFENDER_2022(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_MITSUBISHI_L200(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

can_message calibrateSpeedOdo_MITSUBISHI_PAJERO_SPORT(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

can_message calibrateSpeedOdo_GREAT_WALL_POER(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_GREAT_WALL_POER(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_GREAT_WALL_POER(can_message *msg, uint8_t _cruise_mlt);


can_message calibrateSpeedOdo_HONDA_CRV_III(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_HONDA_CRV_III(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_HONDA_CRV_III(can_message *msg, uint8_t _cruise_mlt);

can_message calibrateSpeedOdo_FORD_TRANSIT_2020(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_FORD_TRANSIT_2020(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_FORD_TRANSIT_2020(can_message *msg, uint8_t _cruise_mlt);


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

/***********  MODEL_TOYOTA_LC300  ************/
#define ODO_VAL_MAX_LC300			 		0x3F
#define ODO_VAL_MAX_COUNTER_LC300 64*8
 
typedef struct odometerCounter_LC300{	
	uint32_t counter;
	uint8_t value; 
	uint8_t start;
} odometerCounter_LC300; 


/***********  MODEL_TOYOTA_TUNDRA_2008  ************/ 
#define TOYOTA_ODO_STEP 4

typedef struct tundra_speed{	
	uint8_t low;
	uint8_t high;
} tundra_speed; //creating new type

typedef union un_tundra_speed{
	tundra_speed spval;
	uint16_t hexval;
}un_tundra_speed;

/***********  MODEL_GREAT_WALL_WINGLE7  ************/ 

#define GW_WINGLE_0KMH_REFERENCE 0x20
//#define GW_WINGLE_MAX_SPEED_REFERENCE 0x2D // 0x20

typedef struct chinese_speed{	
	uint8_t high;
	uint8_t low;
} chinese_speed; //creating new type

/***********  MODEL_ISUZU_DMAX  ************/ 

#define INCREMENT_BIT_DMAX_1_23 48
#define INCREMENT_BIT_DMAX_23_M 64
#define INCREMENT_BIT_DMAX_ZERO 0x00D5 //*ISUZU_DMAX_MODIFICATOR/100
#define SPEED23_BIT_MASK_DMAX 0x04E8
#define TIRE_THRESHOLD_KPA_DMAX 0x96
#define SPEEDOMETER_PRECISION_DMAX 8
#define SPEEDOMETER_SCALE_DMAX 10

#define TYRE_PRESSURE_STATUS_OK_DMAX 0

 	typedef struct speed_DMAX{	
	uint8_t data[2];			// Data 0 - first 1- second
} speed_DMAX; //creating new type
	

/***********  MODEL_LAND_ROVER_DEFENDER_2022  ************/ 

#define LR_1_KMH 0x49
#define LR_2_KMH 0x6A
#define LR_3_KMH 0x90
#define LR_4_KMH 0xB5
#define LR_5_KMH 0xFF
#define LR_SP_STEP 0x64

typedef struct land_rover_speed{
	uint8_t hb;
	uint8_t lb;
}land_rover_speed;


/***********  MITSUBISHI      ************/ 

 	typedef struct speed_ML200{	
	uint8_t data[2];			// Data 0 - first 1- second
} speed_ML200; //creating new type


/***************************************************
****************************************************
************* Vehicle specific functions ***********
****************************************************
***************************************************/

/***************************************************
****************************************************
****************** Toyota LC300 ********************
****************************************************
***************************************************/

uint16_t calibrate_speedometer_LC300(uint16_t actualReading, uint32_t mod);
uint16_t convert_KM_H_into_toyota_protocol_LC300(uint32_t speed32);
uint32_t convert_toyota_protocol_into_KM_H_LC300(uint16_t canReading);
uint8_t subtractE3_LC300(uint8_t cur, uint8_t last);
void incE3_LC300(uint8_t *val);
uint8_t calculateOdoValue_LC300(uint32_t counter, uint8_t start);
void increaseOdoCounter_LC300(odometerCounter_LC300 *odo, uint8_t count, uint8_t currentval);
void resetOdoCounter_LC300(odometerCounter_LC300 *odoReal, odometerCounter_LC300 *odoCalibrated, uint32_t mod);
void calibrateOdometer_LC300(odometerCounter_LC300 *odoCalibrated, odometerCounter_LC300 *odoReal, uint32_t mod);

/***************************************************
****************************************************
****************** Toyota TUNDRA2008 ***************
****************************************************
***************************************************/

uint32_t convert_struct_to_kmh(un_tundra_speed sp);
uint16_t convert_kmh_to_struct(const uint32_t speed);
un_tundra_speed recalculate_speed(un_tundra_speed uncal_speed, uint32_t ratio);

/***************************************************
****************************************************
****************** Toyota TUNDRA_2022 **************
****************************************************
***************************************************/

can_message calibrateExtras_TOYOTA_TUNDRA_2022(can_message *msg, uint8_t _mlt);

/***************************************************
****************************************************
********** MODEL_GREAT_WALL_WINGLE7 ****************
****************************************************
***************************************************/

uint32_t chinese_speed_2_kmh(chinese_speed ch_sp);
chinese_speed kmh_2_chinese_speed(uint32_t kmh);
chinese_speed recalculate_chinese_speed(chinese_speed ch_sp, uint32_t mod);

/***************************************************
****************************************************
**********      MODEL_ISUZU_DMAX    ****************
****************************************************
***************************************************/

speed_DMAX calculate_NewSpeed_DMAX(speed_DMAX value, uint8_t mlt);
uint32_t convertSpeedToUint_DMAX(speed_DMAX sp);	
speed_DMAX convertUintToSpeed_DMAX(uint32_t speed_u32);
uint16_t speed2uint16_DMAX(speed_DMAX *speed);
speed_DMAX uint16_2speed_DMAX(uint16_t val16);

/***************************************************
****************************************************
********** MODEL_LAND_ROVER_DEFENDER_2022 **********
****************************************************
***************************************************/

land_rover_speed calculate_cal_speed_LR(land_rover_speed wrong_speed, uint8_t mlt);
land_rover_speed convert_kmh_to_candata_LR(uint16_t kmh);
uint16_t convert_candata_to_kmh_LR(land_rover_speed sp);

/***************************************************
****************************************************
**********           MITSUBISHI           **********
****************************************************
***************************************************/

uint32_t convertSpeedToUint_ML200(speed_ML200 sp);
speed_ML200 convertUint32toSpeed_ML200(uint32_t sp);	
speed_ML200 calculate_NewSpeed_ML200(speed_ML200 value, uint32_t mod);



/***************************************************
****************************************************
**********             Tank 300           **********
****************************************************
***************************************************/

can_message calibrateSpeedOdo_Tank300(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_Tank300(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_Tank300(can_message *msg, uint8_t _cruise_mlt);

/***************************************************
****************************************************
**********             Tank 300           **********
****************************************************
***************************************************/


#endif /* VEHICLE_H_INCLUDED */
