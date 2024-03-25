#ifndef FLASH_F205_H_INCLUDED
#define FLASH_F205_H_INCLUDED

#include "device_model.h"
#ifdef BOARD_MK_STM32F205
#include "Flash/flash_f205.h"

#define CHUNK_SIZE 512 /* how many bytes read and written per cycle */

#define MAIN_PROGRAM_SECTOR_START                     8  // PAGE, NOT sector

#define NVIC_VectTab_FLASH                 ((uint32_t)0x08000000)


#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)

#define WRP0_Mask                ((uint32_t)0x000000FF)
#define WRP1_Mask                ((uint32_t)0x0000FF00)
#define WRP2_Mask                ((uint32_t)0x00FF0000)
#define WRP3_Mask                ((uint32_t)0xFF000000)

typedef enum{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;


void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_Erase_Sector(uint32_t Sector);
void FLASH_ProgramWord(uint32_t Address, uint32_t Data);
void FLASH_Erase_area(uint32_t start_address, uint32_t size);
//void FLASH_ErasePage(uint32_t Page_Address);


#endif // BOARD_MK_STM32F205

#endif // FLASH_F205_H_INCLUDED
