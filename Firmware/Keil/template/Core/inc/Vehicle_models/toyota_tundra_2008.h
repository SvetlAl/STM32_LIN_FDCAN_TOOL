#ifndef VEHICLE_MODELS_TOYOTA_TUNDRA_2008_H_INCLUDED
#define VEHICLE_MODELS_TOYOTA_TUNDRA_2008_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

typedef struct tundra_speed{	
	uint8_t low;
	uint8_t high;
} tundra_speed; //creating new type

typedef union un_tundra_speed{
	tundra_speed spval;
	uint16_t hexval;
}un_tundra_speed;


can_message calibrateSpeedOdo_TUNDRA_2008(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_TOYOTA_LC150_H_INCLUDED
