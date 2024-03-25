/****************************************************************
* 
* FD CAN scanner functions
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

#include "FDCAN/fdcan_scanner.h"


#ifdef BOARD_MK_STM32H730
#include "USB_CDC/stm32h7xx_usbdfs_cdc.h"
#endif // BOARD_MK_STM32H730



//===============================================================================================
//============================================ Scanner ==========================================
//===============================================================================================
/**
* brief  Add a info tag to a message and send via USB: "static u_fdcan_message_info_short _info" and dataflow from a char pointer    
* param  CAN: FDCAN1_E or FDCAN2_E
* param  Timer periph
* param  message header and data pointer
* param  timer second
* param  
* param  
* retval USB transmission result
*/
uint32_t fdcan_usb_transmit_msg(uint8_t can_num, TIM_TypeDef* _TIM_TP, uint8_t *raw_msg, uint32_t *sec){
	static u_fdcan_message_info_short _info;
	_info.info_short.start_char = MSG_INFO_START_CHAR;
	_info.info_short.can_number = can_num;
	_info.info_short.seconds = *sec;
	_info.info_short.msec = (uint16_t)(_TIM_TP->CNT >> 1);
	
	u_fdcan_message_hdr* msg_info_ptr = (u_fdcan_message_hdr*) raw_msg;
	uint16_t total_size = fdcan_calculate_total_msg_size(msg_info_ptr);
	
	if(theDeviceModel.deviceModel.scanner_hardware_filter == DEVICE_OPERATION_MODE_ON){
		const uint32_t can_id = msg_info_ptr->msg_hdr.id;
		uint32_t *lower_hardware_filter  = (uint32_t*)(void*)&theDeviceModel.data[Enm_lower_hw_filter_b0];
		uint32_t *higher_hardware_filter  = (uint32_t*)(void*)&theDeviceModel.data[Enm_higher_hw_filter_b0];
		
		if(can_id <= *lower_hardware_filter || can_id >= *higher_hardware_filter){
			return EP_OK;
		}
	}

	uint8_t result = USB_CDC_send_2data(_info.raw_msg_data, sizeof(fdcan_message_info_short), raw_msg, total_size);
	return result;
}

#endif // SUPPORT_FDCAN

