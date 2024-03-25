#ifndef VEHICLE_MODELS_MITSUBISHI_L200_PJRSPRT_H_INCLUDED
#define VEHICLE_MODELS_MITSUBISHI_L200_PJRSPRT_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

typedef struct speed_ML200{	
	uint8_t data[2];			// Data 0 - first 1- second
} speed_ML200; //creating new type


can_message calibrateSpeedOdo_MITSUBISHI_L200(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateSpeedOdo_MITSUBISHI_PAJERO_SPORT(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_MITSUBISHI_L200_PJRSPRT_H_INCLUDED
