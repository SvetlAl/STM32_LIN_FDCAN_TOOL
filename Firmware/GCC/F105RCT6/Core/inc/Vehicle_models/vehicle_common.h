#ifndef VEHICLE_MODELS_COMMON_H_INCLUDED
#define VEHICLE_MODELS_COMMON_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

#define NO_CALIBRATION_RATIO          (uint8_t)((uint8_t)0x64)
#define TOYOTA_ODO_STEP               4

#define UNUSED(x)                     (void)(x)
	

//============================== Toyota ==============================
uint8_t calculateToyotaCheckSum(can_message *msg);



//============================== Great Wall ========================== 
typedef struct chinese_speed{	
	uint8_t high;
	uint8_t low;
} chinese_speed; //creating new type

uint32_t chinese_speed_2_kmh(chinese_speed ch_sp);
chinese_speed kmh_2_chinese_speed(uint32_t kmh);
chinese_speed recalculate_chinese_speed(chinese_speed ch_sp, uint32_t mod);

uint8_t calculateTankCheckSum(uint8_t val_1, uint8_t val_2,uint8_t *data, uint8_t dlc) ;
void calibrateSpeedOdo_Tank(uint8_t *data, uint32_t model, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_COMMON_H_INCLUDED
