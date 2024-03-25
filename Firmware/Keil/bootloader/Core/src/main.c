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


#define MAIN_LOOP_TIMEOUT 0xFF
//=========================================================================================================
//===================================== Global vars	 and getters ==========================================

static uint8_t flashbuffer[CHUNK_SIZE];

static volatile uint32_t jumpAddress;
static volatile pFunction Jump_To_Application;
static volatile uFlashSize emergency_size;
static volatile uFlashSize update_size;

//=========================================================================================================
//===================================== Bootloader functions ==============================================
static inline uint32_t isEmergencyMode(void);
static inline void load_app_size(uint32_t address);
static void write_app_into_flash(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size);
static uint32_t verify_loaded_data(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size);


static inline uint32_t getCurrentMode(){
	volatile uint32_t current_mode = BOOTLOADER_DEFAULT_MODE; //BOOTLOADER_DEFAULT_MODE;

	if(isEmergencyMode()){
		uint32_t emergency_bin_sz_addr = memchip_make_app_address(memchipEmergencyBinSz);
		load_app_size(emergency_bin_sz_addr);
		emergency_size.data[3] = flashbuffer[0];
		emergency_size.data[2] = flashbuffer[1];
		emergency_size.data[1] = flashbuffer[2];
		emergency_size.data[0] = flashbuffer[3];
		current_mode = BOOTLOADER_EMERGENCY_MODE; 
	}
	else{
		uint32_t update_bin_sz_addr = memchip_make_app_address(memchipUpdateBinSz);
		load_app_size(update_bin_sz_addr);
		update_size.data[3] = flashbuffer[0];
		update_size.data[2] = flashbuffer[1];
		update_size.data[1] = flashbuffer[2];
		update_size.data[0] = flashbuffer[3];
		if(update_size._flashSize.size != INVALID_UPDATE_SIZE){
			current_mode = BOOTLOADER_UPDATE_MODE; 
		}
	} 
	return current_mode;
}


static inline void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset){
  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}


/**********************************************************************************************************
/
/
/                                            MAIN
/
/
**********************************************************************************************************/
static volatile uint32_t current_mode;
 int main(void){
   /* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	set_bor_level(BOR_VALUE);
	enable_peripherals();
	
	__disable_irq();	
	init_device_general_pinout();
	SPI_start_memchip_spi();
	
	
	//======================================================================================
	//================================= Interrupt init =====================================
	//======================================================================================
	
	SIGNAL_LED_OFF;
	
	//======================================================================================
	//=================================   Bootloader   =====================================
	//======================================================================================
	
	//volatile uint32_t 
		current_mode = getCurrentMode();
	
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
		SIGNAL_LED_ON;
		#ifdef BOARD_MK_STM32F105  // TODO delete this
		FLASH_Unlock();
		#endif
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
//		FLASH_Lock();
		FLASH_Unlock();
		
		
		uint32_t emergency_bin_addr = memchip_make_app_address(memchipEmergencyBin);
		
		write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, emergency_bin_addr,  emergency_size._flashSize.size ); //MAIN_PROGRAM_START_ADDRESS
		FLASH_Lock();
		uint32_t verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, emergency_bin_addr, emergency_size._flashSize.size);
		
		if(verify == VERIFY_OK){
			SIGNAL_LED_OFF;
		}	
		else {
			SIGNAL_LED_ON;
		}
	}
       
	//========================= UPDATE ===========================
  else if (current_mode == BOOTLOADER_UPDATE_MODE){    
		SIGNAL_LED_ON;
		#ifdef BOARD_MK_STM32F105  // TODO delete this
		FLASH_Unlock();
		#endif
		FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, update_size._flashSize.size);
		FLASH_Lock();
		
		uint32_t verify;
		uint32_t update_bin_addr = memchip_make_app_address(memchipUpdateBin);
		
		FLASH_Unlock();
		write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, update_bin_addr,  update_size._flashSize.size ); //MAIN_PROGRAM_START_ADDRESS
		FLASH_Lock();
		
		verify = verify_loaded_data(MAIN_PROGRAM_START_ADDRESS, update_bin_addr, update_size._flashSize.size);
		
		if(verify == VERIFY_FAILED){
			/*
			SIGNAL_LED_ON;
			FLASH_Unlock();
			FLASH_Erase_area(MAIN_PROGRAM_START_ADDRESS, emergency_size._flashSize.size);
			FLASH_Lock();
			FLASH_Unlock();
			write_app_into_flash(MAIN_PROGRAM_START_ADDRESS, BOOTLOADER_EMERGENCY_PROGRAMM_ADDR, emergency_size._flashSize.size); //MAIN_PROGRAM_START_ADDRESS
			FLASH_Lock();
			*/
		}

		/******** erase the programm from memory chip **********/
		
		const uint32_t erase_start_addr = memchip_make_app_address(memchipUpdateBin);
		const uint32_t erase_end_addr = memchip_make_app_address(memchipUpdateBinSz);
		memchip_erase_data_within_address(erase_start_addr, erase_end_addr);
		NVIC_SystemReset();
	}

	
	
	//======================================================================================
	//=================================   Main loop    =====================================
	//======================================================================================
	static volatile uint32_t timeout = MAIN_LOOP_TIMEOUT;
	while(1){

		reset_hw_watchdog();
		
		timeout = MAIN_LOOP_TIMEOUT;
		while(timeout-- > 0){
			//*******************************************************************
			//******************** buffered transmission procedure ***************
			//*******************************************************************
		}
		//********** LED blinking **************
		main_led_blink();
	}
}



