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
#include "cdc_flow_can_buffer.h"

extern uDeviceModel theDeviceModel;
can_injection_status theCanInjectionStatus = {0};
static dual_cdc_can_buff theDualBuffer;


//===============================================================================================
//============================================ Scanner ==========================================
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


//===============================================================================================
//============================================ Override =========================================
//===============================================================================================

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
//================================== Circular injection buffer ==================================
//===============================================================================================
	
static uint8_t injection_temp_Buffer[CAN_INJECTION_BUFFER_SIZE];
static uint32_t injection_temp_Buffer_Pos = 0;
static uint32_t injection_temp_Buffer_PendingMsg = 0;

static inline void read_inj_buffer(can_message_info_raw *_can_msg_raw){
	memcpy(&_can_msg_raw->raw_msg_data[0], &injection_temp_Buffer[injection_temp_Buffer_Pos*sizeof(can_message_info_raw)], sizeof(can_message_info_raw));
	if(injection_temp_Buffer_Pos < CAN_INJECTION_BUFFER_ITEMS) injection_temp_Buffer_Pos++;
	if(injection_temp_Buffer_PendingMsg > 0) injection_temp_Buffer_PendingMsg--;
}
//===============================================================================================
//=================================== Injection from memory chip ================================
//===============================================================================================

void initMessageInjectionStatus(can_injection_status *_status){
	_status->current_address = CAN_INJECTION_MEMCHIP_ADDR;
}

void startMessageInjection(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode){
	stopMessageInjection();
	initMessageInjectionStatus(_status); 
	setInjectionMsg(_status, _canInjectionMode);
}

void stopMessageInjection(){
	deinit_dual_cc_buf(&theDualBuffer);
	SET_CAN_INJECTION_CDC_MODE(DEVICE_OPERATION_MODE_OFF);
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


void injection_timer_procedure(){
	if(theDeviceModel.deviceModel.canInjectionMode_CDC != DEVICE_OPERATION_MODE_OFF){
			
		if(theCanInjectionStatus.msg.info.start_char == '@'){
			injectPresetMessage(&theCanInjectionStatus, theDeviceModel.deviceModel.canInjectionMode_CDC);
			CDC_setInjectionMsg(&theCanInjectionStatus);
		}
		else{
			CDC_stopMessageInjection();
		}
		
	}
	else if(theDeviceModel.deviceModel.canInjectionMode != DEVICE_OPERATION_MODE_OFF){
		injectPresetMessage(&theCanInjectionStatus, theDeviceModel.deviceModel.canInjectionMode);
		setInjectionMsg(&theCanInjectionStatus, theDeviceModel.deviceModel.canInjectionMode);
	}
}


//===============================================================================================
//====================================== Injection from USB CDC =================================
//===============================================================================================

static inline void send_needed_length(uint32_t length){
	length = length/sizeof(can_message_info_raw);
	uint8_t bytes_count_arr[4] = {
		SC_BYTE_FROM32BIT(length, 0),
		SC_BYTE_FROM32BIT(length, 1),
		SC_BYTE_FROM32BIT(length, 2),
		SC_BYTE_FROM32BIT(length, 3)
	};
	USB_CDC_send_data(bytes_count_arr, 4);
}

void CDC_initMessageInjection(){
	theCanInjectionStatus.current_address = 0xFFFFFFFF;
	uint32_t bytes_count = init_dual_cc_buf(&theDualBuffer);
	send_needed_length(bytes_count);
}

void CDC_startMessageInjection(){
	theDualBuffer.status |= DUAL_CCB_INJECTION_STARTED;
	CDC_setInjectionMsg(&theCanInjectionStatus);
}


void CDC_setInjectionMsg(can_injection_status *_status){
	uint32_t refill_size = pop_dual_cc_buf_item(&theCanInjectionStatus.msg, &theDualBuffer);
	if(refill_size){
		send_needed_length(refill_size);
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
	UNUSED(_status);
	calculate_tim_settings(_status);
	startBasicTimer(_status->tim_val.prescaler, _status->tim_val.reloadValue, TIM2); // 80 ms
}


extern void TIM2_IRQHandler(void);
void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){
		stopBasicTimer(TIM2);
		TIM2->SR &= ~TIM_SR_UIF; // Flag down
		injection_timer_procedure();
	}
}

