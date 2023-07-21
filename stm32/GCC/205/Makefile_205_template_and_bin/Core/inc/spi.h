#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED
/****************************************************************
* 
* SPI basic implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"

#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif

//#include "dma.h"

#define SPI_TIMEOUT 0xFFF	

/***********************************************/
/***************** Latch pin *******************/
/***********************************************/
#ifdef TEC_MODULE
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;
#endif
#ifdef ALLIGATOR
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;
#endif
#ifdef DEVICE_2CAN
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;
#endif
	
#ifdef DEVICE_2CAN_BOXED 
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;
#endif
	
#ifdef DEVICE_2CAN_TJA1042 
#define CS_SET GPIOA->BSRR |= GPIO_BSRR_BS4;
#define CS_RESET GPIOA->BSRR |= GPIO_BSRR_BR4;
#endif
	
#ifdef DEVICE_SIGMA 
#define CS_SET GPIOC->BSRR |= GPIO_BSRR_BS9;
#define CS_RESET GPIOC->BSRR |= GPIO_BSRR_BR9;
#endif
	

typedef enum{
	SPI_master_mode = 0,
	SPI_slave_mode = 1
} eSpiMode;

typedef enum{
	SPI_no_Dma = 0,
	SPI_DmaRx = SPI_CR2_RXDMAEN,
	SPI_DmaTx = SPI_CR2_TXDMAEN,
	SPI_DmaTxRx = (SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN)
} eSpiDmaMode;


typedef enum{
	SPI_polling_mode = 0,
	SPI_irq_mode = 1
} eSpiIRQMode;

typedef enum{
	SPI_b_mode = 0,
	SPI_db_mode = SPI_CR1_DFF
} eSpiByteMode;

typedef enum{
	SPI_msb_mode = 0,
	SPI_lsb_mode = SPI_CR1_LSBFIRST
} eSpiFrameFormat;



void SPI1_init_pinout(void);
void SPI1_start(eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode);

uint8_t SPI1_transmit_byte(uint8_t data);
uint16_t SPI1_transmit_dbyte(uint16_t data);
uint8_t SPI1_recieve_byte(void);
uint16_t SPI1_recieve_dbyte(void);

void SPI3_init_pinout(void);
void SPI3_start(eSpiMode mode, eSpiIRQMode irqMode, eSpiByteMode byteMode, eSpiFrameFormat frameFormatMode, eSpiDmaMode dmaMode);

uint8_t SPI3_transmit_byte(uint8_t data);
uint16_t SPI3_transmit_dbyte(uint16_t data);
uint8_t SPI3_recieve_byte(void);
uint16_t SPI3_recieve_dbyte(void);



#endif /* SPI_H_INCLUDED*/
