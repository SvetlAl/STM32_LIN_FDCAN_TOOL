#ifndef SPI_1xx_MACROS_H_INCLUDED
#define SPI_1xx_MACROS_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"

typedef enum{
	SPI_master_mode = 0,
	SPI_slave_mode = 1
} eSpiMode;
	

typedef enum{
	SPI_no_Dma = 0,
	SPI_DmaRx = (uint32_t)(0x1UL << 0U), //SPI_CR2_RXDMAEN
	SPI_DmaTx = (uint32_t)(0x1UL << 1U), //SPI_CR2_TXDMAEN,
	SPI_DmaTxRx = (uint32_t)((0x1UL << 0U) | (0x1UL << 1U))  //(SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN)
} eSpiDmaMode;

typedef enum{
	SPI_polling_mode = 0,
	SPI_irq_mode = 1
} eSpiIRQMode;

typedef enum{
	SPI_b_mode = (uint32_t)0,
	SPI_db_mode = (uint32_t)(0x1UL << 11U), //SPI_CR1_DFF, 22
} eSpiByteMode;

typedef enum{
	SPI_msb_mode = 0,
	SPI_lsb_mode = (uint32_t)(0x1UL << 7U) //SPI_CR1_LSBFIRST
} eSpiFrameFormat;



#endif /* SPI_1xx_MACROS_H_INCLUDED */
