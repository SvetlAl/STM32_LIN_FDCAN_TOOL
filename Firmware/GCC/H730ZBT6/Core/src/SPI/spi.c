/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "SPI/spi.h"

//=========================================================================================================
//========================================== Initialuzation ===============================================
//=========================================================================================================
/**
* brief  SPI initialization wrap  function
* param 
* param  
* param  
* retval
*/
void SPI_start_memchip_spi(void){
#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	SPI_1xx_start(MEMCHIP_SPI, SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
#elif defined(BOARD_MK_STM32H730)
	SPI_7xx_start(MEMCHIP_SPI, SPI_master_mode, SPI_polling_mode, SPI_msb_mode, SPI_no_Dma);
#endif
}


//=========================================================================================================
//========================================= Receive/transmit ==============================================
//=========================================================================================================

/**
* brief  Transmit and receive a single byte
* param  SPI_TypeDef
* param  transmit byte value
* param  
* retval received byte
*/


uint8_t SPI_transmit_byte(SPI_TypeDef * spi, uint8_t data){
#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	return SPI_1xx_transmit_byte(spi, data);
#elif defined(BOARD_MK_STM32H730)
//	tx_byte = data;
//	SPI_7xx_transmit_receive(spi, SPI_transmission_rx_tx, &rx_byte, &tx_byte, 0x01);
//	return rx_byte;
	
	static uint8_t _result = 0;
	uint8_t _data = data;
	SPI_7xx_transmit_receive(spi, SPI_transmission_rx_tx, &_result, &_data, 1);
	return _result;
	
#endif
}
/**
* brief  Receive a single byte
* param  SPI_TypeDef
* param  
* param  
* retval received byte
*/
uint8_t  SPI_receive_byte(SPI_TypeDef * spi){
#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	return SPI_1xx_receive_byte(spi);
#elif defined(BOARD_MK_STM32H730)
//	uint8_t tx_byte = 0xFF;
//	return SPI_transmit_byte(spi, tx_byte);
	static uint8_t _result = 0;
	SPI_7xx_transmit_receive(spi, SPI_transmission_rx, &_result, &_result, 1);
	return _result;
#endif
}

/**
* brief  Transmit and receive a bytea array
* param  SPI_TypeDef
* param  RX data pointer
* param  TX data pointer
* param  length
* retval 
*/
void SPI_transmit_receive_data(SPI_TypeDef * spi, uint8_t *rx_data, uint8_t *tx_data, uint16_t size){
	#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	for(uint16_t i = 0; i < size; i++){
		rx_data[i] = SPI_1xx_transmit_byte(spi, tx_data[i]);
	}
	#elif defined(BOARD_MK_STM32H730)
	SPI_7xx_transmit_receive(spi, SPI_transmission_rx_tx, rx_data, tx_data, size);
	#endif
}

/**
* brief  Receive a bytea array
* param  SPI_TypeDef
* param  RX data pointer
* param  
* param  length
* retval 
*/
void SPI_receive_data(SPI_TypeDef * spi,uint8_t *rx_data, uint16_t size){
	#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	for(uint16_t i = 0; i < size; i++){
		rx_data[i] = SPI_1xx_receive_byte(spi);
	}
	#elif defined(BOARD_MK_STM32H730)
	SPI_7xx_transmit_receive(spi, SPI_transmission_rx, rx_data, rx_data, size);
	#endif
}

/**
* brief  Transmit a bytea array
* param  SPI_TypeDef
* param  
* param  TX data pointer
* param  length
* retval 
*/
void SPI_transmit_data(SPI_TypeDef * spi,uint8_t *tx_data, uint16_t size){
	#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	for(uint16_t i = 0; i < size; i++){
		SPI_1xx_transmit_byte(spi, tx_data[i]);
	}
	#elif defined(BOARD_MK_STM32H730)
	SPI_7xx_transmit_receive(spi, SPI_transmission_tx, tx_data, tx_data, size);
	#endif
}




