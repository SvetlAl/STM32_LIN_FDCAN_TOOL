#ifndef VEHICLE_MODELS_JEEP_GCHER_2017_H_INCLUDED
#define VEHICLE_MODELS_JEEP_GCHER_2017_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

can_message calibrateCruise_JEEP_GCHER_2017(can_message *msg, uint8_t _cruise_mlt);

#endif // VEHICLE_MODELS_JEEP_GCHER_2017_H_INCLUDED
