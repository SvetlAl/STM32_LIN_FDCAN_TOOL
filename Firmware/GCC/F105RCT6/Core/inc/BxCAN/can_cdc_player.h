#ifndef CAN_CDC_PLAYER_H_INCLUDED
#define CAN_CDC_PLAYER_H_INCLUDED

/****************************************************************
* 
* Can override and scanner functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"
#ifdef SUPPORT_BXCAN
//#include "BxCAN/can_macros.h"
#include "can.h"
#include "USB_CDC/stm32f105_usbdfs_cdc.h"
#include "TIM/tim.h"


/****************************************************************************************/
/*************************************** Main format settings. **************************/
/****************************************************************************************/

#define CAN_INJECTION_MEMCHIP_ADDR	FREE_MEMSPACE_ADDRESS


/****************************************************************************************/
/****** User settings customized here. Comment/uncomment unused/used configurations *****/
/****************************************************************************************/
#define FOCRED_DELAY_STEP            0x0AU // 0x3E8 // (100.0) msecs

#define BUFFER_OVERFLOW_CTR_LEVEL_PRCNT 75    // percents
#define BUFFER_OVERFLOW_CTR_LEVEL (CDC_CAN_INJECTION_BUFFER_SIZE*BUFFER_OVERFLOW_CTR_LEVEL_PRCNT)/100





//=========================================================================================================
//====================================   The Vehicle global var  ==========================================
//=========================================================================================================
/*******************************************************
* 								Injection from memory chip
*******************************************************/
#ifdef SUPPORT_MEMCHIP_CAN_INJECTION
void startMessageInjection(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode);
#endif
/*******************************************************
* 								Injection from USB CDC
*******************************************************/
void CDC_startMessageInjection(void);
void CDC_stopMessageInjection(void);
void CDC_initMessageInjection(void);
void CDC_can_inj_receive_data(uint8_t *data, uint32_t length);


void stopMessageInjection(void);


#endif // SUPPORT_BXCAN


#endif /* CAN_CDC_PLAYER_H_INCLUDED*/
