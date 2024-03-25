/****************************************************************
* Functions for initial STM32F407 configuration
* e.g. clocking
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "device_model.h"
#ifdef BOARD_MK_STM32F407
#include <stm32f407_clock.h>

#define HSEStartUp_TimeOut   ((uint16_t)0x0500) /*!< Time out for HSE start up */

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
	
	// Enable HSE oscillator
	RCC->CR |= RCC_CR_HSEON;
    
	// Wait until HSE is ready
	while((HSE_TimeoutCounter < HSEStartUp_TimeOut) &&  HSE_Status == 0){
		HSE_TimeoutCounter++;
		if ((RCC->CR & RCC_CR_HSERDY) != 0){
			HSE_Status = 1;
		}		
	}
	
	if(HSE_Status != 0){
	// Configure PLL
	/*
	RCC->PLLCFGR = RCC_PLLCFGR_PLLSRC_HSE |
	RCC_PLLCFGR_PLLM_3 |
	RCC_PLLCFGR_PLLN_6 |
	RCC_PLLCFGR_PLLP_1;
	*/
		RCC->PLLCFGR = 0x07402A04;
		// Enable PLL
		RCC->CR |= RCC_CR_PLLON;
		// Wait until PLL is ready
		while(!(RCC->CR & RCC_CR_PLLRDY));
		// Set the flash latency to 5 wait states
		FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
		
		// Configure the clock source for system and peripheral clocks
		RCC->CFGR =  0x0000940A;
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		
		// Wait until the selected clock source is ready
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		return CLOCK_OK; 
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
void enable_peripherals(void){
//GPIO	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
  //	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
 	
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
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

#ifdef SUPPORT_USART
//USART1	
RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;
//USART2	
RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;	
//USART3	
RCC->APB1ENR	|= RCC_APB1ENR_USART3EN;
#endif	

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


