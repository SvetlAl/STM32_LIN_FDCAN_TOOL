#ifndef EXTRAS_H_INCLUDED
#define EXTRAS_H_INCLUDED

//*****************************************************************
// 
//
//	TEST FUNCTIONS
//
//
//*****************************************************************

#include "device_model.h"
#include "watchdog.h"

#define EXTRA_TRANSMISSION_TIMEOUT (uint32_t)4500

#ifdef STM32F105
#if defined (TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define SIGNAL_LED_A_ON GPIOA->BSRR |= GPIO_BSRR_BS3
#define SIGNAL_LED_B_ON GPIOC->BSRR |= GPIO_BSRR_BS11
#define SIGNAL_LED_A_OFF GPIOA->BSRR |= GPIO_BSRR_BR3
#define SIGNAL_LED_B_OFF GPIOC->BSRR |= GPIO_BSRR_BR11
#endif
#endif

#ifdef STM32F205
#if defined (TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)
#define SIGNAL_LED_A_ON 
#define SIGNAL_LED_B_ON 
#define SIGNAL_LED_A_OFF
#define SIGNAL_LED_B_OF
#endif
#endif

void init_extras(void);
void process_extra_transmission(void);
void calculate_cnt_and_transmit(void);
void check_test_transmission_request(void);





#endif /* EXTRAS_H_INCLUDED */
