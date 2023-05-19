#ifndef DEVICE_MODEL_H_INCLUDED
#define DEVICE_MODEL_H_INCLUDED
/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
// #define  __GNUC__ 

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)

#define DEBUG_UNI

/**********************************************************************************************************/
/**********************************************************************************************************/
/******         User settings customized here. Comment/uncomment unused/used configurations           *****/
/**********************************************************************************************************/
/**********************************************************************************************************/

//=========================================================================================================
//=====================================       Environment      ============================================
#define MDK_ARM_ENV

//=========================================================================================================
//=====================================           Model        ============================================
//#define ALLIGATOR
#define TEC_MODULE

//#define DEVICE_2CAN
//#define DEVICE_2CAN_TJA1042
//#define DEVICE_2CAN_BOXED
//#define DEVICE_SIGMA

// If a new model is added, check spi init in spi.h and spi.c
// flash_mem_chip_spi.h and flash_mem_chip_spi.c - memchip description

//=========================================================================================================
//=================================       Processor   frequency   =========================================
//== Timer frequencies are supposed to be twice much more, than defined. Eg TIM1_FREQ_60MHZ means 120 Mhz =
//=========================================================================================================


#if defined(ALLIGATOR) | defined(TEC_MODULE)
#define STM32F205
#define DEV_FREQ	120000
#define DEV_FREQ_120MHZ
#define APB1_FREQ_30MHZ
#define TIM1_FREQ_60MHZ 	// used for scanner timestamp and watchdog
#define TIM2_FREQ_30MHZ 	// used for trace injection
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA)
#define STM32F105
#define DEV_FREQ	72000
#define DEV_FREQ_72MHZ

#define APB1_FREQ_36MHZ
#define TIM1_FREQ_36MHZ 		// used for scanner timestamp and watchdog
#define TIM2_FREQ_36MHZ 		// used for trace injection
#endif


#ifdef APB1_FREQ_30MHZ
#define APB1_FREQ_MHZ	30000	// used for CAN1/CAN2
#elif defined(APB1_FREQ_36MHZ)
#define APB1_FREQ_MHZ	36000	// used for CAN1/CAN2
#elif defined(APB1_FREQ_24MHZ)
#define APB1_FREQ_MHZ	24000	// used for CAN1/CAN2
#endif

//=========================================================================================================
//===================================       Memory chip settings      =====================================

#if defined(ALLIGATOR)
#define MEMCHIP_M45PE16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(TEC_MODULE)
#define MEMCHIP_MX25L16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA)
#define MEMCHIP_MX25L323
#define MEMCHIP_VOLUME	0x200000*2
#endif

//=========================================================================================================
//=======================================  LED signal handling ============================================

#ifdef TEC_MODULE
#define TOGGLE_SIGNAL_LED if(GPIOC->ODR & GPIO_ODR_OD13)  \
	GPIOC->BSRR |= GPIO_BSRR_BR_13;	\
	else GPIOC->BSRR |= GPIO_BSRR_BS_13	\
		
#define SIGNAL_LED_ON GPIOC->BSRR |= GPIO_BSRR_BS_13
#define SIGNAL_LED_OFF GPIOC->BSRR |= GPIO_BSRR_BR_13
	
#elif defined(ALLIGATOR)
#define TOGGLE_SIGNAL_LED if(GPIOA->ODR & GPIO_ODR_OD8)  \
	GPIOA->BSRR |= GPIO_BSRR_BR_8;	\
	else GPIOA->BSRR |= GPIO_BSRR_BS_8	\
		
#define SIGNAL_LED_OFF GPIOA->BSRR |= GPIO_BSRR_BS_8
#define SIGNAL_LED_ON GPIOA->BSRR |= GPIO_BSRR_BR_8
#else
#define SIGNAL_LED_ON 
#define SIGNAL_LED_OFF 
#endif
	
//=========================================================================================================
//================================  Reset pin or button handling ==========================================	
	
#ifdef TEC_MODULE
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID3))
#endif
#ifdef ALLIGATOR
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID1))
#endif
#ifdef DEVICE_2CAN
#define EMERGENCY_PIN_SET (!(GPIOA->IDR & GPIO_IDR_IDR10))
#endif
#ifdef DEVICE_2CAN_TJA1042
#define EMERGENCY_PIN_SET (!(GPIOA->IDR & GPIO_IDR_IDR10))
#endif
#ifdef DEVICE_2CAN_BOXED
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_IDR14))
#endif
#ifdef DEVICE_SIGMA
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_IDR14))
#endif
	
