/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"
#if defined(BOARD_MK_STM32H730)
#define UNUSED(x)                     (void)(x)

static uint16_t SPI_transmit_receive_byte(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size);
static uint16_t SPI_transmit_receive_quadro(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size);

//=========================================================================================================
//=========================================== Initialization ==============================================
//=========================================================================================================
static void reset_SPI(SPI_TypeDef * _spi){
	if(_spi == SPI2){
    RCC->APB1LRSTR |= RCC_APB1LRSTR_SPI2RST;
    for(uint32_t i=0; i<0x1000; i++){__NOP();}
    RCC->APB1LRSTR &= ~RCC_APB1LRSTR_SPI2RST;
	}
}

/**
@TODO Handle params
* brief  Init and start SPI_2 periphery 
* param  IRQ on/off 
* param	 Master/slave
* param  1 byte/ double byte	
* retval  
*/
void SPI_7xx_start(SPI_TypeDef * _spi, eSpiMode mode, eSpiIRQMode irqMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode){
	reset_SPI(_spi);
	_spi->CFG1 &= ~SPI_CFG1_MBR_Msk;
	_spi->CFG1 |= (SPI_MBR << SPI_CFG1_MBR_Pos);
	
	_spi->CR1 |= SPI_CR1_SSI;
	_spi->CFG2 |= SPI_CFG2_SSM;
	_spi->CFG2 |= SPI_CFG2_SSOM;
	if(mode == SPI_master_mode){
		_spi->CFG2 |= SPI_CFG2_MASTER ;  // master mode
	}
	else{
		// TODO
	}

	_spi->CFG1 &=~SPI_CFG1_DSIZE_Msk;
	_spi->CFG1 |= (0x07UL << SPI_CFG1_DSIZE_Pos);

	UNUSED(irqMode);
	UNUSED(frameFormatMode);
	UNUSED(dmaMode);
}

//=========================================================================================================
//=========================================== Transmit/receive ============================================
//=========================================================================================================

/**
@TODO Handle params
* brief  Simultaneously transmit/receive SPI data PER BYTE or PER DWORD (32)
* param  SPI 
* param  mode (byte, dbyte) 
* param  buff pointers 
* param	 size
* param  
* retval  received data
*/

uint16_t SPI_7xx_transmit_receive(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size){
	const uint16_t residue = size%4;
	const uint16_t quadro_bytes = (size > 4) ? (uint16_t)(size - residue) : 0;
	
	uint16_t transfer_cnt4 = 0;
	uint16_t quadro_rx_tx_cnt = 0;
	while (quadro_rx_tx_cnt < quadro_bytes){
		uint16_t tmp = SPI_transmit_receive_quadro(_spi, mode, &rx_data[quadro_rx_tx_cnt], &tx_data[quadro_rx_tx_cnt], 1);
		quadro_rx_tx_cnt = (uint16_t)(quadro_rx_tx_cnt + 4);
		transfer_cnt4 = (uint16_t)(transfer_cnt4 + tmp);
	}
	
	uint16_t transfer_cnt1 = 0;
	uint16_t single_rx_tx_cnt = 0;
	while (single_rx_tx_cnt < residue){
		uint16_t tmp = SPI_transmit_receive_byte(_spi, mode, &rx_data[quadro_bytes + single_rx_tx_cnt], &tx_data[quadro_bytes + single_rx_tx_cnt], 1);
		single_rx_tx_cnt = (uint16_t)(single_rx_tx_cnt + 1);
		transfer_cnt1 = (uint16_t)(transfer_cnt1 + tmp);
	}
	return (uint16_t)(transfer_cnt4 + transfer_cnt1);
}


