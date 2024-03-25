#ifndef USART_MACROS_H_INCLUDED
#define USART_MACROS_H_INCLUDED
/****************************************************************
* 
* USART
*
* Alex Svetlichnyy 2018 svetlal@outlook.com
*
*
* TODO: add STM32F205 DMA support
*
*****************************************************************/
#include "device_model.h"

typedef enum{
	Baudrate_1200  = 1200,
	Baudrate_2400  = 2400,
	Baudrate_4800  = 4800,
	Baudrate_9600  = 9600,
	Baudrate_19200 = 19200,
	Baudrate_38400 = 38400,
	Baudrate_57600 = 57600,
	Baudrate_115200 = 115200,
	Baudrate_921600 = 921600} eUsartBaudrate;

#endif /* USART_MACROS_H_INCLUDED */