//=========================================================================================================
//==========================================  Includes ====================================================
	
#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#include "stm32f105xc.h"
#endif

#include "spi.h"
#include "can.h"

#define DEVICE_INFO_STRING_SZ 16
//=========================================================================================================
//========================================  Buffer size  ==================================================

#define USB_CDC_CIRC_BUF_USED
#define USB_CDC_CIRC_BUFFER_SIZE 0x800UL*2

#define CAN_INJECTION_BUFFER_ITEMS 2
#define CAN_INJECTION_BUFFER_SIZE CAN_INJECTION_BUFFER_ITEMS*sizeof(can_message_info_raw) // elements count

/**********************************************************************************************************/
/**********************************************************************************************************/
/******                               Protocol settings                                               *****/
/**********************************************************************************************************/
/**********************************************************************************************************/

//=========================================================================================================
//=======================================  Addresses defs =================================================

#define VEHICLE_SETTINGS_ADDRESS                0x000000 // VehicleStruct
#define DEVICE_MODES_ADDRESS                    0x010000 // uDeviceModel, can_override_status theOverrideStatus
#define DEVICE_MODES_SETTINGS_LENGTH            sizeof(DeviceModel)
#define DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS 0x010200
#define DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH  sizeof(u_can_override_status)
	

#define BOOTLOADER_EMERGENCY_PROGRAMM_ADDR      0x020000
#define BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR (0x030000 - 0x04)

#define BOOTLOADER_UPDATE_PROGRAMM_ADDR         0x030000
#define BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR    (0x040000 - 0x04)

#define FREE_MEMSPACE_ADDRESS                   0x040000



	
//=========================================================================================================
//=======================================  Manufactors defs ===============================================


#define NULL_MCODE                 '0'
#define ALLIGATOR_MCODE            '1'
#define TEC_MODULE_MCODE           '2'
#define DEVICE_2CAN_MCODE          '3'
#define DEVICE_2CAN_TJA1042_MCODE  '4'
#define DEVICE_2CAN_BOXED_MCODE    '5'
#define DEVICE_SIGMA_MCODE         '6'

#define DEV_SPD_CLBR_MODE
#define DEV_CANSCANNER_MODE
#define DEV_2CANSCANNER_MODE
#define DEV_CAN_OVERRIDE_MODE
#define DEV_CAN_INJECTION_MODE

/***** Device supported modes are exposed as uint_16 value 0x0000 with bit masks applied on ******/


#define DEV_DEFAULT_CODE           (uint16_t)0x0000


/***** Device modes masks ******/
#ifdef DEV_SPD_CLBR_MODE
#define DEV_SPD_CLBR_CODE_MSK      (uint16_t)0x0001
#else 
#define DEV_SPD_CLBR_CODE_MSK      DEV_DEFAULT_CODE
#endif

#ifdef DEV_CANSCANNER_MODE
#define DEV_CANSCANNER_CODE_MSK	   (uint16_t)0x0002
#else 
#define DEV_CANSCANNER_CODE_MSK    DEV_DEFAULT_CODE
#endif

#ifdef DEV_2CANSCANNER_MODE
#define DEV_2CANSCANNER_CODE_MSK   (uint16_t)0x0004
#else 
#define DEV_2CANSCANNER_CODE_MSK   DEV_DEFAULT_CODE
#endif

#ifdef DEV_CAN_OVERRIDE_MODE
#define DEV_CAN_OVERRIDE_CODE_MSK  (uint16_t)0x0008
#else 
#define DEV_CAN_OVERRIDE_CODE_MSK  DEV_DEFAULT_CODE
#endif

#ifdef DEV_CAN_INJECTION_MODE
#define DEV_CAN_INJECTION_CODE_MSK  (uint16_t)0x0010
#else 
#define DEV_CAN_INJECTION_CODE_MSK  DEV_DEFAULT_CODE
#endif


#define DEV_CODE (uint16_t)(DEV_DEFAULT_CODE | DEV_SPD_CLBR_CODE_MSK | DEV_CANSCANNER_CODE_MSK | DEV_2CANSCANNER_CODE_MSK | DEV_CAN_OVERRIDE_CODE_MSK | DEV_CAN_INJECTION_CODE_MSK)

