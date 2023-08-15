#include "cdc_flow_can_buffer.h"

static inline void SET_CDC_CAN_BUF_FLAG(uint32_t *status, uint32_t flag){
	*status = *status | flag;
}
static inline void RST_CDC_CAN_BUF_FLAG(uint32_t *status, uint32_t flag){
	*status = *status & ~flag;
}
static inline uint32_t GET_CDC_CAN_BUF_FLAG(const uint32_t status, uint32_t flag){
	return (status & flag);
}


uint32_t init_dual_cc_buf(dual_cdc_can_buff *dbl_buf){
	dbl_buf->status = DUAL_CCB_INIT_MODE;
	dbl_buf->buffer_A.read_pos = 0;
	dbl_buf->buffer_A.write_pos = 0;
	dbl_buf->buffer_B.read_pos = 0;
	dbl_buf->buffer_B.write_pos = 0;
	return (get_ccb_freespace(&dbl_buf->buffer_A) + get_ccb_freespace(&dbl_buf->buffer_B));
//	dbl_buf->buffer_A.status = CDC_CAN_BUF_INIT_MODE;
//	dbl_buf->buffer_B.status = CDC_CAN_BUF_INIT_MODE;
}

void deinit_dual_cc_buf(dual_cdc_can_buff *dbl_buf){
	dbl_buf->status = DUAL_CCB_DEFAULT_MODE;
	dbl_buf->buffer_A.read_pos = 0;
	dbl_buf->buffer_A.write_pos = 0;
	dbl_buf->buffer_B.read_pos = 0;
	dbl_buf->buffer_B.write_pos = 0;
//	dbl_buf->buffer_A.status = CDC_CAN_BUF_DEFAULT_MODE;
//	dbl_buf->buffer_B.status = CDC_CAN_BUF_DEFAULT_MODE;
}
	

/**
* brief  Fill single buffer with data
* param
* param
* retval bytes count written
*/

uint32_t fill_single_cc_buf(cdc_flow_can_buffer *buf, uint8_t *data, uint32_t length){
	// fill A or B
	uint32_t freespace = get_ccb_freespace(buf);
	uint32_t data_sz = length <= freespace ? length : freespace;
	
	if(data_sz!= 0){
		// __disable_irq();
		memcpy(&buf->data[buf->write_pos], data, data_sz);
		buf->write_pos += data_sz;
		// __enable_irq();
	}
	return data_sz;
}


/**
* brief  init buffers A and B with data
* param
* param
* retval
*/

static inline uint32_t initial_fill_dual_buf(dual_cdc_can_buff *dual_buf, uint8_t *data, uint32_t length){
	
	uint32_t bytes_written_A = 0x00;
	uint32_t bytes_written_B = 0x00;
	
	uint32_t buffer_A_freesize = get_ccb_freespace(&dual_buf->buffer_A);
	
	if(buffer_A_freesize != 0){
		bytes_written_A = fill_single_cc_buf(&dual_buf->buffer_A, data, length); //
		
		if(bytes_written_A < length){ // not all data is gone into buf A
			uint32_t buffer_B_freesize = get_ccb_freespace(&dual_buf->buffer_B);
			
			if(buffer_B_freesize != 0){
				uint32_t residue = (length - bytes_written_A);
				bytes_written_B = fill_single_cc_buf(&dual_buf->buffer_B, (data + bytes_written_A), residue); //
				return bytes_written_B;
			}
		}
		else return bytes_written_A;
	}
	else{
		bytes_written_B = fill_single_cc_buf(&dual_buf->buffer_B, data, length); //
		return bytes_written_B;
	}
	return bytes_written_A;
}
/**
* brief  Fill dual buffer with data
* param
* param
* retval how many bytes needed to refill buffers
*/
uint32_t fill_dual_cc_buf(dual_cdc_can_buff *dual_buf, uint8_t *data, uint32_t length){
	//============================== Stop and deinit ====================================
	if(length == 0){
	//	deinit_dual_cc_buf(dual_buf);
		return 0;
	}
	// if a stop cmd has come 
	/*
	else if(*data == 0xFF){
		uint32_t i = 0;
		for(i = 0; i < length; i++){
			if(data[i] != 0xFF) break;
		}
		if(data[i] == 0xFF){
			SET_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_STOP);
			return 0;
		}
	}
	*/
	//==================== The dual buffer is not inited yet ============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_INIT_MODE)){
		initial_fill_dual_buf(dual_buf, data, length);
		uint32_t buffer_B_freesize = get_ccb_freespace(&dual_buf->buffer_B);
		
		if(buffer_B_freesize == 0){
			
			RST_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_INIT_MODE);
			SET_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_INITED_FLAG);
			
			SET_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_A_READ_B_WRITE); // From here read from A and write to B
			return 0;
		}
		else{
			uint32_t buffer_A_freesize = get_ccb_freespace(&dual_buf->buffer_A);
			return (buffer_A_freesize + buffer_B_freesize);
		}
	}
	//==================== Reading from A, writing to B ============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_A_READ_B_WRITE)){
		uint32_t bytes_written_B = fill_single_cc_buf(&dual_buf->buffer_B, data, length);
		if(bytes_written_B != length){
			deinit_dual_cc_buf(dual_buf);
			return 0;
		}
		uint32_t buffer_B_freesize = get_ccb_freespace(&dual_buf->buffer_B);
		return buffer_B_freesize;
	}
	//==================== Reading from B, writing to A ============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_B_READ_A_WRITE)){
		uint32_t bytes_written_A = fill_single_cc_buf(&dual_buf->buffer_A, data, length);
		if(bytes_written_A != length){
			deinit_dual_cc_buf(dual_buf);
			return 0;
		}
		uint32_t buffer_A_freesize = get_ccb_freespace(&dual_buf->buffer_A);
		return buffer_A_freesize;
	}
	return 0;
}


