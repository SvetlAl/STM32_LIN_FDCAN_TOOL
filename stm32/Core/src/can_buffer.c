#include "can_buffer.h"

#ifdef CAN_TX_BUFFER_ENABLED
CanBufferStruct CAN_buffer[CAN_INTERFACES_USED];

void initCanBuffers(){
	for (uint32_t i = 0; i < CAN_INTERFACES_USED; i++){
		CAN_buffer[i].read_pos = 0;
		CAN_buffer[i].write_pos = 0;
		CAN_buffer[i].overrun_cnt = 0;
		CAN_buffer[i].err_cnt = 0;
		for (uint32_t k = 0; k < CAN_MAX_MAILBOXES_USED; k++){
			CAN_buffer[i].mailbox_status[k] = CB_MAILBOX_IDLE;
		}
	}
	
	CAN_buffer[CAN1_BUF_NUM].PeriphLink = CAN1;
	CAN_buffer[CAN1_BUF_NUM].write_item = &write_can1_buffer;
	CAN_buffer[CAN1_BUF_NUM].read_item = &read_can1_buffer;
	CAN_buffer[CAN1_BUF_NUM].read_free_size = &read_can1_buf_free_size;
	
	#if (CAN_INTERFACES_USED > 1)
	CAN_buffer[CAN2_BUF_NUM].PeriphLink = CAN2;
	CAN_buffer[CAN2_BUF_NUM].write_item = &write_can2_buffer;
	CAN_buffer[CAN2_BUF_NUM].read_item = &read_can2_buffer;
	CAN_buffer[CAN2_BUF_NUM].read_free_size = &read_can2_buf_free_size;	
	#endif
}


void write_can_msg (can_message *msg, CanBufferStruct* buf){
	// calculate pos++
	uint16_t predicted_write_pos = (uint16_t)(buf->write_pos + 1);
	if(predicted_write_pos == CAN_TX_BUFFER_SIZE) predicted_write_pos = 0;
	// avoid overrun
	if(predicted_write_pos == buf->read_pos){
		buf->overrun_cnt++;
		return;
	}
	buf->data[buf->write_pos] = *msg;
	buf->write_pos = predicted_write_pos;
}

void write_can1_buffer (can_message *msg){
	write_can_msg (msg, &CAN_buffer[CAN1_BUF_NUM]);
}

void write_can2_buffer (can_message *msg){
	write_can_msg (msg, &CAN_buffer[CAN2_BUF_NUM]);
}

// ASSERT FREE SIZE BEFORE USE
void read_can_msg(CanBufferStruct* buf, uint8_t mailbox_num){
	uint16_t predicted_read_pos = (uint16_t)(buf->read_pos + 1);
	if(predicted_read_pos == CAN_TX_BUFFER_SIZE) predicted_read_pos = 0;
	buf->msg[mailbox_num] = buf->data[buf->read_pos];
	buf->read_pos = predicted_read_pos;
}

void read_can1_buffer(uint8_t mailbox_num){
	read_can_msg(&CAN_buffer[CAN1_BUF_NUM], mailbox_num);
}
void read_can2_buffer(uint8_t mailbox_num){
	read_can_msg(&CAN_buffer[CAN2_BUF_NUM], mailbox_num);
}

uint32_t read_can_buf_free_size(CanBufferStruct* buf){
	if(buf->write_pos == buf->read_pos) return CAN_TX_BUFFER_SIZE;
	
	uint32_t freeSz = (buf->write_pos > buf->read_pos) ? (uint32_t)(CAN_TX_BUFFER_SIZE - (buf->write_pos - buf->read_pos)) : 
	(uint32_t) ((CAN_TX_BUFFER_SIZE - buf->write_pos) - (CAN_TX_BUFFER_SIZE - buf->read_pos));
	
	return freeSz;
}

uint32_t read_can1_buf_free_size(void){
	return read_can_buf_free_size(&CAN_buffer[CAN1_BUF_NUM]);
}	
uint32_t read_can2_buf_free_size(void){
	return read_can_buf_free_size(&CAN_buffer[CAN2_BUF_NUM]);
}		

#endif
