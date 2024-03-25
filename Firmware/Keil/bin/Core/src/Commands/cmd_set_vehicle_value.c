#include "Commands/cmd_set_vehicle_value.h"
#include "Commands/user_cmd.h"

void set_vehicle_value(uint32_t cmd, uint32_t _value){
	switch(cmd){
		case ELP_VEHICLE_SET_MODEL:
		  vehicle_set_model((uint16_t)_value, VEHICLE_INIT_DEFAULT);
			break;

		/* Applying a mask: uint32_t value 0x00001234, 0x12 - is a mask to "&= ~", 34 is a mask to "|= "*/
		case ELP_VEHICLE_SET_TEST_MODE:	/* deprecated */
		case ELP_VEHICLE_SET_MODE:{
			uint8_t setMask = SC_BYTE_FROM32BIT(_value, 3);
			uint8_t resetMask = SC_BYTE_FROM32BIT(_value, 2);	
      uint8_t _modes = vehicle_modes();
			_modes = (uint8_t)(_modes & ~resetMask);
			_modes |= setMask;
			vehicle_set_modes(_modes);
			break;}
			
			
		case ELP_VEHICLE_SET_SPEEDOMETER_MLT:
			vehicle_set_spd_mlt((uint8_t)(_value));
			break;
		
		case ELP_VEHICLE_SET_ODOMETER_MLT:
			vehicle_set_odo_mlt((uint8_t)(_value));
			break;
		
		case ELP_VEHICLE_SET_CRUISE_MLT:
			vehicle_set_crs_mlt((uint8_t)(_value));
			break;
		
		case ELP_VEHICLE_SET_TYRES_THRESHOLD:
			vehicle_set_tyr_thr((uint8_t)(_value));
			break;
		
		default:
		break;			
	}
}
