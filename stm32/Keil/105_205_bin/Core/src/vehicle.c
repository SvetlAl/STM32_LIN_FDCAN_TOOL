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
	//	Init_IWDG(STARTUP_TIMEOUT);
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
		vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
		vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
		vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
	}
	
	vehicle->calibrate_extra = &dummy_Cruise;
	
	if(vehicle->model == MODEL_TOYOTA_LC300){																												/* MODEL_TOYOTA_LC300 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		}

	else if(vehicle->model == MODEL_TOYOTA_LC150){																									/* MODEL_TOYOTA_LC150 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		}
		
	else if(vehicle->model == MODEL_TOYOTA_HILUX){																									/* MODEL_TOYOTA_HILUX */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){	
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_odometer = &dummy_SpeedOdo;		/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		}
		
	else if(vehicle->model == MODEL_TOYOTA_TUNDRA_2008){																						/* MODEL_TOYOTA_TUNDRA_2008 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;

		if(mode == VEHICLE_INIT_DEFAULT){		
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;		/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		}		
		
	else if(vehicle->model == MODEL_GREAT_WALL_WINGLE7){																						/* MODEL_GREAT_WALL_WINGLE7 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;		/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;							/* dummy */
		}
		
	else if(vehicle->model == MODEL_DODGE_RAM_2013){																						/* MODEL_DODGE_RAM_2013 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;			/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;							
		}
		
	else if(vehicle->model == MODEL_ISUZU_DMAX_MUX){																				/* MODEL_ISUZU_DMAX_MUX */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;			/* dummy */
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
			vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;			/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		vehicle->calibrate_extra = &dummy_Extras;			
		}
		
	else if(vehicle->model == MODEL_LAND_ROVER_DEFENDER_2022){																	/* MODEL_LAND_ROVER_DEFENDER_2022 */
		vehicle->startup_settings = STARTUP_SETTINGS_DEFAULT;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;			/* dummy */
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;			/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;		
		}
	
	else if(vehicle->model == MODEL_MITSUBISHI_L200){																						/* MODEL_MITSUBISHI_L200 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_speedometer_extra = 0xFFF;
		vehicle->id_odometer = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;			
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;    /* dummy */
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;					/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;		/* dummy */
		}

	else if(vehicle->model == MODEL_MITSUBISHI_PAJERO_SPORT){									/* MODEL_MITSUBISHI_PAJERO_SPORT */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_speedometer_extra = 0xFFF;
		vehicle->id_odometer = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;			
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;    /* dummy */
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;			/* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;				/* dummy */	
		}

	else if(vehicle->model == MODEL_GREAT_WALL_POER){												/* MODEL_GREAT_WALL_POER */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
			vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;				
		vehicle->calibrate_cruise = &dummy_Cruise;						
		vehicle->calibrate_extra = &dummy_Extras;	
		}

	else if(vehicle->model == MODEL_TOYOTA_LC200){															/* MODEL_TOYOTA_LC200 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		}
	
	else if(vehicle->model == MODEL_LEXUS_LX570){															/* MODEL_LEXUS_LX570 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
		}
			
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; 
		vehicle->calibrate_cruise = &dummy_Cruise;
		}			
	
		else if(vehicle->model == MODEL_TOYOTA_TUNDRA_2022){													/* MODEL_TOYOTA_LC300 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
			vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
		}
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		vehicle->calibrate_extra = &dummy_Extras;
		}
		
		else if(vehicle->model == MODEL_TANK_300){																/* MODEL_TANK_300 */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
			vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
		}
		vehicle->calibrate_speedometer = &dummy_SpeedOdo; 
		vehicle->calibrate_odometer = &dummy_SpeedOdo;				
		vehicle->calibrate_cruise = &dummy_Cruise;						
		vehicle->calibrate_extra = &dummy_Extras;	
		}
		
		else if(vehicle->model == MODEL_EXTRA){																	/* MODEL_EXTRA */
		vehicle->startup_settings = STARTUP_SETTINGS_IWDG;
		vehicle->id_speedometer = 0xFFF;
		vehicle->id_odometer = 0xFFF;
		vehicle->id_cruise = 0xFFF;
			
		if(mode == VEHICLE_INIT_DEFAULT){
			vehicle->speedometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->odometer_mlt = NO_CALIBRATION_RATIO;
			vehicle->cruise_mlt = NO_CALIBRATION_RATIO;
			vehicle->tyres_threshold = NO_CALIBRATION_RATIO;
		}
		vehicle->calibrate_speedometer = &dummy_SpeedOdo;
		vehicle->calibrate_odometer = &dummy_SpeedOdo; /* dummy */
		vehicle->calibrate_cruise = &dummy_Cruise;
		vehicle->calibrate_extra = &dummy_Extras;
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


