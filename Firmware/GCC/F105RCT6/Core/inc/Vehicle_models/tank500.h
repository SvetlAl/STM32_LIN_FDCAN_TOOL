#ifndef VEHICLE_MODELS_TANK500_H_INCLUDED
#define VEHICLE_MODELS_TANK500_H_INCLUDED

#include "device_model.h"

void fdcan_TANK500_calibrate_speed_odo      (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
void fdcan_TANK500_calibrate_odometer       (uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
void fdcan_TANK500_calibrate_cruise         (uint8_t *msg_data, uint8_t siz, uint8_t _cruise_mlt);
void fdcan_TANK500_calibrate_extra          (uint8_t *msg, uint32_t id, uint8_t _threshold_mlt);

void fdcan_test_TANK500_calibrate_speed_odo(uint8_t *msg_data, uint8_t siz, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);

#endif // VEHICLE_MODELS_TANK500_H_INCLUDED
