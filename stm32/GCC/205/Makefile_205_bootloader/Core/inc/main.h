#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/****************************************************************
* A bootloader based on STM32F10X/205
*
* Library code is mostly standalone except marked as @DD
*
* The algorithm from the start: 
*
*****************************************
* Is the emergency pin set?**************
**YES**********************************NO
* ||                                   ||
* \/                                   ||
* Write emergency application          ||
* into the built-in flash memory       ||
*                                      ||
*                                      ||
************************************** //
* Is the update programm  <============/
* size set?****************************
* at BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR != 0xFFFFFFFF ?
**YES**********************************NO
* ||                                   ||
* \/                                   ||
* Write update application             ||
* into the built-in flash memory       ||
*                                      ||
*                                      ||
*                                      ||
************************************** //
* Start the main application  <========/
* from MAIN_PROGRAM_START_ADDRESS
*
*
* MAX PROGRAMM SIZE 64Kbyte 
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "device_model.h"

#ifdef STM32F205
#include "stm32f205xx.h"
#include "stm32f205_clock.h"
#endif

#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif

#include "stm32f105xc.h"
#include <stm32f105_clock.h>
#endif



#include "flash.h"
#include "flash_mem_chip_spi.h"
#include "spi.h"
#include "string_convertor.h"

extern memchip_status memory_chip_status;

typedef void(*pFunction)(void);

typedef struct FlashSize{
	uint32_t size;
} FlashSize; //creating new type


typedef union uFlashSize{
	FlashSize _flashSize;
	uint8_t data[sizeof(FlashSize)];
}uFlashSize;

#define VERIFY_FAILED		0x00   
#define VERIFY_OK				0x01

#define BOOTLOADER_DEFAULT_MODE				0x00
#define BOOTLOADER_EMERGENCY_MODE			0x01
#define BOOTLOADER_UPDATE_MODE				0x02
#define BOOTLOADER_TEST_MODE					0x03

#define INVALID_UPDATE_SIZE						0xFFFFFFFF



#ifdef STM32F105
// @TODO write definitions
#endif


	
	
/****************************************************************
* Extern vars
*****************************************************************/

	
#endif /* MAIN_H_INCLUDED*/
