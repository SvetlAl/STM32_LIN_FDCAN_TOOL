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
#include "BxCAN/can_macros.h"


#ifdef SUPPORT_SPEEDO_CALIBRATOR
#include "Vehicle_models/vehicle_common.h"

#include "Vehicle_models/toyota_lc300.h"
#include "Vehicle_models/toyota_lc150.h"
#include "Vehicle_models/great_wall_wingle7.h"
#include "Vehicle_models/toyota_tundra_2008.h"
#include "Vehicle_models/toyota_tundra_2022.h"
#include "Vehicle_models/dodge_ram2013.h"
#include "Vehicle_models/isuzu_dmax_mux.h"
#include "Vehicle_models/land_rover_defender_2022.h"
#include "Vehicle_models/mitsubishi_l200_pjrsprt.h"
#include "Vehicle_models/great_wall_poer.h"
#include "Vehicle_models/nissan_patrol2020.h"
#include "Vehicle_models/ford_transit2020.h"
#include "Vehicle_models/honda_crv2006.h"
#include "Vehicle_models/extra.h"
#include "Vehicle_models/tank300.h"
#include "Vehicle_models/jeep_g_cherokee_2017.h"

#ifdef SUPPORT_FDCAN
#include "Vehicle_models/tank500.h"
#endif // SUPPORT_FDCAN

#endif // SUPPORT_SPEEDO_CALIBRATOR

#define UNUSED(x) (void)(x)

#define VEHICLE_MODEL(vhcl)                     (uint16_t) (vhcl._vehicleStruct.model)
#define VEHICLE_MODES(vhcl)                     (uint8_t)  (vhcl._vehicleStruct.modes)

#define ODO_MLT(vhcl)                           (uint8_t)  (vhcl._vehicleStruct.odometer_mlt)
#define SPEED_MLT(vhcl)                         (uint8_t)  (vhcl._vehicleStruct.speedometer_mlt)
#define CRUISE_MLT(vhcl)                        (uint8_t)  (vhcl._vehicleStruct.cruise_mlt)
#define TYRES_THRESHOLD(vhcl)                   (uint8_t)  (vhcl._vehicleStruct.tyres_threshold)

#define SPEEDOMETER_ID(vhcl)                    (uint32_t) (vhcl._vehicleStruct.id_speedometer)
#define ODOMETER_ID(vhcl)                       (uint32_t) (vhcl._vehicleStruct.id_odometer)
#define CRUISE_ID(vhcl)                         (uint32_t) (vhcl._vehicleStruct.id_cruise)
#define EXTRAS_ID(vhcl)                         (uint32_t) (vhcl._vehicleStruct.id_speedometer_extra)

#define CALIBRATE_SPEEDOMETER(vhcl, msg, odo_mlt)  (vhcl._vehicleStruct.calibrate_speedometer   (msg, vhcl._vehicleStruct.speedometer_mlt, odo_mlt))
#define CALIBRATE_ODOMETER(vhcl, msg, odo_mlt)     (vhcl._vehicleStruct.calibrate_odometer      (msg, vhcl._vehicleStruct.speedometer_mlt, odo_mlt))
#define CALIBRATE_CRUISE(vhcl, msg)                (vhcl._vehicleStruct.calibrate_cruise        (msg, vhcl._vehicleStruct.cruise_mlt))
#define CALIBRATE_EXTRAS(vhcl, msg)                (vhcl._vehicleStruct.calibrate_extra         (msg, vhcl._vehicleStruct.tyres_threshold))

#ifdef SUPPORT_FDCAN
#define FDCAN_CALIBRATE_SPEEDOMETER(data, siz, odo_mlt)  (theVehicle._vehicleStruct.fdcan_calibrate_speedometer (data, siz, theVehicle._vehicleStruct.speedometer_mlt, odo_mlt))
#define FDCAN_CALIBRATE_ODOMETER(data, siz, odo_mlt)     (theVehicle._vehicleStruct.fdcan_calibrate_odometer    (data, siz, theVehicle._vehicleStruct.speedometer_mlt, odo_mlt))
#define FDCAN_CALIBRATE_CRUISE(data, siz)                (theVehicle._vehicleStruct.fdcan_calibrate_cruise      (data, siz, theVehicle._vehicleStruct.cruise_mlt))
#define FDCAN_CALIBRATE_EXTRAS(id, msg)                  (theVehicle._vehicleStruct.fdcan_calibrate_extra       (msg, id,   theVehicle._vehicleStruct.tyres_threshold))
#endif // SUPPORT_FDCAN


