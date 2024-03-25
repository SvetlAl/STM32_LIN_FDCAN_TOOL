#ifndef FDCAN_OVERRIDE_H_INCLUDED
#define FDCAN_OVERRIDE_H_INCLUDED

/****************************************************************
* 
* FD CAN override and scanner functions
*
* Alex Svetlichnyy 2024 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

#include "USB_CDC/stm32h7xx_usbdfs_cdc.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan_buffer.h"
#include "BxCAN/can_macros.h"



//========================================================================================
//===========================   The Vehicle global var  ==================================
//========================================================================================
uint8_t *fdcan_get_filter_ptr(void);

//========================================================================================
//===========================   Apply FD CAN filter and calibrate ========================
//========================================================================================
void fdcan_can_override_calibrate(uint8_t* msg);

uint8_t filter_condition_match(uint16_t can_num, uint32_t _id);
void fdcan_apply_filter(uint16_t can_num, uint16_t data_sz);

#endif /* CAN_OVERRIDE_H_INCLUDED*/
