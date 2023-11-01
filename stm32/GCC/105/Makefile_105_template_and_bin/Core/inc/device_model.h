#ifndef DEVICE_MODEL_H_INCLUDED
#define DEVICE_MODEL_H_INCLUDED
/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*
*
* It's recommended to perform full memory chip erase before first usage.
* 
* Connect to device using any COM-Port terminal and send @S00000007@E command. Then wait about 30 seconds.
*****************************************************************/
// #define  __GNUC__ 

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)

#define DEBUG_MODE

/**********************************************************************************************************/
/**********************************************************************************************************/
/******         User settings customized here. Comment/uncomment unused/used configurations           *****/
/**********************************************************************************************************/
/**********************************************************************************************************/

//=========================================================================================================
//=====================================       Environment      ============================================
//#define MDK_ARM_ENV // if MDK ARM Keil IDE is used

//=========================================================================================================
//=====================================           Model        ============================================
/*
Tank-300 vehicle.c
*/
//#define ALLIGATOR
//#define TEC_MODULE

#define DEVICE_2CAN
//#define DEVICE_2CAN_TJA1042
//#define DEVICE_2CAN_BOXED
//#define DEVICE_SIGMA
//#define DEVICE_1CAN2LIN
//#define DEVICE_FCAN_V6

// If a new model is added, check spi init in spi.h and spi.c
// flash_mem_chip_spi.h and flash_mem_chip_spi.c - memchip description

//=========================================================================================================
//=================================     Extra functions and tests    ======================================
//#define TEST_SPEED_TRANSMITTER
//#define TEST_SPEED_RESPONDER


//=========================================================================================================
//=====================================     Supported modes    ============================================
// Comment/Uncomment to reduce code size and RAM usage
#define CAN_TX_BUFFER_ENABLED                 // Buffered CAN transmission.  Buffer size is defined in "can_buffer.h"
//#define SUPPORT_MEMCHIP_CAN_INJECTION				// playing CAN trace from a memory chip


//#define SUPPORT_SPEEDO_CALIBRATOR

#ifdef DEVICE_2CAN // USART is supported for DEVICE_2CAN only
#define SUPPORT_USART
#ifdef SUPPORT_USART
#define SUPPORT_LIN     // Enable/disable LIN
#endif
#endif

#if defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define CAN_INTERFACES_USED 1
#else 
#define CAN_INTERFACES_USED 2
#endif

//=========================================================================================================
//=====================================     LIN Settings    ===============================================
#ifdef SUPPORT_LIN 
#define LIN_PROGRAMM_PRESETS      // Enable/disable LIN programm presets
#define LIN_DEVICE_SUPPORT        // Device mode works as a regular LIN device with a Master logic in "void lin_device_master_rx()"/"void lin_device_master_tx()"
                                  // and Slave logic in "void lin_device_slave_rx()"/"void lin_device_slave_tx()"
#endif

//=========================================================================================================
//=====================================     IRQ priorities    =============================================
#define USB_FS_IRQ_P                  5  // This should be the highest priority
#define CAN1_RX0_IRQ_P                7
#define CAN2_RX0_IRQ_P                8
#define CAN1_TX_IRQ_P                 9
#define CAN2_TX_IRQ_P                 9
#define CAN1_SCE_IRQ_P                8
#define CAN2_SCE_IRQ_P                8

#define MAIN_TIMER_IRQ_P              11  // This timer is used for timestamps and watchdog procedure
#define TRACE_INJ_TIMER_IRQ_P         4   // This timer is used to schedule CAN trace play into a network

#define USART_IRQ_P                   15  // All USARTs have the same priority

#define LIN_MS_POLLING_TIM_IRQ_P      14  // This timer is used for LIN Master polling period
#define LIN_SLAVE_USART_IRQ_P         10
#define LIN_MASTER_USART_IRQ_P        10


//=========================================================================================================
//=================================       Processor   frequency   =========================================
//== Timer frequencies are supposed to be twice much more, than defined. Eg TIM1_FREQ_60MHZ means 120 Mhz =
//=========================================================================================================

#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
#define STM32F205
#define DEV_FREQ	120000
#define DEV_FREQ_120MHZ
#define APB1_FREQ_30MHZ
#define TIM1_FREQ_60MHZ 	// used for scanner timestamp and watchdog
#define TIM2_FREQ_30MHZ 	// used for trace injection

#define APB2_FREQ_60MHZ
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA) | defined(DEVICE_1CAN2LIN)
#define STM32F105
#define DEV_FREQ	72000
#define DEV_FREQ_72MHZ
#define APB1_FREQ_36MHZ
#define TIM1_FREQ_36MHZ 		// used for scanner timestamp and watchdog
#define TIM2_FREQ_36MHZ 		// used for trace injection

#define APB2_FREQ_36MHZ
#endif


#ifdef APB1_FREQ_30MHZ
#define APB1_FREQ_MHZ	30000	// used for CAN1/CAN2
#define CAN_INJ_TIM_PSC (uint16_t)0x1780 // used for injection CAN messages timing
#elif defined(APB1_FREQ_36MHZ)
#define APB1_FREQ_MHZ	36000	// used for CAN1/CAN2
#define CAN_INJ_TIM_PSC (uint16_t)0x1C34 // used for injection CAN messages timing
#elif defined(APB1_FREQ_24MHZ)
#define APB1_FREQ_MHZ	24000	// used for CAN1/CAN2
#endif

