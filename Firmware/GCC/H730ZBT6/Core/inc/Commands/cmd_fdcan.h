#ifndef CMD_FDCAN_H_INCLUDED
#define CMD_FDCAN_H_INCLUDED
/****************************************************************
* 
* FD CAN user command handler
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
* 
*****************************************************************/
#include "device_model.h"
#include "Commands/user_cmd.h"


void process_fdcan_cmd(elp_cmd *com);


#endif // CMD_FDCAN_H_INCLUDED
