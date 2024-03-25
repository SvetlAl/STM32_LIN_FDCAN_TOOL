#ifndef VEHICLE_MODELS_ISUZU_DMAX_MUX_H_INCLUDED
#define VEHICLE_MODELS_ISUZU_DMAX_MUX_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

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
	

can_message calibrateSpeedOdo_ISUZU_DMAX_MUX(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_ISUZU_DMAX_MUX(can_message *msg, uint8_t _cruise_mlt);
can_message calibrateExtras_ISUZU_DMAX_MUX(can_message *msg, uint8_t _mlt);

#endif // VEHICLE_MODELS_ISUZU_DMAX_MUX_H_INCLUDED
