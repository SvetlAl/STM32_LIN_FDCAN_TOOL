/****************************************************************
* 
* Microcontroller built-in Flash memory  basic implementation
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*
*
*****************************************************************/

#include "device_model.h"
#include "flash.h"


static inline uint32_t get_sector_size(uint32_t sector_num){
	#ifdef STM32F205
	TOGGLE_SIGNAL_LED;
	if(sector_num < 4) return 16*1024;
	else if(sector_num == 4) return 64*1024;
	else return 128*1024;
	#endif
	#ifdef STM32F105
	if(sector_num < 128)
	return 2*1024;
	else return 0;
	#endif
}

static inline uint32_t get_sector_num(uint32_t address){
	#ifdef STM32F205
	uint32_t sector_num = 0;
	uint32_t address_pos = 0x08000000;
	while(address_pos <= address){
		address_pos += get_sector_size(sector_num++);
	}
	return sector_num-1;
	#endif
	#ifdef STM32F105
	uint32_t sector_num = 0;
	uint32_t address_pos = 0x08000000;
	while(address_pos <= address){
		address_pos += get_sector_size(sector_num++);
	}
	return sector_num-1;
	#endif
}



/**
* brief   Unlock Flash
* param   
* param 	
* retval  
*/
void FLASH_Unlock(void){
	#ifdef STM32F205
  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
	TOGGLE_SIGNAL_LED;
	#endif
	#ifdef STM32F105
  /* Authorize the FPEC Access */
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
	#endif
}

/**
* brief   Lock Flash
* param   
* param 	
* retval  
*/
void FLASH_Lock(void){
	#ifdef STM32F205
	FLASH->CR |= FLASH_CR_LOCK;
	TOGGLE_SIGNAL_LED;
	#endif
	#ifdef STM32F105
	FLASH->CR |= FLASH_CR_LOCK;
	#endif
}

/**
* brief  Erase page
* param   
* param 	
* retval  
*/	
#ifdef STM32F105
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
	#ifdef STM32F205
	while (FLASH->SR & FLASH_SR_BSY){}	
		FLASH->CR |= FLASH_CR_SER | (Sector << FLASH_CR_SNB_Pos);
		FLASH->CR |= FLASH_CR_STRT;
	while (FLASH->SR & FLASH_SR_BSY){}

    // Clear the sector erase bit
    FLASH->CR &= ~FLASH_CR_SER;
		FLASH->CR &= ~FLASH_CR_SNB;
		TOGGLE_SIGNAL_LED;
		#endif
		#ifdef STM32F105
	//
		FLASH->SR &= ~(uint32_t)FLASH_SR_EOP; 
		FLASH->SR &= ~(uint32_t)FLASH_SR_PGERR; 
		FLASH->SR &= ~(uint32_t)FLASH_SR_WRPRTERR; 

  // Erase the page
  FLASH_ErasePage(Sector * get_sector_size(Sector));
  // Lock flash memory

		#endif
} 

/**
* brief  Program word (32-bit) at a specified address.
* param   Address specifies the address to be programmed.
* param 	Data specifies the data to be programmed.
* retval  
*/

void FLASH_ProgramWord(uint32_t Address, uint32_t Data){
  /* If the previous operation is completed, proceed to program the new data */
	#ifdef STM32F205
	while (FLASH->SR & FLASH_SR_BSY){}
	uint32_t tmp_psize = CHUNK_SIZE;
  FLASH->CR &= ~FLASH_CR_PSIZE;
  FLASH->CR |= tmp_psize;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t*)Address = Data;
	while (FLASH->SR & FLASH_SR_BSY){}
	TOGGLE_SIGNAL_LED;
	FLASH->CR &= ~FLASH_CR_PG;
	#endif
	#ifdef STM32F105
	FLASH_Unlock();
	while((FLASH->SR & FLASH_SR_BSY) != 0){}
	  // Set the PG bit in the FLASH_CR register
  FLASH->CR |= FLASH_CR_PG;
  // Write the data to the memory address
  *(__IO uint16_t*)Address = (uint16_t)Data;
	while((FLASH->SR & FLASH_SR_BSY) != 0){}
	Address += 2;//���������� � ������ ��� �����
	Data >>= 16;//�������� ������
  // Wait for the BSY bit to be cleared
  while((FLASH->SR & FLASH_SR_BSY) != 0){}
	*(__IO uint16_t*)Address = (uint16_t)Data;
	while((FLASH->SR & FLASH_SR_BSY) != 0){}
  // Clear the PG bit in the FLASH_CR register
  FLASH->CR &= ~(uint32_t)FLASH_CR_PG;
	FLASH_Lock();
	#endif
}

/**
* brief  Erase all the sectors within the size
* param  Start address
* param Size
* retval  
*/

void FLASH_Erase_area(uint32_t start_address, uint32_t size){
	#ifdef STM32F205
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
	#endif
	#ifdef STM32F105
	if((start_address < 0x08000000) | (start_address > 0x080FFFFF)){
		return;
	}
	uint32_t address_pos = start_address;
	uint32_t last_address_pos = start_address + size;
	// if(last_address_pos > MEMCHIP_VOLUME) last_address_pos = MEMCHIP_VOLUME;
	
	while(address_pos <= last_address_pos){
		uint32_t sector_num = get_sector_num(address_pos);
		FLASH_Unlock();
		FLASH_Erase_Sector(sector_num);
		FLASH_Lock();
		address_pos += get_sector_size(sector_num);
	}
	#endif
	
}
