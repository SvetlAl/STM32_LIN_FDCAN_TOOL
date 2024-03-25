/****************************************************************
* 
* Can override and scanner functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*
*
*
*
*****************************************************************/

#include "device_model.h"
#ifdef SUPPORT_FDCAN

#include "FDCAN/fdcan.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan_can_override.h"
#include "FDCAN/fdcan_buffer.h"
#include "vehicle.h"

u_fdcan_filter theFdcanFilter;

#define FDCAN_FILTER_CAN1_OUT (theFdcanFilter.filter.hdr.input_dir == FDCAN_filter_dir_2i1o || theFdcanFilter.filter.hdr.input_dir == FDCAN_filter_dir_both)
#define FDCAN_FILTER_CAN2_OUT (theFdcanFilter.filter.hdr.input_dir == FDCAN_filter_dir_1i2o || theFdcanFilter.filter.hdr.input_dir == FDCAN_filter_dir_both)

//========================================================================================
//===========================   The Vehicle global var  ==================================
//========================================================================================
uint8_t *fdcan_get_filter_ptr(void){
	return &theFdcanFilter.data[0];
}

//========================================================================================
//===========================   Apply FD CAN filter     ==================================
//========================================================================================


/**
* brief  Calibration (user function override) from CAN1 to CAN2    
* param  can_override_status var 
* param  
* retval 
*/
void fdcan_can_override_calibrate(uint8_t* msg){
	u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*) msg;
	const fdcan_message_hdr *msg_hdr = &msg_ptr->msg_hdr;
	uint16_t data_sz = (uint16_t)FDCAN_FD_MSG_LENGTH(msg_hdr);
	//uint16_t total_message_size = (uint16_t)(data_sz + sizeof(fdcan_message_hdr));
	uint8_t *data_pos = (uint8_t *)(msg + sizeof(fdcan_message_hdr));
	
	if((msg_hdr->id == vehicle_spd_id()) | (msg_hdr->id == vehicle_ext_id())){
		/* set odometer MLT. 0x00 if frozen */
		uint8_t odo_mlt = (vehicle_modes() & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : vehicle_odo_mlt();
		uint8_t spd_mlt = vehicle_spd_mlt();
		/***************************************************************/
		/************************ TEST SECTION *************************/
		/***************************************************************/
		if(vehicle_modes() & CALIBRATOR_TEST_MODE){
			if (vehicle_model() == MODEL_TANK_500){
				if(msg_hdr->id == vehicle_spd_id()){
					#ifdef SUPPORT_SPEEDO_CALIBRATOR
					fdcan_test_TANK500_calibrate_speed_odo(data_pos, data_sz, spd_mlt, odo_mlt);
					#endif
				}
			}
		} // CALIBRATOR_TEST_MODE
		
		else{	
			fdcan_vehicle_calibrate_spd(data_pos, data_sz, odo_mlt);
		}					
	}//  (msg_hdr->id == vehicle_spd_id()) | (msg_hdr->id == EXTRAS_ID(theVehicle)
			
		/*************** ID matches vehicle's odometer id and SPEED and ODO are different ID's ***********************/
	
	if((msg_hdr->id == vehicle_odo_id()) & (vehicle_odo_id() != vehicle_spd_id())){
		/* set odometer MLT. 0x00 if frozen */
		uint8_t odo_mlt = (vehicle_modes() & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : vehicle_odo_mlt();
		fdcan_vehicle_calibrate_odo(data_pos, data_sz, odo_mlt);
	}	
		
		/*************** ID matches vehicle's cruise id ***********************/
	if(msg_hdr->id  == vehicle_crs_id()){
		fdcan_vehicle_calibrate_crs(data_pos, data_sz);
	}
		/*************** EXTRA calibration for ISUZU DMAX and GW POER ***********************/
	if(vehicle_model() == MODEL_TANK_500){
		fdcan_vehicle_calibrate_ext(msg_hdr->id, msg);
	}
}


uint8_t filter_condition_match(uint16_t can_num, uint32_t _id){
	if((_id < theFdcanFilter.filter.hdr.id_begin) | (_id > theFdcanFilter.filter.hdr.id_end)) return 0;
	if((can_num == FDCAN1_E) && FDCAN_FILTER_CAN1_OUT){
		return 0xFF;
	}
	else if((can_num == FDCAN2_E) && FDCAN_FILTER_CAN2_OUT){
		return 0xFF;
	}
	
	else return 0;
}


void fdcan_apply_filter(uint16_t can_num, uint16_t data_sz){
	const uint8_t *start_data_pos = (uint8_t *)(FDCAN_TX_BUF_R_POS_PTR(can_num) + sizeof(fdcan_message_hdr));
	for (uint16_t k = 0; k < data_sz; k++){
		
		eFdcanByteFilterMethod method = theFdcanFilter.filter.filter_byte[k].method;
		uint8_t *data_pos = (uint8_t *)(start_data_pos + k);
		
		if(method == FDCAN_filter_method_const){
			*data_pos = theFdcanFilter.filter.filter_byte[k].tmp;
		}
		else if(method == FDCAN_filter_method_inc){
			uint8_t newval = theFdcanFilter.filter.filter_byte[k].tmp + theFdcanFilter.filter.filter_byte[k].step;
			if(newval > theFdcanFilter.filter.filter_byte[k].to_value) newval = theFdcanFilter.filter.filter_byte[k].from_value;
			theFdcanFilter.filter.filter_byte[k].tmp = newval;
			*data_pos = theFdcanFilter.filter.filter_byte[k].tmp;
		}
		else if(method == FDCAN_filter_method_dec){
			uint8_t newval = theFdcanFilter.filter.filter_byte[k].tmp - theFdcanFilter.filter.filter_byte[k].step;
			if(newval < theFdcanFilter.filter.filter_byte[k].to_value) newval = theFdcanFilter.filter.filter_byte[k].from_value;
			theFdcanFilter.filter.filter_byte[k].tmp = newval;
			*data_pos = theFdcanFilter.filter.filter_byte[k].tmp;
		}
	}
}




#endif // SUPPORT_FDCAN

