#ifndef FDCAN_SCANNER_H_INCLUDED
#define FDCAN_SCANNER_H_INCLUDED

/****************************************************************
* 
* FD CAN override and scanner functions
*
* Alex Svetlichnyy 2024 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

#ifdef SUPPORT_FDCAN

#include "FDCAN/fdcan.h"
#include "FDCAN/fdcan_macros.h"


/****************************************************************************************/
/*************************************** Main format settings. **************************/
/****************************************************************************************/
//#define CAN_INJECTION_MEMCHIP_ADDR	FREE_MEMSPACE_ADDRESS
#define MSG_INFO_START_CHAR		'#'



//========================================================================================
//===========================   The Vehicle global var  ==================================
//========================================================================================


//========================================================================================
//===========================           Scanner         ==================================
//========================================================================================

uint32_t fdcan_usb_transmit_msg(uint8_t can_num, TIM_TypeDef* _TIM_TP, uint8_t *raw_msg, uint32_t *sec);

#endif // SUPPORT_FDCAN

#endif // FDCAN_SCANNER_H_INCLUDED
