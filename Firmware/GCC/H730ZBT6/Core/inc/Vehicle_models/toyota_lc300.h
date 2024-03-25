#ifndef VEHICLE_MODELS_TOYOTA_LC300_H_INCLUDED
#define VEHICLE_MODELS_TOYOTA_LC300_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can.h"


/***********  MODEL_TOYOTA_LC300  ************/
#define ODO_VAL_MAX_LC300			 		0x3F
#define ODO_VAL_MAX_COUNTER_LC300 64*8
 
typedef struct odometerCounter_LC300{	
	uint32_t counter;
	uint8_t value; 
	uint8_t start;
	
	uint8_t unused0;
	uint8_t unused1;
} odometerCounter_LC300; 


can_message calibrateSpeedOdo_TOYOTA_LC300(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt);
can_message calibrateCruise_TOYOTA_LC300(can_message *msg, uint8_t _cruise_mlt);


uint16_t calibrate_speedometer_LC300(uint16_t actualReading, uint32_t mod);
uint16_t convert_KM_H_into_toyota_protocol_LC300(uint32_t speed32);
uint32_t convert_toyota_protocol_into_KM_H_LC300(uint16_t canReading);
uint8_t subtractE3_LC300(uint8_t cur, uint8_t last);
void incE3_LC300(uint8_t *val);
uint8_t calculateOdoValue_LC300(uint32_t counter, uint8_t start);
void increaseOdoCounter_LC300(odometerCounter_LC300 *odo, uint8_t count, uint8_t currentval);
void resetOdoCounter_LC300(odometerCounter_LC300 *odoReal, odometerCounter_LC300 *odoCalibrated, uint32_t mod);
void calibrateOdometer_LC300(odometerCounter_LC300 *odoCalibrated, odometerCounter_LC300 *odoReal, uint32_t mod);


#endif // VEHICLE_MODELS_TOYOTA_LC300_H_INCLUDED
