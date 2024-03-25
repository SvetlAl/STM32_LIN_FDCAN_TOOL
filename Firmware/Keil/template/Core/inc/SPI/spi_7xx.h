#ifndef SPI_7xx_H_INCLUDED
#define SPI_7xx_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"
#if defined(BOARD_MK_STM32H730)

#include "SPI/spi_7xx_macros.h"

#define SPI_TIMEOUT    0x00FF
#define SPI_CS_TIMEOUT 0x000C // 0xFFF

#define SPI_MBR        0x01  // bitrate

//=========================================================================================================
//=========================================== Initialization ==============================================
//=========================================================================================================
void SPI_7xx_start(SPI_TypeDef * _spi, eSpiMode mode, eSpiIRQMode irqMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode);

//=========================================================================================================
//=========================================== Transmit/receive ============================================
//=========================================================================================================
uint16_t SPI_7xx_transmit_receive(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size);


#endif // BOARD_MK_STM32H730

#endif /* SPI_7xx_H_INCLUDED*/
