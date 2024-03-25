//*****************************************************************
// 
// STM32F105/205
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************

#include "device_model.h"
#ifdef SUPPORT_BXCAN
#include "BxCAN/can_scanner.h"

#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
#include "USB_CDC/stm32f105_usbdfs_cdc.h"
#endif 

#define MSG_INFO_START_CHAR		'@'

//===============================================================================================
//============================================ Scanner ==========================================
//===============================================================================================

uint32_t can_receive_and_usb_transmit_msg(CAN_TypeDef* _CAN_TP, TIM_TypeDef* _TIM_TP, uint32_t FifoNo, can_message_info_raw *outup_msg, uint32_t sec){
	uDeviceModel* device_ptr = get_device_model_ptr();
	
	outup_msg->info.start_char = MSG_INFO_START_CHAR;
	outup_msg->info.can_number = (_CAN_TP == CAN1) ? 0x01 : 0x02;
	outup_msg->info.seconds = sec;
	outup_msg->info.msec = (uint16_t)_TIM_TP->CNT / 2;
	Can_Recieve_StdMessage(_CAN_TP, FifoNo, &outup_msg->info.msg);
	
	if(device_ptr->deviceModel.scanner_hardware_filter == DEVICE_OPERATION_MODE_ON){
		can_message *can_msg_ptr = &outup_msg->info.msg;
		uint32_t *lower_hardware_filter  = (uint32_t*)(void*)&device_ptr->data[Enm_lower_hw_filter_b0];
		uint32_t *higher_hardware_filter  = (uint32_t*)(void*)&device_ptr->data[Enm_higher_hw_filter_b0];
		
		if((CAN_ID(can_msg_ptr) <= *lower_hardware_filter) || (CAN_ID(can_msg_ptr) >= *higher_hardware_filter)){
			return EP_OK;
		}
	}
	if(USB_CDC_send_data(outup_msg->raw_msg_data, 24) == EP_FAILED){
		return EP_FAILED;
	}
	return EP_OK;
}

#endif // SUPPORT_BXCAN

