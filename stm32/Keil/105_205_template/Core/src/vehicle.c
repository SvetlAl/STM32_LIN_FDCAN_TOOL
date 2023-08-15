#include "vehicle.h"

/***************************************************
****************************************************
************* Vehicle specific vars ****************
****************************************************
***************************************************/
//VehicleStruct theVehicle;
#include "flash_mem_chip_spi.h"
#include "user_cmd.h"

/***************************************************
****************************************************
************* Standart format vars *****************
****************************************************
***************************************************/


VehicleStructData loadVehicle(uint8_t *buf){
	VehicleStructData load;
	for(uint32_t i = 0; i < VEHICLE_STATUS_SETTINGS_LENGTH; i++){
		load.data[i] = buf[i];
	}	
	load._vehicleStruct.modes = 0x00;
	return load;
}


void initVehicleSettings(VehicleStructData *vhcl){
	uint32_t length = VEHICLE_STATUS_SETTINGS_LENGTH;
	uint32_t addr = VEHICLE_SETTINGS_ADDRESS;
	memory_chip_status.memchip_state = VEHICLE_STATUS_SETTINGS_LENGTH;
	
	read_memchip(&memory_chip_status, addr, vhcl->data, length, SPI_no_Dma);	
		
	if(vhcl->_vehicleStruct.model < MODEL_COUNT){
		initVehicle(&vhcl->_vehicleStruct, VEHICLE_INIT_PRESET);
	}
	
	else if(vhcl->_vehicleStruct.model >= MODEL_COUNT){
		vhcl->_vehicleStruct.model = MODEL_TOYOTA_LC300;
		initVehicle(&vhcl->_vehicleStruct, VEHICLE_INIT_DEFAULT);
	}
	
	if(vhcl->_vehicleStruct.startup_settings & STARTUP_SETTINGS_IWDG){
		#ifndef DEBUG_MODE
		Init_IWDG(STARTUP_TIMEOUT);
		#endif
	}
}


void initVehicle(VehicleStruct *vehicle, uint8_t mode){

	vehicle->startup_settings = STARTUP_SETTINGS_DEFAULT;
	vehicle->modes = 0x00;
	
	/*********** DEFAULT ****************/
	vehicle->id_speedometer = 0xFFF;
	vehicle->id_speedometer_extra = 0xFFF;
	vehicle->id_odometer = 0xFFF;
	vehicle->id_cruise = 0xFFF;
	
	if(mode == VEHICLE_INIT_DEFAULT){
		vehicle->speedometer_mlt = 0x64;
		vehicle->odometer_mlt = 0x64;
		vehicle->cruise_mlt = 0x64;
		vehicle->tyres_threshold = 0x64;
	}
	
	vehicle->calibrate_extra = &dummy_Cruise;
	
	if(vehicle->model == MODEL_EXTRA_I){																	/* MODEL_EXTRA_I */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0x000;
		vehicle->id_odometer = 0x000;
		vehicle->id_cruise = 0x000;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = 0x064;
			vehicle->odometer_mlt = 0x064;
			vehicle->cruise_mlt = 0x64;
			vehicle->tyres_threshold = 0x64;
		}
		vehicle->calibrate_speedometer = &calibrateSpeedOdo_MODEL_EXTRA_I;
		vehicle->calibrate_odometer = &calibrateSpeedOdo_MODEL_EXTRA_I; /* dummy */
		vehicle->calibrate_cruise = &calibrateCruise_MODEL_EXTRA_I;
		vehicle->calibrate_extra = &calibrateExtras_MODEL_EXTRA_I;
		}		

		else if(vehicle->model == MODEL_EXTRA_II){																	/* MODEL_EXTRA_II */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0x000;
		vehicle->id_odometer = 0x000;
		vehicle->id_cruise = 0x000;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = 0x064;
			vehicle->odometer_mlt = 0x064;
			vehicle->cruise_mlt = 0x64;
			vehicle->tyres_threshold = 0x64;
		}
		vehicle->calibrate_speedometer = &calibrateSpeedOdo_MODEL_EXTRA_II;
		vehicle->calibrate_odometer = &calibrateSpeedOdo_MODEL_EXTRA_II; /* dummy */
		vehicle->calibrate_cruise = &calibrateCruise_MODEL_EXTRA_II;
		vehicle->calibrate_extra = &calibrateExtras_MODEL_EXTRA_II;
		}
		
	else if(vehicle->model == MODEL_EXTRA_III){																	/* MODEL_EXTRA_III */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0x000;
		vehicle->id_odometer = 0x000;
		vehicle->id_cruise = 0x000;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = 0x064;
			vehicle->odometer_mlt = 0x064;
			vehicle->cruise_mlt = 0x64;
			vehicle->tyres_threshold = 0x64;
		}
		vehicle->calibrate_speedometer = &calibrateSpeedOdo_MODEL_EXTRA_III;
		vehicle->calibrate_odometer = &calibrateSpeedOdo_MODEL_EXTRA_III; /* dummy */
		vehicle->calibrate_cruise = &calibrateCruise_MODEL_EXTRA_III;
		vehicle->calibrate_extra = &calibrateExtras_MODEL_EXTRA_III;
		}		
			
}

