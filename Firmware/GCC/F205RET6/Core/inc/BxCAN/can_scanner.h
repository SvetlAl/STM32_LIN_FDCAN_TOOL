//****************************************************************************************
// 
// 
// bxCAN gateway override functions
//
// Alex Svetlichnyy 2019
//****************************************************************************************
#ifndef CAN_SCANNER_H_INCLUDED
#define CAN_SCANNER_H_INCLUDED

#include "device_model.h"
#ifdef SUPPORT_BXCAN

#include "BxCAN/can.h"

/*******************************************************
* 								Scanner
*******************************************************/
uint32_t can_receive_and_usb_transmit_msg(CAN_TypeDef* _CAN_TP, TIM_TypeDef* _TIM_TP, uint32_t FifoNo, can_message_info_raw *outup_msg, uint32_t sec);

#endif // SUPPORT_BXCAN

#endif /* CAN_SCANNER_H_INCLUDED*/
