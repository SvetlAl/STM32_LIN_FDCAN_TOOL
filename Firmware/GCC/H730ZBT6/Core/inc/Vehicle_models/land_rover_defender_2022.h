#ifndef VEHICLE_MODELS_LAND_ROVER_DEFENDER_H_INCLUDED
#define VEHICLE_MODELS_LAND_ROVER_DEFENDER_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

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


can_message calibrateSpeedOdo_LAND_ROVER_DEFENDER_2022(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_LAND_ROVER_DEFENDER_2022(can_message *msg, uint8_t _cruise_mlt);

#endif // VEHICLE_MODELS_LAND_ROVER_DEFENDER_H_INCLUDED
