/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "spi.h"


/**
* brief   Init SPI_1 pins
* param   
* param 	
* retval  
*/
void SPI1_init_pinout(){
	#if defined(TEC_MODULE) || defined(ALLIGATOR) || defined(DEVICE_FCAN_V6)
	/* NSS */ /* A4 */
	GPIOA->MODER &= ~GPIO_MODER_MODER4;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_2;

	CS_SET
	/* SCK */ /* A5 */
	GPIOA->MODER &= ~GPIO_MODER_MODER5;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
	GPIOA->MODER |= GPIO_MODER_MODER5_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_2;
	
	/* MISO */ /* A6 */ 
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD6;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_2;
	
	/* MOSI */ /* A7 */
	GPIOA->MODER &= ~GPIO_MODER_MODER7;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD7;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7;	
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL7_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL7_2;
	#endif

	#if defined(DEVICE_2CAN) || defined(DEVICE_2CAN_TJA1042) || defined(DEVICE_2CAN_BOXED) || defined(DEVICE_SIGMA) || defined(DEVICE_1CAN2LIN)
		/* NSS */ /* A4 */
	GPIOA->CRL |= GPIO_CRL_MODE4; /* Alternative Function Push-Pull Output */
	GPIOA->CRL &= ~GPIO_CRL_CNF4;
	CS_SET
//	GPIOA->BSRR |= GPIO_BSRR_BS4;  /* set 1 */
//	GPIOA->CRL |= GPIO_CRL_CNF4_1;
	
	/* SCK */ /* A5 */
	GPIOA->CRL |= GPIO_CRL_MODE5; /* Alternative Function Push-Pull Output */
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->CRL |= GPIO_CRL_CNF5_1;
	
	/* MISO */ /* A6 */ 
	GPIOA->CRL &= ~GPIO_CRL_MODE6; /* A6 - Input mode */
	GPIOA->CRL &= ~GPIO_CRL_CNF6;
	GPIOA->CRL |= GPIO_CRL_CNF6_1;   
	GPIOA->BSRR = GPIO_BSRR_BS6; /* Pull-down */
	
	/* MOSI */ /* A7 */
	GPIOA->CRL |= GPIO_CRL_MODE7; /* Alternative Function Push-Pull Output */
	GPIOA->CRL &= ~GPIO_CRL_CNF7; 
	GPIOA->CRL |= GPIO_CRL_CNF7_1;
	#endif
}
/**
* brief  Init and start SPI_1 periphery 
* param  IRQ on/off 
* param	 Master/slave
* param  1 byte/ double byte	
* retval  
*/

void SPI1_start(eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode){
	SPI1->CR1     = 0x0000; 
	//SPI1->CR1			|= SPI_CR1_BIDIMODE;
	SPI1->CR2			= 0x0000;  
	SPI1->CR1			|= byteMode; /* 8-16-bit data */
	SPI1->CR2			|= dmaMode;
	
	if(mode == SPI_master_mode){
		SPI1->CR1    |= SPI_CR1_MSTR;           
		SPI1->CR1    |= SPI_CR1_BR ; 	/* bitrate */
		SPI1->CR1    |= SPI_CR1_SSI;  /* Enable master mode */
		SPI1->CR1    |= SPI_CR1_SSM;	/* with NSS pull-up *///Software slave management & Internal slave select
	}
	else if(mode == SPI_slave_mode){
	/* TODO implement */
	/* TODO implement */
	/* TODO implement */
	}
	SPI1->CR1    |= frameFormatMode;	/* 1 - LSB first; 0 - MSB first */
	
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	SPI1->CR1 &= ~SPI_CR1_CPOL;             /* Polarity cls signal CPOL = 0 */
	SPI1->CR1 &= ~SPI_CR1_CPHA;             /* Phase cls signal    CPHA = 0 */

	if(irqMode == SPI_irq_mode){
		SPI1->CR2 |= SPI_CR2_TXEIE;		/* TX finished interrupt */
		SPI1->CR2 |= SPI_CR2_RXNEIE;	/* "A byte recieved" interrupt */
		SPI1->CR2 |= SPI_CR2_ERRIE;		/* Error interrupt */
		NVIC_EnableIRQ (SPI1_IRQn); 
	}	
	
	SPI1->CR1 |= SPI_CR1_SPE;	/* Enable */
}