//=========================================================================================================
//============================ Timer settings of CAN message trace-player =================================

// Since it's not possible to send a big real trace to a network at maximum supported CAN speed, it's needed to set minimum milsec timeout to slow down transmission.
// For example, the app can't keep sending messages with so little as 0.1 msec timeout between them,
// So we set CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD as 50, and minimum timeout between messages is 5 msec.
//
// This is a default value
// actual value is stored in theDeviceModel.deviceModel.canInjection_CDC_threshold_value

#define CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD (uint8_t)0x0D // real-time timing with max 4 messages with 10 msec period




//=========================================================================================================
//=====================================       BOR Settings     ============================================
#ifdef STM32F205
#define BOR_VALUE (uint8_t)0x00 // BOR_3 = 0x00, BOR_2 = 0x01, BOR_1 = 0x02, BOR_OFF = 0x03
#endif


//=========================================================================================================
//===================================       Memory chip settings      =====================================

#if defined(ALLIGATOR) | defined(DEVICE_FCAN_V6)
#define MEMCHIP_M45PE16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(TEC_MODULE)
#define MEMCHIP_MX25L16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA) | defined(DEVICE_1CAN2LIN)
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
 
#elif defined(DEVICE_FCAN_V6)
#define SIGNAL_LED_OFF GPIOB->BSRR |= GPIO_BSRR_BR_0
#define SIGNAL_LED_ON GPIOB->BSRR |= GPIO_BSRR_BS_0

#define TOGGLE_SIGNAL_LED if(GPIOB->ODR & GPIO_ODR_OD0)  \
	SIGNAL_LED_OFF;	\
	else SIGNAL_LED_ON	\
		

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
#ifdef DEVICE_1CAN2LIN
#define EMERGENCY_PIN_SET (!(GPIOA->IDR & GPIO_IDR_IDR10))
#endif
#ifdef DEVICE_FCAN_V6
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID1))
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

//#include "vehicle.h"
#include "spi.h"
#include "can.h"

//#ifdef SUPPORT_USART
#include "usart.h"
//#include "lin.h"
//#endif

#define DEVICE_INFO_STRING_SZ 16
//=========================================================================================================
//========================================  Buffer size  ==================================================

#define USB_CDC_CIRC_BUF_USED
#if defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define USB_CDC_CIRC_BUFFER_SIZE 0x100 // 0x800UL*2
#else 
#define USB_CDC_CIRC_BUFFER_SIZE 0x200UL*2// 0x400UL*2
#endif


// CAN injection from memory chip
#ifdef SUPPORT_MEMCHIP_CAN_INJECTION
#define CAN_INJECTION_BUFFER_ITEMS 2
#define CAN_INJECTION_BUFFER_SIZE CAN_INJECTION_BUFFER_ITEMS*sizeof(can_message_info_raw) // elements count
#endif

// CAN injection from USB CDC
#if defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define CDC_CAN_INJECTION_BUFFER_ITEMS 16 //256
#else 
#define CDC_CAN_INJECTION_BUFFER_ITEMS 256
#endif

#define CDC_CAN_INJECTION_BUFFER_SIZE CDC_CAN_INJECTION_BUFFER_ITEMS*sizeof(can_message_info_raw) // elements count


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
#define DEVICE_1CAN2LIN_MCODE      '7'
#define DEVICE_FCAN_V6_MCODE       '8'


typedef enum{
	DEVICE_OPERATION_MODE_DEFAULT = (uint8_t)0xFF,
	DEVICE_OPERATION_MODE_ON = (uint8_t)0x01,
	DEVICE_OPERATION_MODE_OFF = (uint8_t)0x02,
	DEVICE_OPERATION_MODE_REV = (uint8_t)0x03,   // Reverse CAN1 and CAN2
	DEVICE_OPERATION_MODE_CIRCULAR_REV = (uint8_t)0x04,
	DEVICE_OPERATION_MODE_CIRCULAR = (uint8_t)0x05,
	DEVICE_OPERATION_MODE_FILTR_UPD = (uint8_t)0x06,
	DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD = (uint8_t)0x07,
	DEVICE_OPERATION_MODE_CDC_TRACE_FIXED_THRESHOLD = (uint8_t)0x08} eDeviceFunctionMode;

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
	Enm_lin_filter = 33
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


//=========================================================================================================
//================================== Version managmement functions  =======================================

uint8_t* getDeviceSoftwareVersion (void);
uint8_t* getHardwareVersion(void);
void initDeviceModelDefaults(uDeviceModel *p_deviceModel);
void initDeviceGeneralPinout(void);
void initModelSettings(void);
void initCANSettings(uint16_t vehicle_model, uDeviceModel *p_deviceModel);


//=========================================================================================================
//==================================   Power management functions   =======================================

#ifdef STM32F205
void set_bor_level(uint8_t br_lvl);
#endif


//=========================================================================================================
//====================================== Standart format defs  ============================================


#define DEVICE_MODEL_OK 		0
#define DEVICE_MODEL_FAIL 	1




















//=========================================================================================================
//================================================ OBSOLETE  ==============================================

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




#endif /* DEVICE_MODEL_H_INCLUDED*/
