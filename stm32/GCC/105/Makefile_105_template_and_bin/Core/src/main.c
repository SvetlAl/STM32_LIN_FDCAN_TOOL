/****************************************************************
* A device based on STM32F205
*
* CAN scanner, gateway, filter, multi-purpose tool
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*
*****************************************************************/


#include "main.h"

/********************************************************************************************/
/************************************ 		Global vars			 **********************************/
/********************************************************************************************/

VehicleStructData theVehicle;
u_can_override_status theOverrideStatus;

static volatile uint32_t secs = 0x00; /* Timer, that counts seconds from the start */

extern memchip_status memory_chip_status;
extern volatile uint32_t cmd_fll;				/* cmd_buffer flag. If recieved data contains a message, the flag changes its status */


/* blink LED*/
#if defined(ALLIGATOR) | defined(TEC_MODULE)
extern volatile uint8_t blink_timeout;
extern volatile uint8_t blink_switch;
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
#if defined (TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
	SIGNAL_LED_A_ON;
#endif

	if(CAN1->RF0R & CAN_RF0R_FMP0){
		// Recieve a new message
		#if !defined(TEST_SPEED_TRANSMITTER) | !defined(TEST_SPEED_RESPONDER)
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		
		//============ CAN scanner Mode ====================
		if(CANSCANNER_MODE == DEVICE_OPERATION_MODE_ON){
			can_recieve_and_usb_transmit_msg(CAN1, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
		}
		else{			
			Can_Recieve_StdMessage(CAN1, CAN_FIFO_0, newMessage);
		}
		
		//============ Gateway Mode ====================
		if(CAN_GATEWAY_MODE != DEVICE_OPERATION_MODE_ON){
			CAN1->RF0R |= CAN_RF0R_RFOM0;
			return;
		}
		
		//============ Calibrator Mode ====================
		if(CALIBRATOR_FILTER_MODE == DEVICE_OPERATION_MODE_ON){
			
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){
				if(process_override_procedure(newMessage, 1) == DISCARD_MSG){
					CAN1->RF0R |= CAN_RF0R_RFOM0;
					return;
				}
			}
			process_calibrator_procedure(newMessage);
		}
		
		if(Can_Transmit_Message(CAN2, newMessage) != ERR_CAN_NO_EMPTY_MAILBOX){
			IWDG_reset();			 
		}
		
		#endif
		
		#ifdef TEST_SPEED_RESPONDER
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		Can_Recieve_StdMessage(CAN1, CAN_FIFO_0, newMessage);
		newMessage->id.std_id.id_lowbyte += 0x09;
		Can_Transmit_Message(CAN1, newMessage);
		#endif
	}
	#if defined (TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
	SIGNAL_LED_A_OFF;
	#endif
	CAN1->RF0R |= CAN_RF0R_RFOM0; //release
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
			//__disable_irq ();
			can_recieve_and_usb_transmit_msg(CAN2, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
			//__enable_irq ();
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
				if(process_override_procedure(newMessage, 2) == DISCARD_MSG) {
					CAN2->RF0R |= CAN_RF0R_RFOM0;
					return;
				}
			}
		}

		//__disable_irq ();
		if(Can_Transmit_Message(CAN1, newMessage) != ERR_CAN_NO_EMPTY_MAILBOX){
			IWDG_reset();			 
		}
		//__enable_irq ();
	}
	CAN2->RF0R |= CAN_RF0R_RFOM0; //release		
}

/********************************************************************************************
/
/
/                                            MAIN
/
/
********************************************************************************************/

int main(void){
   	/* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	#ifdef STM32F205
	//RCC->APB1ENR	|= RCC_APB1ENR_PWREN;
	set_bor_level(BOR_VALUE);
	#endif	
	EnablePeripherals();
	__disable_irq();
	Can_InitFilters_GatewayTemplate();
	Can_Init_Buffers();
	
	initDeviceGeneralPinout();
	
	initVehicleSettings(&theVehicle);  // here theVehicle structure is initialized
	initModelSettings(); // here uDeviceModel (Scanner or Gateway or whatever), theOverrideStatus (filters) are initialized
	initCANSettings(theVehicle._vehicleStruct.model, &theDeviceModel);
	
	USB_OTG_FS_init_pinout();
	USB_OTG_FS_init_device();

	NVIC_EnableIRQ(CAN1_RX0_IRQn);
	NVIC_SetPriority(CAN1_RX0_IRQn, 7);
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
	
	#if defined (TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
	init_extras();
	#endif
	
	__enable_irq ();
	while(1){
		#ifndef CAN_TX_BUFFER_ENABLED
		timeout = 0xFFF;
		while(timeout-- > 0){
		}
		#endif
		
		#ifdef CAN_TX_BUFFER_ENABLED
		timeout = 0xFF;
		while(timeout-- > 0){
				
			/*******************************************************************
			******************** buffered transmission procedure ***************
			*******************************************************************/
			
			#if !defined(TEST_SPEED_TRANSMITTER) & defined(CAN_TX_BUFFER_ENABLED)
			process_buffered_can_tx();
			#endif	
				
			/*******************************************************************
			******************** Network test presets **************************
			*******************************************************************/
			
			#if defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
			volatile uint32_t extra_tx_timeout = 0;
			while (extra_tx_timeout++ < EXTRA_TRANSMISSION_TIMEOUT){}
			
			uint32_t processed_msgs  = process_buffered_can_tx();	
			if(!processed_msgs){
				SIGNAL_LED_B_ON;
				#if defined(TEST_SPEED_TRANSMITTER) 
				check_test_transmission_request(); 
				#endif
			}
			else{
				#if defined(TEST_SPEED_TRANSMITTER) 
				calculate_cnt_and_transmit();
				#endif
			}
			SIGNAL_LED_B_OFF;
			#endif
		}
		findAndProcess_cmd();
		#endif
			
		/*********** LED blinking **************/
		#if defined(ALLIGATOR) | defined(TEC_MODULE)
		if(blink_switch) if(blink_timeout++ == blink_switch) {TOGGLE_SIGNAL_LED;}
		#endif
		
		/*********** Process pending command **************/
		#if (!defined(TEST_SPEED_TRANSMITTER) | !defined(TEST_SPEED_RESPONDER)) & !defined(CAN_TX_BUFFER_ENABLED)
		findAndProcess_cmd();	
		#endif
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
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_ON)))
			runWatchdogProcedure();
		else if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON) IWDG_reset();
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
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_ON)))
			runWatchdogProcedure();
		else if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON) IWDG_reset();
	}
}
#endif




void resetCanTimer(TIM_TypeDef * TIM_n){
	TIM_n->CNT = 0;
	secs = 0;
}
