#ifndef FDCAN_BUFFER_H_INCLUDED
#define FDCAN_BUFFER_H_INCLUDED
/****************************************************************
*
* FD CAN proc buffers
*
*
*****************************************************************/

#include "device_model.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan_ram_config.h"

#define FDCAN_BUFFER_MAX_ITEM_SZ     72 // Bytes. An FD-CAN message can take up to 72 bytes (header + data) do not change
#define FDCAN_BUFFER_SIZE_TX         FDCAN_BUFFER_MAX_ITEM_SZ*FDCAN_TX_ITEMS_IN_BUFFER // Bytes. Maximum transmisson buffer size.
#define FDCAN_BUFFER_SIZE_RX         FDCAN_BUFFER_MAX_ITEM_SZ*FDCAN_RX_ITEMS_IN_BUFFER  // Bytes. Maximum recieve buffer size.

//=========================================================================================================
//=======================================    Global vars    ===============================================
// Buffer headers
extern fdcan_buffers fdcan_bufs_tx;
extern fdcan_buffers fdcan_bufs_rx;
// Buffer data
extern uint8_t fdcan_buf_tx[FDCANC_E][FDCAN_BUFFER_SIZE_TX];
extern uint8_t fdcan_buf_rx[FDCANC_E][FDCAN_BUFFER_SIZE_RX];

//=========================================================================================================
//=====================================     Initialization     ============================================
void fdcan_enable_buffers(void);
//=========================================================================================================
//=====================================     Buffer handling    ============================================
uint16_t fdcan_get_buf_freesize (fdcan_buffer* _buf);

uint16_t fdcan_buf_w_lock(fdcan_buffer* _buf);
uint16_t fdcan_buf_w_unlock(fdcan_buffer* _buf);
uint16_t fdcan_buf_r_lock(fdcan_buffer* _buf);
uint16_t fdcan_buf_r_unlock(fdcan_buffer* _buf);

void fdcan_mov_r_idx(fdcan_buffer* _buf, uint16_t val);
void fdcan_mov_w_idx(fdcan_buffer* _buf, uint16_t val);

#endif

