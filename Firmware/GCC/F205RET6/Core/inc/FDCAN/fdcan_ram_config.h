#ifndef FDCAN_RAM_CONFIG_H_INCLUDED
#define FDCAN_RAM_CONFIG_H_INCLUDED

/****************************************************************
*
* FD CAN RAM configuration
*
* Inspired by https://github.com/Yoda49/STM32H743IIT6-FDCAN-EXAMPLE/blob/main/stm32h743_fdcan.h
*
*
*
*****************************************************************/

#include "device_model.h"

#if defined BOARD_MK_STM32H730
#include "stm32h730xx.h"
#endif

/*
Message ram start address = 0x4000AC00
----------------------------------------------------------------
Start addr  | Description    | Elements count   | Max memory
----------------------------------------------------------------
SIDFC.FLSSA | 11-bit filters | 0 - 128 elements | 0 -  128 words
XIDFC.FLESA | 29-bit filters | 0 -  64 elements | 0 -  128 words
RXF0C.F0SA  | Rx FIFO 0      | 0 -  64 elements | 0 - 1152 words
RXF1C.F1SA  | Rx FIFO 1      | 0 -  64 elements | 0 - 1152 words
RXBC.RBSA   | Rx buffer      | 0 -  64 elements | 0 - 1152 words
TXEFC.EFSA  | Tx event FIFO  | 0 -  32 elements | 0 -   64 words
TXBC.TBSA   | Tx buffers     | 0 -  32 elements | 0 -  576 words
TMC.TMSA    | Trigger memory | 0 -  64 elements | 0 -  128 words
----------------------------------------------------------------
Message ram end address = 0x4000D3FF
----------------------------------------------------------------
offset  measured in words (32bit / 4 bytes)
address measured in bytes (8 bit / 1 byte)
*/

#define FDCAN_MEM_START_ADDR          0x4000AC00UL
#define FDCAN_MEM_END_ADDR            0x4000D3FFUL

// 11-bit filters
#define FDCAN_11B_FILTER_EL_CNT       0UL
#define FDCAN_11B_FILTER_EL_SIZE      4UL
#define FDCAN_11B_FILTER_EL_W_SIZE    (FDCAN_11B_FILTER_EL_SIZE / 4)
#define FCCAN_11B_FILTER_START_ADDR   (FDCAN_MEM_START_ADDR)
#define FDCAN_11B_FILTER_OFFSET       0UL

// 29-bit filters
#define FDCAN_29B_FILTER_EL_CNT       0UL
#define FDCAN_29B_FILTER_EL_SIZE      8UL 
#define FDCAN_29B_FILTER_EL_W_SIZE    (FDCAN_29B_FILTER_EL_SIZE / 4) 
#define FCCAN_29B_FILTER_START_ADDR   (FCCAN_11B_FILTER_START_ADDR + FDCAN_11B_FILTER_EL_CNT * FDCAN_11B_FILTER_EL_SIZE)
#define FDCAN_29B_FILTER_OFFSET       (FDCAN_11B_FILTER_OFFSET     + FDCAN_11B_FILTER_EL_CNT * FDCAN_11B_FILTER_EL_W_SIZE)

// Rx FIFO 0
#define FDCAN_RX_FIFO_0_EL_CNT        16UL
#define FDCAN_RX_FIFO_0_HEAD_SIZE     8UL
#define FDCAN_RX_FIFO_0_DATA_SIZE     64UL
#define FDCAN_RX_FIFO_0_EL_SIZE       (FDCAN_RX_FIFO_0_HEAD_SIZE   + FDCAN_RX_FIFO_0_DATA_SIZE)
#define FDCAN_RX_FIFO_0_EL_W_SIZE     (FDCAN_RX_FIFO_0_EL_SIZE / 4)
#define FDCAN_RX_FIFO_0_START_ADDR    (FCCAN_29B_FILTER_START_ADDR + FDCAN_29B_FILTER_EL_CNT * FDCAN_29B_FILTER_EL_SIZE)
#define FDCAN_RX_FIFO_0_OFFSET        (FDCAN_29B_FILTER_OFFSET     + FDCAN_29B_FILTER_EL_CNT * FDCAN_29B_FILTER_EL_W_SIZE)