/**
* brief  Get free space in a buffer within the double buffer
* param
* param
* retval
*/
uint32_t get_ccb_freespace(cdc_flow_can_buffer *buf){
	return (CDC_CAN_INJECTION_BUFFER_SIZE - buf->write_pos - sizeof(can_message_info_raw));
}

uint32_t get_available_ccb_bytes(cdc_flow_can_buffer *buf){
	return (buf->write_pos - buf->read_pos);
}

/**
* brief  Pop a can_message_info_raw from single/dual buffer
* param
* param
* retval how many bytes needed to refill buffers
*/

uint32_t pop_single_cc_buf_item(can_message_info_raw *msg, cdc_flow_can_buffer *buf){
	
	//====================== No new messages found ===============================
	if(get_available_ccb_bytes(buf) < sizeof(can_message_info_raw)){
		return 0xFFFFFFFF;
	}
	
	memcpy(&msg->raw_msg_data[0], &buf->data[buf->read_pos], sizeof(can_message_info_raw));
	buf->read_pos += sizeof(can_message_info_raw);
	
	return get_available_ccb_bytes(buf);
}

/**
* brief  
* param
* param
* retval how many bytes of current READ buffer is already read
*/
uint32_t get_current_READ_buf_read_level(dual_cdc_can_buff *dual_buf){
	if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_A_READ_B_WRITE)){
		//return (uint32_t)(((uint32_t)(dual_buf->buffer_A.read_pos * CDC_CAN_INJECTION_BUFFER_SIZE))/100);
		return (uint32_t)dual_buf->buffer_A.read_pos;
	}
		//==================== reading from B ===============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_B_READ_A_WRITE)){
		return (uint32_t)dual_buf->buffer_B.read_pos;
		//return (uint32_t)(((uint32_t)(dual_buf->buffer_B.read_pos * CDC_CAN_INJECTION_BUFFER_SIZE))/100);
	}	
	else return 0;
}

/**
* brief  
* param
* param
* retval  zero if full
*/

uint32_t get_current_WRITE_buf_fill_level(dual_cdc_can_buff *dual_buf){
	if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_A_READ_B_WRITE)){
		return get_ccb_freespace(&dual_buf->buffer_B);
	}
		//==================== reading from B ===============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_B_READ_A_WRITE)){
		return get_ccb_freespace(&dual_buf->buffer_A);
	}	
	else return CDC_CAN_INJECTION_BUFFER_SIZE;
}



uint32_t pop_dual_cc_buf_item(can_message_info_raw *msg, dual_cdc_can_buff *dual_buf){
	uint32_t result = 0x00;
	// __disable_irq();
	//==================== reading from A ===============================
	if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_A_READ_B_WRITE)){
		
		result = pop_single_cc_buf_item(msg, &dual_buf->buffer_A);
		
		// this was the last message in the buffer
		if(result == 0){ 
			dual_buf->buffer_A.read_pos = 0x00;
			dual_buf->buffer_A.write_pos = 0x00;
			RST_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_A_READ_B_WRITE);
			SET_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_B_READ_A_WRITE);
			// __enable_irq();
			return get_ccb_freespace(&dual_buf->buffer_A);
		}
	}
	//==================== reading from B ===============================
	else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_B_READ_A_WRITE)){
		result = pop_single_cc_buf_item(msg, &dual_buf->buffer_B);
		// this was the last message in the buffer
		if(result == 0){
			dual_buf->buffer_B.read_pos = 0x00;
			dual_buf->buffer_B.write_pos = 0x00;
			RST_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_B_READ_A_WRITE);
			SET_CDC_CAN_BUF_FLAG(&dual_buf->status, DUAL_CCB_A_READ_B_WRITE);
			// __enable_irq();
			return get_ccb_freespace(&dual_buf->buffer_B);
		}
	}
	//====================== No new messages found ===============================
	if(result == 0xFFFFFFFF){
		//==================== reading from A ===============================
		if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_A_READ_B_WRITE)){
			return get_ccb_freespace(&dual_buf->buffer_A);
		}
		//==================== reading from B ===============================
		else if(GET_CDC_CAN_BUF_FLAG(dual_buf->status, DUAL_CCB_B_READ_A_WRITE)){
			return get_ccb_freespace(&dual_buf->buffer_B);
		}
	}
	return 0x00;
}

