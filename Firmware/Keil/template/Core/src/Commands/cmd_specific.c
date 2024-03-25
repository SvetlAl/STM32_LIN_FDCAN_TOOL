#include "Commands/cmd_specific.h"
#include "Commands/device_modes.h"

#include "ram_updater.h"


static inline void parse_and_set_calibrator_value(uint32_t PARAMETER, uint32_t value){
	//value &= ~0xFFFFFF00;
	set_vehicle_value(PARAMETER, value);
	protocol_response(ELP_OK);
	el_reset_state();
}	


static inline void read_vehicleStatus_and_usb_send_ASCII(){
	uint8_t *status = get_vehicle_settings_data();
	uint8_t temp[VEHICLE_STATUS_SETTINGS_LENGTH*2];
	
	hexArray2asciiArray((status + 1), &temp[0], 1);
	hexArray2asciiArray((status), &temp[2], 1);
	hexArray2asciiArray((status + 2), &temp[4], VEHICLE_STATUS_SETTINGS_LENGTH - 2);
	
	USB_CDC_send_data(temp, VEHICLE_STATUS_SETTINGS_LENGTH*2);
}


static inline void start_override_filters_upd_procedure(void){ /* @SF0000008#00#01#02#12#23#45@E Start programming procedure at addr 0x000102 with 0x122345 bytes */
	#if defined(SUPPORT_BXCAN)
	ram_upd_set_size(DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH);
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FILTR_UPD);
	#endif // SUPPORT_BXCAN
	
	#if defined(SUPPORT_FDCAN) 
	ram_upd_set_size(sizeof(fdcan_filter));
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FILTR_UPD);
	#endif // SUPPORT_FDCAN
	
	protocol_response(ELP_OK);
	el_reset_state();
}

static inline uint32_t save_deviceStatus(){
	uint8_t *dev_modes_status = get_device_modes_data();
	uint32_t save_address = memchip_make_app_address(memchipModes);
	
	uint32_t result = memchip_rewrite(save_address, dev_modes_status, (uint32_t)DEVICE_MODES_SETTINGS_LENGTH);
	if(result == OPERATION_FAIL) return result;
	
	// save override filters
	#if defined(MEMCHIP_NOR_FLASH) && defined(SUPPORT_BXCAN)
	uint8_t *ovr_status = can_override_get_dataptr();
	save_address = memchip_make_app_address(memchipOverrideFilters);
	result = memchip_write(save_address, ovr_status, (uint32_t)DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH);
	#endif // !MEMCHIP_NAND_FLASH

	return result;
}

static inline uint32_t save_vehicleStatus(){
	uint8_t *status = get_vehicle_settings_data();		
	uint32_t save_address = memchip_make_app_address(memchipVehicle);
	return memchip_rewrite(save_address, status, (uint32_t)VEHICLE_STATUS_SETTINGS_LENGTH);
}

void cmd_specific_process(elp_cmd *com){
	uint32_t response = ELP_OK;
	switch(com->cmd){
		/*
		case(ELP_VEHICLE_GET_MEMORY_STATUS_STRING_HEX):
			read_memorySnapshot_and_usb_send(STATUS_STRING_LENGTH*2, VEHICLE_SETTINGS_ADDRESS);
			el_reset_state();
			break;
		*/		
		/*************** ELP_VEHICLE_SET_XXXXXXXXXXXXXX *****************/
		case(ELP_VEHICLE_SET_MODE/* ELP_VEHICLE_SET_ODOMETER_MODE */):
		case(ELP_VEHICLE_SET_TEST_MODE):
		case(ELP_VEHICLE_SET_MODEL):
		case(ELP_VEHICLE_SET_ODOMETER_MLT):
		case(ELP_VEHICLE_SET_TYRES_THRESHOLD):
		case(ELP_VEHICLE_SET_CRUISE_MLT):
		case(ELP_VEHICLE_SET_SPEEDOMETER_MLT):{
			response = assert_cmd_length(ELP_VEHICLE_SET_MODE_CMDSTR_LENGTH, com);
			
			if(response != ELP_ERROR){
				uint32_t value = str_to_uint32(&com->string_buffer.raw_data8[0]);
				parse_and_set_calibrator_value(com->cmd, value);
			}
			break;
		}
		/****************	ELP_VEHICLE_GET_SW_VERSION	****************/		
		case(ELP_VEHICLE_GET_SW_VERSION):{
			uint8_t* sw_vers = getDeviceSoftwareVersion();
			USB_CDC_send_data(sw_vers, DEVICE_INFO_STRING_SZ);
			el_reset_state();
			break;}

		/****************	ELP_VEHICLE_GET_DEV_MODEL	****************/		
		case(ELP_VEHICLE_GET_DEV_MODEL):{
			uint8_t* sw_vers = get_board_name();
			USB_CDC_send_data(sw_vers, DEVICE_INFO_STRING_SZ);
			el_reset_state();
			break;}	
		//********** Get 8 bytes of current vehicle settings	**************
		case(ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII):
			read_vehicleStatus_and_usb_send_ASCII();
			el_reset_state();
			break;
		//************ Save 8 bytes of current vehicle settings **********/
		case(ELP_VEHICLE_SAVE_STATUS):{
			uint32_t result = save_vehicleStatus();
			result = (result == OPERATION_OK) ? ELP_OK : ELP_ERROR;
			response = ELP_OK;
			protocol_response(response);
			el_reset_state();
			break;	
		}
		
		/****************	ELP_DEVICE_SET_MODE	****************/		
		case(ELP_DEVICE_SET_MODE):								/* @S00000B07#00#00#01#02@E set the first (0x 000001)var in DeviceModel as 02 */	
			user_cmd_set_device_mode(com);
			el_reset_state();
			break;
		
				/****************	ELP_UPDATE_OVR_FILTERS	****************/		
		case(ELP_UPDATE_OVR_FILTERS):{								/* @S00000BA1@E Start filter update procedure */
			start_override_filters_upd_procedure();
			break;}	

		/****************	ELP_DEVICE_SAVE_STATUS	****************/		
		case(ELP_DEVICE_SAVE_STATUS):{								/* @S00000BA0@E Save current device settings into (0x00FA00) DEVICE_MODES_ADDRESS */
			response = save_deviceStatus();
			protocol_response(response);
			el_reset_state();
			break;}	
		
		
		default:
			response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
	}
}