can_message dummy_SpeedOdo(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	UNUSED(msg);
	UNUSED(_speedometer_mlt);
	UNUSED(_odometer_mlt);
	return *msg;
}

can_message dummy_Cruise(can_message *msg, uint8_t _cruise_mlt){
	UNUSED(_cruise_mlt);
	UNUSED(msg);
	return *msg;
}

can_message dummy_Extras(can_message *msg, uint8_t _mlt){
	UNUSED(_mlt);
	UNUSED(msg);
	return *msg;
}




/***************************************************
****************************************************
**********					MODEL_EXTRA_I	    		 *********
****************************************************
***************************************************/

can_message calibrateSpeedOdo_MODEL_EXTRA_I(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	return dummy_SpeedOdo(msg, _speedometer_mlt, _odometer_mlt);
}
can_message calibrateExtras_MODEL_EXTRA_I(can_message *msg, uint8_t _mlt){
	return dummy_Extras(msg, _mlt);
}
can_message calibrateCruise_MODEL_EXTRA_I(can_message *msg, uint8_t _cruise_mlt){
	return dummy_Extras(msg, _cruise_mlt);
}

/***************************************************
****************************************************
**********					MODEL_EXTRA_II    		 *********
****************************************************
***************************************************/
can_message calibrateSpeedOdo_MODEL_EXTRA_II(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	return dummy_SpeedOdo(msg, _speedometer_mlt, _odometer_mlt);
}
can_message calibrateExtras_MODEL_EXTRA_II(can_message *msg, uint8_t _mlt){
	return dummy_Extras(msg, _mlt);
}
can_message calibrateCruise_MODEL_EXTRA_II(can_message *msg, uint8_t _cruise_mlt){
	return dummy_Extras(msg, _cruise_mlt);
}

/***************************************************
****************************************************
**********					MODEL_EXTRA_III    		 *********
****************************************************
***************************************************/
can_message calibrateSpeedOdo_MODEL_EXTRA_III(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	return dummy_SpeedOdo(msg, _speedometer_mlt, _odometer_mlt);
}
can_message calibrateExtras_MODEL_EXTRA_III(can_message *msg, uint8_t _mlt){
	return dummy_Extras(msg, _mlt);
}
can_message calibrateCruise_MODEL_EXTRA_III(can_message *msg, uint8_t _cruise_mlt){
	return dummy_Extras(msg, _cruise_mlt);
}	

/***************************************************
****************************************************
*********    MODEL_NISSAN_PATROL_2020      *********
****************************************************
***************************************************/
can_message calibrateSpeedOdo_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _speedometer_mlt, uint8_t _odometer_mlt){
	uint16_t speed_reading = (uint16_t)((uint16_t)(msg->data[4] << 8) | (uint16_t)(msg->data[5] &~0xFF00));
	uint16_t calibrated_speed_reading = (uint16_t)((speed_reading*_speedometer_mlt)/100);
	msg->data[4] = (uint8_t)((calibrated_speed_reading &~0x00FF) >> 8);
	msg->data[5] = (uint8_t)((calibrated_speed_reading &~0xFF00) >> 0);
	UNUSED(_odometer_mlt);
	
	return *msg;
}
can_message calibrateExtras_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _mlt){
	return dummy_Extras(msg, _mlt);
}
can_message calibrateCruise_MODEL_NISSAN_PATROL_2020(can_message *msg, uint8_t _cruise_mlt){
	return dummy_Extras(msg, _cruise_mlt);
}	
	
	
