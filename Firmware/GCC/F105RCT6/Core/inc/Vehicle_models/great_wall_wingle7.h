#ifndef VEHICLE_MODELS_GREAT_WALL_WINGLE7_H_INCLUDED
#define VEHICLE_MODELS_GREAT_WALL_WINGLE7_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

#define GW_WINGLE_0KMH_REFERENCE 0x20
//#define GW_WINGLE_MAX_SPEED_REFERENCE 0x2D // 0x20

can_message calibrateSpeedOdo_GREAT_WALL_WINGLE7(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_GREAT_WALL_WINGLE7_H_INCLUDED
