/**************************************************************************************************
* 
* This file describes configuration of the "Starline Sigma" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "Board_models/F105/DEVICE_SIGMA.h"
typedef int empty_DEVICE_SIGMA;
#ifdef MDK_ARM_ENV
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#endif

#ifdef DEVICE_SIGMA
#define UNUSED(x)                     (void)(x)

static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'a',
	'r',
	'l',
	'i',
	'n',
	'e',
	'_',
	'S',
	'i',
	'g',
	'm',
	'a',
	'_',
	DEVICE_SIGMA_MCODE
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
		default: return 0x00;
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
	GPIOB->CRL	&= ~GPIO_CRL_CNF1;						
	GPIOB->CRL 	|= GPIO_CRL_MODE1_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE1_1;
	GPIOB->BSRR |= GPIO_BSRR_BS1;						
		
	GPIOC->CRH	&= ~GPIO_CRH_CNF14;						
	GPIOC->CRH 	|= GPIO_CRH_MODE14_0;					
	GPIOC->CRH 	|= GPIO_CRH_MODE14_1;
	GPIOC->BSRR |= GPIO_BSRR_BS14;
	
		// EMERGENCY PIN	
	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->ODR |= GPIO_ODR_ODR14;
	
	INIT_MEMCHIP_SPI_PINOUT
}

//==============================   Version management functions   ===================================
uint8_t *get_board_name(void){
	return &hardwareVersion[0];
}
//==============================   Power management functions   =====================================
void set_bor_level(uint8_t br_lvl){
	UNUSED(br_lvl);
}

#endif








