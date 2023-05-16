/****************************************************************
* 
* Can override and scanner functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "can_override.h"
#include "flash_mem_chip_spi.h"
#include "user_cmd.h"

extern uDeviceModel theDeviceModel;
can_injection_status theCanInjectionStatus = {0};

//===============================================================================================
//================================== Circular injection buffer ==================================
//===============================================================================================
	
static uint8_t injection_temp_Buffer[CAN_INJECTION_BUFFER_SIZE];
static uint32_t injection_temp_Buffer_Pos = 0;
static uint32_t injection_temp_Buffer_PendingMsg = 0;

static inline void read_inj_buffer(can_message_info_raw *_can_msg_raw){
/*
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[0] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)];
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[4] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)+4];
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[8] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)+8];
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[12] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)+12];
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[16] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)+16];
	*(uint32_t *)(void *)&_can_msg_raw->raw_msg_data[20] = *(uint32_t *)(void *)&injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)+20];
	*/	
	
	memcpy(&_can_msg_raw->raw_msg_data[0], &injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)], sizeof(can_message_info_raw));
	if(injection_temp_Buffer_Pos < CAN_INJECTION_BUFFER_ITEMS) injection_temp_Buffer_Pos++;
	if(injection_temp_Buffer_PendingMsg > 0) injection_temp_Buffer_PendingMsg--;
}

//===============================================================================================
//============================================ Override =========================================
//===============================================================================================


uint32_t can_recieve_and_usb_transmit_msg(CAN_TypeDef* _CAN_TP, TIM_TypeDef* _TIM_TP, uint32_t FifoNo, can_message_info_raw *outup_msg, uint32_t sec){
	outup_msg->info.start_char = MSG_INFO_START_CHAR;
	outup_msg->info.can_number = (_CAN_TP == CAN1) ? 0x01 : 0x02;
	outup_msg->info.seconds = sec;
	outup_msg->info.msec = (uint16_t)_TIM_TP->CNT / 2;
	Can_Recieve_StdMessage(_CAN_TP, FifoNo, &outup_msg->info.msg);
	if(USB_CDC_send_data(outup_msg->raw_msg_data, 24) == EP_FAILED){
		return EP_FAILED;
	}
	return EP_OK;
}


/**
* brief  Read override settings from memory and init     
* param  can_override_status var 
* param  
* retval 
*/
void initModelOverrideSettings(can_override_status *_ovr_status){
	uint32_t length = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	uint32_t addr = DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS;
	memory_chip_status.memchip_state = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	__disable_irq ();
	read_memchip(&memory_chip_status, addr, (uint8_t *)_ovr_status, length, SPI_no_Dma);	
	__enable_irq ();
}



//===============================================================================================
//============================================ Injection ========================================
//===============================================================================================

void initMessageInjectionStatus(can_injection_status *_status){
	_status->current_address = CAN_INJECTION_MEMCHIP_ADDR;
}

void startMessageInjection(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode){
	initMessageInjectionStatus(_status); // ��������� ��������� �����
	setInjectionMsg(_status, _canInjectionMode); // ��������� ������ ��������� �� ��������
	
}

void stopMessageInjection(){
	stopBasicTimer(TIM2);
}

/**
* brief  Read a message from memory chip and put in the transmission queue     
* param  can_injection_status
* param  eDeviceFunctionMode _canInjectionMode
* retval 
*/

void setInjectionMsg(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode){
	/* The end of the memory chip? */
	if(_status->current_address >= (MEMCHIP_VOLUME - sizeof(can_message_info_raw))){
		/* Circular mode? */
		if((_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR) | (_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR_REV)){
			_status->current_address = CAN_INJECTION_MEMCHIP_ADDR;
		}
		else{
			stopMessageInjection();
			return;
		}
	}	

	if(injection_temp_Buffer_PendingMsg == 0){
		memory_chip_status.memchip_state = CAN_INJECTION_BUFFER_SIZE;
		read_memchip(&memory_chip_status, _status->current_address, &injection_temp_Buffer[0], CAN_INJECTION_BUFFER_SIZE, SPI_no_Dma);
		injection_temp_Buffer_Pos = 0;
		injection_temp_Buffer_PendingMsg = CAN_INJECTION_BUFFER_ITEMS;
		_status->current_address += CAN_INJECTION_BUFFER_SIZE;
	}
	read_inj_buffer(&_status->msg);
		
	/* The end of preset data? */
	if(_status->msg.info.msg.id.ext_id == 0xFFFFFFFF){
		/* Circular mode? */
		if((_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR) | (_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR_REV)){
			_status->current_address = CAN_INJECTION_MEMCHIP_ADDR;
			memory_chip_status.memchip_state = sizeof(can_message_info);
			read_memchip(&memory_chip_status, _status->current_address, &_status->msg.raw_msg_data[0], sizeof(can_message_info), SPI_no_Dma);
		}
		else{
			stopMessageInjection();
			return;
		}
	}
	setInjectionMsgTimer(_status);
}

/**
* brief  Set timer for a message to transmit     
* param  can_injection_status
* param  
* retval 
*/

void setInjectionMsgTimer(can_injection_status *_status){
//	uint32_t seconds_timeout = _status->msg.info.seconds - _status->seconds;
//	uint16_t milseconds_timeout = _status->msg.info.msec - _status->milseconds;
	UNUSED(_status);
	startBasicTimer(0x190, 0xA, TIM2); // 80 ms
}

void injection_timer_procedure(){
	// ��������� ������������������ ���������.
	injectPresetMessage(&theCanInjectionStatus, theDeviceModel.deviceModel.canInjectionMode);
	// ��������� ���������, ��������� ������� �������
	setInjectionMsg(&theCanInjectionStatus, theDeviceModel.deviceModel.canInjectionMode);
	// ��������� ��� ���� ������
}

extern void TIM2_IRQHandler(void);
void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){
		stopBasicTimer(TIM2);
		TIM2->SR &= ~TIM_SR_UIF; // Flag down
		injection_timer_procedure();
	}
}


/**
* brief  Inject a message preset into the CAN bus
* param  can_injection_status
* param  _canInjectionMode
* retval 
*/
void injectPresetMessage(can_injection_status *_status,eDeviceFunctionMode _canInjectionMode){
	/* Reverse mode? */
	CAN_TypeDef * can_num;
	if((_canInjectionMode == DEVICE_OPERATION_MODE_REV) | (_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR_REV)){
		can_num = (_status->msg.info.can_number == 1) ? CAN2 : CAN1;
	}
	else can_num = (_status->msg.info.can_number == 1) ? CAN1 : CAN2;
	Can_Transmit_Message(can_num, &_status->msg.info.msg);
}
