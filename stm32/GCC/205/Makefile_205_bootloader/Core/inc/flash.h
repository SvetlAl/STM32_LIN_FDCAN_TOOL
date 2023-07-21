#ifndef FLASH_H_INCLUDED
#define FLASH_H_INCLUDED
/****************************************************************
* 
*  Microcontroller built-in Flash memory basic implementation
*
*  Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

/****************************************************************
* 								Address presets
*
*	
*
*****************************************************************/
#ifdef STM32F205
#define CHUNK_SIZE 512 /* how many bytes read and written per cycle */

#define MAIN_PROGRAM_START_ADDRESS	(uint32_t)0x08004000
#define MAIN_PROGRAM_SECTOR_START			1											

// Addresses on a memchip
#define BOOTLOADER_EMERGENCY_PROGRAMM_ADDR 			0x020000
#define BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR (0x030000 - 0x04)

#define BOOTLOADER_UPDATE_PROGRAMM_ADDR 			0x030000
#define BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR 	(0x040000 - 0x04)

#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#endif

#ifdef STM32F105
#define CHUNK_SIZE 512 /* how many bytes read and written per cycle */

#define MAIN_PROGRAM_START_ADDRESS	(uint32_t)0x08004000
#define MAIN_PROGRAM_SECTOR_START			8			// PAGE, NOT sector

// Addresses on a memchip
#define BOOTLOADER_EMERGENCY_PROGRAMM_ADDR 			0x020000
#define BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR (0x030000 - 0x04)

#define BOOTLOADER_UPDATE_PROGRAMM_ADDR 			0x030000
#define BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR 	(0x040000 - 0x04)

#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#endif


/****************************************************************
* Flash configuration
*****************************************************************/

#ifdef STM32F205
#include "stm32f205xx.h"
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)
#endif

#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

#else
#include "stm32f1xx.h"
#endif



#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)
#endif





typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


#ifdef STM32F205
typedef enum 
{
  DISABLE = 0U, 
  ENABLE = !DISABLE
} FunctionalState;
#endif


void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_Erase_Sector(uint32_t Sector);
void FLASH_ProgramWord(uint32_t Address, uint32_t Data);
void FLASH_Erase_area(uint32_t start_address, uint32_t size);
void FLASH_ErasePage(uint32_t Page_Address);

#endif /* FLASH_H_INCLUDED*/
