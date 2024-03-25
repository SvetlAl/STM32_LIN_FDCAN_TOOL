/* This is an intentionally empty file to be filled later */
/**************************************************************************************************
* 
* This file describes configuration of the "Arctic Trucks TEC-Module" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "Board_models/F205/DEVICE_TEC_MODULE.h"

typedef int empty_DEVICE_TEC_MODULE;

#ifdef MDK_ARM_ENV
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#endif

#ifdef DEVICE_TEC_MODULE
#include "SPI/spi.h"
#define UNUSED(x)                     (void)(x)

static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'A',
	'r',
	'c',
	't',
	'i',
	'c',
	'T',
	'r',
	'u',
	'c',
	'k',
	's',
	'T',
	'E',
	'C',
	TEC_MODULE_MCODE
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
	/* CAN 1 STB  B4  */
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_2;
	
	GPIOB->BSRR |= GPIO_BSRR_BR4;
	
	/* CAN 2 STB  B15 */
	GPIOB->MODER &= ~GPIO_MODER_MODER15;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
	GPIOB->MODER |= GPIO_MODER_MODER15_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD15_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_2;
	
	GPIOB->BSRR |= GPIO_BSRR_BR15;
	
	/* LED */
	
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOC->MODER |= (GPIO_MODER_MODER13_0) ;
	GPIOC->BSRR |= GPIO_BSRR_BR_13;
 
	/* PB3 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
 
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




