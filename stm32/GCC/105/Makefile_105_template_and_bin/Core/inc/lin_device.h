#ifndef LIN_DEVICE_H_INCLUDED
#define LIN_DEVICE_H_INCLUDED

#include "device_model.h"
#include "lin_item.h"
#include "lin.h"

void lin_device_report(lin_message_info_raw *_item);
void lin_device_master_tx(void);
void lin_device_slave_rx(void);


#endif /* LIN_DEVICE_H_INCLUDED*/
