/****************************************************************
* A device based on STM32F205
*
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*
*****************************************************************/


#include "main.h"

/********************************************************************************************/
/************************************ Device modes handler **********************************/
/********************************************************************************************/

static inline void process_calibrator_procedure(can_message *newMessage);
static inline uint32_t process_override_procedure(can_message *newMessage, uint32_t _can_num);

/********************************************************************************************/
/************************************ 		Global vars			 **********************************/
/********************************************************************************************/

VehicleStructData theVehicle;
static u_can_override_status theOverrideStatus;

static volatile uint32_t secs = 0x00; /* seconds from the start */

memchip_status memory_chip_status;
static volatile uint32_t cmd_fll = ELP_IDLE;				/* cmd_buffer flag. If recieved data contains a message, the flag changes its status */


/* blink LED*/

#if defined(ALLIGATOR) | defined(TEC_MODULE)
static volatile uint8_t blink_timeout = 0x00;
static volatile uint8_t blink_switch = 0x00;
#endif

/********************************************************************************************/
/************************************ 	   Getters	     	 **********************************/
/********************************************************************************************/

uint8_t *get_vehicle_settings_data(){
	return &theVehicle.data[0];
}

uint8_t *get_device_modes_data(){
	return &theDeviceModel.data[0];
}

uint8_t *get_override_settings_data(){
	return &theOverrideStatus.raw_data[0];
}
can_override_status *getCanOverrideStatus(){
	return &theOverrideStatus.status;
}

/********************************************************************************************/
/*********************************** Calibrated CAN channel *********************************/
/********************************************************************************************/
#if defined(STM32F105) & !defined(MDK_ARM_ENV)
extern void USB_LP_CAN_RX0_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void) {
#else
extern void CAN1_RX0_IRQHandler(void);
void CAN1_RX0_IRQHandler(void) {
#endif

	if(CAN1->RF0R & CAN_RF0R_FMP0){
		// Recieve a new message
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		
		//============ CAN scanner Mode ====================
		if(CANSCANNER_MODE == DEVICE_OPERATION_MODE_ON){
			__disable_irq ();
			can_recieve_and_usb_transmit_msg(CAN1, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
			__enable_irq ();
		}
		else{			
			Can_Recieve_StdMessage(CAN1, CAN_FIFO_0, newMessage);
		}
		
		//============ Gateway Mode ====================
		if(CAN_GATEWAY_MODE != DEVICE_OPERATION_MODE_ON) return;
		
		//============ Calibrator Mode ====================
		if(CALIBRATOR_FILTER_MODE == DEVICE_OPERATION_MODE_ON){
			process_calibrator_procedure(newMessage);
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){
				if(process_override_procedure(newMessage, 1) == DISCARD_MSG) return;
			}
		}
		
		__disable_irq ();
		if(Can_Transmit_Message(CAN2, newMessage) != ERR_CAN_NO_EMPTY_MAILBOX){
			IWDG_reset();			 
		}
		__enable_irq ();
	}
}

/********************************************************************************************/
/************************************ Bypass  CAN channel  **********************************/
/********************************************************************************************/

extern void CAN2_RX0_IRQHandler(void);
void CAN2_RX0_IRQHandler(void){
	if(CAN2->RF0R & CAN_RF0R_FMP0){
		// Recieve a new message
		
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		
		//============ CAN scanner Mode ====================
		if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON){
			__disable_irq ();
			can_recieve_and_usb_transmit_msg(CAN2, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
			__enable_irq ();
		}
		else{			
			Can_Recieve_StdMessage(CAN2, CAN_FIFO_0, newMessage);
		}
		
		//============ Gateway Mode ====================
		// if(CAN2_GATEWAY_MODE != DEVICE_OPERATION_MODE_ON) return; // OBSOLETE
		
		//============ Calibrator Mode ====================
		if(CALIBRATOR_FILTER_MODE == DEVICE_OPERATION_MODE_ON){
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){
				if(process_override_procedure(newMessage, 2) == DISCARD_MSG) return;
			}
		}

		__disable_irq ();
		if(Can_Transmit_Message(CAN1, newMessage) != ERR_CAN_NO_EMPTY_MAILBOX){
			IWDG_reset();			 
		}
		__enable_irq ();
	}
}

