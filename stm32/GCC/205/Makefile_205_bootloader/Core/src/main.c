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
* MAX PROGRAMM SIZE 64Kbyte 
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "main.h"

/********************************************************************************************/
/************************************ Device modes handler **********************************/
/********************************************************************************************/


/********************************************************************************************/
/************************************ 		Global vars			 **********************************/
/********************************************************************************************/

/* blink LED*/
#ifdef _BOOTLOADER_DEBUG
volatile uint32_t _debug_current_mode = 0xFF;
#endif

memchip_status memory_chip_status;

static uint8_t flashbuffer[CHUNK_SIZE];

static volatile uint32_t jumpAddress;
static volatile pFunction Jump_To_Application;
static volatile uFlashSize emergency_size;
static volatile uFlashSize update_size;

static inline uint32_t isEmergencyMode(void);
static inline void load_app_size(uint32_t address);
static inline void write_app_into_flash(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size);
static inline uint32_t verify_loaded_data(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size);


//================= DEBUG =======================
/*
volatile uint32_t TEST_write_flash_address = 0x00;
volatile uint32_t TEST_write_memcp_address = 0x00;
volatile uint32_t TEST_write_address_count = 0x00;

volatile uint32_t TEST_verif_flash_address = 0x00;
volatile uint32_t TEST_verif_memcp_address = 0x00;
volatile uint32_t TEST_verif_address_count = 0x00;
*/
//===============================================



static inline uint32_t getCurrentMode(){
	uint32_t current_mode = BOOTLOADER_DEFAULT_MODE; //BOOTLOADER_DEFAULT_MODE;

	if(isEmergencyMode()){
		load_app_size(BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR);
		current_mode = BOOTLOADER_EMERGENCY_MODE; 
		}
	
	else{
		load_app_size(BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR);
		if(update_size._flashSize.size != INVALID_UPDATE_SIZE){
			current_mode = BOOTLOADER_UPDATE_MODE; 
		}
	} 
		
#ifdef _BOOTLOADER_DEBUG
_debug_current_mode = current_mode;
#endif
	return current_mode;
}

static inline void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset){
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

static inline uint32_t erase_memchip_sector(uint32_t addr){
	erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, addr);		
		/* Make timeout and report the result */
	return erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
}

uint32_t TEST = 0xAA;
int main(void){
	/* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	__disable_irq();
	
	EnablePeripherals();
	initDeviceGeneralPinout();
	SIGNAL_LED_OFF;
	uint32_t current_mode = getCurrentMode();
	TEST = current_mode;
	//========================= DEFAULT ===========================
	if (current_mode == BOOTLOADER_DEFAULT_MODE){
		SIGNAL_LED_OFF;
    __disable_irq();
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, MAIN_PROGRAM_START_ADDRESS);
      
    jumpAddress = *(__IO uint32_t*) (MAIN_PROGRAM_START_ADDRESS + 4);
    Jump_To_Application = (pFunction) jumpAddress;
    __set_MSP(*(__IO uint32_t*) MAIN_PROGRAM_START_ADDRESS);
    Jump_To_Application();
  }
	
	//========================= EMERGENCY ===========================
  else if (current_mode == BOOTLOADER_EMERGENCY_MODE){    
 #ifdef STM32F205
		SIGNAL_LED_ON;
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
		FLASH_Unlock();
		write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size); //MAIN_PROGRAM_START_ADDRESS
		FLASH_Lock();
		
		
		uint32_t verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size);
		if(verify == VERIFY_OK){
			SIGNAL_LED_OFF;
		}	
		else {
				SIGNAL_LED_ON;
		}
		#endif	
		
		#ifdef STM32F105
		SIGNAL_LED_ON;
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
		
			FLASH_Unlock();
			write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR,  emergency_size._flashSize.size ); //MAIN_PROGRAM_START_ADDRESS
			FLASH_Lock();
			uint32_t verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size);
		
		if(verify == VERIFY_OK){
			SIGNAL_LED_OFF;
		}	
		else {
			SIGNAL_LED_ON;
		}
		#endif
		}
		
//		NVIC_SystemReset();
       
	//========================= UPDATE ===========================
  else if (current_mode == BOOTLOADER_UPDATE_MODE){    
 #ifdef STM32F205
		SIGNAL_LED_ON;
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, update_size._flashSize.size);
		FLASH_Unlock();
		write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_UPDATE_PROGRAMM_ADDR, update_size._flashSize.size); //MAIN_PROGRAM_START_ADDRESS
		FLASH_Lock();
		
		/* If programming failed, fallback to emergency version */
		uint32_t verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_UPDATE_PROGRAMM_ADDR, update_size._flashSize.size);
		if(verify == VERIFY_FAILED){
			SIGNAL_LED_ON;
			
			FLASH_Unlock();
			FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
			FLASH_Lock();
			FLASH_Unlock();
			write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size); //MAIN_PROGRAM_START_ADDRESS
			FLASH_Lock();
		}
		#endif	
		
		#ifdef STM32F105
		SIGNAL_LED_ON;
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, update_size._flashSize.size);
		
		uint32_t verify;
	//	if(update_size._flashSize.size < MEMCHIP_VOLUME - BOOTLOADER_UPDATE_PROGRAMM_ADDR){
			FLASH_Unlock();
			write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_UPDATE_PROGRAMM_ADDR,  update_size._flashSize.size ); //MAIN_PROGRAM_START_ADDRESS
			FLASH_Lock();
			verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_UPDATE_PROGRAMM_ADDR, update_size._flashSize.size);
