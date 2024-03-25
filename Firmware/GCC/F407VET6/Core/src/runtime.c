/****************************************************************************************************************
*                      Runtime procedures
*                      used in main.c
*
*****************************************************************************************************************/

#include "device_model.h"

#include "runtime.h"
#include "ram_updater.h"

#ifdef SUPPORT_BXCAN
#include "BxCAN/can_override.h"
#include "BxCAN/can_scanner.h"
#include "BxCAN/can_cdc_player.h"
#endif // SUPPORT_BXCAN

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan.h"
#endif // SUPPORT_FDCAN



//=========================================================================================================
//============================================== Local vars ===============================================
//=========================================================================================================
static volatile uint32_t cmd_fll = ELP_IDLE;
static volatile uint8_t blink_timeout = 0x00;
static volatile uint8_t blink_switch = 0x00;

void main_led_blink(void){
  if(blink_switch) if(blink_timeout++ == blink_switch) {TOGGLE_SIGNAL_LED;}
}

/********************************************************************************************************************************************/
/***************************************************** Watchdog procedures   ****************************************************************/
/********************************************************************************************************************************************/

/**
* brief  This function is invoked according to main timer every N ticks
* brief  It performs some watchdog procedures, preventing the system from freeze.
* brief  Sets the LED indicator to indicate the device status
* brief  
* brief  Also some additional functions can be added. Like Periodic transmission.
* param
* param
* retval
*/

void runWatchdogProcedure(void){
	extra_broadcast();
	eLinkState _link_status = USB_CDC_process_watchdog();
	
	/*** LED blinking ***/
	if(_link_status == LINK_STATE_DEFAULT){
		if(!blink_switch){
			SIGNAL_LED_OFF;
		}
	}
	else if(_link_status == LINK_STATE_DISCONNECTED){
		IWDG_reset();
		if(!blink_switch){
			SIGNAL_LED_OFF;
		}
	}
	else{ /* connected */
		IWDG_reset();
		if(!blink_switch){
			SIGNAL_LED_ON;
		}
	}
	#ifdef SUPPORT_BXCAN
	/*** CAN error ***/
	if((!(CAN1->ESR & CAN_ESR_LEC)) & (!(CAN2->ESR & CAN_ESR_LEC))){
		IWDG_reset();
	}
	/* this point may be removed */
	else if((CAN1->ESR & CAN_ESR_LEC_2)/* & ((CAN2->ESR & CAN_ESR_LEC) == 0x02)*/){
		IWDG_reset();
	}
	#endif // SUPPORT_BXCAN
}


/********************************************************************************************/
/********************************************************************************************/
/* Recieve data via USB Virtual COM-Port and check, if the received bytes contain a command */
/********************************************************************************************/
/********************************************************************************************/

static void update_filter_procedure(uint8_t *data, uint16_t length){
	uint32_t pending_data = ram_upd_get_pending_size();
	
	#ifdef SUPPORT_BXCAN
	uint8_t *write_address = can_override_get_dataptr() + (DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH - pending_data);
	#elif defined(SUPPORT_FDCAN)
	uint8_t *write_address = fdcan_get_filter_ptr() + (DEVICE_FDCAN_SETTINGS_LENGTH - pending_data);
	#endif

	uint32_t bytes_to_write = (pending_data > length) ? length : (uint32_t)(pending_data);
		
	for(uint32_t i = 0; i < bytes_to_write; i++){
			*write_address++ = *data++;
	}
	ram_upd_record_written_size(bytes_to_write);
	pending_data = ram_upd_get_pending_size();
	/*** If all data is received, finish the process ***/
	if(pending_data == 0){
		SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
		protocol_response(ELP_OK);
	}		
}

#ifdef SUPPORT_FDCAN
static void update_fdcan_settings_procedure(uint8_t *data, uint16_t length){
	uint32_t pending_data = ram_upd_get_pending_size();
	IWDG_reset();
	uint8_t *write_address = fdcan_get_settings_ptr() + (DEVICE_FDCAN_SETTINGS_LENGTH - pending_data);
	uint32_t bytes_to_write = (pending_data > length) ? length : (uint32_t)(pending_data);
	
	for(uint32_t i = 0; i < bytes_to_write; i++){
		*write_address++ = *data++;
	}
	ram_upd_record_written_size(bytes_to_write);
	pending_data = ram_upd_get_pending_size();
	
	/*** If all data is received, finish the process ***/
	if(pending_data == 0){
		SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
		protocol_response(ELP_OK);
	}	
}
#endif // SUPPORT_FDCAN

//================================================================================================================================
//================================================================================================================================
//============================================ USB CDC on data received ==========================================================
//================================================================================================================================
//================================================================================================================================
/**
* brief  Declared in USB lib. Invoked on USB CDC data coming
* brief  
* brief  
* param
* param
* retval
*/
uint32_t USB_CDC_receive_data(uint16_t length){
	uint8_t *data = EndPoint[1].rxBuffer_ptr;
	
//================================================================================================================================
//============================================ Programming memory chip ===========================================================

	if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_ON){
		
		IWDG_reset();
		uint32_t pending_length = memchip_get_pending_length();
		uint32_t bytes_to_write = (pending_length > length) ? length : pending_length;
		
		uint32_t address = memchip_get_address();
		memchip_write(address, data, (uint32_t)bytes_to_write);

		memchip_deduct_pending_data(bytes_to_write);
		/*** If all data is received, finish the process ***/
		pending_length = memchip_get_pending_length();
		if(pending_length == 0){
			SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
			protocol_response(ELP_OK);
		}		
	}
