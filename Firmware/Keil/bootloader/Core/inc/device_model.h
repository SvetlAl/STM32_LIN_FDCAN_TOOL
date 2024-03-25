#ifndef DEVICE_MODEL_H_INCLUDED
#define DEVICE_MODEL_H_INCLUDED
/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
* It's recommended to perform full memory chip erase before first usage.
* 
*****************************************************************/
#include "project_settings.h"
#include "device_model_macros.h"


//=========================================================================================================
//=====================================     IRQ priorities    =============================================
#define USB_FS_IRQ_P                  1  // This should be the highest priority
#define CAN1_RX0_IRQ_P                7
#define CAN2_RX0_IRQ_P                7
#define CAN1_TX_IRQ_P                 9
#define CAN2_TX_IRQ_P                 9
#define CAN1_SCE_IRQ_P                8
#define CAN2_SCE_IRQ_P                8

#define MAIN_TIMER_IRQ_P              11  // This timer is used for timestamps and watchdog procedure
#define TRACE_INJ_TIMER_IRQ_P         6   // This timer is used to schedule CAN trace play into a network

#define USART_IRQ_P                   15  // All USARTs have the same priority

#define LIN_MS_POLLING_TIM_IRQ_P      14  // This timer is used for LIN Master polling period
#define LIN_SLAVE_USART_IRQ_P         10
#define LIN_MASTER_USART_IRQ_P        10


//=========================================================================================================
//==========================================  Includes ====================================================
#ifdef MEMCHIP_NAND_FLASH
#include "Flash_memchip/flash_nand_mem_chip_spi.h"

typedef union nand_app_address{
	uint32_t word32;
	uint8_t data8[4];
}nand_app_address;

uint32_t make_app_address(uint16_t assgnd_blk);
#endif // MEMCHIP_NAND_FLASH

//=========================================================================================================
//======================================== Global var =====================================================


//=========================================================================================================
//======================================= Initialization ==================================================

//=========================================================================================================
//================================== Version managmement functions  =======================================


//=========================================================================================================
//=========================================== Setters/getters =============================================


//=========================================================================================================
//========================================   Misc. functions   ============================================



#endif /* DEVICE_MODEL_H_INCLUDED*/
