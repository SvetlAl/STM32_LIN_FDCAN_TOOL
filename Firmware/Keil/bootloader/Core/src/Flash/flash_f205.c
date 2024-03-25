#include "device_model.h"

#ifdef BOARD_MK_STM32F205
#include "Flash/flash_f205.h"


static inline uint32_t get_sector_size(uint32_t sector_num){
	TOGGLE_SIGNAL_LED;
	if(sector_num < 4) return 16*1024;
	else if(sector_num == 4) return 64*1024;
	else return 128*1024;
}

static inline uint32_t get_sector_num(uint32_t address){
	uint32_t sector_num = 0;
	uint32_t address_pos = 0x08000000;
	while(address_pos <= address){
		address_pos += get_sector_size(sector_num++);
	}
	return sector_num-1;
}


/**
* brief   Unlock Flash
* param   
* param 	
* retval  
*/
void FLASH_Unlock(void){
  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
	TOGGLE_SIGNAL_LED;
}

/**
* brief   Lock Flash
* param   
* param 	
* retval  
*/
void FLASH_Lock(void){
	FLASH->CR |= FLASH_CR_LOCK;
	TOGGLE_SIGNAL_LED;
}

/**
* brief  Erase page
* param   
* param 	
* retval  
*/	
#ifdef UNUSED_SIL
void FLASH_ErasePage(uint32_t Page_Address){

  // Set the Erase bit in the FLASH_CR register
  FLASH->CR |= FLASH_CR_PER;

  // Write the page address to the FLASH_AR register
  FLASH->AR = Page_Address;

  // Set the Start bit in the FLASH_CR register
  FLASH->CR |= FLASH_CR_STRT;

  // Wait for the BSY bit to be cleared
  while((FLASH->SR & FLASH_SR_BSY) != 0);

  // Clear the PER bit in the FLASH_CR register
  FLASH->CR &= ~(uint32_t)FLASH_CR_PER;
}
#endif

/**
* brief  Erase sector. In 105/107 page is used instead of sector
* param   
* param 	
* retval  
*/

void FLASH_Erase_Sector(uint32_t Sector){
	while (FLASH->SR & FLASH_SR_BSY){}	
		FLASH->CR |= FLASH_CR_SER | (Sector << FLASH_CR_SNB_Pos);
		FLASH->CR |= FLASH_CR_STRT;
	while (FLASH->SR & FLASH_SR_BSY){}

    // Clear the sector erase bit
    FLASH->CR &= ~FLASH_CR_SER;
		FLASH->CR &= ~FLASH_CR_SNB;
		TOGGLE_SIGNAL_LED;
} 

/**
* brief  Program word (32-bit) at a specified address.
* param   Address specifies the address to be programmed.
* param 	Data specifies the data to be programmed.
* retval  
*/

void FLASH_ProgramWord(uint32_t Address, uint32_t Data){
  /* If the previous operation is completed, proceed to program the new data */
	while (FLASH->SR & FLASH_SR_BSY){}
	uint32_t tmp_psize = CHUNK_SIZE;
  FLASH->CR &= ~FLASH_CR_PSIZE;
  FLASH->CR |= tmp_psize;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t*)Address = Data;
	while (FLASH->SR & FLASH_SR_BSY){}
	TOGGLE_SIGNAL_LED;
	FLASH->CR &= ~FLASH_CR_PG;
}

/**
* brief  Erase all the sectors within the size
* param  Start address
* param Size
* retval  
*/
void FLASH_Erase_area(uint32_t start_address, uint32_t size){
	if((start_address < 0x08000000) | (start_address > 0x080FFFFF)){
		return;
	}
	uint32_t address_pos = start_address;
	uint32_t last_address_pos = start_address + size;
//	if(last_address_pos > MEMCHIP_VOLUME) last_address_pos = MEMCHIP_VOLUME;
	
	while(address_pos <= last_address_pos){
		
		uint32_t sector_num = get_sector_num(address_pos);
		FLASH_Unlock();
		FLASH_Erase_Sector(sector_num);
		FLASH_Lock();
		address_pos += get_sector_size(sector_num);
		TOGGLE_SIGNAL_LED;
	}
}



#endif // BOARD_MK_STM32F205