//========================================================================================================================
//========================================================================================================================

static inline uint32_t isEmergencyMode(){
	if(EMERGENCY_PIN_SET) return BOOTLOADER_EMERGENCY_MODE;
	else return BOOTLOADER_DEFAULT_MODE;
}

//========================================================================================================================
//============================================ Load application's size ===================================================

static inline void load_app_size(uint32_t address){
	TOGGLE_SIGNAL_LED;
	memchip_read(address, &flashbuffer[0], 4);
}


//========================================================================================================================
//====================================== Write app into microcontroller flash ============================================


static void write_app_into_flash(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size){ //MAIN_PROGRAM_START_ADDRESS
	uint32_t write_pos = 0;
	uint32_t bytes_left = size;
	uint32_t currentAddress = main_app_address ;
	uint32_t test_counter = 0x00;
	
	while(bytes_left > CHUNK_SIZE){
		TOGGLE_SIGNAL_LED;
		memchip_read((loaded_app_address + write_pos), &flashbuffer[0], CHUNK_SIZE);
	
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
		memchip_read((loaded_app_address + write_pos), &flashbuffer[0], bytes_left);
		for (uint32_t i = 0; i < bytes_left; i += 4){
        FLASH_ProgramWord(currentAddress, *((uint32_t *)(void *)&flashbuffer[i]) );
        currentAddress += 4;
    } // for
	} // if(bytes_left > 0)
}


//========================================================================================================================
//======================================== Verify programmed data ========================================================

static uint32_t CORRUPTED_BLOCK = 0x00;
static uint32_t CORRUPTED_BYTE = 0xAA;


static uint32_t verify_loaded_data(uint32_t main_app_address, uint32_t loaded_app_address, uint32_t size){ //MAIN_PROGRAM_START_ADDRESS
	uint32_t write_pos = 0;
	uint32_t bytes_left = size;
	uint32_t currentAddress = main_app_address ;
	uint32_t test_counter = 0x00;
	
	while(bytes_left > CHUNK_SIZE){
		TOGGLE_SIGNAL_LED;
		memchip_read((loaded_app_address + write_pos), &flashbuffer[0], CHUNK_SIZE);
	
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
		
		memchip_read((loaded_app_address + write_pos), &flashbuffer[0], bytes_left);

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




