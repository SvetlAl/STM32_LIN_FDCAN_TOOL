#ifndef USART_RX_BUFFER_H_INCLUDED
#define USART_RX_BUFFER_H_INCLUDED
/****************************************************************
* 
* USART buffer
*
*
*
*****************************************************************/

#include "device_model.h"
#include "string.h"

#define URB_STATUS_IDLE   (uint8_t)0x00
#define URB_STATUS_LOCKED (uint8_t)0x01

#define URB_LOCK_TIMEOUT  (uint32_t)0xFFFF

typedef struct usart_rx_buffer usart_rx_buffer;

struct usart_rx_buffer{
	uint8_t* data;
	void (*write)(uint8_t *data, uint8_t length);
	void (*read)(uint8_t *dest_data);
	
	uint8_t max_size;
	uint8_t write_pos;
	uint8_t status;
	uint8_t unused;
};

//================================ Init ===================================


//================================ Read/write =============================
uint8_t urb_get_data_length(usart_rx_buffer *buf);
void urb_write_data(usart_rx_buffer *buf, uint8_t *data, uint8_t length);
void urb_read_data(usart_rx_buffer *buf, uint8_t *dest_data);

#endif /* USART_RX_BUFFER_H_INCLUDED */
