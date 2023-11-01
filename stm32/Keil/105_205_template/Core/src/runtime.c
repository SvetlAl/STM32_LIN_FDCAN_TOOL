/****************************************************************
*                      Runtime procedures
*                      used in main.c
*
*****************************************************************/


#include "runtime.h"

#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
uint8_t volatile blink_timeout = 0x00;
uint8_t volatile blink_switch = 0x00;
#endif


/********************************************************************************************/
/***************************** Watchdog procedures	 ****************************************/
/********************************************************************************************/

void runWatchdogProcedure(){
	eLinkState _link_status = USB_CDC_process_watchdog();
	
	/*** LED blinking ***/
	if(_link_status == LINK_STATE_DEFAULT){
		#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
		if(!blink_switch)SIGNAL_LED_OFF;
		#endif
		}
	else if(_link_status == LINK_STATE_DISCONNECTED){
		IWDG_reset();
		#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
		if(!blink_switch)SIGNAL_LED_OFF;
		#endif
		}
	else{ /* connected */
		IWDG_reset();
		#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
		if(!blink_switch)SIGNAL_LED_ON;
		#endif
		}
	/*** Reset button ***/
		#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
		if(EMERGENCY_PIN_SET){
			NVIC_SystemReset();
		}
		#endif
		
		/*** CAN error ***/
		if((!(CAN1->ESR & CAN_ESR_LEC)) & (!(CAN2->ESR & CAN_ESR_LEC))){
			IWDG_reset();
		}
		/* this point may be removed */
		else if((CAN1->ESR & CAN_ESR_LEC_2)/* & ((CAN2->ESR & CAN_ESR_LEC) == 0x02)*/){
			IWDG_reset();
		}
}

/********************************************************************************************/
/********************************************************************************************/
/* Recieve data via USB Virtual COM-Port and check, if the recieved bytes contain a command */
/********************************************************************************************/
/********************************************************************************************/


volatile uint32_t cmd_fll = ELP_IDLE;
memchip_status memory_chip_status;

uint32_t USB_CDC_recieve_data(uint16_t length){
	uint8_t *data = EndPoint[1].rxBuffer_ptr;
	
	//============================== Programming memory chip =====================================
	if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_ON){

		IWDG_reset();
		uint16_t bytes_to_write = (memory_chip_status.stream_pending_data > length) ? length : (uint16_t)(memory_chip_status.stream_pending_data);

		programm_memchip(&memory_chip_status, memory_chip_status.stream_address, data, bytes_to_write, SPI_no_Dma);
		memory_chip_status.stream_address += bytes_to_write;
		memory_chip_status.stream_pending_data -= bytes_to_write;
		
		/*** If all data is recieved, finish the process ***/
		if(memory_chip_status.stream_pending_data == 0){
			SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
			protocol_response(ELP_OK);
		}		
	}
	//============================== Updating device modes =====================================
	else if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FILTR_UPD ){
		IWDG_reset();
		uint8_t *write_address = get_override_settings_data() + (DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH - memory_chip_status.stream_pending_data);
		uint16_t bytes_to_write = (memory_chip_status.stream_pending_data > length) ? length : (uint16_t)(memory_chip_status.stream_pending_data);
		for(uint32_t i = 0; i < bytes_to_write; i++){
			*write_address++ = *data++;
		}
		memory_chip_status.stream_pending_data -= bytes_to_write;
		
		/*** If all data is recieved, finish the process ***/
		if(memory_chip_status.stream_pending_data == 0){
			SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
			protocol_response(ELP_OK);
		}		
	}
	//=================== CAN messages injection mode. Via USB CDC ==============================
	else if((CAN_INJECTION_CDC_MODE != DEVICE_OPERATION_MODE_OFF) & (CAN_INJECTION_CDC_MODE != DEVICE_OPERATION_MODE_DEFAULT)){
		IWDG_reset();	
		CDC_can_inj_recieve_data(data, (uint32_t)length);
	}
	
	/*** Fill command buffer ***/
	else if(cmd_fll != ELP_BUSY) cmd_fll = fill_elp_buffer(data, length);
	/*** if busy, send bsy response ***/
	else protocol_response(ELP_BUSY);
	return length;
}

void findAndProcess_cmd(){
	uint32_t parse_result = ELP_IDLE;
		/* if there's something new in cmd buffer */
		if(cmd_fll ==  ELP_OK){
			cmd_fll = ELP_BUSY;
			parse_result = find_and_parse_elp_cmd();
		}
		
		/* parsing a cmd */
		if(parse_result !=  ELP_IDLE){
						
			/*** Blinking LED indicates, that restart is needed ***/
			if(parse_result ==  ELP_ERROR){
				#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
				blink_switch = 0x10;
				#endif
				el_reset_state();
			}
			
			/*** Blinking LED indicates, that memory write is done.  ***/	
			else if(global_el_command.cmd == ELP_VEHICLE_SAVE_STATUS){
				#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
				blink_switch = 0x80;
				#endif
				
				if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_ON){
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_OFF);
					SET_CALIBRATOR_FILTER_MODE(DEVICE_OPERATION_MODE_OFF);		
						
					process_protocol_cmd(&global_el_command);
					
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
					SET_CALIBRATOR_FILTER_MODE(DEVICE_OPERATION_MODE_ON);
				}
				else process_protocol_cmd(&global_el_command);
			}
			else{			
				process_protocol_cmd(&global_el_command);	
			}
		}
		/* reset cmd fill flag */
		cmd_fll = ELP_IDLE;
}


