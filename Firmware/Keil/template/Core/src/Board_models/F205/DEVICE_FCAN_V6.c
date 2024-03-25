/* This is an intentionally empty file to be filled later */
/**************************************************************************************************
* 
* This file describes configuration of the "TEC F-CAN V6" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "Board_models/F205/DEVICE_FCAN_V6.h"

typedef int empty_DEVICE_FCAN_V6;

#ifdef MDK_ARM_ENV
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#endif

#ifdef DEVICE_FCAN_V6
#include "SPI/spi.h"
#define UNUSED(x)                     (void)(x)

static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'F',
	'_',
	'C',
	'A',
	'N',
	'_',
	'V',
	'6',
	'_',
	'_',
	'_',
	'_',
	'_',
	'_',
	'_',
	DEVICE_FCAN_V6_MCODE
};

//===================================  Address allocation ===========================================
/**
* brief  Calculate a memory chip address 
* param  area name
* param  
* retval 32-but address
*/
uint32_t memchip_make_app_address(eMemchipAddress _addr){
	switch(_addr){
		case memchipVehicle:         return VEHICLE_SETTINGS_ADDRESS;
		case memchipModes:           return DEVICE_MODES_ADDRESS;
		case memchipOverrideFilters: return DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS;
		case memchipEmergencyBin:    return BOOTLOADER_EMERGENCY_PROGRAMM_ADDR;
		case memchipEmergencyBinSz:  return BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR;
		case memchipUpdateBin:       return BOOTLOADER_UPDATE_PROGRAMM_ADDR;
		case memchipUpdateBinSz:     return BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR;
	}
}
//===================================  Initialization  ==============================================
/**
* brief  Init main device pins: LEDs, CAN STB and others
* param  defined with preprocessor
* param  
* retval 
*/
void init_device_general_pinout(void){
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
	
	INIT_MEMCHIP_SPI_PINOUT
}

//==============================   Version management functions   ===================================
uint8_t *get_board_name(void){
	return &hardwareVersion[0];
}
//==============================   Power management functions   =====================================
void set_bor_level(uint8_t br_lvl){
	if(br_lvl > 0x03) return;
	uint32_t current_br_lvl = (uint32_t)((FLASH->OPTCR & FLASH_OPTCR_BOR_LEV_Msk) >> FLASH_OPTCR_BOR_LEV_Pos);
	if(current_br_lvl == br_lvl){
		return;
	}
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->KEYR = ((uint32_t)0x45670123);
	FLASH->KEYR = ((uint32_t)0xCDEF89AB);
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTKEYR = ((uint32_t)0x08192A3B);
  FLASH->OPTKEYR = ((uint32_t)0x4C5D6E7F);
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTCR &= ~((uint32_t)(FLASH_OPTCR_BOR_LEV_Msk)); // clear BOR bits
	
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	FLASH->OPTCR |= (uint8_t)(br_lvl << FLASH_OPTCR_BOR_LEV_Pos);
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	
	FLASH->OPTCR |= FLASH_OPTCR_OPTSTRT;
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	FLASH->CR |= FLASH_CR_LOCK;
	while((FLASH->SR & FLASH_SR_BSY) != 0);
}
#endif

