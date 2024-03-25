#ifndef STM32H730_CLOCK_H_INCLUDED
#define STM32H730_CLOCK_H_INCLUDED

/****************************************************************
* Functions for initial STM32H730 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
****************************************************************/


typedef enum{
	CLOCK_OK = 0,
	CLOCK_ERROR = 1 } eClockState;


eClockState ClockInit(void);			/* Configuring initial clocks and prescalers */
void enable_peripherals(void);			/* Choose the peripherals to be used in the project and set clocking */

#endif /* STM32H730_CLOCK_H_INCLUDED*/
