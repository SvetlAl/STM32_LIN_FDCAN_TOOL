#ifndef FDCAN_H_INCLUDED
#define FDCAN_H_INCLUDED

/****************************************************************
*
* FD CAN
*
* FDCAN periph functions and structs for STM32
* FDCAN1 and FDCAN2
*
*****************************************************************
* Default configuration:
* 500  Kb/s nominal bitrate
* 2000 Kb/s data bitrate
* FD mode on
* Bitrate switching mode on
*
* CAN filters accept all messages from both CANs
*
* FDCAN1 stores messages in FIFO0
* FDCAN2 stores messages in FIFO1
*
* FDCAN1 TX buffers located in 0-15 elements
* FDCAN2 TX buffers located in 16-31 elements
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/

//#define FDCAN_ENABLE_FILTERS


#include "device_model.h"
#include "FDCAN/fdcan_macros.h"
#include "FDCAN/fdcan_buffer.h"
#include "BxCAN/can_macros.h"

#if defined BOARD_MK_STM32H730
#include "stm32h730xx.h"
#endif

#define FDCAN_TX_BUF_PTR(n)                       (&fdcan_bufs_tx.buf[n])
#define FDCAN_TX_BUF_W_POS_PTR(n)                 (&fdcan_bufs_tx.buf[n].data[fdcan_bufs_tx.buf[n].write_pos])
#define FDCAN_TX_BUF_R_POS_PTR(n)                 (&fdcan_bufs_tx.buf[n].data[fdcan_bufs_tx.buf[n].read_pos])

#define FDCAN_RX_BUF_PTR(n)                       (&fdcan_bufs_rx.buf[n])
#define FDCAN_RX_BUF_W_POS_PTR(n)                 (&fdcan_bufs_rx.buf[n].data[fdcan_bufs_rx.buf[n].write_pos])
#define FDCAN_RX_BUF_R_POS_PTR(n)                 (&fdcan_bufs_rx.buf[n].data[fdcan_bufs_rx.buf[n].read_pos])


//=========================================================================================================
//=====================================     Setters/getters    ============================================
uint8_t *fdcan_get_settings_ptr(void);
fdcan_settings *fdcan_get_settings(void);
	
//=========================================================================================================
//=====================================     Initialization     ============================================
void fdcan_make_default_cfg(void);
void fdcan_init(void);

//=========================================================================================================
//===================================== Send/Recieve functions ============================================
// void fdcan_read_msg (uint8_t can_num, uint8_t* output, uint8_t idx);
void fdcan_irq_procedure(uint8_t can_num);

//=========================================================================================================
//===================================== Buffered transmission =============================================
uint32_t process_buffered_can_tx(void);

//=========================================================================================================
//=======================================   Miscelaneous   ================================================
uint16_t fdcan_calculate_total_msg_size(u_fdcan_message_hdr* _hdr);
uint32_t fdcan_watchdog(void);


#endif /* FDCAN_H_INCLUDED */
