#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define STARTUP_TIMEOUT 0x1FFF

/****************************************************************
* A device based on STM32F105 / F205 / H730
*
*
* Library code is mostly standalone except marked as @DD
*
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "device_model.h"

//=========================================================================================================
//===================================== Includes dependencies chain =======================================
//=========================================================================================================

//=========================================================================================================
//=======================================    F105 F205    =================================================

//=========================================================================================================
//==========================================    F105    ===================================================
#ifdef BOARD_MK_STM32F105
#include "stm32f105_clock.h"
#include "Flash/flash_f105.h"
#endif // BOARD_MK_STM32F105
//=========================================================================================================
//==========================================    F205    ===================================================
#ifdef BOARD_MK_STM32F205
#include "stm32f205_clock.h"
#include "Flash/flash_f205.h"
#endif
//=========================================================================================================
//==========================================    H730    ===================================================
#ifdef BOARD_MK_STM32H730
#include "stm32h730_clock.h"
#include "Flash/flash_h730.h"
#endif

//=========================================================================================================
//============================================= Common ====================================================
#include "string_convertor.h"
#include "runtime.h"
#include "watchdog.h"
#include <string.h>
#include "SPI/spi.h"


#ifdef MEMCHIP_NOR_FLASH
#include "Flash_memchip/flash_nor_mem_chip_spi.h"
#endif
#ifdef MEMCHIP_NAND_FLASH
#include "Flash_memchip/flash_nand_mem_chip_spi.h"
#endif

//=========================================================================================================
//====================================== Interrupt init Wrap ==============================================
//=========================================================================================================

//====================================== STD/FD CAN RX ====================================================
#ifdef SUPPORT_BXCAN
#define ENABLE_CAN1_RX_IRQ NVIC_EnableIRQ(CAN1_RX0_IRQn); \
                           NVIC_SetPriority(CAN1_RX0_IRQn, CAN1_RX0_IRQ_P);
#ifdef DEVICE_1CAN2LIN
#define ENABLE_CAN2_RX_IRQ
#else
#define ENABLE_CAN2_RX_IRQ NVIC_EnableIRQ(CAN2_RX0_IRQn); \
                           NVIC_SetPriority(CAN2_RX0_IRQn, CAN2_RX0_IRQ_P);
#endif // DEVICE_1CAN2LIN
#endif // SUPPORT_BXCAN

#ifdef SUPPORT_FDCAN
#define ENABLE_CAN1_RX_IRQ NVIC_EnableIRQ(FDCAN1_IT0_IRQn); \
                           NVIC_SetPriority(FDCAN1_IT0_IRQn, CAN1_RX0_IRQ_P);

#define ENABLE_CAN2_RX_IRQ NVIC_EnableIRQ(FDCAN2_IT0_IRQn); \
                           NVIC_SetPriority(FDCAN2_IT0_IRQn, CAN2_RX0_IRQ_P);

#endif // SUPPORT_FDCAN

//========================================== Main timer ===================================================
	// watchdog
#ifdef BOARD_MK_STM32F205
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); \
	                          NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 11);
	
#elif defined(BOARD_MK_STM32F105)
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM1_UP_IRQn); \
                            NVIC_SetPriority(TIM1_UP_IRQn, MAIN_TIMER_IRQ_P);
#endif
#if defined(BOARD_MK_STM32H730)
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM2_IRQn); \
                            NVIC_SetPriority(TIM2_IRQn, MAIN_TIMER_IRQ_P);
#endif

//====================================== CAN Trace player timer ===========================================

#if defined(BOARD_MK_STM32F105) || defined(BOARD_MK_STM32F205)
#define ENABLE_TRACE_PLAYER_TIM_IRQ	NVIC_EnableIRQ (TIM2_IRQn); \
                                    NVIC_SetPriority(TIM2_IRQn, TRACE_INJ_TIMER_IRQ_P);
#elif defined(BOARD_MK_STM32H730)
#define ENABLE_TRACE_PLAYER_TIM_IRQ NVIC_EnableIRQ (TIM3_IRQn); \
                                    NVIC_SetPriority(TIM3_IRQn, TRACE_INJ_TIMER_IRQ_P);
#endif

//=========================================================================================================
//=========================================== Startup Wrap ================================================
//=========================================================================================================
#if defined BOARD_MK_STM32F105 | defined BOARD_MK_STM32F205
#define ENABLE_USB_CDC USB_OTG_FS_init_pinout(); \
                       USB_OTG_FS_init_device();
#elif defined BOARD_MK_STM32H730
#define ENABLE_USB_CDC USB_OTG_HS_init_pinout(); \
                       USB_OTG_HS_init_device();
#endif

//=========================================================================================================
//=========================================== Typedefs ====================================================
//=========================================================================================================

typedef void(*pFunction)(void);

typedef struct FlashSize{
	uint32_t size;
} FlashSize; //creating new type


typedef union uFlashSize{
	FlashSize _flashSize;
	uint8_t data[sizeof(FlashSize)];
}uFlashSize;


#define VERIFY_FAILED		0x00   
#define VERIFY_OK				0x01

#define BOOTLOADER_DEFAULT_MODE				0x00
#define BOOTLOADER_EMERGENCY_MODE			0x01
#define BOOTLOADER_UPDATE_MODE				0x02
#define BOOTLOADER_TEST_MODE					0x03

#define INVALID_UPDATE_SIZE						0xFFFFFFFF

//=========================================================================================================
//=========================================== Functions ===================================================
//=========================================================================================================

//=========================================================================================================
//=========================================== Setters/Getters =============================================

	
#endif /* MAIN_H_INCLUDED*/
