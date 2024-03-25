#ifndef LIN_DEVICE_H_INCLUDED
#define LIN_DEVICE_H_INCLUDED

#include "LIN/lin.h"

//=========================================================================================================
//======================================= LIN device mode functions =======================================
void lin_device_report(lin_message_info_raw *_item);
void lin_device_slave_rx(void);
void lin_device_master_tx(void);


#endif /* LIN_DEVICE_H_INCLUDED*/
