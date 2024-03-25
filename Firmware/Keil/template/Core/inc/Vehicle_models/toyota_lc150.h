#ifndef VEHICLE_MODELS_TOYOTA_LC150_H_INCLUDED
#define VEHICLE_MODELS_TOYOTA_LC150_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

can_message calibrateSpeedOdo_TOYOTA_LC150(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_TOYOTA_LC150_H_INCLUDED
