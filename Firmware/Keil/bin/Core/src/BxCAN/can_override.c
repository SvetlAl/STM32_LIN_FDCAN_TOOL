//*****************************************************************
// 
// STM32F105/205
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************

#include "BxCAN/can_override.h"
#include "vehicle.h"

#ifdef MEMCHIP_NOR_FLASH
//#include "Flash_memchip/flash_nor_mem_chip_spi.h"
#endif

//===============================================================================================
//==================================== GLOBAL VAR & setter/getter ===============================
//===============================================================================================
#ifdef SUPPORT_BXCAN
static u_can_override_status theOverrideStatus;

can_override_status *can_override_get_status(){
	return &theOverrideStatus.status;
}
uint8_t *can_override_get_dataptr(){
	return &theOverrideStatus.raw_data[0];
}
#endif

//===============================================================================================
//======================================== Initialization =======================================
//===============================================================================================


//===============================================================================================
//============================================ Override =========================================
//===============================================================================================
/**
* brief  Calibration (user function override) from CAN1 to CAN2    
* param  can_override_status var 
* param  
* retval 
*/

void can_override_calibrate(can_message *newMessage){
/*************** ID matches vehicle's speedometer id. Speed can be found in one or two id's ***********************/
		if((CAN_ID(newMessage) == vehicle_spd_id()) |
			(CAN_ID(newMessage) == vehicle_ext_id())){
				
				/* set odometer MLT. 0x00 if frozen */
				uint8_t odo_mlt = (vehicle_modes() & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : vehicle_odo_mlt();
				/***************************************************************/
				/************************ TEST SECTION *************************/
				/***************************************************************/
			if(vehicle_modes() & CALIBRATOR_TEST_MODE){
				if((vehicle_model() != MODEL_GREAT_WALL_WINGLE7) & (vehicle_model() != MODEL_DODGE_RAM_2013)){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE;
				}
				else if (vehicle_model() == MODEL_GREAT_WALL_WINGLE7){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE_GW;
				}
				else if (vehicle_model() == MODEL_DODGE_RAM_2013){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE_DR;
				}
			}
			
			else{	
				vehicle_calibrate_spd(newMessage, odo_mlt);
			}					
		}		
			
		/*************** ID matches vehicle's odometer id and SPEED and ODO are different ID's ***********************/
		if((CAN_ID(newMessage) == vehicle_odo_id()) &
			(vehicle_odo_id() != vehicle_spd_id())){
				/* set odometer MLT. 0x00 if frozen */
				uint8_t odo_mlt = (vehicle_modes() & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : vehicle_odo_mlt();
				vehicle_calibrate_odo(newMessage, odo_mlt);
			}	
		
		/*************** ID matches vehicle's cruise id ***********************/
		if(CAN_ID(newMessage) == vehicle_crs_mlt()){
			vehicle_calibrate_crs(newMessage);
		}
		
		/*************** EXTRA calibration for ISUZU DMAX and GW POER ***********************/
		if(vehicle_model() == MODEL_ISUZU_DMAX_MUX || vehicle_model() == MODEL_GREAT_WALL_POER || vehicle_model() == MODEL_TOYOTA_TUNDRA_2022 || vehicle_model() == MODEL_EXTRA_III ){
			vehicle_calibrate_ext(newMessage);
		}
}

/**
* brief  Calibration (user function override) from CAN2 to CAN1    
* param  can_override_status var 
* param  
* retval 
*/
void can_override_proc_reverse_calibrate(can_message *newMessage){
	#ifdef SUPPORT_TUNDRA_ENGLISH_MULTIMEDIA
	if(vehicle_model() == MODEL_TOYOTA_TUNDRA_2022){
		reverse_calibrateExtras_TOYOTA_TUNDRA_2022(newMessage);
	}
	#endif
	#ifndef SUPPORT_TUNDRA_ENGLISH_MULTIMEDIA
	UNUSED(newMessage);
	#endif
}


/********************************************************************************************/
/************************************ 	Override procedure 	*********************************/
/********************************************************************************************/
/**
* brief  Apply a custom filter to a message coming through the gateway
* param  CAN num (from CAN1 to CAN2 or from CAN2 to CAN1)
* param  CAN message pointer
* retval PROCESS_MSG - keep a message
* retval DISCARD_MSG - discard a message, do not send further
*/
#ifdef SUPPORT_BXCAN
uint32_t can_override_process_filters(can_message *newMessage, uint32_t _can_num /* CAN1 or CAN2 */){
	if(MEMORY_PROGRAMM_MODE != DEVICE_OPERATION_MODE_OFF) return PROCESS_MSG;
	/* How many Id's to skip */
	if(theOverrideStatus.status.ignored_id_num >0){
		
		for(uint32_t i = 0; i < theOverrideStatus.status.ignored_id_num; i++){
			uint32_t ignored_id = (uint32_t)(newMessage->ide == EXT_ID ? theOverrideStatus.status.ignored_ids[i].ext_id : (uint32_t)((theOverrideStatus.status.ignored_ids[i].std_id.id_highbyte << 8) | theOverrideStatus.status.ignored_ids[i].std_id.id_lowbyte) );
			if(_can_num == 1){
				if((CAN_ID(newMessage) == ignored_id) & ((theOverrideStatus.status.ignored_id_dirs_msk & (1 << i)) != (1 << i)) ) return DISCARD_MSG;
			}
			else if (_can_num == 2){
				if((CAN_ID(newMessage) == ignored_id) & ((theOverrideStatus.status.ignored_id_dirs_msk & (1 << i)) == (1 << i)) ) return DISCARD_MSG;
			}
		} // for
	}
	
	if(theOverrideStatus.status.overrided_id_num >0){
		
		for(uint32_t i = 0; i < theOverrideStatus.status.overrided_id_num; i++){
			uint32_t overrided_id = (uint32_t)(newMessage->ide == EXT_ID ? theOverrideStatus.status.filters[i].id.ext_id : (uint32_t)((theOverrideStatus.status.filters[i].id.std_id.id_highbyte << 8) | theOverrideStatus.status.filters[i].id.std_id.id_lowbyte) );
			
			/*** Id matches ***/
			if(CAN_ID(newMessage) == overrided_id){
				
				if((_can_num == 1) & ((theOverrideStatus.status.overrided_id_dirs_msk & (1 << i)) == (1 << i)) ) return PROCESS_MSG;
				if((_can_num == 2) & ((theOverrideStatus.status.overrided_id_dirs_msk & (1 << i)) != (1 << i)) ) return PROCESS_MSG;
									
				for(uint8_t k = 0; k < newMessage->dlc; k++){
						if((theOverrideStatus.status.override_msks[i] & (1 << k)) == (1 << k)) 
							newMessage->data[k] = theOverrideStatus.status.filters[i].override_data[k];
				} // for
			}
		} // for
	}	
	return PROCESS_MSG;
}
#endif // SUPPORT_BXCAN






