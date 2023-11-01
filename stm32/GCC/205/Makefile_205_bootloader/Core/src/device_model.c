/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"


void initDeviceGeneralPinout(void){
	#ifdef TEC_MODULE
	/* init signal LED */
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOC->MODER |= (GPIO_MODER_MODER13_0) ;
	GPIOC->BSRR |= GPIO_BSRR_BR_13;
	/* init emergency pin */
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef ALLIGATOR
	
		/* LED */
	
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD8;
	GPIOA->MODER |= (GPIO_MODER_MODER8_0) ;
	GPIOA->BSRR |= GPIO_BSRR_BS_8;
	
	/* PB1 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER1;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_2CAN
		// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_2CAN_BOXED 
	// EMERGENCY PIN	
	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->ODR |= GPIO_ODR_ODR14;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_2CAN_TJA1042 
		// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	
	#ifdef DEVICE_SIGMA 
		// EMERGENCY PIN	
	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->ODR |= GPIO_ODR_ODR14;
	
	SPI3_init_pinout();
	AFIO->MAPR  |= AFIO_MAPR_SPI3_REMAP;
	SPI3_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	#ifdef DEVICE_1CAN2LIN
		// STB PIN
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BR7;						
	
	// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_FCAN_V6
	GPIOB->MODER &= ~GPIO_MODER_MODER7;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7;
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_2;
	
		/* LED */
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOB->MODER |= (GPIO_MODER_MODER0_0) ;
	GPIOB->BSRR |= GPIO_BSRR_BS_0;
	
	
		/* PB1 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER1;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	
	GPIOB->BSRR |= GPIO_BSRR_BR7;

	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
}
