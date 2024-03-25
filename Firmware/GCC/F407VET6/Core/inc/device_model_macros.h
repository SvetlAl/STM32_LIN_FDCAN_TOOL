#ifndef DEVICE_MODEL_MACROS_H_INCLUDED
#define DEVICE_MODEL_MACROS_H_INCLUDED
/****************************************************************
* 
* Device Model structures
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
//#include "project_settings.h"
#include "device_model_board_config.h"

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)

typedef enum{
	DEVICE_OPERATION_MODE_DEFAULT = (uint8_t)0xFF,
	DEVICE_OPERATION_MODE_ON = (uint8_t)0x01,
	DEVICE_OPERATION_MODE_OFF = (uint8_t)0x02,
	DEVICE_OPERATION_MODE_REV = (uint8_t)0x03,   // Reverse CAN1 and CAN2
	DEVICE_OPERATION_MODE_CIRCULAR_REV = (uint8_t)0x04,
	DEVICE_OPERATION_MODE_CIRCULAR = (uint8_t)0x05,
	DEVICE_OPERATION_MODE_FILTR_UPD = (uint8_t)0x06,
	DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD = (uint8_t)0x07,
	DEVICE_OPERATION_MODE_CDC_TRACE_FIXED_THRESHOLD = (uint8_t)0x08,
	DEVICE_OPERATION_MODE_FDCAN_SETTINGS_UPD = (uint8_t)0x09,        // update FDCAN filters
	DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_1 = (uint8_t)0x0A,    // single FDCAN1 message injection
	DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_2 = (uint8_t)0x0B,    // single FDCAN2 message injection
} eDeviceFunctionMode;

	/* this needed for interface application for a correct command set */
typedef enum{
  MEMCHIP_MODEL_DEFAULT = (uint8_t)0xFF,
  MEMCHIP_MODEL_MX25L323 = (uint8_t)0x01,
  MEMCHIP_MODEL_M45PE16 = (uint8_t)0x02,
  MEMCHIP_MODEL_MX25L16 = (uint8_t)0x03,
  MEMCHIP_MODEL_MX35LF1GE4A = (uint8_t)0x04,
	MEMCHIP_MODEL_W25Q16 = (uint8_t)0x05
} eMemChipModel;
	
	
typedef struct DeviceModel{
	eMemChipModel memChipModel;
	eDeviceFunctionMode canGatewayMode;
	eDeviceFunctionMode can2GatewayMode; // OBSOLETE
	eDeviceFunctionMode calibratorMode;
	eDeviceFunctionMode canOverrideMode;
	eDeviceFunctionMode canScannerMode;
	eDeviceFunctionMode can2ScannerMode;
	eDeviceFunctionMode memoryProgramingMode;
	eDeviceFunctionMode canInjectionMode;
	uint8_t val_BTR_PSC;
	uint8_t val_BTR_BS1;
	uint8_t val_BTR_BS2;
	uint8_t val_BTR_SJW;
	eDeviceFunctionMode customBTR;
	uint8_t val_BTR_PSC_2;
	uint8_t val_BTR_BS1_2;
	uint8_t val_BTR_BS2_2;
	uint8_t val_BTR_SJW_2;
	eDeviceFunctionMode customBTR_2;
	eDeviceFunctionMode canInjectionMode_CDC;
	eDeviceFunctionMode canInjection_CDC_threshold_mode;
	uint8_t canInjection_CDC_threshold_value;
	eDeviceFunctionMode scanner_hardware_filter;
	uint8_t lower_hw_filter_b0;
	uint8_t lower_hw_filter_b1;
	uint8_t lower_hw_filter_b2;
	uint8_t lower_hw_filter_b3;
	uint8_t higher_hw_filter_b0;
	uint8_t higher_hw_filter_b1;
	uint8_t higher_hw_filter_b2;
	uint8_t higher_hw_filter_b3;
	
	uint8_t lin_baudrate_preset;
	uint8_t lin_mode;
	uint8_t lin_filter;
	
	uint8_t can_periph_freq;
} DeviceModel; //creating new type

enum DeviceModelProperties{
	Enm_memChipModel = 0,
	Enm_canGatewayMode = 1,
	Enm_can2GatewayMode = 2, // OBSOLETE
	Enm_calibratorMode = 3,
	Enm_canOverrideMode = 4,
	Enm_canScannerMode = 5,
	Enm_can2ScannerMode = 6, 
	Enm_memoryProgramingMode = 7,
	Enm_canInjectionMode = 8, // not tested properly
	Enm_val_BTR_PSC = 9,
	Enm_val_BTR_BS1 = 10,
	Enm_val_BTR_BS2 = 11,
	Enm_val_BTR_SJW = 12,
	Enm_customBTR = 13,
	Enm_val_BTR_PSC_2 = 14,
	Enm_val_BTR_BS1_2 = 15,
	Enm_val_BTR_BS2_2 = 16,
	Enm_val_BTR_SJW_2 = 17,
	Enm_customBTR_2 = 18,
	Enm_canInjectionMode_CDC = 19,
	Enm_canInjection_CDC_threshold_mode = 20,
	Enm_canInjection_CDC_threshold_value = 21,
	Enm_scanner_hardware_filter = 22,
	Enm_lower_hw_filter_b0 = 23,
	Enm_lower_hw_filter_b1 = 24,
	Enm_lower_hw_filter_b2 = 25,
	Enm_lower_hw_filter_b3 = 26,
	Enm_higher_hw_filter_b0 = 27,
	Enm_higher_hw_filter_b1 = 28,
	Enm_higher_hw_filter_b2 = 29,
	Enm_higher_hw_filter_b3 = 30,
	Enm_lin_baudrate_preset = 31,
	Enm_lin_mode = 32,
	Enm_lin_filter = 33,
	Enm_can_periph_freq = 34
};