#define DEV_CODE_HBYTE(x) (uint8_t) ((DEV_CODE >> (12 - x*4)) & ~0xF0)
#define DEV_CODE_ASCII(x) (uint8_t) ((DEV_CODE_HBYTE(x) >= 10) ? ('A' + DEV_CODE_HBYTE(x) -10) : ('0' + DEV_CODE_HBYTE(x)))	



typedef enum{
	DEVICE_OPERATION_MODE_DEFAULT = (uint8_t)0xFF,
	DEVICE_OPERATION_MODE_ON = (uint8_t)0x01,
	DEVICE_OPERATION_MODE_OFF = (uint8_t)0x02,
	DEVICE_OPERATION_MODE_REV = (uint8_t)0x03,   // Reverse CAN1 and CAN2
	DEVICE_OPERATION_MODE_CIRCULAR_REV = (uint8_t)0x04,
	DEVICE_OPERATION_MODE_CIRCULAR = (uint8_t)0x05,
	DEVICE_OPERATION_MODE_FILTR_UPD = (uint8_t)0x06} eDeviceFunctionMode;

	/* this needed for interface application for a correct command set */
typedef enum{
	MEMCHIP_MODEL_DEFAULT = (uint8_t)0xFF,
	MEMCHIP_MODEL_MX25L323 = (uint8_t)0x01,
	MEMCHIP_MODEL_M45PE16 = (uint8_t)0x02,
	MEMCHIP_MODEL_MX25L16 = (uint8_t)0x03 } eMemChipModel;
	
	
typedef struct DeviceModel{
	eMemChipModel memChipModel;
	eDeviceFunctionMode canGatewayMode;
	eDeviceFunctionMode can2GatewayMode; // OBSOLETE
	eDeviceFunctionMode calibratorFilterMode;
	eDeviceFunctionMode canOverrideMode;
	eDeviceFunctionMode canScannerMode;
	eDeviceFunctionMode can2ScannerMode;
	eDeviceFunctionMode memoryProgramingMode;
	eDeviceFunctionMode canInjectionMode;
} DeviceModel; //creating new type

enum DeviceModelProperties{
    Enm_memChipModel = 0,
    Enm_canGatewayMode = 1,
    Enm_can2GatewayMode = 2, // OBSOLETE
    Enm_calibratorFilterMode = 3,
    Enm_canOverrideMode = 4,
    Enm_canScannerMode = 5,
    Enm_can2ScannerMode = 6, 
    Enm_memoryProgramingMode = 7,
    Enm_canInjectionMode = 8,
};


typedef union uDeviceModel{
	DeviceModel deviceModel;
	uint8_t data[sizeof(DeviceModel)];
}uDeviceModel;



//=========================================================================================================
//====================================   The Vehicle global var  ==========================================

extern uDeviceModel theDeviceModel;

//=========== CAN gateway mode ====================
#define CAN_GATEWAY_MODE theDeviceModel.deviceModel.canGatewayMode
#define SET_CAN_GATEWAY_MODE(uDevMod) (theDeviceModel.deviceModel.canGatewayMode = uDevMod)
//=========== CAN2 gateway mode ====================
// OBSOLETE
#define CAN2_GATEWAY_MODE theDeviceModel.deviceModel.can2GatewayMode
#define SET_CAN2_GATEWAY_MODE(uDevMod) (theDeviceModel.deviceModel.can2GatewayMode = uDevMod)
//========== Calibrator filter mode ===============
#define CALIBRATOR_FILTER_MODE theDeviceModel.deviceModel.calibratorFilterMode
#define SET_CALIBRATOR_FILTER_MODE(uDevMod) (theDeviceModel.deviceModel.calibratorFilterMode = uDevMod)
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
#define SET_CAN_INJECTION_MODE(uDevMod) (theDeviceModel.deviceModel.canInjectionMode = uDevMod)



//=========================================================================================================
//================================== Version managmement functions  =======================================

uint8_t* getDeviceSoftwareVersion (void);
uint8_t* getHardwareVersion(void);
void initDeviceModelDefaults(uDeviceModel *p_deviceModel);
void initDeviceGeneralPinout(void);
void initModelSettings(void);


//=========================================================================================================
//====================================== Standart format defs  ============================================


#define DEVICE_MODEL_OK 		0
#define DEVICE_MODEL_FAIL 	1




#endif /* DEVICE_MODEL_H_INCLUDED*/
