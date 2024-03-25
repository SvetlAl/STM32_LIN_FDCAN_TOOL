#ifndef DEVICE_MODELS_DEVICE_PRZRK8XL_H_INCLUDED
#define DEVICE_MODELS_DEVICE_PRZRK8XL_H_INCLUDED

/**************************************************************************************************
* 
* This file describes configuration of the "Prizrak 8XL" board.
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

#ifdef DEVICE_PRZRK8XL
#include "stm32h730xx.h"

#define BOARD_MK_STM32H730

//========================================= CAN settings ===================================================
#define SUPPORT_FDCAN
#define CAN_INTERFACES_USED 2

//========================================= TIM clocking settings ==========================================
#define DEV_FREQ	                 360000U
#define DEV_FREQ_400MHZ
#define FD_CAN_CK_FRQ_96MHZ
#define APB1_FREQ_50MHZ
#define TIM2_FREQ_180MHZ                     // used for scanner timestamp and watchdog
#define TIM3_FREQ_180MHZ                     // used for trace injection

//=========================================================================================================
//=====================================       BOR Settings     ============================================
#define BOR_VALUE (uint8_t)0x00 // BOR_3 = 0x00, BOR_2 = 0x01, BOR_1 = 0x02, BOR_OFF = 0x03

//=========================================================================================================
//===================================== Hardware watchdog trigger =========================================
#define TOGGLE_HW_WATCHDOG ((GPIOD->ODR & GPIO_ODR_OD0) ? (GPIOD->BSRR |= GPIO_BSRR_BR0) : (GPIOD->BSRR |= GPIO_BSRR_BS0))


//======================================= Memory chip settings ============================================
#define MEMCHIP_NAND_FLASH

#define MEMCHIP_MX35LF1GE4A
#define MEMCHIP_VOLUME	(128000U + 4000U)*1024U // 1024 blocks

//=======================================  LED signal handling ============================================
/* Main LED */
#define SIGNAL_LED_OFF  GPIOG->BSRR |= GPIO_BSRR_BR0
#define SIGNAL_LED_ON   GPIOG->BSRR |= GPIO_BSRR_BS0

#define TOGGLE_SIGNAL_LED ((GPIOG->ODR & GPIO_ODR_OD0) ? (GPIOG->BSRR |= GPIO_BSRR_BR0) : (GPIOG->BSRR |= GPIO_BSRR_BS0))
		
/* LED A */
#define SIGNAL_LED_A_OFF GPIOG->BSRR |= GPIO_BSRR_BR1
#define SIGNAL_LED_A_ON  GPIOG->BSRR |= GPIO_BSRR_BS1

#define TOGGLE_SIGNAL_LED_A ((GPIOG->ODR & GPIO_ODR_OD1) ? (GPIOG->BSRR |= GPIO_BSRR_BR1) : (GPIOG->BSRR |= GPIO_BSRR_BS1))
		
/* LED B */	
#define SIGNAL_LED_B_OFF GPIOF->BSRR |= GPIO_BSRR_BR15
#define SIGNAL_LED_B_ON GPIOF->BSRR |= GPIO_BSRR_BS15

#define TOGGLE_SIGNAL_LED_B ((GPIOF->ODR & GPIO_ODR_OD15) ? (GPIOF->BSRR |= GPIO_BSRR_BR15) : (GPIOF->BSRR |= GPIO_BSRR_BS15))

//=========================================================================================================
//================================  Reset pin or button handling ==========================================	
#define EMERGENCY_PIN_SET (!(GPIOA->IDR & GPIO_IDR_ID3))

//=========================================================================================================
//===========================================  SPI latch pin ==============================================	
#define CS_SET GPIOB->BSRR |= GPIO_BSRR_BR12;
#define CS_RESET GPIOB->BSRR |= GPIO_BSRR_BS12;