/********************************************************************************************/
/************************************ Calibration procedure *********************************/
/********************************************************************************************/

void process_calibrator_procedure(can_message *newMessage){
/*************** ID matches vehicle's speedometer id. Speed can be found in one or two id's ***********************/
		if((CAN_ID(newMessage) == SPEEDOMETER_ID(theVehicle)) |
			(CAN_ID(newMessage) == EXTRAS_ID(theVehicle))){
				
				/* set odometer MLT. 0x00 if frozen */
				uint8_t odo_mlt = (VEHICLE_MODES(theVehicle) & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : ODO_MLT(theVehicle);
				/***************************************************************/
				/************************ TEST SECTION *************************/
				/***************************************************************/
			if(VEHICLE_MODES(theVehicle) & CALIBRATOR_TEST_MODE){
				if((VEHICLE_MODEL(theVehicle) != MODEL_GREAT_WALL_WINGLE7) & (VEHICLE_MODEL(theVehicle) != MODEL_DODGE_RAM_2013)){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE;
				}
				else if (VEHICLE_MODEL(theVehicle) == MODEL_GREAT_WALL_WINGLE7){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE_GW;
				}
				else if (VEHICLE_MODEL(theVehicle) == MODEL_DODGE_RAM_2013){
					for(uint32_t i = 0; i < newMessage->dlc; i++) newMessage->data[i] = SPEEDOMETER_TEST_VALUE_DR;
				}
			}
			
			else{	
				CALIBRATE_SPEEDOMETER(theVehicle, newMessage, odo_mlt);
			}					
		}		
			
		/*************** ID matches vehicle's odometer id and SPEED and ODO are different ID's ***********************/
		if((CAN_ID(newMessage) == ODOMETER_ID(theVehicle)) &
			(ODOMETER_ID(theVehicle) != SPEEDOMETER_ID(theVehicle))){
				/* set odometer MLT. 0x00 if frozen */
				uint8_t odo_mlt = (VEHICLE_MODES(theVehicle) & CALIBRATOR_ODO_FREEZE_MODE) ?  0x00 : ODO_MLT(theVehicle);
				CALIBRATE_ODOMETER(theVehicle, newMessage, odo_mlt);
			}	
		
		/*************** ID matches vehicle's cruise id ***********************/
		if(CAN_ID(newMessage) == CRUISE_ID(theVehicle)){
			CALIBRATE_CRUISE(theVehicle, newMessage);
		}
		
		/*************** EXTRA calibration for ISUZU DMAX and GW POER ***********************/
		if(VEHICLE_MODEL(theVehicle) == MODEL_ISUZU_DMAX_MUX || VEHICLE_MODEL(theVehicle) == MODEL_GREAT_WALL_POER || VEHICLE_MODEL(theVehicle) == MODEL_TOYOTA_TUNDRA_2022){
			CALIBRATE_EXTRAS(theVehicle, newMessage);
		}
}

/********************************************************************************************/
/************************************ 	Override procedure 	*********************************/
/********************************************************************************************/
extern u_can_override_status theOverrideStatus;

uint32_t process_override_procedure(can_message *newMessage, uint32_t _can_num /* CAN1 or CAN2 */){
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


/********************************************************************************************/
/********************************************************************************************/
/***********                    USART data recieved                               ***********/
/********************************************************************************************/
/********************************************************************************************/

#if defined(DEBUG_MODE) && defined(SUPPORT_USART) && !defined(SUPPORT_LIN)
static uint8_t recieved_from_usart[64];

uint32_t usart_recieve_data(uint8_t usart_num, uint16_t length){
	if(usart_num < 1 || usart_num > 3) return 0;
	
	if(length >= 4){
		usart_bufs[usart_num]->read(recieved_from_usart);
		
		uint8_t data_to_send[64];
		uint8_t pos = 0;
		data_to_send[pos++] = 'U';
		data_to_send[pos++] = 'S';
		data_to_send[pos++] = 'A';
		data_to_send[pos++] = 'R';
		data_to_send[pos++] = 'T';
		data_to_send[pos++] = SC_4BIT_TO_ASCII(((usart_num << 0) &~0xFF00));
		data_to_send[pos++] = 'R';
		data_to_send[pos++] = 'X';
		data_to_send[pos++] = ' ';
		
		uint32_t com_pos = 0;
		while((pos < 64) && (com_pos < length)){
			// data_to_send[pos++] = recieved_from_usart[com_pos++];
			data_to_send[pos++] = recieved_from_usart[com_pos++];
		}
		USB_CDC_send_data(data_to_send, pos);
		
	}
	return length;
}
#endif
