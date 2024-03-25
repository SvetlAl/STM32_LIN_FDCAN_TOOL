
#include "device_model.h"

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan_std_can_legacy.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan.h"
#include "FDCAN/fdcan_buffer.h"


static can_message legacy_can_msg;

can_message *legacy_can_message(void){
	return &legacy_can_msg;
}


/**
* brief  convert an FDCAN msg into STD CAN msg
* param  msg data pointers
* param  
* retval 
*/
void legacy_fdcan_to_can(can_message *_std, uint8_t *_fd){
	u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*)_fd;
	const fdcan_message_hdr *msg_hdr = &msg_ptr->msg_hdr;
	uint16_t data_sz = (uint16_t)FDCAN_FD_MSG_LENGTH(msg_hdr);
	
	if(data_sz > 8) data_sz = 8; // std CAN supports max 8 bytes
	//uint16_t total_message_size = (uint16_t)(data_sz + sizeof(fdcan_message_hdr));
	_std->dlc = data_sz;
	if(FDCAN_IS_MSG_XTD(msg_hdr) == FDCAN_FLAG_SET){ // extended
		_std->id.ext_id = msg_hdr->id;
		_std->ide = EXT_ID;
	}
	else{
		_std->id.std_id.id_lowbyte  = (uint8_t) (msg_hdr->id       & 0xFF);
		_std->id.std_id.id_highbyte = (uint8_t)((msg_hdr->id >> 8) & 0xFF);
		_std->ide = STD_ID;
	}
	
	uint8_t *start_data_pos = (uint8_t *)(_fd + sizeof(fdcan_message_hdr));
	for(uint8_t i = 0; i < data_sz; i++){
		_std->data[i] = *start_data_pos++;
	}
}


/**
* brief  convert an STD CAN msg into FDCAN msg
* param  msg data pointers
* param  
* retval 
*/
void legacy_can_to_fdcan(can_message *_std, uint8_t *_fd){
	u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*)_fd;
	fdcan_message_hdr *msg_hdr = &msg_ptr->msg_hdr;

	msg_hdr->id = CAN_ID(_std);
	if(_std->ide == EXT_ID){ // extended
		FDCAN_SET_MSG_XTD(msg_hdr, FDCAN_FLAG_SET);
	}
	else{
		FDCAN_SET_MSG_XTD(msg_hdr, FDCAN_FLAG_RST);
	}
	msg_hdr->dlc = _std->dlc;
	uint16_t data_sz = _std->dlc;
	
	uint8_t *start_data_pos = (uint8_t *)(_fd + sizeof(fdcan_message_hdr));
	for(uint8_t i = 0; i < data_sz; i++){
		*start_data_pos++ = _std->data[i];
	}
}

/**
* brief Send a standart CAN msg from a BxCAN lib via FDCAN
* param  std CAN ptr
* param  CAN num
* retval How many messages were sent
*/

void legacy_queue_std_msg_tx(uint8_t can_num, can_message *_std){
	volatile uint8_t lock_sts = FDCAN_BUFFER_STS_FAIL;
	uint16_t total_message_size = 0;
	
	
	if(fdcan_get_buf_freesize(FDCAN_TX_BUF_PTR(can_num)) >= FDCAN_BUFFER_MAX_ITEM_SZ){
		lock_sts = fdcan_buf_w_lock(FDCAN_TX_BUF_PTR(can_num));
	}
	if(lock_sts != FDCAN_BUFFER_STS_FAIL){
		legacy_can_to_fdcan(_std, FDCAN_TX_BUF_W_POS_PTR(can_num));
		u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*) FDCAN_TX_BUF_W_POS_PTR(can_num);
		
		total_message_size = fdcan_calculate_total_msg_size(msg_ptr);
		
		fdcan_mov_w_idx(FDCAN_TX_BUF_PTR(can_num), total_message_size);
		fdcan_buf_w_unlock(FDCAN_TX_BUF_PTR(can_num));
	}  // lock_sts != FDCAN_BUFFER_STS_FAIL)
}





#endif // SUPPORT_FDCAN

