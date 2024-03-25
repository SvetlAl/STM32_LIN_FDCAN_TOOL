#ifndef FDCAN_STD_CAN_LEGACY_H_INCLUDED
#define FDCAN_STD_CAN_LEGACY_H_INCLUDED

/****************************************************************
*
* FD CAN
*
* FDCAN legacy library to use a code based on a standart can.h 
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"

#ifdef SUPPORT_FDCAN
#include "BxCAN/can_macros.h"

can_message *legacy_can_message(void);

void legacy_can_to_fdcan(can_message *_std, uint8_t *_fd);
void legacy_fdcan_to_can(can_message *_std, uint8_t *_fd);

void legacy_queue_std_msg_tx(uint8_t can_num, can_message *_std);

#endif // SUPPORT_FDCAN


#endif //FDCAN_STD_CAN_LEGACY_H_INCLUDED