//		}
//		else verify = VERIFY_FAILED;
		
		
		
		if(verify == VERIFY_FAILED){
			SIGNAL_LED_ON;
			FLASH_Unlock();
			FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
			FLASH_Lock();
			FLASH_Unlock();
			write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size); //MAIN_PROGRAM_START_ADDRESS
			FLASH_Lock();
		}

		#endif	
		/******** erase the programm from memory chip **********/
//		else {
#ifdef MEMCHIP_MX25L16
			SIGNAL_LED_OFF;
			
			uint32_t _address_pos_to_erase = BOOTLOADER_UPDATE_PROGRAMM_ADDR;
			uint32_t border_address_to_erase = BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR + 4;
			
			while(_address_pos_to_erase < border_address_to_erase){
				erase_memchip_sector(_address_pos_to_erase);
				_address_pos_to_erase += MEMCHIP_CMD_SECTOR_SIZE;
			}
			NVIC_SystemReset();
#endif
#ifdef MEMCHIP_MX25L323
			SIGNAL_LED_OFF;
			
			uint32_t _address_pos_to_erase = BOOTLOADER_UPDATE_PROGRAMM_ADDR;
			uint32_t border_address_to_erase = BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR + 4;
			
			while(_address_pos_to_erase < border_address_to_erase){
				erase_memchip_sector(_address_pos_to_erase);
				_address_pos_to_erase += MEMCHIP_CMD_SECTOR_SIZE;
			}
			NVIC_SystemReset();
#endif
#ifdef MEMCHIP_M45PE16
			SIGNAL_LED_OFF;
			
			uint32_t _address_pos_to_erase = BOOTLOADER_UPDATE_PROGRAMM_ADDR;
			uint32_t border_address_to_erase = BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR + 4;
			
			while(_address_pos_to_erase < border_address_to_erase){
				erase_memchip_sector(_address_pos_to_erase);
				_address_pos_to_erase += MEMCHIP_CMD_SECTOR_SIZE;
			}
			NVIC_SystemReset();
#endif
//			}
		}
	static volatile uint32_t timeout = 0xFFFF;
	while(1){
		timeout = 0xFFFF;
		timeout--;
	}
}



//========================================================================================================================
//========================================================================================================================

static inline uint32_t isEmergencyMode(){
	if(EMERGENCY_PIN_SET) return BOOTLOADER_EMERGENCY_MODE;
	else return 0;
}

//========================================================================================================================
//========================================================================================================================

static inline void load_app_size(uint32_t address){
	TOGGLE_SIGNAL_LED;
	memory_chip_status.memchip_state = 4;
	if(address == BOOTLOADER_EMERGENCY_PROGRAMM_SIZE_ADDR){
		read_memchip(&memory_chip_status, address, &flashbuffer[0], 4, SPI_no_Dma);
		emergency_size.data[3] = flashbuffer[0];
		emergency_size.data[2] = flashbuffer[1];
		emergency_size.data[1] = flashbuffer[2];
		emergency_size.data[0] = flashbuffer[3];
	}
	
	else if(address == BOOTLOADER_UPDATE_PROGRAMM_SIZE_ADDR){
		read_memchip(&memory_chip_status, address, &flashbuffer[0], 4, SPI_no_Dma);
		update_size.data[3] = flashbuffer[0];
		update_size.data[2] = flashbuffer[1];
		update_size.data[1] = flashbuffer[2];
		update_size.data[0] = flashbuffer[3];
	}
}