// Rx FIFO 1
#define FDCAN_RX_FIFO_1_EL_CNT        16UL
#define FDCAN_RX_FIFO_1_HEAD_SIZE     8UL
#define FDCAN_RX_FIFO_1_DATA_SIZE     64UL
#define FDCAN_RX_FIFO_1_EL_SIZE       (FDCAN_RX_FIFO_1_HEAD_SIZE + FDCAN_RX_FIFO_1_DATA_SIZE)
#define FDCAN_RX_FIFO_1_EL_W_SIZE     (FDCAN_RX_FIFO_1_EL_SIZE / 4)
#define FDCAN_RX_FIFO_1_START_ADDR    (FDCAN_RX_FIFO_0_START_ADDR + FDCAN_RX_FIFO_0_EL_CNT * FDCAN_RX_FIFO_0_EL_SIZE)
#define FDCAN_RX_FIFO_1_OFFSET        (FDCAN_RX_FIFO_0_OFFSET     + FDCAN_RX_FIFO_0_EL_CNT * FDCAN_RX_FIFO_0_EL_W_SIZE)

// Rx buffer
#define FDCAN_RX_BUFFER_EL_CNT        0UL
#define FDCAN_RX_BUFFER_HEAD_SIZE     0UL
#define FDCAN_RX_BUFFER_DATA_SIZE     0UL
#define FDCAN_RX_BUFFER_EL_SIZE       (FDCAN_RX_BUFFER_HEAD_SIZE + FDCAN_RX_BUFFER_DATA_SIZE)
#define FDCAN_RX_BUFFER_EL_W_SIZE     (FDCAN_RX_BUFFER_EL_SIZE / 4)
#define FDCAN_RX_BUFFER_START_ADDR    (FDCAN_RX_FIFO_1_START_ADDR + FDCAN_RX_FIFO_1_EL_CNT * FDCAN_RX_FIFO_1_EL_SIZE)
#define FDCAN_RX_BUFFER_OFFSET        (FDCAN_RX_FIFO_1_OFFSET     + FDCAN_RX_FIFO_1_EL_CNT * FDCAN_RX_FIFO_1_EL_W_SIZE)

// Tx event FIFO
#define FDCAN_TX_EVENT_FIFO_EL_CNT    0UL
#define FDCAN_TX_EVENT_FIFO_EL_SIZE   8UL
#define FDCAN_TX_EVENT_FIFO_EL_W_SIZE (FDCAN_TX_EVENT_FIFO_EL_SIZE / 4) 
#define FDCAN_TX_EVENT_START_ADDR     (FDCAN_RX_BUFFER_START_ADDR + FDCAN_RX_BUFFER_EL_CNT * FDCAN_RX_BUFFER_EL_SIZE)
#define FDCAN_TX_EVENT_OFFSET         (FDCAN_RX_BUFFER_OFFSET     + FDCAN_RX_BUFFER_EL_CNT * FDCAN_RX_BUFFER_EL_W_SIZE)

// TX buffers (FIFO)
/*
#define FDCAN_TX_FIFO_EL_CNT          8UL
#define FDCAN_TX_FIFO_HEAD_SIZE       8UL
#define FDCAN_TX_FIFO_DATA_SIZE       64UL
#define FDCAN_TX_FIFO_EL_SIZE         (FDCAN_TX_FIFO_HEAD_SIZE + FDCAN_TX_FIFO_DATA_SIZE)
#define FDCAN_TX_FIFO_EL_W_SIZE       (FDCAN_TX_FIFO_EL_SIZE / 4)
#define FDCAN_TX_FIFO_START_ADDR      (FDCAN_TX_EVENT_START_ADDR + FDCAN_TX_EVENT_FIFO_EL_CNT * FDCAN_TX_EVENT_FIFO_EL_SIZE)
#define FDCAN_TX_FIFO_OFFSET          (FDCAN_TX_EVENT_OFFSET     + FDCAN_TX_EVENT_FIFO_EL_CNT * FDCAN_TX_EVENT_FIFO_EL_W_SIZE)
*/