uint8_t SPI1_transmit_byte(uint8_t data){
	uint8_t RxData;
	uint16_t timeout = 0;
	while (!(SPI1->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI1->DR = data; 
	timeout = 0;	
	while (!(SPI1->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));   
	RxData = (uint8_t)SPI1->DR;
	return RxData;	
}
	

uint16_t SPI1_transmit_dbyte(uint16_t data){
	uint16_t RxData;
	uint16_t timeout = 0;
	while (!(SPI1->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI1->DR = data;
	timeout = 0;	
	while (!(SPI1->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)SPI1->DR;	
	return RxData;
}

	
uint8_t SPI1_recieve_byte(void){
	uint8_t RxData;
	uint8_t Txdata = 0xFF;
	uint16_t timeout = 0;
	while (!(SPI1->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI1->DR = Txdata; 			
	timeout = 0;	
	while (!(SPI1->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));    
	RxData = (uint8_t)SPI1->DR;
	return RxData;	
}


uint16_t SPI1_recieve_dbyte(void){
	uint16_t RxData;
	uint16_t Txdata = 0xFFFF;
	uint16_t timeout = 0;
	while (!(SPI1->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI1->DR = Txdata;		
	timeout = 0;	
	while (!(SPI1->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)SPI1->DR;	
	return RxData;
}

#if defined(DEVICE_2CAN) || defined(DEVICE_2CAN_TJA1042) || defined(DEVICE_2CAN_BOXED) || defined(DEVICE_SIGMA)

/**
* brief   Init SPI_3 pins
* param   
* param 	
* retval  
*/
void SPI3_init_pinout(){
	
	/* NSS */ /* C9 */
	GPIOC->CRH |= GPIO_CRH_MODE9; /* Alternative Function Push-Pull Output */
	GPIOC->CRH &= ~GPIO_CRH_CNF9;
	
	GPIOA->CRH |= GPIO_CRH_MODE15; /* Alternative Function Push-Pull Output */
	GPIOA->CRH &= ~GPIO_CRH_CNF15;
	CS_SET
//	GPIOA->BSRR |= GPIO_BSRR_BS4;  /* set 1 */
//	GPIOA->CRL |= GPIO_CRL_CNF4_1;
	
	/* SCK */ /*C10 */
	GPIOC->CRH |= GPIO_CRH_MODE10; /* Alternative Function Push-Pull Output */
	GPIOC->CRH &= ~GPIO_CRH_CNF10;
	GPIOC->CRH |= GPIO_CRH_CNF10_1;
	
	/* MISO */ /* C11 */ 
	GPIOC->CRH &= ~GPIO_CRH_MODE11; /* C11 - Input mode */
	GPIOC->CRH &= ~GPIO_CRH_CNF11;
	GPIOC->CRH |= GPIO_CRH_CNF11_1;   
	GPIOC->BSRR = GPIO_BSRR_BS11; /* Pull-down */
	
	/* MOSI */ /* C12 */
	GPIOC->CRH |= GPIO_CRH_MODE12; /* Alternative Function Push-Pull Output */
	GPIOC->CRH &= ~GPIO_CRH_CNF12; 
	GPIOC->CRH |= GPIO_CRH_CNF12_1;
}
/**
* brief  Init and start SPI_3 periphery 
* param  IRQ on/off 
* param	 Master/slave
* param  1 byte/ double byte	
* retval  
*/

void SPI3_start(eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode){
	SPI3->CR1     = 0x0000; 
	//SPI1->CR1			|= SPI_CR1_BIDIMODE;
	SPI3->CR2			= 0x0000;  
	SPI3->CR1			|= byteMode; /* 8-16-bit data */
	SPI3->CR2			|= dmaMode;
	
	if(mode == SPI_master_mode){
		SPI3->CR1    |= SPI_CR1_MSTR;           
		SPI3->CR1    |= SPI_CR1_BR_1 ; 	/* bitrate */
		SPI3->CR1    |= SPI_CR1_SSI;  /* Enable master mode */
		SPI3->CR1    |= SPI_CR1_SSM;	/* with NSS pull-up *///Software slave management & Internal slave select
	}
	else if(mode == SPI_slave_mode){
	/* TODO implement */
	/* TODO implement */
	/* TODO implement */
	}
	SPI3->CR1    |= frameFormatMode;	/* 1 - LSB first; 0 - MSB first */
	
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	/* TODO CPOL settings */
	SPI3->CR1 &= ~SPI_CR1_CPOL;             /* Polarity cls signal CPOL = 0 */
	SPI3->CR1 &= ~SPI_CR1_CPHA;             /* Phase cls signal    CPHA = 0 */

	if(irqMode == SPI_irq_mode){
		SPI3->CR2 |= SPI_CR2_TXEIE;		/* TX finished interrupt */
		SPI3->CR2 |= SPI_CR2_RXNEIE;	/* "A byte recieved" interrupt */
		SPI3->CR2 |= SPI_CR2_ERRIE;		/* Error interrupt */
		NVIC_EnableIRQ (SPI3_IRQn); 
	}	
	
	SPI3->CR1 |= SPI_CR1_SPE;	/* Enable */
}

uint8_t SPI3_transmit_byte(uint8_t data){
	uint8_t RxData;
	uint16_t timeout = 0;
	while (!(SPI3->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI3->DR = data; 
	timeout = 0;	
	while (!(SPI3->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));   
	RxData = (uint8_t)SPI3->DR;
	return RxData;	
}
	

uint16_t SPI3_transmit_dbyte(uint16_t data){
	uint16_t RxData;
	uint16_t timeout = 0;
	while (!(SPI3->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI3->DR = data;
	timeout = 0;	
	while (!(SPI3->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)SPI3->DR;
	return RxData;
}

	
uint8_t SPI3_recieve_byte(void){
	uint8_t RxData;
	uint8_t Txdata = 0xFF;
	uint16_t timeout = 0;
	while (!(SPI3->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI3->DR = Txdata; 			
	timeout = 0;	
	while (!(SPI3->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));    
	RxData = (uint8_t)SPI3->DR;
	return RxData;	
}


uint16_t SPI3_recieve_dbyte(void){
	uint16_t RxData;
	uint16_t Txdata = 0xFFFF;
	uint16_t timeout = 0;
	while (!(SPI3->SR & SPI_SR_TXE) & (timeout++ < SPI_TIMEOUT));
	SPI3->DR = Txdata;		
	timeout = 0;	
	while (!(SPI3->SR & SPI_SR_RXNE) & (timeout++ < SPI_TIMEOUT));
	RxData = (uint16_t)SPI3->DR;
	return RxData;
}
#endif


