/****************************************************************
*
* FD CAN proc buffers
*
*
*
*
*
*****************************************************************/
#include "device_model_macros.h"
#ifdef SUPPORT_FDCAN

#include "FDCAN/fdcan_buffer.h"

//=========================================================================================================
//=======================================    Global vars    ===============================================

// Buffer headers
fdcan_buffers fdcan_bufs_tx;
fdcan_buffers fdcan_bufs_rx;
// Buffer data
uint8_t fdcan_buf_tx[FDCANC_E][FDCAN_BUFFER_SIZE_TX];
uint8_t fdcan_buf_rx[FDCANC_E][FDCAN_BUFFER_SIZE_RX];

//=========================================================================================================
//=====================================     Initialization     ============================================
/**
* brief  Init FDCAN buffers
* brief  Set data pointers and buffers max size
* brief  Reset all counters and read/write pos
* param  
* param  
* retval 
*/
void fdcan_enable_buffers(){
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		fdcan_bufs_rx.buf[k].err_cnt = 0;
		fdcan_bufs_rx.buf[k].overrun_cnt = 0;
		fdcan_bufs_rx.buf[k].read_pos = 0;
		fdcan_bufs_rx.buf[k].write_pos = 0;
		fdcan_bufs_rx.buf[k].max_size = FDCAN_BUFFER_SIZE_RX;
		fdcan_bufs_rx.buf[k].data = fdcan_buf_rx[k];
		fdcan_bufs_rx.buf[k].status = FDCAN_BUFFER_STS_FREE;
		
		
		fdcan_bufs_tx.buf[k].err_cnt = 0;
		fdcan_bufs_tx.buf[k].overrun_cnt = 0;
		fdcan_bufs_tx.buf[k].read_pos = 0;
		fdcan_bufs_tx.buf[k].write_pos = 0;
		fdcan_bufs_tx.buf[k].max_size = FDCAN_BUFFER_SIZE_TX;
		fdcan_bufs_tx.buf[k].data = fdcan_buf_tx[k];
		fdcan_bufs_tx.buf[k].status = FDCAN_BUFFER_STS_FREE;
	}
}

//=========================================================================================================
//=====================================     Buffer handling    ============================================
/**
* brief  Get FDCAN buffer freesize
* param  buffer pointer
* param  
* retval Available for write byte count
*/

uint16_t fdcan_get_buf_freesize (fdcan_buffer* _buf){
	const uint16_t c_buffer_size = _buf->max_size;
	uint16_t freesize = 0;
	// R00 000 000
	// W00 000 000
	if(_buf->read_pos == _buf->write_pos){
		freesize = c_buffer_size;
	}
	// R00 000 000
	// 111 1W0 000
	else if(_buf->read_pos < _buf->write_pos){
		uint16_t r_end_sz = c_buffer_size - _buf->write_pos;       // free
		//uint16_t m_end_sz = _buf->write_pos - _buf->read_pos;    // set
		uint16_t l_end_sz = _buf->read_pos;                        // free
		
		if(r_end_sz >= FDCAN_BUFFER_MAX_ITEM_SZ) freesize = (uint16_t)(l_end_sz + r_end_sz);
		if(l_end_sz >= FDCAN_BUFFER_MAX_ITEM_SZ) freesize = (uint16_t)(freesize + l_end_sz);
	}
	// 111 100 0R1
	// 111 1W0 011
	else if(_buf->read_pos > _buf->write_pos){
		//uint16_t r_end_sz = FDCAN_BUFFER_SIZE - _buf->read_pos;  // set
		uint16_t m_end_sz = _buf->read_pos - _buf->write_pos;    // free
		//uint16_t l_end_sz = _buf->write_pos;                     // set
		
		if(m_end_sz >= FDCAN_BUFFER_MAX_ITEM_SZ) freesize = (uint16_t)(freesize + m_end_sz);
	}
	return freesize;
}

/**
* brief  Move a READ position N bytes forward
* param  buffer pointer
* param  val - how many bytes to move
* retval
*/

