/****************************************************************
* Functions for initial STM32F105 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2018 svetlal@outlook.com
*****************************************************************/
#include "device_model.h"
#ifdef STM32F105
#include <stm32f105_clock.h>

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
	#ifdef STM32F105
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
		/* Since we`re going to use 72Mhz we have to set up flash memory access latency to "two wait" mode */
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;
		/* Next Step is to set up all the PLL configuration bits BEFORE it started	*/
		RCC->CFGR  |= RCC_CFGR_PLLMULL9;
		RCC->CFGR  |= RCC_CFGR_PLLXTPRE;
		RCC->CFGR  |= RCC_CFGR_PLLSRC;
		RCC->CFGR  |= RCC_CFGR_PPRE1_2;
		RCC->CFGR  |= RCC_CFGR_PPRE2_2;
		// RCC->CFGR  |= RCC_CFGR_OTGFSPRE;
			/* Starting PLL */
		RCC->CR |= RCC_CR_PLLON;
		while ((RCC->CR & RCC_CR_PLLRDY) == 0){}  /* Make sure PLL has started */
			
		RCC->CR |= RCC_CR_PLL3ON;
		while ((RCC->CR & RCC_CR_PLL3RDY) == 0){} /* Make sure PLL has started */
			
		RCC->CFGR |= RCC_CFGR_SW_1; /* PLL was selected as system clock switch */
		while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0){} /* Make sure this worked out */	

		return CLOCK_OK; /* RCC has started for good!!! */	
	}
	else{
		return CLOCK_ERROR; /* RCC hasn`t started and we need to sort this out. */	
	}	
	#endif
	#ifndef STM32F105
	return CLOCK_ERROR;
	#endif
}

/**
 * brief  EnablePeripherals - Enable clocking of the peripherals that will be used
 * param  
 * param  
 * retval
 */
void EnablePeripherals(void){
	#ifdef STM32F105
//GPIO	
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC -> APB2ENR |= RCC_APB2ENR_IOPDEN;
//	RCC -> APB2ENR |= RCC_APB2ENR_IOPDEN;
//ADC1
// RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN;
//AFIO	//EXT
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
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

//RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//TIM
RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

#if defined(SUPPORT_LIN) &&  defined(DEVICE_2CAN)
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
#endif

#ifdef SUPPORT_USART
//USART1	
RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;
//USART2	
RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;	
//USART3	
RCC->APB1ENR	|= RCC_APB1ENR_USART3EN;
#endif

//USB
//RCC->APB1ENR |= RCC_APB1ENR_USBEN;	
	RCC->AHBENR |= RCC_AHBENR_OTGFSEN;

	AFIO->MAPR|=AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
#endif



#if defined(DEVICE_2CAN) || defined(DEVICE_2CAN_BOXED) || defined(DEVICE_2CAN_TJA1042) || defined(DEVICE_1CAN2LIN)
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
#endif
	
#ifdef DEVICE_SIGMA 
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
#endif

}
#endif