int main(void){
   	/* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	EnablePeripherals();
	__disable_irq ();
	Can_InitFilters_GatewayTemplate();
	

	initDeviceGeneralPinout();
	
	initVehicleSettings(&theVehicle);  // here theVehicle structure is initialized
	initModelSettings(); // here uDeviceModel (Scanner or Gateway or whatever), theOverrideStatus (filters) are initialized
	
	
	
	USB_OTG_FS_init_pinout();
	USB_OTG_FS_init_device();

	NVIC_EnableIRQ(CAN1_RX0_IRQn);
	NVIC_SetPriority(CAN1_RX0_IRQn, 8);
	NVIC_EnableIRQ(CAN2_RX0_IRQn);
	NVIC_SetPriority(CAN2_RX0_IRQn, 8);
	
	// watchdog
	#ifdef STM32F205
	NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn);
	NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 11);
	#elif defined(STM32F105)
	NVIC_EnableIRQ (TIM1_UP_IRQn);
	NVIC_SetPriority(TIM1_UP_IRQn, 11);
	#endif
	// trace injection
	NVIC_EnableIRQ (TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 4);
	
	
	SIGNAL_LED_OFF;
	startBasicTimer(WATCHDOG_PROCEDURE_PSC, WATCHDOG_PROCEDURE_CNT, TIM1);
	
	static volatile uint32_t timeout = 0xFFFF;
	
	__enable_irq ();
	while(1){
		timeout = 0xFFFF;
		while(timeout-- > 0){
		}
			
		/*********** LED blinking **************/
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
		if(blink_switch) if(blink_timeout++ == blink_switch) {TOGGLE_SIGNAL_LED;}
		#endif
		
		/*********** Process pending command **************/
		findAndProcess_cmd();	
	}
}



/********************************************************************************************/
/***************************** Watchdog procedures	 ****************************************/
/********************************************************************************************/

#ifdef STM32F205
extern void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void){
	if(TIM1->SR & TIM_SR_UIF){
		TIM1->SR &= ~TIM_SR_UIF; // Flag down
		__disable_irq();
		TIM1->CNT = 0;
		secs++;
		__enable_irq();
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE == DEVICE_OPERATION_MODE_OFF) | (CAN_INJECTION_MODE == DEVICE_OPERATION_MODE_DEFAULT)))
		runWatchdogProcedure();
	}
}
#elif defined(STM32F105)
extern void TIM1_UP_IRQHandler(void);
void TIM1_UP_IRQHandler(void){
	if(TIM1->SR & TIM_SR_UIF){
		TIM1->SR &= ~TIM_SR_UIF; // Flag down
		__disable_irq();
		TIM1->CNT = 0;
		secs++;
		__enable_irq();
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & (CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_OFF))
		runWatchdogProcedure();
	}
}
#endif

void runWatchdogProcedure(){
	eLinkState _link_status = USB_CDC_process_watchdog();
	
	/*** LED blinking ***/
	if(_link_status == LINK_STATE_DEFAULT){
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
		if(!blink_switch)SIGNAL_LED_OFF;
		#endif
		}
	else if(_link_status == LINK_STATE_DISCONNECTED){
		IWDG_reset();
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
		if(!blink_switch)SIGNAL_LED_OFF;
		#endif
		}
	else{ /* connected */
		IWDG_reset();
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
		if(!blink_switch)SIGNAL_LED_ON;
		#endif
		}
	/*** Reset button ***/
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
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

uint32_t USB_CDC_recieve_data(uint16_t length){
	uint8_t *data = EndPoint[1].rxBuffer_ptr;
	
	/*** If recieveing raw data is in progress, continue recieving ***/
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
				#ifdef TEC_MODULE
				blink_switch = 0x10;
				#endif
				el_reset_state();
			}
			
			/*** Blinking LED indicates, that memory write is done.  ***/	
			else if(global_el_command.cmd == ELP_VEHICLE_SAVE_STATUS){
				#ifdef TEC_MODULE
				blink_switch = 0x80;
				#endif
				
				if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_ON){
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_OFF);
					SET_CAN2_GATEWAY_MODE(DEVICE_OPERATION_MODE_OFF);
					SET_CALIBRATOR_FILTER_MODE(DEVICE_OPERATION_MODE_OFF);		
						
					process_protocol_cmd(&global_el_command);
					
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
					SET_CAN2_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
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

static inline void process_calibrator_procedure(can_message *newMessage){
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


static inline uint32_t process_override_procedure(can_message *newMessage, uint32_t _can_num /* CAN1 or CAN2 */){
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

void resetCanTimer(TIM_TypeDef * TIM_n){
	TIM_n->CNT = 0;
	secs = 0;
}
