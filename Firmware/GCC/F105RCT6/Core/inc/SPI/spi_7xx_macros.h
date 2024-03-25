#ifndef SPI_7xx_MACROS_H_INCLUDED
#define SPI_7xx_MACROS_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"


typedef enum{
	SPI_master_mode = (uint8_t)0x00,
	SPI_slave_mode = (uint8_t)0x01
} eSpiMode;

typedef enum{
	SPI_no_Dma = (uint8_t)0x00,
	SPI_DmaRx = (uint8_t)(0x1UL << 0U), 
	SPI_DmaTx = (uint8_t)(0x1UL << 1U),
	SPI_DmaTxRx = (uint8_t)(SPI_DmaRx |SPI_DmaTx)
} eSpiDmaMode;

typedef enum{
	SPI_polling_mode = 0,
	SPI_irq_mode = 1
} eSpiIRQMode;

typedef enum{
	SPI_msb_mode = 0,
	SPI_lsb_mode = (uint32_t)(0x1UL << 7U) //SPI_CR1_LSBFIRST
} eSpiFrameFormat;

typedef enum{
	SPI_transmission_rx_tx = 0,
	SPI_transmission_tx = 1,
	SPI_transmission_rx = 2
} eSpiTxRxMode;


#endif /* SPI_7xx_MACROS_H_INCLUDED */
