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

//#define DEBUG_MODE


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
//============================ Timer settings of CAN message trace-player =================================

// Since it's not possible to send a big real trace to a network at maximum supported CAN speed, it's needed to set minimum milsec timeout to slow down transmission.
// For example, the app can't keep sending messages with so little as 0.1 msec timeout between them,
// So we set CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD as 50, and minimum timeout between messages is 5 msec.
//
// This is a default value
// actual value is stored in theDeviceModel.deviceModel.canInjection_CDC_threshold_value

#define CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD (uint8_t)0x0D // real-time timing with max 4 messages with 10 msec period

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
extern uDeviceModel theDeviceModel;

//=========================================================================================================
//======================================= Initialization ==================================================
void make_default_device_settings(uDeviceModel *p_deviceModel);
void init_device_settings(void);
void init_STD_CAN_settings(uint16_t vehicle_model, uDeviceModel *p_deviceModel);
void init_CAN_settings(uint16_t vehicle_model);
void init_CAN_override_settings(void);

//=========================================================================================================
//================================== Version managmement functions  =======================================
uint8_t* getDeviceSoftwareVersion (void);

//=========================================================================================================
//=========================================== Setters/getters =============================================
uDeviceModel * get_device_model_ptr(void);
uint8_t *get_device_modes_data(void);

//=========================================================================================================
//========================================   Misc. functions   ============================================
void restart_fd_can(void);


#endif /* DEVICE_MODEL_H_INCLUDED*/
