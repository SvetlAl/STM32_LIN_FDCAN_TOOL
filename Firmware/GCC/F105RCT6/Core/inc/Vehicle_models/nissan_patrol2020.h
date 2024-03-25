#ifndef VEHICLE_MODELS_NISSAN_PATROL2020_H_INCLUDED
#define VEHICLE_MODELS_NISSAN_PATROL2020_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"


can_message calibrateSpeedOdo_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateExtras_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _mlt);
can_message calibrateCruise_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _cruise_mlt);

#endif // VEHICLE_MODELS_NISSAN_PATROL2020_H_INCLUDED
