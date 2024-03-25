/****************************************************************
* USART TX buffer
*
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/

#include "USART/usart_rx_buffer.h"

static inline void lock_timeout(usart_rx_buffer *buf){
	volatile uint32_t timeout = URB_LOCK_TIMEOUT;
	while(buf->status == URB_STATUS_LOCKED){
		timeout--;
	}
}

/**
* brief  Write data into a buffer
* param  buffer pointer, data pointer, length
* param  
* retval 
*/

void urb_write_data(usart_rx_buffer *buf, uint8_t *data, uint8_t length){
	lock_timeout(buf);
	if(buf->status == URB_STATUS_LOCKED) return;
	buf->status = URB_STATUS_LOCKED;
	
	for(uint16_t i = 0; i< length; i++){
		buf->data[buf->write_pos] = *data++;
		if((buf->write_pos + 1) < buf->max_size) {
			buf->write_pos = (uint8_t)(buf->write_pos + 1);
		}
	}
	buf->status = URB_STATUS_IDLE;
}

/**
* brief  How many bytes written
* param  buffer pointer
* param  
* retval byte count
*/
uint8_t urb_get_data_length(usart_rx_buffer *buf){
	return buf->write_pos;
}

/**
* brief  Copy data from a buffer to a destination
* param  buffer pointer, destination pointer, length
* param  
* retval 
*/
void urb_read_data(usart_rx_buffer *buf, uint8_t *dest_data){
	lock_timeout(buf);
	if(buf->status == URB_STATUS_LOCKED) return;
	buf->status = URB_STATUS_LOCKED;
	
	memcpy(dest_data, buf->data, buf->write_pos);
	buf->write_pos = 0;
	

	buf->status = URB_STATUS_IDLE;
}



