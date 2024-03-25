#ifndef VEHICLE_MODELS_DODGE_RAM2013_H_INCLUDED
#define VEHICLE_MODELS_DODGE_RAM2013_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

can_message calibrateSpeedOdo_DODGE_RAM_2013(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_DODGE_RAM_2013(can_message *msg, uint8_t _cruise_mlt);

#endif // VEHICLE_MODELS_DODGE_RAM2013_H_INCLUDED