void CDC_can_inj_recieve_data(uint8_t *data, uint32_t length){
	fill_dual_cc_buf(&theDualBuffer, data, length);

	if(theDualBuffer.status & DUAL_CCB_INITED_FLAG){
		if(!(theDualBuffer.status & DUAL_CCB_INJECTION_STARTED)){
			CDC_startMessageInjection();
		}
	}	
}

void CDC_stopMessageInjection(){
	deinit_dual_cc_buf(&theDualBuffer);
	SET_CAN_INJECTION_CDC_MODE(DEVICE_OPERATION_MODE_OFF);
	stopBasicTimer(TIM2);
	const uint32_t stop_cmd = 0xFFFFFFFF;
	uint8_t bytes_stop_cmd_arr[4] = {
		SC_BYTE_FROM32BIT(stop_cmd, 0),
		SC_BYTE_FROM32BIT(stop_cmd, 1),
		SC_BYTE_FROM32BIT(stop_cmd, 2),
		SC_BYTE_FROM32BIT(stop_cmd, 3)
	};
	USB_CDC_send_data(bytes_stop_cmd_arr, 4);
}



/**
* brief  Inject a message preset into the CAN bus
* param  can_injection_status
* param  _canInjectionMode
* retval 
*/
void injectPresetMessage(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode){
	/* Reverse mode? */
	CAN_TypeDef * can_num;
	if((_canInjectionMode == DEVICE_OPERATION_MODE_REV) | (_canInjectionMode == DEVICE_OPERATION_MODE_CIRCULAR_REV)){
		can_num = (_status->msg.info.can_number == 1) ? CAN2 : CAN1;
	}
	else can_num = (_status->msg.info.can_number == 1) ? CAN1 : CAN2;
	Can_Transmit_Message(can_num, &_status->msg.info.msg);
}

/**
* brief  calculate prescaler and reload value for CAN injection
* param  
* param  
* retval 
*/
	
void calculate_tim_settings(can_injection_status *_status){
	uint32_t sec_residue; // = _status->seconds == _status->tim_val.ref_seconds ? ;
	uint16_t msec_residue; // = _status->seconds - _status->tim_val.ref_seconds;
	
	if((_status->msg.info.seconds < _status->tim_val.ref_seconds) | ((_status->msg.info.seconds == _status->tim_val.ref_seconds) & (_status->msg.info.msec < _status->tim_val.ref_milseconds))){
		_status->tim_val.ref_seconds = 0;
		_status->tim_val.ref_milseconds = 0;
	}
	
	if(_status->msg.info.msec >= _status->tim_val.ref_milseconds){
		msec_residue = (uint16_t)(_status->msg.info.msec - _status->tim_val.ref_milseconds);
		sec_residue  = _status->msg.info.seconds - _status->tim_val.ref_seconds;
	}
	else if(_status->msg.info.msec < _status->tim_val.ref_milseconds){
		msec_residue = (uint16_t)(9999 - _status->tim_val.ref_milseconds + _status->msg.info.msec);
		sec_residue  = _status->msg.info.seconds - _status->tim_val.ref_seconds - 1;
	}	
	else{
		msec_residue = 0;
		sec_residue  = 1;
	}
	_status->tim_val.ref_seconds = (uint16_t)_status->msg.info.seconds;
	_status->tim_val.ref_milseconds = _status->msg.info.msec;
	
	_status->tim_val.prescaler = CAN_INJ_TIM_PSC;
	_status->tim_val.reloadValue = (uint16_t)((uint16_t)(sec_residue*10000) + msec_residue);
	
	//if(_status->tim_val.reloadValue == 0) _status->tim_val.reloadValue = 5;
	if(_status->tim_val.reloadValue < CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD) _status->tim_val.reloadValue = (uint16_t)CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD;
}
