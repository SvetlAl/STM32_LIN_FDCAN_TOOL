#ifndef DEVICE_MODELS_DEVICE_ALLIGATOR_H_INCLUDED
#define DEVICE_MODELS_DEVICE_ALLIGATOR_H_INCLUDED

/**************************************************************************************************
* 
* This file describes configuration of the "Alligator 2CAN" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "project_settings.h"
#ifdef DEVICE_ALLIGATOR
#include "stm32f205xx.h"

#define BOARD_MK_STM32F205

//========================================= Bootloader settings ============================================
#define MAIN_PROGRAM_START_ADDRESS          (uint32_t)0x08004000

//========================================= CAN settings ===================================================
#define SUPPORT_BXCAN
#define CAN_INTERFACES_USED 2

#define CAN1_INIT_PINS GPIOB->MODER &= ~GPIO_MODER_MODER8; \
                       GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8; \
                       GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD8; \
                       GPIOB->MODER |= GPIO_MODER_MODER8_1; \
                       GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED8; \
                       GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_0; \
                       GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_3; \
                       GPIOB->MODER &= ~GPIO_MODER_MODER9; \
                       GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED9; \
                       GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD9; \
                       GPIOB->MODER |= GPIO_MODER_MODER9_1; \
                       GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED9; \
                       GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_0; \
                       GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_3;
											 
#define CAN2_INIT_PINS GPIOB->MODER &= ~GPIO_MODER_MODER5; \
                       GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5; \
                       GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5; \
                       GPIOB->MODER |= GPIO_MODER_MODER5_1; \
                       GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5; \
                       GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_0; \
                       GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_3; \
                       GPIOB->MODER &= ~GPIO_MODER_MODER6; \
                       GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6; \
                       GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6; \
                       GPIOB->MODER |= GPIO_MODER_MODER6_1; \
                       GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6; \
                       GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_0; \
                       GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_3;
											 
//========================================= TIM clocking settings ==========================================
#define DEV_FREQ	        120000U
#define DEV_FREQ_120MHZ
#define APB1_FREQ_30MHZ
#define TIM1_FREQ_60MHZ 	// used for scanner timestamp and watchdog
#define TIM2_FREQ_30MHZ 	// used for trace injection

#define APB2_FREQ_60MHZ

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
//===================================== Hardware watchdog trigger =========================================
#define TOGGLE_HW_WATCHDOG

//=========================================================================================================
//=====================================       BOR Settings     ============================================
#define BOR_VALUE (uint8_t)0x00 // BOR_3 = 0x00, BOR_2 = 0x01, BOR_1 = 0x02, BOR_OFF = 0x03


//======================================= Memory chip settings ============================================
#define MEMCHIP_NOR_FLASH

#define MEMCHIP_M45PE16
#define MEMCHIP_VOLUME	0x1F4000

//=======================================  LED signal handling ============================================
#define TOGGLE_SIGNAL_LED if(GPIOA->ODR & GPIO_ODR_OD8)  \
	GPIOA->BSRR |= GPIO_BSRR_BR_8;	\
	else GPIOA->BSRR |= GPIO_BSRR_BS_8	\
		
#define SIGNAL_LED_OFF GPIOA->BSRR |= GPIO_BSRR_BS_8
#define SIGNAL_LED_ON GPIOA->BSRR |= GPIO_BSRR_BR_8
	
		
/* LED A */
#define SIGNAL_LED_A_OFF
#define SIGNAL_LED_A_ON
#define TOGGLE_SIGNAL_LED_A
		
/* LED B */	
#define SIGNAL_LED_B_OFF
#define SIGNAL_LED_B_ON
#define TOGGLE_SIGNAL_LED_B

//=========================================================================================================
//================================  Reset pin or button handling ==========================================	
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID1))

//=========================================================================================================
//===========================================  SPI latch pin ==============================================	
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;

//=========================================================================================================
//===========================================  SPI pin init  ==============================================
#define INIT_MEMCHIP_SPI_PINOUT GPIOA->MODER &= ~GPIO_MODER_MODER4; \
                                GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4; \
                                GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4; \
                                GPIOA->MODER |= GPIO_MODER_MODER4_0; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_0; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_2; \
                                CS_SET \
                                GPIOA->MODER &= ~GPIO_MODER_MODER5; \
                                GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5; \
                                GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5; \
                                GPIOA->MODER |= GPIO_MODER_MODER5_1; \
                                GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_2; \
                                GPIOA->MODER &= ~GPIO_MODER_MODER6; \
                                GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6; \
                                GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD6; \
                                GPIOA->MODER |= GPIO_MODER_MODER6_1; \
                                GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_0; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_2; \
                                GPIOA->MODER &= ~GPIO_MODER_MODER7; \
                                GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7; \
                                GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD7; \
                                GPIOA->MODER |= GPIO_MODER_MODER7_1; \
                                GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL7_0; \
                                GPIOA->AFR[0] |= GPIO_AFRL_AFSEL7_2;
																
//==================================  SPI used for memory chip link =======================================	
#define MEMCHIP_SPI                             ((SPI_TypeDef *) SPI1_BASE)
	
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

typedef enum{
	memchipVehicle = 0x00,
	memchipModes = 0x01,
	memchipOverrideFilters = 0x02,
	memchipEmergencyBin = 0x03,
	memchipEmergencyBinSz = 0x04,
	memchipUpdateBin = 0x05,
	memchipUpdateBinSz = 0x06,
} eMemchipAddress;

uint32_t memchip_make_app_address(eMemchipAddress _addr);

//=========================================================================================================
//=========================================   USB Settings  ===============================================
//#define USB_PERIPH_HS_IN_FS_MODE      // H7 type
#define USB_PERIPH_FS_ONLY          // F1, F2 type

#define USB_PERIPH_FS_SPD             // HS or FS
#define USB_PERIPH_USB1               // USB1 or USB2


//=========================================================================================================
//========================================   Initialization  ==============================================
void init_device_general_pinout(void);
//=========================================================================================================
//==================================   Power management functions   =======================================
void set_bor_level(uint8_t br_lvl);
//=========================================================================================================
//===================================   Version management functions   ====================================
uint8_t *get_board_name(void);

#endif // DEVICE_ALLIGATOR

#endif // DEVICE_MODELS_DEVICE_ALLIGATOR_H_INCLUDED
