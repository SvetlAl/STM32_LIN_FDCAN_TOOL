/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"
#include "Commands/user_cmd.h"

#if defined BOARD_MK_STM32H730
#include "FDCAN/fdcan.h"
#endif

//==============================================================================================
//================================== The Vehicle global var ====================================
uDeviceModel theDeviceModel;

//==============================================================================================
//================================== Device version ============================================
static uint8_t deviceSoftwareVersion[DEVICE_INFO_STRING_SZ] = {
	'v',
	'1',
	'.',
	'2',
	'0',
	'.',
	'0',
	'3',
	'.',
	'2',
	'4',
	'.',
	'0',
	'0',
	'0',
	'0' };



/**
* brief  Init DEFAULT "Device modes". Supported modes defined in "uDeviceModel": Scanner, Gateway, Calibrator...
* param  uDeviceModel ref
* param  
* retval 
*/	
void make_default_device_settings(uDeviceModel *p_deviceModel){
	p_deviceModel->deviceModel.canGatewayMode = DEVICE_OPERATION_MODE_ON;
	p_deviceModel->deviceModel.calibratorMode = DEVICE_OPERATION_MODE_ON;
	p_deviceModel->deviceModel.canInjectionMode = DEVICE_OPERATION_MODE_OFF;
	p_deviceModel->deviceModel.canOverrideMode = DEVICE_OPERATION_MODE_OFF;
	p_deviceModel->deviceModel.customBTR = DEVICE_OPERATION_MODE_OFF;
	p_deviceModel->deviceModel.customBTR_2 = DEVICE_OPERATION_MODE_OFF;
	
	#ifdef MEMCHIP_MX25L323
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_MX25L323;
	#endif
	#ifdef MEMCHIP_M45PE16
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_M45PE16;
	#endif
	#ifdef MEMCHIP_MX25L16
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_MX25L16;
	#endif
	#ifdef MEMCHIP_MX35LF1GE4A
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_MX35LF1GE4A;
	#endif
	#ifdef MEMCHIP_W25Q16
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_W25Q16;
	#endif
	
	#if defined(SUPPORT_FDCAN) & (defined(FD_CAN_CK_FRQ_96MHZ) )
	p_deviceModel->deviceModel.can_periph_freq = 96;
	#endif
}

/**
* brief  Init CAN
* param  vehicle and device settings
* param  
* retval 
*/	
#ifdef SUPPORT_BXCAN
void init_STD_CAN_settings(uint16_t vehicle_model, uDeviceModel *p_deviceModel){
	can_btr_setting  settings_can1;
	can_btr_setting  settings_can2;
	if(CUSTOM_BTR_MODE == DEVICE_OPERATION_MODE_OFF){
		if(vehicle_model < MODEL_COUNT){
			settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
			settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
		}	
		//========== default BTR preset =============
		else{
			settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
			settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
		}
	}
	else if(CUSTOM_BTR_MODE == DEVICE_OPERATION_MODE_ON){
		settings_can1.psc = p_deviceModel->deviceModel.val_BTR_PSC > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_PSC - 1) : 0;
		settings_can1.bs1 = p_deviceModel->deviceModel.val_BTR_BS1 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS1 - 1) : 0;
		settings_can1.bs2 = p_deviceModel->deviceModel.val_BTR_BS2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS2 - 1) : 0;
		settings_can1.sjw = p_deviceModel->deviceModel.val_BTR_SJW > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_SJW - 1) : 0;
		
		settings_can2.psc = p_deviceModel->deviceModel.val_BTR_PSC_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_PSC_2 - 1) : 0;
		settings_can2.bs1 = p_deviceModel->deviceModel.val_BTR_BS1_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS1_2 - 1) : 0;
		settings_can2.bs2 = p_deviceModel->deviceModel.val_BTR_BS2_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS2_2 - 1) : 0;
		settings_can2.sjw = p_deviceModel->deviceModel.val_BTR_SJW_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_SJW_2 - 1) : 0;
	}
	else{
		//========== default BTR preset =============
		settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
		settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
	}
	Can_Init(settings_can1, settings_can2);  
}
#endif

/**
* brief  This function incapsulates both STD CAN init and FD CAN init
* param  vehicle model
* param  
* retval 
*/
void init_CAN_settings(uint16_t vehicle_model){
	#ifdef SUPPORT_BXCAN
	init_STD_CAN_settings(vehicle_model, &theDeviceModel);
	#endif
	#ifdef SUPPORT_FDCAN
	fdcan_settings *stng = fdcan_get_settings();
	if(stng->data_bitrate[0].PSC == 0xFF){
		fdcan_make_default_cfg();
	}
	fdcan_init();
	#endif
	
}
/**
* brief  Load "Device modes". Supported modes defined in "uDeviceModel": Scanner, Gateway, Calibrator...
* param  defined with preprocessor
* param  
* retval 
*/

