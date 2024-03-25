#ifndef DEVICE_MODELS_DEVICE_2CAN_H_INCLUDED
#define DEVICE_MODELS_DEVICE_2CAN_H_INCLUDED

/**************************************************************************************************
* 
* This file describes configuration of the "Starline 2CAN2LIN v4" board.
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
#ifdef DEVICE_2CAN

#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#include "stm32f105xc.h"


#define BOARD_MK_STM32F105

//========================================= Bootloader settings ============================================
#define MAIN_PROGRAM_START_ADDRESS          (uint32_t)0x08004000

//========================================= CAN settings ===================================================
#define SUPPORT_BXCAN
#define CAN_INTERFACES_USED 2

#define CAN1_INIT_PINS GPIOB->CRH	&= ~GPIO_CRH_CNF8; \
                       GPIOB->CRH 	&= ~GPIO_CRH_MODE8; \
                       GPIOB->CRH	&= ~GPIO_CRH_CNF9; \
                       GPIOB->CRH	|= GPIO_CRH_CNF8_0;	\
                       GPIOB->CRH	|= GPIO_CRH_CNF9_1;	\
                       GPIOB->CRH 	|= GPIO_CRH_MODE9;	\
                       AFIO->MAPR  |= AFIO_MAPR_CAN_REMAP_REMAP2;
											 
#define CAN2_INIT_PINS GPIOB->CRL	&= ~GPIO_CRL_CNF5;	\
                       GPIOB->CRL 	&= ~GPIO_CRL_MODE5; \
                       GPIOB->CRL	&= ~GPIO_CRL_CNF6; \
                       GPIOB->CRL	|= GPIO_CRL_CNF5_0; \
                       GPIOB->CRL	|= GPIO_CRL_CNF6_1; \
                       GPIOB->CRL 	|= GPIO_CRL_MODE6; \
                       AFIO->MAPR  |= AFIO_MAPR_CAN2_REMAP;

//========================================= TIM clocking settings ==========================================
#define DEV_FREQ	72000U
#define DEV_FREQ_72MHZ
#define APB1_FREQ_36MHZ
#define TIM1_FREQ_36MHZ 		// used for scanner timestamp and watchdog
#define TIM2_FREQ_36MHZ 		// used for trace injection

#define APB2_FREQ_36MHZ

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
#define TOGGLE_HW_WATCHDOG  // not used

//=========================================================================================================
//========================================       BOR Settings     =========================================
#define BOR_VALUE (uint8_t)0x00 // BOR_3 = 0x00, BOR_2 = 0x01, BOR_1 = 0x02, BOR_OFF = 0x03

//======================================= Memory chip settings ============================================
#define MEMCHIP_NOR_FLASH

#define MEMCHIP_MX25L323
#define MEMCHIP_VOLUME	0x1F4000*2

//=======================================  LED signal handling ============================================
// ** Not supported for this board
#define SIGNAL_LED_ON      // There's no LED on the board
#define SIGNAL_LED_OFF     // There's no LED on the board
#define TOGGLE_SIGNAL_LED
		
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
#define EMERGENCY_PIN_SET (!(GPIOA->IDR & GPIO_IDR_IDR10))

//=========================================================================================================
//===========================================  SPI latch pin ==============================================	
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;

//=========================================================================================================
//===========================================  SPI pin init  ==============================================
#define INIT_MEMCHIP_SPI_PINOUT GPIOA->CRL |= GPIO_CRL_MODE4; \
                                GPIOA->CRL &= ~GPIO_CRL_CNF4; \
                                CS_SET \
                                GPIOA->CRL |= GPIO_CRL_MODE5; \
                                GPIOA->CRL &= ~GPIO_CRL_CNF5; \
                                GPIOA->CRL |= GPIO_CRL_CNF5_1; \
                                GPIOA->CRL &= ~GPIO_CRL_MODE6; \
                                GPIOA->CRL &= ~GPIO_CRL_CNF6; \
                                GPIOA->CRL |= GPIO_CRL_CNF6_1; \
                                GPIOA->BSRR = GPIO_BSRR_BS6; \
                                GPIOA->CRL |= GPIO_CRL_MODE7; \
                                GPIOA->CRL &= ~GPIO_CRL_CNF7; \
                                GPIOA->CRL |= GPIO_CRL_CNF7_1;

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
//=======================================  USART Settings =================================================
#define USART1_INIT_PINS // not used
#define USART2_INIT_PINS GPIOA->CRL	&= ~(uint32_t)(GPIO_CRL_CNF2); \
                         GPIOA->CRL	|=  (uint32_t)(GPIO_CRL_CNF2_1); \
                         GPIOA->CRL	|=  (uint32_t)(GPIO_CRL_MODE2); \
                         GPIOA->CRL &= ~(uint32_t)(GPIO_CRL_CNF3); \
                         GPIOA->CRL &= ~(uint32_t)(GPIO_CRL_CNF3_0); \
                         GPIOA->CRL &= ~(uint32_t)(GPIO_CRL_MODE3);

#define USART3_INIT_PINS GPIOC->CRH	&= ~(uint32_t)(GPIO_CRH_CNF10); \
                         GPIOC->CRH	|=  (uint32_t)(GPIO_CRH_CNF10_1); \
                         GPIOC->CRH	|=  (uint32_t)(GPIO_CRH_MODE10); \
                         GPIOC->CRH &= ~(uint32_t)(GPIO_CRH_CNF11); \
                         GPIOC->CRH &= ~(uint32_t)(GPIO_CRH_CNF11_0); \
                         GPIOC->CRH &= ~(uint32_t)(GPIO_CRH_MODE11); \
												 AFIO->MAPR |= AFIO_MAPR_USART3_REMAP_0;

#define USART_INIT_PINS USART2_INIT_PINS \
                        USART3_INIT_PINS
												
#define SUPPORT_USART2
#define SUPPORT_USART2_IRQ
#define SUPPORT_USART2_LIN

#define SUPPORT_USART3
#define SUPPORT_USART3_IRQ
#define SUPPORT_USART3_LIN
//=========================================================================================================
//========================================  LIN Settings  =================================================
#define SUPPORT_LIN_MASTER
#define LIN_MASTER_USART_NUM       2U
#define LIN_MASTER_USART_PERIPH    USART2

#define SUPPORT_LIN_SLAVE
#define LIN_SLAVE_USART_NUM        3U
#define LIN_SLAVE_USART_PERIPH     USART3

#define LIN_HARDWARE_PULLUP GPIOA->CRL	&= ~GPIO_CRL_CNF0; \
                            GPIOA->CRL 	|= GPIO_CRL_MODE0_0; \
                            GPIOA->CRL 	|= GPIO_CRL_MODE0_1; \
                            GPIOA->BSRR |= GPIO_BSRR_BS0; \
                            GPIOC->CRL	&= ~GPIO_CRL_CNF4; \
                            GPIOC->CRL 	|= GPIO_CRL_MODE4_0; \
                            GPIOC->CRL 	|= GPIO_CRL_MODE4_1; \
                            GPIOC->BSRR |= GPIO_BSRR_BS4; \
                            GPIOB->CRL	&= ~GPIO_CRL_CNF1; \
                            GPIOB->CRL 	|= GPIO_CRL_MODE1_0; \
                            GPIOB->CRL 	|= GPIO_CRL_MODE1_1; \
                            GPIOB->BSRR |= GPIO_BSRR_BS1; \
                            GPIOC->CRL	&= ~GPIO_CRL_CNF5; \
                            GPIOC->CRL 	|= GPIO_CRL_MODE5_0; \
                            GPIOC->CRL 	|= GPIO_CRL_MODE5_1; \
                            GPIOC->BSRR |= GPIO_BSRR_BS5;
														
#define LIN_SET_INTERRUPT_PRIORITY NVIC_SetPriority(USART2_IRQn, LIN_MASTER_USART_IRQ_P); \
                                   NVIC_SetPriority(USART3_IRQn, LIN_SLAVE_USART_IRQ_P);

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


#endif // DEVICE_2CAN

#endif // DEVICE_MODELS_DEVICE_2CAN_H_INCLUDED