//================================================================================================================================
//=================================================== Filter update ==============================================================

	else if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FILTR_UPD ){
		IWDG_reset();
		update_filter_procedure(data, length);
	}
//================================================================================================================================
//======================================= CAN messages injection mode. Via USB CDC ===============================================
	
	else if((CAN_INJECTION_CDC_MODE != DEVICE_OPERATION_MODE_OFF) & (CAN_INJECTION_CDC_MODE != DEVICE_OPERATION_MODE_DEFAULT)){
		#ifdef SUPPORT_BXCAN // not supported for FD CAN yet
		IWDG_reset();	
		CDC_can_inj_receive_data(data, (uint32_t)length);
		#endif
	}
	
//================================================================================================================================
//====================================================== FD CAN ==================================================================
//================================================================================================================================
	#ifdef SUPPORT_FDCAN
//================================================================================================================================
//============================================== Update  FD CAN Settings =========================================================

	else if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FDCAN_SETTINGS_UPD ){
		update_fdcan_settings_procedure(data, length);
	}
//================================================================================================================================
//============================================== Send a single FD CAN message ====================================================

	else if(MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_1 || MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_2){
		IWDG_reset();
		uint32_t pending_data = ram_upd_get_pending_size();
		uint8_t can_n = (MEMORY_PROGRAMM_MODE == DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_1) ? FDCAN1_E : FDCAN2_E;
		 
		uint8_t *write_address = (FDCAN_TX_BUF_W_POS_PTR(can_n) + FDCAN_TX_BUF_PTR(can_n)->tmp_write_pos);
		uint32_t bytes_to_write = (pending_data > length) ? length : (uint32_t)(pending_data);
		for(uint32_t i = 0; i < bytes_to_write; i++){
			*write_address++ = *data++;
		}
		ram_upd_record_written_size(bytes_to_write);
		pending_data = ram_upd_get_pending_size();

		FDCAN_TX_BUF_PTR(can_n)->tmp_write_pos += bytes_to_write;
		
		/*** If all data is received, finish the process ***/
		if(pending_data == 0){
			SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
			
			fdcan_mov_w_idx(FDCAN_TX_BUF_PTR(can_n), FDCAN_TX_BUF_PTR(can_n)->tmp_write_pos);
			FDCAN_TX_BUF_PTR(can_n)->tmp_write_pos = 0;
			
			fdcan_buf_w_unlock(FDCAN_TX_BUF_PTR(can_n));
			protocol_response(ELP_OK);
		}	
	}
	#endif // SUPPORT_FDCAN
	
//================================================================================================================================
//====================================================== Default =================================================================
//================================================================================================================================
	/*** Fill command buffer ***/
	else if(cmd_fll != ELP_BUSY) cmd_fll = fill_elp_buffer(data, length);
	/*** if busy, send bsy response ***/
	else protocol_response(ELP_BUSY);
	return length;
}

/**
* brief  If a command buffer contains a command string,
* brief  try to find and process it
* param
* param
* retval
*/
void findAndProcess_cmd(void){
	uint32_t parse_result = ELP_IDLE;
		/* if there's something new in cmd buffer */
		if(cmd_fll ==  ELP_OK){
			cmd_fll = ELP_BUSY;
			parse_result = find_and_parse_elp_cmd();
		}
		
		/* parsing a cmd */
		if(parse_result !=  ELP_IDLE){
			elp_cmd *the_cmd = el_get_current_cmd();
			/*** Blinking LED indicates, that restart is needed ***/
			if(parse_result ==  ELP_ERROR){
				blink_switch = 0x10;
				el_reset_state();
			}
			
			/*** Blinking LED indicates, that memory write is done.  ***/	
			else if(the_cmd->cmd == ELP_VEHICLE_SAVE_STATUS){
				blink_switch = 0x80;
				
				if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_ON){
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_OFF);
					SET_CALIBRATOR_MODE(DEVICE_OPERATION_MODE_OFF);		
						
					process_protocol_cmd(the_cmd);
					
					SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
					SET_CALIBRATOR_MODE(DEVICE_OPERATION_MODE_ON);
				}
				else process_protocol_cmd(the_cmd);
			}
			else{			
				process_protocol_cmd(the_cmd);	
			}
		}
		/* reset cmd fill flag */
		cmd_fll = ELP_IDLE;
}






#ifdef SUPPORT_TUNDRA_SPOILER_REMOVAL
#include "Vehicle_models/toyota_tundra_2022.h"
#endif
void extra_broadcast(void){
	#ifdef SUPPORT_TUNDRA_SPOILER_REMOVAL
	extra_broadcast_TOYOTA_TUNDRA_2022();
	#endif
}




