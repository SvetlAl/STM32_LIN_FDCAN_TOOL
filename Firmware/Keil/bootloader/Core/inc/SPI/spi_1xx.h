#ifndef SPI_1xx_H_INCLUDED
#define SPI_1xx_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation for STM32F1xx F2xx
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)
#include "SPI/spi_1xx_macros.h"

#define SPI_TIMEOUT    0xFFF	
#define SPI_CS_TIMEOUT 0xFFF	

//=========================================================================================================
//=========================================== Initialization ==============================================
//=========================================================================================================
void SPI_1xx_start(SPI_TypeDef * _spi, eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode);

//=========================================================================================================
//=========================================== Transmit/receive ============================================
//=========================================================================================================
uint8_t  SPI_1xx_transmit_byte(SPI_TypeDef * spi, uint8_t data);
uint16_t SPI_1xx_transmit_dbyte(SPI_TypeDef * spi,uint16_t data);
uint8_t  SPI_1xx_receive_byte(SPI_TypeDef * spi);
uint16_t SPI_1xx_receive_dbyte(SPI_TypeDef * spi);


#endif // defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)

#endif /* SPI_1xx_H_INCLUDED*/