void init_device_settings(){

	//======== Gateway is always on by default ==========================
	if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_DEFAULT){
		make_default_device_settings(&theDeviceModel);
	}
	
	//======= Memory programming is always off from the start ===========
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
	
	//======= CDC CAN injection is always off from the start ============
	SET_CAN_INJECTION_CDC_MODE(DEVICE_OPERATION_MODE_OFF);
	
	//======= Scanner is always off from the start ======================
	SET_CANSCANNER_MODE(DEVICE_OPERATION_MODE_OFF);
	SET_CAN2SCANNER_MODE(DEVICE_OPERATION_MODE_OFF);
	
	//======= If custom calibration filter is default, set it on ========
	//===== and set all settings according to calibration preset ========
	if(CALIBRATOR_MODE == DEVICE_OPERATION_MODE_DEFAULT) SET_CALIBRATOR_MODE(DEVICE_OPERATION_MODE_ON);
	if(CALIBRATOR_MODE == DEVICE_OPERATION_MODE_ON){
		SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
		SET_CAN_OVERRIDE_MODE(DEVICE_OPERATION_MODE_OFF);
		SET_CAN_INJECTION_MEMCHIP_MODE(DEVICE_OPERATION_MODE_OFF);
	}
	
	//=== CDC CAN injection's timing threshold default value - auto =====
	if((CAN_INJECTION_CDC_THRESHOLD_MODE != DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD) ||
		(CAN_INJECTION_CDC_THRESHOLD_MODE != DEVICE_OPERATION_MODE_CDC_TRACE_FIXED_THRESHOLD)){
			SET_CAN_INJECTION_CDC_THRESHOLD_MODE(DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD);
	}
	
	if((CAN_INJECTION_CDC_THRESHOLD_VALUE < CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD) || (CAN_INJECTION_CDC_THRESHOLD_VALUE == 0xFF))
		SET_CAN_INJECTION_CDC_THRESHOLD_VALUE(CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD);
	
	//======= Hardware filter is always off from the start ==============
	if(CAN_SCANNER_HARDWARE_FILTER == DEVICE_OPERATION_MODE_DEFAULT) SET_CAN_SCANNER_HARDWARE_FILTER(DEVICE_OPERATION_MODE_OFF);
	
	// LIN & USART
	#if defined(SUPPORT_USART)
	init_device_usart(Baudrate_9600);
	#ifdef SUPPORT_LIN
	if(theDeviceModel.deviceModel.lin_baudrate_preset == DEVICE_OPERATION_MODE_DEFAULT){
		theDeviceModel.deviceModel.lin_baudrate_preset = LIN_9600;
	}
	if(theDeviceModel.deviceModel.lin_mode == DEVICE_OPERATION_MODE_DEFAULT){
		theDeviceModel.deviceModel.lin_mode = 0x00;
		theDeviceModel.deviceModel.lin_mode |= (uint8_t)((LIN_STATUS_ON << 4) &~0x0F); // LIN validation ON
		theDeviceModel.deviceModel.lin_mode |= LIN_MODE_DEFAULT;
	}
	if(theDeviceModel.deviceModel.lin_filter == DEVICE_OPERATION_MODE_DEFAULT){
		theDeviceModel.deviceModel.lin_filter = LIN_FILTER_OFF;
	}
			
	volatile uint32_t *sec_ptr = get_main_tim_sec_ptr();
	enable_lin(&theDeviceModel.deviceModel.lin_mode,
             &theDeviceModel.deviceModel.lin_baudrate_preset,
	           &theDeviceModel.deviceModel.lin_filter,
	           MAIN_TIMER, 
	           sec_ptr);
	#endif // SUPPORT_LIN
	#endif // #if defined(SUPPORT_USART)
}

void init_CAN_override_settings(void){
	#ifdef SUPPORT_BXCAN
	if(*can_override_get_dataptr() == 0xFF){ // Make sure the override status data is valid
		memset((void *)can_override_get_dataptr(), 0x00, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH);
	}
	#endif
}


#ifdef SUPPORT_FDCAN
void restart_fd_can(void){
	fdcan_init();
}
#endif


//=========================================================================================================
//================================== Version managmement functions  =======================================
uint8_t* getDeviceSoftwareVersion (void){return &deviceSoftwareVersion[0];}

//=========================================================================================================
//======================================== Setters/getters ================================================
uDeviceModel* get_device_model_ptr(void){
	return &theDeviceModel;
}

uint8_t *get_device_modes_data(){
	return &theDeviceModel.data[0];
}


