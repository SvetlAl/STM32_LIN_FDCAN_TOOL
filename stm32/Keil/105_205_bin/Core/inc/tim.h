/****************************************************************
* 
* Timer functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#ifndef TIM_H_INCLUDED
#define TIM_H_INCLUDED
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

#ifdef TIM1_FREQ_60MHZ // * 2
#define WATCHDOG_PROCEDURE_CNT 19999
#define WATCHDOG_PROCEDURE_PSC 6000
/* once per   0.1/2   msec */
#endif

#ifdef TIM1_FREQ_24MHZ // * 2
#define WATCHDOG_PROCEDURE_CNT 19999
#define WATCHDOG_PROCEDURE_PSC 2400
/* once per   0.1/2   msec */
#endif

#ifdef TIM1_FREQ_36MHZ // * 2
#define WATCHDOG_PROCEDURE_CNT 19999
#define WATCHDOG_PROCEDURE_PSC 3600
/* once per   0.1/2   msec */
#endif


#ifdef TIM2_FREQ_30MHZ // *2
#define TRACE_INJECTION_PROCEDURE_CNT 10000
#define TRACE_INJECTION_PROCEDURE_PSC 25
#endif

#ifdef TIM2_FREQ_24MHZ // *2
#define TRACE_INJECTION_PROCEDURE_CNT 10000
#define TRACE_INJECTION_PROCEDURE_PSC 30
#endif

#ifdef TIM2_FREQ_36MHZ // *2
#define TRACE_INJECTION_PROCEDURE_CNT 10000
#define TRACE_INJECTION_PROCEDURE_PSC 30
#endif



void startBasicTimer(uint16_t prescaler, uint16_t reloadValue, TIM_TypeDef * TIM_n);
void stopBasicTimer(TIM_TypeDef * TIM_n);

#endif /* TIM_H_INCLUDED*/