//========================================================================================================================
//========================================================================================================================


static inline void write_app_into_flash(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size){ //MAIN_PROGRAM_START_ADDRESS
	uint32_t write_pos = 0;
	uint32_t bytes_left = size;
	uint32_t currentAddress = main_app_address ;
	uint32_t test_counter = 0x00;
	


	while(bytes_left > CHUNK_SIZE){
		TOGGLE_SIGNAL_LED;
		memory_chip_status.memchip_state = CHUNK_SIZE;
		read_memchip(&memory_chip_status, (loaded_app_address + write_pos), &flashbuffer[0], CHUNK_SIZE, SPI_no_Dma);
	
		// write flashbuffer into Flash 
		for (uint32_t i = 0; i < CHUNK_SIZE; i += 4){
			TOGGLE_SIGNAL_LED;
        FLASH_ProgramWord(currentAddress, *((uint32_t *)(void *)&flashbuffer[i]) );
			
				if(*(__IO uint32_t*)currentAddress != *((uint32_t *)(void *)&flashbuffer[i])){
				}
				test_counter+=4;
				currentAddress += 4;
    }
		write_pos += CHUNK_SIZE;
		bytes_left -= CHUNK_SIZE;
		
	}
	
	// write flashbuffer into Flash 
	if(bytes_left > 0){
		TOGGLE_SIGNAL_LED;
		memory_chip_status.memchip_state = bytes_left;
		read_memchip(&memory_chip_status, (loaded_app_address + write_pos), flashbuffer, bytes_left, SPI_no_Dma);
		for (uint32_t i = 0; i < bytes_left; i += 4){
        FLASH_ProgramWord(currentAddress, *((uint32_t *)(void *)&flashbuffer[i]) );
        currentAddress += 4;
    }
		
	}
	/*	*/
}


//========================================================================================================================
//========================================================================================================================

uint32_t CORRUPTED_BLOCK = 0x00;
uint32_t CORRUPTED_BYTE = 0xAA;


static inline uint32_t verify_loaded_data(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size){ //MAIN_PROGRAM_START_ADDRESS
	uint32_t write_pos = 0;
	uint32_t bytes_left = size;
	uint32_t currentAddress = main_app_address ;
	uint32_t test_counter = 0x00;
	
	while(bytes_left > CHUNK_SIZE){
		TOGGLE_SIGNAL_LED;
		memory_chip_status.memchip_state = CHUNK_SIZE;
		read_memchip(&memory_chip_status, (loaded_app_address + write_pos), &flashbuffer[0], CHUNK_SIZE, SPI_no_Dma);
	
		/* write flashbuffer into Flash */
		for (uint32_t i = 0; i < CHUNK_SIZE; i += 4){
			TOGGLE_SIGNAL_LED;
        if(*(__IO uint32_t*)currentAddress != *((uint32_t *)(void *)&flashbuffer[i])){

					return VERIFY_FAILED;
				}
				currentAddress += 4;
				test_counter+=4;
    }
		write_pos += CHUNK_SIZE;
		bytes_left -= CHUNK_SIZE;
	}
	
	if(bytes_left > 0){
		CORRUPTED_BYTE = bytes_left;
		
		memory_chip_status.memchip_state = bytes_left;
		read_memchip(&memory_chip_status, (loaded_app_address + write_pos), flashbuffer, bytes_left, SPI_no_Dma);
		for (uint32_t i = 0; i < bytes_left; i += 4){
			
			TOGGLE_SIGNAL_LED;
        if(*(__IO uint32_t*)currentAddress != *((uint32_t *)(void *)&flashbuffer[i])){
					CORRUPTED_BLOCK = *(__IO uint32_t*)currentAddress;
					CORRUPTED_BYTE = *((uint32_t *)(void *)&flashbuffer[i]);
					return VERIFY_FAILED;
				}
        currentAddress += 4;
    }
		/* write flashbuffer into Flash */
	}
	return VERIFY_OK;
}