// FDCAN TX buffers (FIFO)
#define FDCAN_TX_FIFO_EL_CNT          16UL  // FDCAN1->TXBC |= FDCAN_TX_FIFO_EL_CNT << FDCAN_TXBC_TFQS_Pos;
#define FDCAN_TX_FIFO_HEAD_SIZE       8UL
#define FDCAN_TX_FIFO_DATA_SIZE       64UL
#define FDCAN_TX_FIFO_EL_SIZE         (FDCAN_TX_FIFO_HEAD_SIZE + FDCAN_TX_FIFO_DATA_SIZE) // used in fdcan_send_msg
#define FDCAN_TX_FIFO_EL_W_SIZE       (FDCAN_TX_FIFO_EL_SIZE / 4)
#define FDCAN_TX_FIFO_START_ADDR      (FDCAN_TX_EVENT_START_ADDR + FDCAN_TX_EVENT_FIFO_EL_CNT * FDCAN_TX_EVENT_FIFO_EL_SIZE) // used in fdcan_send_msg
#define FDCAN_TX_FIFO_OFFSET          (FDCAN_TX_EVENT_OFFSET     + FDCAN_TX_EVENT_FIFO_EL_CNT * FDCAN_TX_EVENT_FIFO_EL_W_SIZE) // FDCAN1->TXBC |= FDCAN_TX_FIFO_OFFSET << FDCAN_TXBC_TBSA_Pos;

#define FDCAN1_TX_FIFO_START_ADDR     FDCAN_TX_FIFO_START_ADDR // used in fdcan_send_msg
#define FDCAN2_TX_FIFO_START_ADDR     (FDCAN1_TX_FIFO_START_ADDR + FDCAN_TX_FIFO_EL_CNT * FDCAN_TX_FIFO_EL_SIZE) // used in fdcan_send_msg
#define FDCAN1_TX_FIFO_OFFSET         FDCAN_TX_FIFO_OFFSET // FDCAN1->TXBC |= FDCAN_TX_FIFO_OFFSET << FDCAN_TXBC_TBSA_Pos;
#define FDCAN2_TX_FIFO_OFFSET         (FDCAN1_TX_FIFO_OFFSET     + FDCAN_TX_FIFO_EL_CNT * FDCAN_TX_FIFO_EL_W_SIZE) // FDCAN1->TXBC |= FDCAN_TX_FIFO_OFFSET << FDCAN_TXBC_TBSA_Pos;


/*
// FDCAN2 TX buffers (FIFO)
#define FDCAN2_TX_FIFO_EL_CNT          2UL // 16UL
#define FDCAN2_TX_FIFO_HEAD_SIZE       8UL
#define FDCAN2_TX_FIFO_DATA_SIZE       64UL
#define FDCAN2_TX_FIFO_EL_SIZE         (FDCAN2_TX_FIFO_HEAD_SIZE + FDCAN2_TX_FIFO_DATA_SIZE)
#define FDCAN2_TX_FIFO_EL_W_SIZE       (FDCAN2_TX_FIFO_EL_SIZE / 4)
#define FDCAN2_TX_FIFO_START_ADDR      (FDCAN1_TX_FIFO_START_ADDR + FDCAN1_TX_FIFO_EL_CNT * FDCAN1_TX_FIFO_EL_SIZE)
#define FDCAN2_TX_FIFO_OFFSET          (FDCAN1_TX_FIFO_OFFSET     + FDCAN1_TX_FIFO_EL_CNT * FDCAN1_TX_FIFO_EL_W_SIZE)
*/

// Trigger memory
#define FDCAN_TRIG_MEM_EL_CNT          0UL
#define FDCAN_TRIG_MEM_EL_SIZE         8UL
#define FDCAN_TRIG_MEM_EL_W_SIZE       (FDCAN_TRIG_MEM_EL_SIZE / 4)
#define FDCAN_TRIG_MEM_START           (FDCAN_TX_FIFO_START_ADDR + FDCAN_TX_FIFO_EL_CNT * FDCAN_TX_FIFO_EL_SIZE)
#define FDCAN_TRIG_MEM_OFFSET          (FDCAN_TX_FIFO_OFFSET     + FDCAN_TX_FIFO_EL_CNT * FDCAN_TX_FIFO_EL_W_SIZE)




#endif /* FDCAN_RAM_CONFIG_H_INCLUDED */