//=========================================================================================================
//===========================================  SPI pin init  ==============================================
#define INIT_MEMCHIP_SPI_PINOUT GPIOB->MODER &= ~GPIO_MODER_MODE12; \
                                GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD12; \
                                GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED12; \
                                GPIOB->MODER |= GPIO_MODER_MODE12_0; \
                                CS_RESET \
                                GPIOB->MODER &= ~GPIO_MODER_MODE13; \
                                GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13; \
                                GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13; \
                                GPIOB->MODER |= GPIO_MODER_MODE13_1; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_0; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_2; \
                                GPIOB->MODER &= ~GPIO_MODER_MODE14; \
                                GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED14; \
                                GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD14; \
                                GPIOB->MODER |= GPIO_MODER_MODE14_1; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL14_0; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL14_2; \
                                GPIOB->MODER &= ~GPIO_MODER_MODE15; \
                                GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15; \
                                GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15; \
                                GPIOB->MODER |= GPIO_MODER_MODE15_1; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_0; \
                                GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_2;
																
//==================================  SPI used for memory chip link =======================================	
#define MEMCHIP_SPI                             ((SPI_TypeDef *) SPI2_BASE)


//=========================================================================================================
//=======================================  Addresses defs =================================================
#define NAND_DATA_SIZE_NA                          0xFFFFFFFF // bytes
#define NAND_DATA_SIZE_LENGTH                      4U   // bytes
#define NAND_APPLICATION_AREA                      19U  // blocks
#define NAND_DATA_AREA_SIZE_ADDRESS(addr)          (uint32_t)(addr + (NAND_BLOCK_SIZE_DATA_SPARE - NAND_PAGE_SIZ_DATA_SPARE)) // 1st byte address --> size address
#define APP_FULL_ADDRESS_FROM_BLOCK(block)         (uint32_t)(block* NAND_BLOCK_SIZE_DATA_SPARE)                              // block num --> address


#define VEHICLE_SETTINGS_BLOCK_ADDRESS             10U                                                                  // block 10 (Address 0x14A000)

#define DEVICE_MODES_BLOCK_ADDRESS                 VEHICLE_SETTINGS_BLOCK_ADDRESS + NAND_APPLICATION_AREA + 1           // block 30 (Address 0x3DE000)

#define FDCAN_SETTINGS_BLOCK_ADDRESS               DEVICE_MODES_BLOCK_ADDRESS + NAND_APPLICATION_AREA + 1               // block 50 (Address 0x672000)

#define BOOTLOADER_EMERGENCY_PROGRAMM_BLOCK_ADDR   FDCAN_SETTINGS_BLOCK_ADDRESS + NAND_APPLICATION_AREA + 1             // block 70 (Address 0x906000)

#define BOOTLOADER_UPDATE_PROGRAMM_BLOCK_ADDR      BOOTLOADER_EMERGENCY_PROGRAMM_BLOCK_ADDR + NAND_APPLICATION_AREA + 1 // block 90 (Address 0xB9A000)

#define FREE_MEMSPACE_ADDRESS                      BOOTLOADER_UPDATE_PROGRAMM_BLOCK_ADDR + NAND_APPLICATION_AREA + 1     // block 110 

#define DEVICE_MODES_SETTINGS_LENGTH               sizeof(DeviceModel)
#define DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH     sizeof(u_can_override_status)
#define DEVICE_FDCAN_SETTINGS_LENGTH               sizeof(u_fdcan_settings)


typedef enum{
	memchipVehicle = 0x00,
	memchipModes = 0x01,
	memchipFdcanSettings = 0x02,
	memchipEmergencyBin = 0x03,
	memchipEmergencyBinSz = 0x04,
	memchipUpdateBin = 0x05,
	memchipUpdateBinSz = 0x06,
} eMemchipAddress;

uint32_t memchip_make_app_address(eMemchipAddress _addr);

//=========================================================================================================
//=========================================   USB Settings  ===============================================
#define USB_PERIPH_HS_IN_FS_MODE      // H7 type
//#define USB_PERIPH_FS_ONLY          // F1, F2 type

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

#endif  // DEVICE_PRZRK8XL

#endif // DEVICE_MODELS_DEVICE_PRZRK8XL_H_INCLUDED

