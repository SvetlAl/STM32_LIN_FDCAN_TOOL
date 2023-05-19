/****************************************************************
* Functions for initial STM32F205 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "device_model.h"
#ifdef STM32F205
#include <stm32f205_clock.h>

#ifndef MDK_ARM_ENV
#define HSEStartUp_TimeOut   ((uint16_t)0x0500) /*!< Time out for HSE start up */
#endif


/**
 * brief ClockInit - Enable clocking of the STM32f105.
 * brief Inside this function we set configuration bits in RCC_CR and RCC_CFGR.
 * brief Our purpose is to configure HSE, PLL and all the Clock Control except certain Peripherials.
 * param  
 * param  
 * retval OK / Error
 */
eClockState ClockInit(void){
	volatile uint32_t HSE_Status = 0;
	volatile uint32_t HSE_TimeoutCounter = 0;
	RCC->CR |= RCC_CR_HSEON;			// Engaging HSE

	/* Inside this loop we`re waiting for the flag HSERDY to be set within defined timeout period */
	while((HSE_TimeoutCounter < HSEStartUp_TimeOut) &&  HSE_Status == 0){
		HSE_TimeoutCounter++;
		if ((RCC->CR & RCC_CR_HSERDY) != 0){
			HSE_Status = 1;
		}		
	}	
	/* If HSE has successfully started, we continue with RCC configuration */
	if(HSE_Status != 0){
		/* Since we`re going to use 96Mhz we have to set up flash memory access latency to "two wait" mode */
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_3WS;
		FLASH->ACR |= (uint32_t)FLASH_ACR_ICEN;
		FLASH->ACR |= (uint32_t)FLASH_ACR_DCEN;
		FLASH->ACR |= (uint32_t)FLASH_ACR_PRFTEN;
		/* Next Step is to set up all the PLL configuration bits BEFORE it started	*/
//		RCC->CFGR  |= RCC_CFGR_PPRE2_0;
	
		
		RCC->CFGR  &= 0xFFFFFFFF;
		RCC->CFGR  |= RCC_CFGR_PPRE2_2;
		RCC->CFGR  |= RCC_CFGR_PPRE1_2;
		RCC->CFGR  |= RCC_CFGR_PPRE1_0;		
		RCC->PLLCFGR &= ~0xFFFFFFFF;
		
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_0;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_2;
		//RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_1;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
		
		/*
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_3;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_1;
		RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
*/

			/* Starting PLL */
		RCC->CR |= RCC_CR_PLLON;
		while ((RCC->CR & RCC_CR_PLLRDY) == 0){}  /* Make sure PLL has started */
		RCC->CFGR  |= RCC_CFGR_SW_PLL;	

		while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0){} /* Make sure this worked out */	

		return CLOCK_OK; /* RCC has started for good!!! */
	}
	else{
		return CLOCK_ERROR; /* RCC hasn`t started and we need to sort this out. */	
	}	
}

/**
 * brief  EnablePeripherals - Enable clocking of the peripherals that will be used
 * param  
 * param  
 * retval
 */
void EnablePeripherals(void){
//GPIO	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
  //	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
 	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  //	RCC -> APB2ENR |= RCC_APB2ENR_IOPDEN;
//	RCC -> APB2ENR |= RCC_APB2ENR_IOPDEN;
//ADC1
// RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
//AFIO	//EXT
  //	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//DAC1
//RCC->APB1ENR |= RCC_APB1ENR_DACEN;
//CAN1
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
	//CAN2
	RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
//DMA1	
//	RCC->AHBENR |=RCC_AHBENR_DMA1EN;

//I2C
//	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
//SPI
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//TIM
RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
// RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
//USART1	
//	RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;
//USART2	
//	RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;		
//USB
 RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;	
//RCC->AHBENR |= RCC_AHBENR_OTGFSEN;

	RCC->APB1ENR	|= RCC_APB1ENR_PWREN;	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;	

	GPIOA->AFR[0] &= ~0xFFFFFFFF;
	GPIOA->AFR[1] &= ~0xFFFFFFFF;
	GPIOB->AFR[0] &= ~0xFFFFFFFF;
	GPIOB->AFR[1] &= ~0xFFFFFFFF;
//	GPIOC->AFR[0] &= ~0xFFFFFFFF;
//	GPIOC->AFR[1] &= ~0xFFFFFFFF;

// AFIO->MAPR|=AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}

#endif