/***************************************************
****************************************************
************* Standart format defs  ****************
****************************************************
***************************************************/
#define VEHICLE_INIT_PRESET 		        1U
#define VEHICLE_INIT_DEFAULT 		        2U

#define VEHICLE_STATUS_SETTINGS_LENGTH	8U

#define STARTUP_SETTINGS_DEFAULT        0x00
#define STARTUP_SETTINGS_IWDG           0x01
#define STARTUP_SETTINGS_FDCAN          0x02


#define CALIBRATOR_DEFAULT_MODE         0x00
#define CALIBRATOR_ODO_FREEZE_MODE      0x01
#define CALIBRATOR_TEST_MODE            0x02

#define SPEEDOMETER_TEST_VALUE          0x2C
#define SPEEDOMETER_TEST_VALUE_GW       0x2C // 0x9C
#define SPEEDOMETER_TEST_VALUE_DR       0x9C
#define TYRES_THRES_DFLT_VALUE_TNK300   0x80

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
#define MODEL_UAZ_PATRIOT               0x0014
#define MODEL_JEEP_GCHER_2017           0x0015
#define MODEL_EXTRA_I                   0x0016
#define MODEL_EXTRA_II                  0x0017
#define MODEL_EXTRA_III                 0x0018

#define MODEL_COUNT                     0x0019

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
	
	#ifdef SUPPORT_FDCAN
	void (*fdcan_calibrate_speedometer)    (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
	void (*fdcan_calibrate_odometer)       (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t odometer_mlt);
	void (*fdcan_calibrate_cruise)         (uint8_t *msg_data, uint8_t siz, uint8_t _cruise_mlt);
	void (*fdcan_calibrate_extra)          (uint8_t *msg, uint32_t id, uint8_t _threshold_mlt);
	#endif // SUPPORT_FDCAN
} VehicleStruct; //creating new type

typedef union VehicleStructData{
	VehicleStruct _vehicleStruct;
	uint8_t data[sizeof(VehicleStruct)];
}VehicleStructData;

//===============================================================================================
//================================ Load and init functions ======================================
//===============================================================================================
uint32_t initVehicleSettings(void);

//===============================================================================================
//=================================== Vehicle access functions ==================================
//===============================================================================================
uint32_t vehicle_startup_settings(void);

uint16_t vehicle_model  (void);
uint8_t  vehicle_modes  (void);
uint8_t  vehicle_odo_mlt(void);
uint8_t  vehicle_spd_mlt(void);
uint8_t  vehicle_crs_mlt(void);
uint8_t  vehicle_tyr_thr(void);
uint32_t vehicle_spd_id (void);
uint32_t vehicle_odo_id (void);
uint32_t vehicle_crs_id (void);
uint32_t vehicle_ext_id (void);

void vehicle_calibrate_spd(can_message *msg, uint8_t _odo_mlt);
void vehicle_calibrate_odo(can_message *msg, uint8_t _odo_mlt);
void vehicle_calibrate_crs(can_message *msg);
void vehicle_calibrate_ext(can_message *msg);

#ifdef SUPPORT_FDCAN
void fdcan_vehicle_calibrate_spd(uint8_t *msg, uint16_t data_sz, uint8_t _odo_mlt);
void fdcan_vehicle_calibrate_odo(uint8_t *msg, uint16_t data_sz, uint8_t _odo_mlt);
void fdcan_vehicle_calibrate_crs(uint8_t *msg, uint16_t data_sz);
void fdcan_vehicle_calibrate_ext(uint32_t id, uint8_t *msg_data);
#endif // SUPPORT_FDCAN

void vehicle_set_model  (uint16_t val, uint8_t mode);
void vehicle_set_modes  (uint8_t val);
void vehicle_set_odo_mlt(uint8_t val);
void vehicle_set_spd_mlt(uint8_t val);
void vehicle_set_crs_mlt(uint8_t val);
void vehicle_set_tyr_thr(uint8_t val);

//===============================================================================================
//=================================== Setters/getters ===========================================
//===============================================================================================
uint8_t *get_vehicle_settings_data(void);

#endif /* VEHICLE_H_INCLUDED */
