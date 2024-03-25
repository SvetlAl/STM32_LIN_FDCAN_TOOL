/****************************************************************
* 
* SPI basic implementation for STM32F1xx F2xx
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "SPI/spi.h"
#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)  | defined(BOARD_MK_STM32F407)

/**
* brief  Init and start SPI periphery 
* param  IRQ on/off 
* param	 Master/slave
* param  1 byte/ double byte	
* retval  
*/
void SPI_1xx_start(SPI_TypeDef * _spi, eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode){
	_spi->CR1     = 0x0000; 
	//SPI1->CR1			|= SPI_CR1_BIDIMODE;
	_spi->CR2			= 0x0000;  
	_spi->CR1			|= byteMode; /* 8-16-bit data */
	_spi->CR2			|= dmaMode;
	
	if(mode == SPI_master_mode){
		_spi->CR1    |= SPI_CR1_MSTR;           
		_spi->CR1    |= SPI_CR1_BR ; 	/* bitrate */
		_spi->CR1    |= SPI_CR1_SSI;  /* Enable master mode */
		_spi->CR1    |= SPI_CR1_SSM;	/* with NSS pull-up *///Software slave management & Internal slave select
	}
	else if(mode == SPI_slave_mode){
	/* TODO implement */
	/* TODO implement */
	/* TODO implement */
	}
	_spi->CR1    |= frameFormatMode;	/* 1 - LSB first; 0 - MSB first */
	
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	_spi->CR1 &= ~SPI_CR1_CPOL;             /* Polarity cls signal CPOL = 0 */
	_spi->CR1 &= ~SPI_CR1_CPHA;             /* Phase cls signal    CPHA = 0 */

	if(irqMode == SPI_irq_mode){
		_spi->CR2 |= SPI_CR2_TXEIE;		/* TX finished interrupt */
		_spi->CR2 |= SPI_CR2_RXNEIE;	/* "A byte received" interrupt */
		_spi->CR2 |= SPI_CR2_ERRIE;		/* Error interrupt */
		if(_spi == SPI1){
			NVIC_EnableIRQ (SPI1_IRQn); 
		}
		else if(_spi == SPI2){
			NVIC_EnableIRQ (SPI2_IRQn); 
		}
		else if(_spi == SPI3){
			NVIC_EnableIRQ (SPI3_IRQn); 
		}
	}	
	_spi->CR1 |= SPI_CR1_SPE;	/* Enable */
}


//=========================================================================================================
//=========================================== Transmit\receive ============================================
//=========================================================================================================
uint8_t SPI_1xx_transmit_byte(SPI_TypeDef * spi, uint8_t data){
	uint8_t RxData;
	uint16_t timeout = 0;
	while (!(spi->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	spi->DR = data; 
	timeout = 0;	
	while (!(spi->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));   
	RxData = (uint8_t)spi->DR;
	return RxData;	
}

uint16_t SPI_1xx_transmit_dbyte(SPI_TypeDef * spi, uint16_t data){
	uint16_t RxData;
	uint16_t timeout = 0;
	while (!(spi->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	spi->DR = data;
	timeout = 0;	
	while (!(spi->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)spi->DR;	
	return RxData;
}

uint8_t SPI_1xx_receive_byte(SPI_TypeDef * spi){
	uint8_t RxData;
	uint8_t Txdata = 0xFF;
	uint16_t timeout = 0;
	while (!(spi->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	spi->DR = Txdata; 			
	timeout = 0;	
	while (!(spi->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));    
	RxData = (uint8_t)spi->DR;
	return RxData;	
}

uint16_t SPI_1xx_receive_dbyte(SPI_TypeDef * spi){
	uint16_t RxData;
	uint16_t Txdata = 0xFFFF;
	uint16_t timeout = 0;
	while (!(spi->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	spi->DR = Txdata;		
	timeout = 0;	
	while (!(spi->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)spi->DR;	
	return RxData;
}


#endif // defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205)


