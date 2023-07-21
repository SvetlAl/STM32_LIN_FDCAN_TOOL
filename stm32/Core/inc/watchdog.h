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
#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif


void Init_IWDG(uint16_t tw);
void IWDG_reset(void);



#endif /* WATCHDOG_H_INCLUDED */
