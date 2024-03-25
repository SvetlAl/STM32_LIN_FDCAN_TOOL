#ifndef VEHICLE_MODELS_TOYOTA_TUNDRA_2022_H_INCLUDED
#define VEHICLE_MODELS_TOYOTA_TUNDRA_2022_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"

can_message calibrateExtras_TOYOTA_TUNDRA_2022(can_message *msg, uint8_t _mlt);
can_message reverse_calibrateExtras_TOYOTA_TUNDRA_2022(can_message *msg);
void extra_broadcast_TOYOTA_TUNDRA_2022(void);

#endif // VEHICLE_MODELS_TOYOTA_LC150_H_INCLUDED
