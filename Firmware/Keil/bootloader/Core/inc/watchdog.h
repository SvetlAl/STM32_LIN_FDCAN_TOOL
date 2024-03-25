//*****************************************************************
// 
// 
// 
// 
// Alex Svetlichnyy 2019
//*****************************************************************
#ifndef WATCHDOG_H_INCLUDED
#define WATCHDOG_H_INCLUDED

#include "device_model.h"

void Init_IWDG(uint16_t tw);
void IWDG_reset(void);
void reset_hw_watchdog(void);



#endif /* WATCHDOG_H_INCLUDED */
