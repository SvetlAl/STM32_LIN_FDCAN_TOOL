/* This is an intentionally empty file to be filled later */
/**************************************************************************************************
* 
* This file describes configuration of the "Starline 2CAN2LIN v3" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "Board_models/F105/DEVICE_2CAN_TJA1042.h"

typedef int empty_DEVICE_2CAN_TJA1042;

#ifdef MDK_ARM_ENV
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#endif

#ifdef DEVICE_2CAN_TJA1042
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
	'2',
	'C',
	'A',
	'N',
	'_',
	'_',
	DEVICE_2CAN_TJA1042_MCODE
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
		default:                     return 0x00;
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
	// STB PIN
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BS7;						
		
	GPIOB->CRL	&= ~GPIO_CRL_CNF4;						
	GPIOB->CRL 	|= GPIO_CRL_MODE4_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE4_1;
	GPIOB->BSRR |= GPIO_BSRR_BS4;
	
		// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
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