static uint16_t SPI_transmit_receive_quadro(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size){
	uint16_t rx_cnt = size;
	uint16_t tx_cnt = size;
	
	uint16_t transfer_cnt = 0;
	
	_spi->CR2 = size;
	_spi->CFG1 |= 0x1F; // 32 -bit
	
	_spi->CR1 |= SPI_CR1_SPE;
	_spi->CR1 |= SPI_CR1_CSTART;
	volatile uint32_t timeout = SPI_TIMEOUT;
	
	while((tx_cnt > 0UL) || (rx_cnt > 0UL)){
		if(((_spi->SR & SPI_SR_TXP) == SPI_SR_TXP) && (tx_cnt > 0UL)){
			uint32_t tx_dword = 0xFFFFFFFF;
				if((mode == SPI_transmission_rx_tx) || (mode == SPI_transmission_tx)){
					tx_dword = (uint32_t)(*tx_data << 24);
					tx_data = tx_data + (sizeof(uint8_t));
					tx_dword |= (uint32_t)(*tx_data << 16);
					tx_data = tx_data + (sizeof(uint8_t));
					tx_dword |= (uint32_t)(*tx_data << 8);
					tx_data = tx_data + (sizeof(uint8_t));
					tx_dword |= (uint32_t)(*tx_data << 0);
					tx_cnt = (uint16_t)(tx_cnt - 4);
				}
				_spi->TXDR = tx_dword;
		}
		// Check the RXP flag 
		if(((_spi->SR & SPI_SR_RXP) == SPI_SR_RXP) && (rx_cnt > 0UL)){
			volatile uint32_t rx_dword = _spi->RXDR;
			if((mode == SPI_transmission_rx_tx) || (mode == SPI_transmission_rx)){
				*rx_data = (uint8_t)((rx_dword >> 24) & 0xFF);
				rx_data = rx_data + (sizeof(uint8_t));
				*rx_data = (uint8_t)((rx_dword >> 16) & 0xFF);
				rx_data = rx_data + (sizeof(uint8_t));
				*rx_data = (uint8_t)((rx_dword >> 8) & 0xFF);
				rx_data = rx_data + (sizeof(uint8_t));
				*rx_data = (uint8_t)((rx_dword >> 0) & 0xFF);
				rx_data = rx_data + (sizeof(uint8_t));
				rx_cnt = (uint16_t)(rx_cnt - 4);
			}
		}
		transfer_cnt = transfer_cnt+1;
		timeout = (uint16_t)(timeout - 1);
		if(timeout == 0) break;
	}
	_spi->CR1 &=~ SPI_CR1_SPE;
	_spi->CR2 = 0;
	_spi->IFCR = 0xFFFFFFFF;
	return transfer_cnt;
}


static uint16_t SPI_transmit_receive_byte(SPI_TypeDef * _spi, eSpiTxRxMode mode, uint8_t *rx_data, uint8_t *tx_data, uint16_t size){
	uint16_t rx_cnt = size;
	uint16_t tx_cnt = size;

	uint16_t transfer_cnt = 0;

	_spi->CR2 = size;
	_spi->CFG1 &= ~0x1F; // 32 -bit
	_spi->CFG1 |= 0x07; // 8 -bit
	_spi->CR1 |= SPI_CR1_SPE;
	_spi->CR1 |= SPI_CR1_CSTART;
	
	volatile uint32_t timeout = SPI_TIMEOUT;
	while((tx_cnt > 0UL) || (rx_cnt > 0UL)){
		if(((_spi->SR & SPI_SR_TXP) == SPI_SR_TXP) && (tx_cnt > 0UL)){
			const uint8_t dummy_tx_byte = 0xFF;
			if((mode == SPI_transmission_rx_tx) || (mode == SPI_transmission_tx)){
				*((__IO uint8_t*)&_spi->TXDR) = *tx_data;
				tx_data = tx_data + sizeof(uint8_t);
				tx_cnt = (uint16_t)(tx_cnt - 1);
			}
			else{
				*((__IO uint8_t*)&_spi->TXDR) = dummy_tx_byte;
			}
		}
		
		// Check the RXP flag 
		if(((_spi->SR & SPI_SR_RXP) == SPI_SR_RXP) && (rx_cnt > 0UL)){
			if((mode == SPI_transmission_rx_tx) || (mode == SPI_transmission_rx)){
				*rx_data = *((__IO uint8_t *)&_spi->RXDR);
				rx_data = rx_data + sizeof(uint8_t);
				rx_cnt = (uint16_t)(rx_cnt - 1);
			}
			else {
				volatile uint8_t dummy_rx_byte = *((__IO uint8_t *)&_spi->RXDR);
				UNUSED(dummy_rx_byte);
			}
		}
		
		transfer_cnt = transfer_cnt+1;
		timeout = (uint16_t)(timeout - 1);
		if(timeout == 0) break;
	}
	_spi->CR1 &=~ SPI_CR1_SPE;
	_spi->CR2 = 0;
	_spi->IFCR = 0xFFFFFFFF;
	return transfer_cnt;
}

#endif // defined(BOARD_MK_STM32H730)

