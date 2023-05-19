#ifndef DEVICE_MODEL_H_INCLUDED
#define DEVICE_MODEL_H_INCLUDED
/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

// #define  __GNUC__ 

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)

/**********************************************************************************************************/
/**********************************************************************************************************/
/******         User settings customized here. Comment/uncomment unused/used configurations           *****/
/**********************************************************************************************************/
/**********************************************************************************************************/
//=========================================================================================================
//=====================================       Environment      ============================================
//#define MDK_ARM_ENV

//=========================================================================================================
//=====================================         Model          ============================================
//#define ALLIGATOR
//#define TEC_MODULE

//#define DEVICE_2CAN
//#define DEVICE_2CAN_TJA1042
#define DEVICE_2CAN_BOXED
//#define DEVICE_SIGMA

//=========================================================================================================
//=======================================       Processor      ============================================
#if defined(ALLIGATOR) | defined(TEC_MODULE)
#define STM32F205
#define DEV_FREQ	120000
#define DEV_FREQ_120MHZ
#define TIM1_FREQ_60MHZ // used for scanner timestamp and watchdog
#define TIM2_FREQ_30MHZ // used for trace injection
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA)
#define STM32F105
#define DEV_FREQ	72000
#define DEV_FREQ_72MHZ
#define TIM1_FREQ_60MHZ // used for scanner timestamp and watchdog
#define TIM2_FREQ_30MHZ // used for trace injection
#endif

//=========================================================================================================
//===================================       Memory chip settings      =====================================

#if defined(ALLIGATOR)
#define MEMCHIP_M45PE16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(TEC_MODULE)
#define MEMCHIP_MX25L16
#define MEMCHIP_VOLUME	0x200000
#endif

#if defined(DEVICE_2CAN) | defined(DEVICE_2CAN_TJA1042) | defined(DEVICE_2CAN_BOXED) | defined(DEVICE_SIGMA)
#define MEMCHIP_MX25L323
#define MEMCHIP_VOLUME	0x200000*2
#endif

//=========================================================================================================
//=======================================  LED signal handling ============================================

#ifdef TEC_MODULE
#define TOGGLE_SIGNAL_LED if(GPIOC->ODR & GPIO_ODR_OD13)  \
	GPIOC->BSRR |= GPIO_BSRR_BR_13;	\
	else GPIOC->BSRR |= GPIO_BSRR_BS_13	\
		
#define SIGNAL_LED_ON GPIOC->BSRR |= GPIO_BSRR_BS_13
#define SIGNAL_LED_OFF GPIOC->BSRR |= GPIO_BSRR_BR_13

#elif defined(ALLIGATOR)
#define TOGGLE_SIGNAL_LED if(GPIOA->ODR & GPIO_ODR_OD8)  \
	GPIOA->BSRR |= GPIO_BSRR_BR_8;	\
	else GPIOA->BSRR |= GPIO_BSRR_BS_8	\
		
#define SIGNAL_LED_ON GPIOA->BSRR |= GPIO_BSRR_BS_8
#define SIGNAL_LED_OFF GPIOA->BSRR |= GPIO_BSRR_BR_8
	
#else
#define TOGGLE_SIGNAL_LED
#define SIGNAL_LED_ON
#define SIGNAL_LED_OFF
#endif
	
//=========================================================================================================
//================================  Reset pin or button handling ==========================================	
	
#ifdef TEC_MODULE
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID3))
#endif
#ifdef ALLIGATOR
#define EMERGENCY_PIN_SET (!(GPIOB->IDR & GPIO_IDR_ID1))
#endif
#ifdef DEVICE_2CAN
#define EMERGENCY_PIN_SET !(GPIOA->IDR & GPIO_IDR_IDR10)
#endif
#ifdef DEVICE_2CAN_TJA1042
#define EMERGENCY_PIN_SET !(GPIOA->IDR & GPIO_IDR_IDR10)
#endif
#ifdef DEVICE_2CAN_BOXED
#define EMERGENCY_PIN_SET !(GPIOB->IDR & GPIO_IDR_IDR14)
#endif
#ifdef DEVICE_SIGMA
#define EMERGENCY_PIN_SET !(GPIOB->IDR & GPIO_IDR_IDR14)
#endif
	
//=========================================================================================================
//==========================================  Includes ====================================================
	
#ifdef STM32F205
#include "stm32f205xx.h"
#endif

#ifdef STM32F105

#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif

#include "stm32f105xc.h"
#endif

#include "spi.h"


//=========================================================================================================
//=======================================  Addresses defs =================================================

#define VEHICLE_SETTINGS_ADDRESS										0x000000 // VehicleStruct
#define DEVICE_MODES_ADDRESS												0x010000 // uDeviceModel, can_override_status theOverrideStatus
#define DEVICE_MODES_SETTINGS_LENGTH								sizeof(DeviceModel)
#define DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS			0x010200
#define DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH			sizeof(u_can_override_status)
	

#define BOOTLOADER_EMERGENCY_PROGRAMM_ADDR 					0x020000
#define BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR 		(0x030000 - 0x04)

#define BOOTLOADER_UPDATE_PROGRAMM_ADDR 						0x030000
#define BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR 				(0x040000 - 0x04)

#define FREE_MEMSPACE_ADDRESS												0x040000


//=========================================================================================================
//================================== Version managmement functions  =======================================
void initDeviceGeneralPinout(void);


#endif /* DEVICE_MODEL_H_INCLUDED*/
