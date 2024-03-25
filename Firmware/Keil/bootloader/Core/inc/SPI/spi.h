#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation
*
* This lib incapsulates SPI Periphery implementation and makes a "wrap"
* upon receive/transmit
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"

#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)
#include "SPI/spi_1xx.h"
#elif defined(BOARD_MK_STM32H730)
#include "SPI/spi_7xx.h"
#endif


//=========================================================================================================
//========================================== Initialuzation ===============================================
//=========================================================================================================
void SPI_start_memchip_spi(void);

//=========================================================================================================
//========================================= Receive/transmit ==============================================
//=========================================================================================================
uint8_t  SPI_transmit_byte(SPI_TypeDef * spi, uint8_t data);
uint8_t  SPI_receive_byte(SPI_TypeDef * spi);

void SPI_transmit_receive_data(SPI_TypeDef * spi, uint8_t *rx_data, uint8_t *tx_data, uint16_t size);
void SPI_receive_data(SPI_TypeDef * spi, uint8_t *rx_data, uint16_t size);
void SPI_transmit_data(SPI_TypeDef * spi, uint8_t *tx_data, uint16_t size);


#endif /* SPI_H_INCLUDED*/