void fdcan_mov_r_idx(fdcan_buffer* _buf, uint16_t val){
	const uint16_t c_buffer_size = _buf->max_size;
	uint16_t predicted_pos = _buf->read_pos + val;
	
	// R00 000 000
	// W00 000 000
	if(_buf->read_pos == _buf->write_pos) return; // R == W
	// R00 000 000
	// 111 1W0 000
	else if(_buf->read_pos < _buf->write_pos){		// R <  W
		if(predicted_pos > _buf->write_pos) return;
		else{
			_buf->read_pos = predicted_pos;
			return;
		}
	}
	// 111 100 0R1
	// 111 1W0 011
	else if(_buf->read_pos > _buf->write_pos){		// W <  R
		if(predicted_pos > c_buffer_size){
			_buf->read_pos = 0;
			return;
		}
		else{
			uint16_t predicted_dt_sz_r = c_buffer_size - predicted_pos;
			if(predicted_dt_sz_r >= FDCAN_BUFFER_MAX_ITEM_SZ){
				_buf->read_pos = predicted_pos;
				return;
			}
			else{
				_buf->read_pos = 0;
				return;
			}
		}
	}
	
}

/**
* brief  Move a WRITE position N bytes forward
* param  buffer pointer
* param  val - how many bytes to move
* retval
*/

void fdcan_mov_w_idx(fdcan_buffer* _buf, uint16_t val){
	const uint16_t c_buffer_size = _buf->max_size;
	uint16_t predicted_pos = _buf->write_pos + val;
	uint16_t predicted_fr_sz_r = (uint16_t)(c_buffer_size - predicted_pos);
	
	if(predicted_fr_sz_r < FDCAN_BUFFER_MAX_ITEM_SZ){
		if(_buf->read_pos > 0) _buf->write_pos = 0;
		return;
	}
	else if(predicted_fr_sz_r >= FDCAN_BUFFER_MAX_ITEM_SZ){
	// R00 000 000
	// W00 000 000
		
	// R00 000 000
	// 111 1W0 000
		if(_buf->write_pos >= _buf->read_pos){
			_buf->write_pos = predicted_pos;
			return;
		}
	// 111 100 0R1
	// 111 1W0 011
		else if (_buf->write_pos < _buf->read_pos){
			if(predicted_pos < _buf->read_pos){
				_buf->write_pos = predicted_pos;
				return;
			}
		}
	}
}


/**
* brief  Try to lock (write) fdcan buffer
* param  buffer pointer
* param  
* retval Operation status: either failure or current status
*/
uint16_t fdcan_buf_w_lock(fdcan_buffer* _buf){
	uint16_t result = FDCAN_BUFFER_STS_FAIL;
	uint32_t timeout = FDCAN_BUFFER_LOCK_TIMEOUT;
	while(timeout-- != 0){
		if(!(_buf->status & FDCAN_BUFFER_W_STS_LOCKED)){
			_buf->status |= FDCAN_BUFFER_W_STS_LOCKED;
			result = _buf->status;
			break;
		}
	}
	return result;
}
/**
* brief  Try to unlock (write) fdcan buffer
* param  buffer pointer
* param  
* retval Operation status: either failure or current status
*/
uint16_t fdcan_buf_w_unlock(fdcan_buffer* _buf){
	uint16_t result = FDCAN_BUFFER_STS_FAIL;
	uint32_t timeout = FDCAN_BUFFER_LOCK_TIMEOUT;
	while(timeout-- != 0){
		if((_buf->status & FDCAN_BUFFER_W_STS_LOCKED)){
			_buf->status &=~ FDCAN_BUFFER_W_STS_LOCKED;
			result = _buf->status;
			break;
		}
	}
	return result;
}

/**
* brief  Try to lock (read) fdcan buffer
* param  buffer pointer
* param  
* retval Operation status: either failure or current status
*/
uint16_t fdcan_buf_r_lock(fdcan_buffer* _buf){
	uint16_t result = FDCAN_BUFFER_STS_FAIL;
	uint32_t timeout = FDCAN_BUFFER_LOCK_TIMEOUT;
	while(timeout-- != 0){
		if(!(_buf->status & FDCAN_BUFFER_R_STS_LOCKED)){
			_buf->status |= FDCAN_BUFFER_R_STS_LOCKED;
			result = _buf->status;
			break;
		}
	}
	return result;
}
/**
* brief  Try to unlock (read) fdcan buffer
* param  buffer pointer
* param  
* retval Operation status: either failure or current status
*/
uint16_t fdcan_buf_r_unlock(fdcan_buffer* _buf){
	uint16_t result = FDCAN_BUFFER_STS_FAIL;
	uint32_t timeout = FDCAN_BUFFER_LOCK_TIMEOUT;
	while(timeout-- != 0){
		if((_buf->status & FDCAN_BUFFER_R_STS_LOCKED)){
			_buf->status &=~ FDCAN_BUFFER_R_STS_LOCKED;
			result = _buf->status;
			break;
		}
	}
	return result;
}
#endif // SUPPORT_FDCAN