/********************************************************************************************************************************************/
/******************************************************** CAN interrupts *******************************************************************/
/********************************************************************************************************************************************/

/********************************************************************************************/
/*********************************** Calibrated CAN channel *********************************/
/********************************************************************************************/
#if defined(BOARD_MK_STM32F105) & !defined(MDK_ARM_ENV)
extern void USB_LP_CAN_RX0_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void) {
#else
extern void CAN1_RX0_IRQHandler(void);
void CAN1_RX0_IRQHandler(void) {
#endif
	
#ifdef SUPPORT_BXCAN	
	if(CAN1->RF0R & CAN_RF0R_FMP0){
		// Recieve a new message
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		
		//============ CAN scanner Mode ====================
		if(CANSCANNER_MODE == DEVICE_OPERATION_MODE_ON){
			uint32_t secs = get_main_tim_secs();
			can_receive_and_usb_transmit_msg(CAN1, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
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
		if(CALIBRATOR_MODE == DEVICE_OPERATION_MODE_ON){
			
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){
				if(can_override_process_filters(newMessage, 1) == DISCARD_MSG){
					CAN1->RF0R |= CAN_RF0R_RFOM0;
					return;
				}
			}
			can_override_calibrate(newMessage);
		}
		
		if(Can_Transmit_Message(CAN2, newMessage) != ERR_CAN_NO_EMPTY_MAILBOX){
			IWDG_reset();			 
		}
	}
	CAN1->RF0R |= CAN_RF0R_RFOM0; //release
	#endif
}


#ifdef SUPPORT_FDCAN
extern void FDCAN1_IT0_IRQHandler(void);
void FDCAN1_IT0_IRQHandler(void){
	//Bit 0 RF0N: Rx FIFO 0 New message
  //0: No new message written to Rx FIFO 0
  //1: New message written to Rx FIFO 0
	if((FDCAN1->IR & FDCAN_IR_RF0N) != 0){
		fdcan_irq_procedure(FDCAN1_E);
	}
	// message lost
	if((FDCAN1->IR & FDCAN_IR_RF0L) != 0){
		FDCAN1->IR = FDCAN_IR_RF0L; // clear flag
	};
	
	// rx fifo 0 full
	if((FDCAN1->IR & FDCAN_IR_RF0F) != 0){
		while(FDCAN1->RXF0S & FDCAN_RXF0S_F0FL_Msk){
			fdcan_irq_procedure(FDCAN1_E);
		}
		FDCAN1->IR = FDCAN_IR_RF0F;
	};
}
#endif // SUPPORT_FDCAN

/********************************************************************************************/
/************************************ Bypass  CAN channel  **********************************/
/********************************************************************************************/

extern void CAN2_RX0_IRQHandler(void);
void CAN2_RX0_IRQHandler(void){
	#ifdef SUPPORT_BXCAN
	
	if(CAN2->RF0R & CAN_RF0R_FMP0){
		// Recieve a new message
		
		static can_message_info_raw message_data_to_send;
		can_message *newMessage = &message_data_to_send.info.msg;
		
		//============ CAN scanner Mode ====================
		if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON){
			//__disable_irq ();
			uint32_t secs = get_main_tim_secs();
			can_receive_and_usb_transmit_msg(CAN2, MAIN_TIMER, CAN_FIFO_0, &message_data_to_send, secs);
			//__enable_irq ();
		}
		else{			
			Can_Recieve_StdMessage(CAN2, CAN_FIFO_0, newMessage);
		}
		
		//============ Gateway Mode ====================
		// if(CAN2_GATEWAY_MODE != DEVICE_OPERATION_MODE_ON) return; // OBSOLETE
		
		//============ Calibrator Mode ====================
		if(CALIBRATOR_MODE == DEVICE_OPERATION_MODE_ON){
			
			can_override_proc_reverse_calibrate(newMessage);
			
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){
				if(can_override_process_filters(newMessage, 2) == DISCARD_MSG) {
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
	#endif
}

#ifdef SUPPORT_FDCAN
extern void FDCAN2_IT0_IRQHandler(void);
void FDCAN2_IT0_IRQHandler(void){
	//Bit 0 RF0N: Rx FIFO 0 New message
  //0: No new message written to Rx FIFO 0
  //1: New message written to Rx FIFO 0
	if((FDCAN2->IR & FDCAN_IR_RF1N) != 0){
		fdcan_irq_procedure(FDCAN2_E);
	}
	// message lost
	if((FDCAN2->IR & FDCAN_IR_RF1L) != 0){
		FDCAN2->IR = FDCAN_IR_RF1L; // clear flag
	};
	
	// rx fifo 0 full
	if((FDCAN2->IR & FDCAN_IR_RF1F) != 0){
		while(FDCAN2->RXF1S & FDCAN_RXF1S_F1FL_Msk){
			fdcan_irq_procedure(FDCAN2_E);
		}
		FDCAN2->IR = FDCAN_IR_RF1F;
	};
}
#endif // SUPPORT_FDCAN

