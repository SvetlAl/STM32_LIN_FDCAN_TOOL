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
#if defined BOARD_MK_STM32F105 | defined BOARD_MK_STM32F205 | defined BOARD_MK_STM32F407
#include "USB_CDC/stm32f105_usbdfs_cdc.h"
#include "USB_CDC/stm32f105_usbdfs_macros.h"
#include "BxCAN/can_cdc_player.h"
#include "BxCAN/can_buffer.h"
#endif // defined BOARD_MK_STM32F105 | defined BOARD_MK_STM32F205

//=========================================================================================================
//==========================================    F105    ===================================================
#ifdef BOARD_MK_STM32F105

#include "stm32f105_clock.h"

#if defined(SUPPORT_LIN)
#include "LIN/lin.h"
#define PROCESS_LIN_ENGINE lin_process_engine();
#else 
#define PROCESS_LIN_ENGINE
#endif // defined(SUPPORT_LIN)
#else 
#define PROCESS_LIN_ENGINE
#endif // BOARD_MK_STM32F105
//=========================================================================================================
//==========================================    F205    ===================================================
#ifdef BOARD_MK_STM32F205
#include "stm32f205_clock.h"
#endif
//=========================================================================================================
//==========================================    F407    ===================================================
#ifdef BOARD_MK_STM32F407
#include "stm32f407_clock.h"
#endif
//=========================================================================================================
//==========================================    H730    ===================================================
#ifdef BOARD_MK_STM32H730
#include "stm32h730_clock.h"
#endif

#if defined BOARD_MK_STM32H730
#include "USB_CDC/stm32h7xx_usbdfs_cdc.h"
#include "USB_CDC/stm32h7xx_usbdfs_macros.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan_can_override.h"
#endif

//=========================================================================================================
//============================================= Common ====================================================

#include "Commands/el_protocol.h"
#include "Commands/user_cmd.h"
#include "string_convertor.h"
#include "runtime.h"
#include "TIM/tim.h"
#include "watchdog.h"
#include "vehicle.h"
#include <string.h>
#include "SPI/spi.h"
#include "extras.h"

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
	                          NVIC_SetPriority(TIM1_UP_TIM10_IRQn, MAIN_TIMER_IRQ_P);
	
#elif defined(BOARD_MK_STM32F105)
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM1_UP_IRQn); \
                            NVIC_SetPriority(TIM1_UP_IRQn, MAIN_TIMER_IRQ_P);
														
#elif defined(BOARD_MK_STM32F407)
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM1_UP_TIM10_IRQn); \
                            NVIC_SetPriority(TIM1_UP_TIM10_IRQn, MAIN_TIMER_IRQ_P);
														
#endif
#if defined(BOARD_MK_STM32H730)
#define ENABLE_MAIN_TIM_IRQ NVIC_EnableIRQ (TIM2_IRQn); \
                            NVIC_SetPriority(TIM2_IRQn, MAIN_TIMER_IRQ_P);
#endif

//====================================== CAN Trace player timer ===========================================

#if defined(BOARD_MK_STM32F105) || defined(BOARD_MK_STM32F205) || defined(BOARD_MK_STM32F407)
#define ENABLE_TRACE_PLAYER_TIM_IRQ	NVIC_EnableIRQ (TIM2_IRQn); \
                                    NVIC_SetPriority(TIM2_IRQn, TRACE_INJ_TIMER_IRQ_P);
#elif defined(BOARD_MK_STM32H730)
#define ENABLE_TRACE_PLAYER_TIM_IRQ NVIC_EnableIRQ (TIM3_IRQn); \
                                    NVIC_SetPriority(TIM3_IRQn, TRACE_INJ_TIMER_IRQ_P);
#endif

//=========================================================================================================
//=========================================== Startup Wrap ================================================
//=========================================================================================================
#if defined BOARD_MK_STM32F105 | defined BOARD_MK_STM32F205 | defined BOARD_MK_STM32F407
#define ENABLE_USB_CDC USB_OTG_FS_init_pinout(); \
                       USB_OTG_FS_init_device();
#elif defined BOARD_MK_STM32H730
#define ENABLE_USB_CDC USB_OTG_HS_init_pinout(); \
                       USB_OTG_HS_init_device();
#endif

//=========================================================================================================
//=========================================== Functions ===================================================
//=========================================================================================================

//=========================================================================================================
//=========================================== Setters/Getters =============================================
volatile uint32_t *get_main_tim_sec_ptr(void);
uint32_t get_main_tim_secs(void);

void resetCanTimer(TIM_TypeDef * TIM_n);
	
#endif /* MAIN_H_INCLUDED*/
