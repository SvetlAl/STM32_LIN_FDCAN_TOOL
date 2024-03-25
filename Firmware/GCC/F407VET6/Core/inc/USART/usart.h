#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED
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
#include "USART/usart_macros.h"
#include "USART/usart_rx_buffer.h"

#ifdef BOARD_MK_STM32F105
#include "DMAF10x/10x_dma.h"
#endif

#ifdef SUPPORT_USART

#define USART_BUF_SZ 32U

//===============================================================================================
//======================================== Initialization =======================================
//===============================================================================================
void usart1_configure_periph(eUsartBaudrate _baudRate);
void usart2_configure_periph(eUsartBaudrate _baudRate);
void usart3_configure_periph(eUsartBaudrate _baudRate);

void init_device_usart(eUsartBaudrate _baudRate);
void usart_reinit_baudrate(uint8_t usart_num, eUsartBaudrate _baudRate);

//===============================================================================================
//======================================== Send/receive =========================================
//===============================================================================================
__WEAK uint32_t usart_receive_data(uint8_t usart_num, uint16_t length);
void usart_send_byte_array(uint8_t usart_num, uint8_t *data, uint8_t length);
//===============================================================================================
//======================================== Setters/getters ======================================
//===============================================================================================
uint32_t usart_get_rx_buf_ptr(uint8_t usart_num, usart_rx_buffer* target);

#endif /* SUPPORT_USART */


#endif /* USART_H_INCLUDED */