typedef union uDeviceModel{
	DeviceModel deviceModel;
	uint8_t data[sizeof(DeviceModel)];
}uDeviceModel;

//=========================================================================================================
//===================================== Device modes wraps ================================================
//=========== CAN gateway mode ====================
#define CAN_GATEWAY_MODE theDeviceModel.deviceModel.canGatewayMode
#define SET_CAN_GATEWAY_MODE(uDevMod) (theDeviceModel.deviceModel.canGatewayMode = uDevMod)
//=========== CAN2 gateway mode ====================
// OBSOLETE
#define CAN2_GATEWAY_MODE theDeviceModel.deviceModel.can2GatewayMode
#define SET_CAN2_GATEWAY_MODE(uDevMod) (theDeviceModel.deviceModel.can2GatewayMode = uDevMod)
//========== Calibrator filter mode ===============
#define CALIBRATOR_MODE theDeviceModel.deviceModel.calibratorMode
#define SET_CALIBRATOR_MODE(uDevMod) (theDeviceModel.deviceModel.calibratorMode = uDevMod)
//========== Memory chip model ====================
#define MEMCHIP_MODEL theDeviceModel.deviceModel.memChipModel
#define SET_MEMCHIP_MODEL(uDevMod) (theDeviceModel.deviceModel.memChipModel = uDevMod)
//========== Memory Program mode ====================
#define MEMORY_PROGRAMM_MODE theDeviceModel.deviceModel.memoryProgramingMode
#define SET_MEMCHIP_MEMORY_PROGRAMM_MODE(uDevMod) (theDeviceModel.deviceModel.memoryProgramingMode = uDevMod)
//========== CAN scanner mode ====================
#define CANSCANNER_MODE theDeviceModel.deviceModel.canScannerMode
#define SET_CANSCANNER_MODE(uDevMod) (theDeviceModel.deviceModel.canScannerMode = uDevMod)
//========== 2CAN scanner mode ====================
#define CAN2SCANNER_MODE theDeviceModel.deviceModel.can2ScannerMode
#define SET_CAN2SCANNER_MODE(uDevMod) (theDeviceModel.deviceModel.can2ScannerMode = uDevMod)
//========== CAN override mode ====================
#define CAN_OVERRIDE_MODE theDeviceModel.deviceModel.canOverrideMode
#define SET_CAN_OVERRIDE_MODE(uDevMod) (theDeviceModel.deviceModel.canOverrideMode = uDevMod)
//========== CAN Injection mode ====================
#define CAN_INJECTION_MODE theDeviceModel.deviceModel.canInjectionMode
#define SET_CAN_INJECTION_MEMCHIP_MODE(uDevMod) (theDeviceModel.deviceModel.canInjectionMode = uDevMod)
//========== Custom BTR mode ====================
#define CUSTOM_BTR_MODE theDeviceModel.deviceModel.customBTR
#define SET_CUSTOM_BTR_MODE(uDevMod) (theDeviceModel.deviceModel.customBTR = uDevMod)
//========== Custom BTR_2 mode ====================
#define CUSTOM_BTR_MODE_2 theDeviceModel.deviceModel.customBTR_2
#define SET_CUSTOM_BTR_MODE_2(uDevMod) (theDeviceModel.deviceModel.customBTR_2 = uDevMod)
//========== CAN Injection CDC mode ====================
#define CAN_INJECTION_CDC_MODE theDeviceModel.deviceModel.canInjectionMode_CDC
#define SET_CAN_INJECTION_CDC_MODE(uDevMod) (theDeviceModel.deviceModel.canInjectionMode_CDC = uDevMod)
//========== CAN Injection CDC threshold mode ====================
#define CAN_INJECTION_CDC_THRESHOLD_MODE theDeviceModel.deviceModel.canInjection_CDC_threshold_mode
#define SET_CAN_INJECTION_CDC_THRESHOLD_MODE(uDevMod) (theDeviceModel.deviceModel.canInjection_CDC_threshold_mode = uDevMod)
//========== CAN Injection CDC threshold value ====================
#define CAN_INJECTION_CDC_THRESHOLD_VALUE theDeviceModel.deviceModel.canInjection_CDC_threshold_value
#define SET_CAN_INJECTION_CDC_THRESHOLD_VALUE(uDevMod) (theDeviceModel.deviceModel.canInjection_CDC_threshold_value = uDevMod)
//========== CAN Scanner hardware filter ====================
#define CAN_SCANNER_HARDWARE_FILTER theDeviceModel.deviceModel.scanner_hardware_filter
#define SET_CAN_SCANNER_HARDWARE_FILTER(uDevMod) (theDeviceModel.deviceModel.scanner_hardware_filter = uDevMod)


#endif /* DEVICE_MODEL_MACROS_H_INCLUDED*/
