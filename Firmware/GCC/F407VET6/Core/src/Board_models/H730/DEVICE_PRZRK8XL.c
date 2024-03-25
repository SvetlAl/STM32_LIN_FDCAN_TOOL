/**************************************************************************************************
* 
* This file describes configuration of the "Prizrak 8XL" board.
*
*
* If you add a new device, use this template
*
*
* Alex Svetlichnyy 2019 svetlal@outlook.com
*
*
***************************************************************************************************/
#include "Board_models/H730/DEVICE_PRZRK8XL.h"

typedef int empty_DEVICE_PRZRK8XL;

#ifdef MDK_ARM_ENV
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#endif

#ifdef DEVICE_PRZRK8XL
#include "SPI/spi.h"
#define UNUSED(x)                     (void)(x)

static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'P',
	'R',
	'I',
	'Z',
	'R',
	'A',
	'K',
	'_',
	'8',
	'X',
	'L',
	'S',
	'L',
	'I',
	'M',
	PRZRK8XL_MCODE
};

//===================================  Address allocation ===========================================
/**
* brief  Assignated first block
* retval address value
*/	
uint32_t make_app_address (uint16_t assgnd_blk){
	uint16_t actual_block = memchip_find_good_block(assgnd_blk, NAND_APPLICATION_AREA);
	return APP_FULL_ADDRESS_FROM_BLOCK(actual_block);
}

/**
* brief  Calculate a memory chip address 
* param  area name
* param  
* retval 32-but address
*/
uint32_t memchip_make_app_address(eMemchipAddress _addr){
	switch(_addr){
		case memchipVehicle:{
			uint16_t actual_block = memchip_find_good_block(VEHICLE_SETTINGS_BLOCK_ADDRESS, NAND_APPLICATION_AREA);
			return APP_FULL_ADDRESS_FROM_BLOCK(actual_block);
			break;
		}
		case memchipModes:{
			uint16_t actual_block = memchip_find_good_block(DEVICE_MODES_BLOCK_ADDRESS, NAND_APPLICATION_AREA);
			return APP_FULL_ADDRESS_FROM_BLOCK(actual_block);
			break;
		}
		case memchipFdcanSettings:{
			uint16_t actual_block = memchip_find_good_block(FDCAN_SETTINGS_BLOCK_ADDRESS, NAND_APPLICATION_AREA);
			return APP_FULL_ADDRESS_FROM_BLOCK(actual_block);
			break;
		}
		case memchipEmergencyBin:{
			break;
		}
		case memchipEmergencyBinSz:{
			break;
		}
		case memchipUpdateBin:{
			break;
		}
		case memchipUpdateBinSz:{
			break;
		}
		default: return APP_FULL_ADDRESS_FROM_BLOCK(FREE_MEMSPACE_ADDRESS);
	}
	return APP_FULL_ADDRESS_FROM_BLOCK(FREE_MEMSPACE_ADDRESS);
}

//===================================  Initialization  ==============================================

static void PRZRK8XL_init(void){
	//=============== TPL5010 hardware pin DONE pin ===============
	//======================= D0 ==================================
	GPIOD->MODER &= ~GPIO_MODER_MODE0;
	GPIOD->MODER |= GPIO_MODER_MODE0_0;
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOD->PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL0_0;
}


/**
* brief  Init main device pins: LEDs, CAN STB and others
* param  defined with preprocessor
* param  
* retval 
*/
void init_device_general_pinout(void){
	/* LED */
	/************** PG 0 *******************/
	GPIOG->MODER &= ~GPIO_MODER_MODE0;
	GPIOG->MODER |= GPIO_MODER_MODE0_0;
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOG->AFR[0] |= GPIO_AFRL_AFSEL0_0;

	/************** PG 1 *******************/
	GPIOG->MODER &= ~GPIO_MODER_MODE1;
	GPIOG->MODER |= GPIO_MODER_MODE1_0;
	GPIOG->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOG->PUPDR |= GPIO_PUPDR_PUPD1_1;
	GPIOG->AFR[0] |= GPIO_AFRL_AFSEL1_0;
	
	/************** PF 15 ******************/
	GPIOF->MODER &= ~GPIO_MODER_MODE15;
	GPIOF->MODER |= GPIO_MODER_MODE15_0;
	GPIOF->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15;
	//GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED13;
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPD15;
	GPIOF->PUPDR |= GPIO_PUPDR_PUPD15_1;
	GPIOF->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	
	/* PA3 RST */
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
	GPIOA->BSRR |= GPIO_BSRR_BR3;
	
	// FD CAN
	//======== B9 CAN1_TX ========
	GPIOB->MODER       &= ~GPIO_MODER_MODE9;
	GPIOB->OSPEEDR     &= ~GPIO_OSPEEDR_OSPEED9;
	GPIOB->PUPDR       &= ~GPIO_PUPDR_PUPD9;
	GPIOB->MODER       |=  GPIO_MODER_MODE9_1;
	
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_0;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_3;
	
	//======== B8 CAN1_RX ========
	GPIOB->MODER       &= ~GPIO_MODER_MODE8;
	GPIOB->OSPEEDR     &= ~GPIO_OSPEEDR_OSPEED8;
	GPIOB->PUPDR       &= ~GPIO_PUPDR_PUPD8;
	GPIOB->MODER       |=  GPIO_MODER_MODE8_1;
	
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_0;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_3;
	
	//======== B6 CAN2_TX ========
	GPIOB->MODER       &= ~GPIO_MODER_MODE6;
	GPIOB->OSPEEDR     &= ~GPIO_OSPEEDR_OSPEED6;
	GPIOB->PUPDR       &= ~GPIO_PUPDR_PUPD6;
	GPIOB->MODER       |=  GPIO_MODER_MODE6_1;
	
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_3;
	
	//======== B5 CAN2_RX ========
	GPIOB->MODER       &= ~GPIO_MODER_MODE5;
	GPIOB->OSPEEDR     &= ~GPIO_OSPEEDR_OSPEED5;
	GPIOB->PUPDR       &= ~GPIO_PUPDR_PUPD5;
	GPIOB->MODER       |=  GPIO_MODER_MODE5_1;
	
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_3;
	
	
	//========== B7 STB ==========
	GPIOB->MODER       &= ~GPIO_MODER_MODE7;
	GPIOB->OSPEEDR     &= ~GPIO_OSPEEDR_OSPEED7;
	GPIOB->PUPDR       &= ~GPIO_PUPDR_PUPD7;
	GPIOB->MODER       |=  GPIO_MODER_MODE7_0;
	
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL7;
	GPIOB->BSRR |= GPIO_BSRR_BR7;
	
	INIT_MEMCHIP_SPI_PINOUT
	
	PRZRK8XL_init();
}


//==============================   Power management functions   =====================================
void set_bor_level(uint8_t br_lvl){
	UNUSED(br_lvl);
}

//==============================   Version management functions   ===================================
uint8_t *get_board_name(void){
	return &hardwareVersion[0];
}

#endif

