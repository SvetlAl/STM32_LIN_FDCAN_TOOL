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

#if defined(BOARD_MK_STM32F105) || defined(BOARD_MK_STM32F205) || defined(BOARD_MK_STM32F407)
//===============================================================================================
//======================================== Timer assignation ====================================
//===============================================================================================
#define WATCHDOG_PROCEDURE_TIM           TIM1
#define MAIN_TIMER                       WATCHDOG_PROCEDURE_TIM
#define TRACE_INJECTION_PROCEDURE_TIM    TIM2
#define LIN_DEVICE_TIM                   TIM3

//===============================================================================================
//==================================== Timer prescalers/presets =================================
//===============================================================================================
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

#ifdef TIM1_FREQ_84MHZ // * 2
#define WATCHDOG_PROCEDURE_CNT 19999
#define WATCHDOG_PROCEDURE_PSC 8400
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

#ifdef TIM2_FREQ_42MHZ // *2
#define TRACE_INJECTION_PROCEDURE_CNT 10000
#define TRACE_INJECTION_PROCEDURE_PSC 32
#endif

#endif // defined(BOARD_MK_STM32F105) || defined(BOARD_MK_STM32F205)



#ifdef BOARD_MK_STM32H730
//===============================================================================================
//======================================== Timer assignation ====================================
//===============================================================================================
#define WATCHDOG_PROCEDURE_TIM           TIM2
#define MAIN_TIMER                       WATCHDOG_PROCEDURE_TIM
#define TRACE_INJECTION_PROCEDURE_TIM    TIM3
#define TEST_TRANSMITTER_TIM             TIM4
#define TEST_TRANSMITTER_CNT_TIM         TIM5

//===============================================================================================
//==================================== Timer prescalers/presets =================================
//===============================================================================================
#ifdef TIM2_FREQ_180MHZ // * 2
#define WATCHDOG_PROCEDURE_CNT 19998
#define WATCHDOG_PROCEDURE_PSC 9000

/*
#define TEST_TRANSMITTER_CNT 19998
#define TEST_TRANSMITTER_PSC 9000
*/

/* once per   0.1/2   msec */
#endif

#endif // STM32H730

//===============================================================================================
//==================================== Start/Stop Pause/Resume ==================================
void startBasicTimer(uint16_t prescaler, uint16_t reloadValue, TIM_TypeDef * TIM_n);
void stopBasicTimer  (TIM_TypeDef * TIM_n);
void pauseBasicTimer (TIM_TypeDef * TIM_n);
void resumeBasicTimer(TIM_TypeDef * TIM_n);

#endif /* TIM_H_INCLUDED*/

