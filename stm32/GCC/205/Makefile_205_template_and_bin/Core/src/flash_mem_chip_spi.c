/****************************************************************
* 
* MemChip memory chip library
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
* TODO add DMA
*****************************************************************/

#include "flash_mem_chip_spi.h"

void write_enable_memchip(memchip_status *status, uint32_t length){		
	u_memchip_cmd_data read_cmd;
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_WREN;

	status->memchip_state = length;
	CS_RESET
	MX_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
}


void write_disable_memchip(){
	u_memchip_cmd_data read_cmd;
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_WRDI;
	
	CS_RESET
	MX_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
}

/**
* brief  Make sure RDSR bit indicates that programming is finished
* param  
* param 
* param  
* retval OK/Failed
*/

uint32_t write_timeout_memchip(){
	uint8_t result = 0xFF;
	uint32_t timeout = MEMCHIP_WR_TIMEOUT;
	
	while((timeout!=0) & (result & MEMCHIP_RDSR_WIP)){
		timeout--;
		result = read_status_reg_memchip();
	}
	
	if(!(result & MEMCHIP_RDSR_WIP)){
		return MEMCHIP_OK;
	}
	else return MEMCHIP_FAIL;
}

/**
* brief  Make sure RDSR bit indicates that erasing is finished
* param  
* param 
* param  
* retval OK/Failed
*/
uint32_t erase_timeout_memchip(uint32_t timeout){
	uint8_t result = 0xFF;

	while((timeout!=0) & (result & MEMCHIP_RDSR_WIP)){
		timeout--;
		result = read_status_reg_memchip();
	}
	if(!(result & MEMCHIP_RDSR_WIP)){
		return MEMCHIP_OK;
	}
	
	else return MEMCHIP_FAIL;
}

/**
* brief  Erase sector in memchip
* param  sector number or exact address
* param  if sector_num is not used leave as MEMCHIP_ERASE_SECTOR_REF
* param  
* retval 
*/

uint32_t erase_sector_memchip(memchip_status *status, uint32_t sector_num, uint32_t address_input){
	/* Enable write */	
		// CHK
	write_timeout_memchip();
	
	write_enable_memchip(status, status->memchip_state);
	u_memchip_cmd_data read_cmd;

	read_cmd.cmd.cmd_name = MEMCHIP_CMD_SE;

	
	if(sector_num != MEMCHIP_ERASE_USE_ADDRESS){
		
		uint32_t address = MEMCHIP_ADDRESS_FROM_SEC(sector_num);

		read_cmd.cmd.address[0] = (uint8_t)(address & 0xFF);					/* 03 */
		read_cmd.cmd.address[1] = (uint8_t)((address >> 8) & 0xFF);		/* 02 */
		read_cmd.cmd.address[2] = (uint8_t)((address >> 16) & 0xFF); 	/* 01 */
	}
	else{
		read_cmd.cmd.address[0] = (uint8_t)(address_input & 0xFF);					/* 03 */
		read_cmd.cmd.address[1] = (uint8_t)((address_input >> 8) & 0xFF);		/* 02 */
		read_cmd.cmd.address[2] = (uint8_t)((address_input >> 16) & 0xFF); 	/* 01 */		
	}
	CS_RESET
	
	MX_SPI_transmit_byte(read_cmd.raw_data[0]);
	MX_SPI_transmit_byte(read_cmd.raw_data[3]);	/* 03 */
	MX_SPI_transmit_byte(read_cmd.raw_data[2]);	/* 02 */
	MX_SPI_transmit_byte(read_cmd.raw_data[1]);	/* 01 */
	
	CS_SET
	/* Disable write */	
	write_disable_memchip();
	
	uint32_t result = write_timeout_memchip();
	return result;
}


/**
* brief  Read RDSR 
* param  
* param  
* param  
* retval RDSR 
*/
uint8_t read_status_reg_memchip(){
	uint8_t result = 0;
	CS_RESET	
	u_memchip_cmd_data rdsr_cmd;
	
	rdsr_cmd.cmd.cmd_name = MEMCHIP_CMD_RDSR;

	MX_SPI_transmit_byte(rdsr_cmd.raw_data[0]);
	result = MX_SPI_recieve_byte();
	CS_SET
	return result;
}

/**
* brief  Read RDCR 
* param  
* param  
* param  
* retval RDCR 
*/
uint8_t read_rdcr_reg_memchip(){
	uint8_t result = 0;
	CS_RESET	
	u_memchip_cmd_data rdsr_cmd;
	#ifdef MEMCHIP_M45PE16
	
	#else
	rdsr_cmd.cmd.cmd_name = MEMCHIP_CMD_RDCR;
	#endif
	
	MX_SPI_transmit_byte(rdsr_cmd.raw_data[0]);
	result = MX_SPI_recieve_byte();
	CS_SET
	return result;
}

/**
* brief  Write data into mx25l323
* param  address 0xXXXXXX
* param  buffer
* param  length
* retval MEMCHIP_OK/FAIL
*/

uint32_t programm_memchip(memchip_status *status, uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode){
	/* Enable write */
		// CHK
	write_timeout_memchip();
	
	u_memchip_cmd_data write_cmd;
	write_enable_memchip(status, length);
	
	write_cmd.cmd.cmd_name = MEMCHIP_CMD_PP;

	write_cmd.cmd.address[0] = (uint8_t)(address & 0xFF);						/* 03 */
	write_cmd.cmd.address[1] = (uint8_t)((address >> 8) & 0xFF);		/* 02 */
	write_cmd.cmd.address[2] = (uint8_t)((address >> 16) & 0xFF); 	/* 01 */
	CS_RESET
	
	MX_SPI_transmit_byte(write_cmd.raw_data[0]);
	MX_SPI_transmit_byte(write_cmd.raw_data[3]);	/* 03 */
	MX_SPI_transmit_byte(write_cmd.raw_data[2]);	/* 02 */
	MX_SPI_transmit_byte(write_cmd.raw_data[1]);	/* 01 */
	
	
	/***********************/
	/*****    No DMA   *****/
	/***********************/
	if(dma_mode == SPI_no_Dma){		
		for(uint32_t i = 0; i < length; i++){
			MX_SPI_transmit_byte(*buff_input++);
		}	
		CS_SET	
		/* Disable write */
		
		write_disable_memchip();
		uint32_t result = write_timeout_memchip();
		if(result == MEMCHIP_OK){
			status->memchip_state = 0;
		}
		return result;
	}
	
	/****************************/
	/*****   TX DMA   TODO ******/
	/****************************/	
	
	else if(dma_mode & SPI_DmaTx){
		#ifdef _MEMCHIP_DMA_DEBUG
		static uint8_t dummy[1] = {0xFF};
		SPI1->CR1  &= ~SPI_CR1_SPE;
	
		DMA_Disable(DMA1_Channel2);  					 
		DMA_DeInit(DMA1_Channel2);
		DMA_Init( DMA1_Channel2,								
              (uint32_t)&(SPI1->DR),				// Data register (peripherals)
              (uint32_t)dummy,							// Buffer address(memory)
              (uint16_t)length,							// Buffer size (param uint32_t ArraySize)
              TransCompl_Int_Disable 			+	// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +	// Half data completed interrupt disabled 
              TransError_Int_Disable      +	// Error interrupt disabled
              ReadPerif										+	// Reading from peripheral, writing to memory
              CircularMode_Disable        +	// Circular mode disabled 
              PeripheralInc_Disable       +	// Peripheral address not increased 
              MemoryInc_Enable            +	// Memory address is increased with every recieved byte 
              PDataSize_B                 +	// One-Byte sized data in the peripherals
              MDataSize_B                 +	// One-Byte sized data in the memory
              DMA_Priority_Low            +	// Priority
              M2M_Disable                 );// Not from memory to memory

		DMA1->IFCR = DMA_IFCR_CTCIF2;		

		DMA_Disable(DMA1_Channel3);  					  	
		DMA_DeInit(DMA1_Channel3);
		DMA_Init( DMA1_Channel3,									
              (uint32_t)&(SPI1->DR),				// Data register (peripherals)
              (uint32_t)buff_input,					// Buffer address(memory)
              (uint16_t)length,							// Buffer size (param uint32_t ArraySize)
              TransCompl_Int_Enable       +	// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +	// Half data completed interrupt disabled 
              TransError_Int_Disable      +	// Error interrupt disabled
              ReadMemory                  +	// Reading from peripheral, writing to memory
              CircularMode_Disable        +	// Circular mode disabled 
              PeripheralInc_Disable       +	// Peripheral address not increased 
              MemoryInc_Enable            +	// Memory address is increased with every recieved byte 
              PDataSize_B                 +	// One-Byte sized data in the peripherals
              MDataSize_B                 +	// One-Byte sized data in the memory
              DMA_Priority_Hi             +	// Priority
              M2M_Disable                 );// Not from memory to memory

		DMA1->IFCR = DMA_IFCR_CTCIF3;

	
		DMA_Enable(DMA1_Channel3);
	  DMA_Enable(DMA1_Channel2);	
		
		SPI1->CR1  |= SPI_CR1_SPE;		
		#endif
		return MEMCHIP_OK;		
		/* Programming procedure would be finished in DMA1_Channel3_IRQHandler */
		/* CS_SET would be set in DMA_IRQ */
	}
		
	else return MEMCHIP_FAIL;
}
/* programming with more than 256 */
uint32_t programm_memchip_long(memchip_status *status, uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode){
	uint32_t addr_pos = address;
	uint32_t total_length = length;
	while(total_length > MEMCHIP_MAX_WRITE_CHUNK){
		programm_memchip(status, addr_pos, buff_input, MEMCHIP_MAX_WRITE_CHUNK, dma_mode);
		addr_pos += MEMCHIP_MAX_WRITE_CHUNK;
		buff_input += MEMCHIP_MAX_WRITE_CHUNK;
		total_length -= MEMCHIP_MAX_WRITE_CHUNK;
	}
	if(total_length != 0) programm_memchip(status, addr_pos, buff_input, total_length, dma_mode);
	return MEMCHIP_OK;
}

/**************************************************************/
/**************************************************************/
/**** IMPORTANT! Full chip erase can take up ******************/
/**** to 30 seconds according to MX25L3233F datasheet**********/
/**************************************************************/
/**************************************************************/
/**
* brief  Erase the whole chip
* param  
* param  
* param  
* retval 
*/

uint32_t erase_chip_memchip(memchip_status *status){
	write_enable_memchip(status, status->memchip_state);
	u_memchip_cmd_data read_cmd;
	
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_CE ;

	CS_RESET
	MX_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
	
	write_disable_memchip();	
	uint32_t result = erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
	return result;
}


/**
* brief  Read an adrdress in mx25l323
* param  address 0xXXXXXX
* param  buffer
* param  length
* retval 
*/

void read_memchip(memchip_status *status, uint32_t address, uint8_t *buff, uint32_t length, eSpiDmaMode dma_mode){
	if(status->memchip_state == 0){
		return;
	}
	else{
		status->memchip_state = length;
	}
	
	u_memchip_cmd_data read_cmd;
	
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_READ;

	read_cmd.cmd.address[0] = (uint8_t)(address & 0xFF);					/* 03 */
	read_cmd.cmd.address[1] = (uint8_t)((address >> 8) & 0xFF);		/* 02 */
	read_cmd.cmd.address[2] = (uint8_t)((address >> 16) & 0xFF); 	/* 01 */
	CS_RESET
	
	MX_SPI_transmit_byte(read_cmd.raw_data[0]);
	MX_SPI_transmit_byte(read_cmd.raw_data[3]);	/* 03 */
	MX_SPI_transmit_byte(read_cmd.raw_data[2]);	/* 02 */
	MX_SPI_transmit_byte(read_cmd.raw_data[1]);	/* 01 */
	

	/***********************/
	/*****    No DMA   *****/
	/***********************/
	if(dma_mode == 0){						
		for(uint32_t i = 0; i < length; i++){
			*buff++ = MX_SPI_recieve_byte();
		}
	CS_SET
	status->memchip_state = 0;
	}
	/***************************/
	/*****   RX DMA  TODO ******/
	/***************************/		
	else if(dma_mode & SPI_DmaRx){
		#ifdef _MEMCHIP_DMA_DEBUG
		MX_SPI_transmit_byte(read_cmd.raw_data[0]); /* dummy */
		DMA_Disable(DMA1_Channel2);  					  	// USART1 TX is linked to DMA1 Ch4
		DMA_DeInit(DMA1_Channel2);
		DMA_Init( DMA1_Channel2,									// Channel4 is used for USART1
              (uint32_t)&(SPI1->DR),				// Data register (peripherals)
              (uint32_t)buff,								// Buffer address(memory)
              (uint16_t)length,							// Buffer size (param uint32_t ArraySize)
              TransCompl_Int_Enable				+	// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +	// Half data completed interrupt disabled 
              TransError_Int_Disable      +	// Error interrupt disabled
              ReadPerif										+	// Reading from peripheral, writing to memory
              CircularMode_Disable        +	// Circular mode disabled 
              PeripheralInc_Disable       +	// Peripheral address not increased 
              MemoryInc_Enable            +	// Memory address is increased with every recieved byte 
              PDataSize_B                 +	// One-Byte sized data in the peripherals
              MDataSize_B                 +	// One-Byte sized data in the memory
              DMA_Priority_Hi            	+	// Priority
              M2M_Disable                 );// Not from memory to memory

		DMA1->IFCR = DMA_IFCR_CTCIF2;		
		DMA_Enable(DMA1_Channel2);	

		uint8_t dummy = 0xFF;
		DMA_Disable(DMA1_Channel3);  					  	// USART1 TX is linked to DMA1 Ch4
		DMA_DeInit(DMA1_Channel3);
		DMA_Init( DMA1_Channel3,									// Channel4 is used for USART1
              (uint32_t)&(SPI1->DR),				// Data register (peripherals)
              (uint32_t)&dummy,							// Buffer address(memory)
              (uint16_t)length,												// Buffer size (param uint32_t ArraySize)
              TransCompl_Int_Disable      +	// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +	// Half data completed interrupt disabled 
              TransError_Int_Disable      +	// Error interrupt disabled
              ReadMemory                  +	// Reading from peripheral, writing to memory
              CircularMode_Disable        +	// Circular mode disabled 
              PeripheralInc_Disable       +	// Peripheral address not increased 
              MemoryInc_Enable	           +	// Memory address is increased with every recieved byte 
              PDataSize_B                 +	// One-Byte sized data in the peripherals
              MDataSize_B                 +	// One-Byte sized data in the memory
              DMA_Priority_Med            +	// Priority
              M2M_Disable                 );// Not from memory to memory

		DMA1->IFCR = DMA_IFCR_CTCIF3;		
		DMA_Enable(DMA1_Channel3);
		#endif
		/* CS_SET would be set in DMA_IRQ */
	}
}

/**
* brief  Write data into mx25l323 along with logging data index into the last page
* brief  And then validate
* param  address 0xXXXXXX
* param  buffer
* param  length
* param  validation
* param  DMA mode (!!! Cancels validation mode !!!)
* retval MEMCHIP_FAIL / MEMCHIP_OK
*/
#ifdef _MEMCHIP_STREAM_DEBUG
uint32_t put_data_memchip(memchip_status *status, uint32_t address, uint8_t *buff_input, uint32_t length, uint32_t validation_mode, eSpiDmaMode dma_mode){
	/******* check length *********/
	/* if a previous command is still being processed */
	if(status->memchip_state != 0){
		return MEMCHIP_FAIL;
	}
	
	if((validation_mode == VALIDATE_WRITE) & (length > VALIDATED_MAX_SIZE)){
		return MEMCHIP_FAIL;
	}
	
	if(dma_mode & SPI_DmaTx){
		programm_memchip(status, address, buff_input, length, dma_mode);
		return MEMCHIP_OK;
	}
	else{
		uint32_t programming_result = programm_memchip(status, address, buff_input, length, SPI_no_Dma);

		if(validation_mode == VALIDATE_WRITE){
			if(programming_result == MEMCHIP_FAIL){
				return MEMCHIP_FAIL;
			}
			
			uint8_t validation_read_buffer[VALIDATED_MAX_SIZE];
			read_memchip(status, address, validation_read_buffer, length, SPI_no_Dma);
				
			/******** compare the two byte arrays ******/
			uint32_t validation_length_counter = 0;
			uint32_t validation_index = 0; 
		
			while(validation_length_counter++ < length){
				if(validation_read_buffer[validation_index++] != *buff_input++){
					return MEMCHIP_FAIL;
				}			
			}
		}
	return programming_result;
	}
}
#endif	

 /**
* brief  Write data into mx25l323 along with logging data index into the last page
* brief  And then validate
* param  address 0xXXXXXX
* param  buffer
* param  length
* param  validation
* retval MEMCHIP_FAIL / MEMCHIP_OK
*/
#ifdef _MEMCHIP_STREAM_DEBUG
uint32_t input_stream_memchip(memchip_status *status, uint8_t *buff_input, uint32_t length, uint32_t validation_mode, eSpiDmaMode dma_mode){


	uint32_t result = put_data_memchip(status, status->stream_address.adress, buff_input, length, validation_mode, dma_mode);
	
	if((dma_mode & SPI_DmaTx) == SPI_DmaTx){
		return result;
	}

	else if(result == MEMCHIP_OK){ /* without DMA */
		
		result = write_timeout_memchip();
		if(result == MEMCHIP_OK){
			update_stream_index(status, length);
		}			
	}
	return result;
}
#endif	

/**
* brief  Get index of last written byte (used space on mx25 chip)
* param 
* param  
* param  
* retval OK/Failed
*/
#ifdef _MEMCHIP_STREAM_DEBUG
uint32_t init_memchip_status(memchip_status *status){
	
	#ifdef MEMCHIP_MX25L643
	uint32_t last_addr = MX25L323_STREAM_DATA_ADDRESS + MX25L323_STREAM_DATA_PAGE_SIZE;
	#endif	
	#ifdef MEMCHIP_MX25L323
	uint32_t last_addr = MX25L323_STREAM_DATA_ADDRESS + MX25L323_STREAM_DATA_PAGE_SIZE;
	#endif	
	#ifdef MEMCHIP_M45PE16
	uint32_t last_addr = M45PE16_STREAM_DATA_ADDRESS + M45PE16_STREAM_DATA_PAGE_SIZE;
	#endif

	#ifdef MEMCHIP_MX25L643
	u_memchip_index temp_index = {0};
	for(uint32_t i = MX25L643_STREAM_DATA_ADDRESS; i < last_addr; i+=MX25L643_STREAM_DATA_SIZE){
		read_memchip(status, i, temp_index.raw_data, MX25L643_STREAM_DATA_SIZE, SPI_no_Dma);
		if(temp_index.adress == 0xFFFFFFFF){
			if(i == MX25L643_STREAM_DATA_ADDRESS){ /* the first 4 bytes of the index page are 0xFF (the page is erased) */
				temp_index.adress = 0x00000000;
				status->stream_address = temp_index;
				status->stream_address_location.adress = i;
				programm_memchip(status, MX25L643_STREAM_DATA_ADDRESS, status->stream_address.raw_data, MX25L643_STREAM_DATA_SIZE, SPI_no_Dma);
				return MEMCHIP_OK;
			}	
		
		else{
				read_memchip(status, (i - MX25L643_STREAM_DATA_SIZE), temp_index.raw_data, MX25L643_STREAM_DATA_SIZE, SPI_no_Dma);
				status->stream_address = temp_index;
				status->stream_address_location.adress = i - MX25L643_STREAM_DATA_SIZE;
				return MEMCHIP_OK;
			}
		}
	}
	#endif	
	#ifdef MEMCHIP_MX25L323
	u_memchip_index temp_index = {0};
	for(uint32_t i = MX25L323_STREAM_DATA_ADDRESS; i < last_addr; i+=MX25L323_STREAM_DATA_SIZE){
		read_memchip(status, i, temp_index.raw_data, MX25L323_STREAM_DATA_SIZE, SPI_no_Dma);
		if(temp_index.adress == 0xFFFFFFFF){
			if(i == MX25L323_STREAM_DATA_ADDRESS){ /* the first 4 bytes of the index page are 0xFF (the page is erased) */
				temp_index.adress = 0x00000000;
				status->stream_address = temp_index;
				status->stream_address_location.adress = i;
				programm_memchip(status, MX25L323_STREAM_DATA_ADDRESS, status->stream_address.raw_data, MX25L323_STREAM_DATA_SIZE, SPI_no_Dma);
				return MEMCHIP_OK;
			}	
		
		else{
				read_memchip(status, (i - MX25L323_STREAM_DATA_SIZE), temp_index.raw_data, MX25L323_STREAM_DATA_SIZE, SPI_no_Dma);
				status->stream_address = temp_index;
				status->stream_address_location.adress = i - MX25L323_STREAM_DATA_SIZE;
				return MEMCHIP_OK;
			}
		}
	}
	#endif	
	#ifdef	MEMCHIP_M45PE16
	u_memchip_index temp_index = {0};
	for(uint32_t i = M45PE16_STREAM_DATA_ADDRESS; i < last_addr; i+=M45PE16_STREAM_DATA_SIZE){
		read_memchip(status, i, temp_index.raw_data, M45PE16_STREAM_DATA_SIZE, SPI_no_Dma);
		if(temp_index.adress == 0xFFFFFFFF){
			if(i == M45PE16_STREAM_DATA_ADDRESS){ /* the first 4 bytes of the index page are 0xFF (the page is erased) */
				temp_index.adress = 0x00000000;
				status->stream_address = temp_index;
				status->stream_address_location.adress = i;
				programm_memchip(status, M45PE16_STREAM_DATA_ADDRESS, status->stream_address.raw_data, M45PE16_STREAM_DATA_SIZE, SPI_no_Dma);
				return MEMCHIP_OK;
			}	
		
		else{
				read_memchip(status, (i - M45PE16_STREAM_DATA_SIZE), temp_index.raw_data, M45PE16_STREAM_DATA_SIZE, SPI_no_Dma);
				status->stream_address = temp_index;
				status->stream_address_location.adress = i - M45PE16_STREAM_DATA_SIZE;
				return MEMCHIP_OK;
			}
		}
	}
	#endif

	return MEMCHIP_FAIL;
}
	#endif
	
/**
* brief Update service page with a new stream index
* param "Status" structure to update,
* param  length of written string
* param  
* retval OK/Failed
*/
#ifdef _MEMCHIP_STREAM_DEBUG
uint32_t update_stream_index(memchip_status *status_for_update, uint32_t length){
	
	#ifdef MEMCHIP_MX25L643
	if(status_for_update->stream_address_location.adress >= (MX25L643_STREAM_DATA_ADDRESS + MX25L643_STREAM_DATA_PAGE_SIZE - MX25L643_STREAM_DATA_SIZE)){/* the end of the allocated service space on a chip */
		uint32_t result = erase_sector_memchip(status_for_update, MX25L643_STREAM_DATA_SECTOR, 0xFFFFFFFF); //length
		if(result == MEMCHIP_OK){
			status_for_update->stream_address_location.adress = MX25L643_STREAM_DATA_ADDRESS;
		}	
	}

	else{
		status_for_update->stream_address_location.adress += MX25L643_STREAM_DATA_SIZE;		
	}
	
	status_for_update->stream_address.adress += length;
			
	uint32_t result =  programm_memchip(status_for_update, status_for_update->stream_address_location.adress,
	status_for_update->stream_address.raw_data, MX25L643_STREAM_DATA_SIZE, SPI_no_Dma);
		
	return result;
	#endif	
	#ifdef MEMCHIP_MX25L323
	if(status_for_update->stream_address_location.adress >= (MX25L323_STREAM_DATA_ADDRESS + MX25L323_STREAM_DATA_PAGE_SIZE - MX25L323_STREAM_DATA_SIZE)){/* the end of the allocated service space on a chip */
		uint32_t result = erase_sector_memchip(status_for_update, MX25L323_STREAM_DATA_SECTOR, 0xFFFFFFFF); //length
		if(result == MEMCHIP_OK){
			status_for_update->stream_address_location.adress = MX25L323_STREAM_DATA_ADDRESS;
		}	
	}

	else{
		status_for_update->stream_address_location.adress += MX25L323_STREAM_DATA_SIZE;		
	}
	
	status_for_update->stream_address.adress += length;
			
	uint32_t result =  programm_memchip(status_for_update, status_for_update->stream_address_location.adress,
	status_for_update->stream_address.raw_data, MX25L323_STREAM_DATA_SIZE, SPI_no_Dma);
		
	return result;
	#endif	
	#ifdef MEMCHIP_M45PE16
	if(status_for_update->stream_address_location.adress >= (M45PE16_STREAM_DATA_ADDRESS + M45PE16_STREAM_DATA_PAGE_SIZE - M45PE16_STREAM_DATA_SIZE)){/* the end of the allocated service space on a chip */
		uint32_t result = erase_sector_memchip(status_for_update, M45PE16_STREAM_DATA_SECTOR, 0xFFFFFFFF); //length
		if(result == MEMCHIP_OK){
			status_for_update->stream_address_location.adress = M45PE16_STREAM_DATA_ADDRESS;
		}	
	}

	else{
		status_for_update->stream_address_location.adress += M45PE16_STREAM_DATA_SIZE;		
	}
	
	status_for_update->stream_address.adress += length;
			
	uint32_t result =  programm_memchip(status_for_update, status_for_update->stream_address_location.adress,
	status_for_update->stream_address.raw_data, M45PE16_STREAM_DATA_SIZE, SPI_no_Dma);
		
	return result;
	#endif
}
	#endif

/**
* brief  standardization function for SPI
* param 
* param  
* param  
* retval OK/Failed
*/
uint8_t MX_SPI_transmit_byte(uint8_t data){
	#ifdef TEC_MODULE 
	uint8_t _result = SPI1_transmit_byte(data);
	return _result;
	#endif
	#ifdef ALLIGATOR 
	uint8_t _result = SPI1_transmit_byte(data);
	return _result;
	#endif
	#ifdef DEVICE_2CAN
	uint8_t _result = SPI1_transmit_byte(data);
	return _result;
	#endif
	#ifdef DEVICE_2CAN_BOXED 
	uint8_t _result = SPI1_transmit_byte(data);
	return _result;
	#endif
	#ifdef DEVICE_2CAN_TJA1042 
	uint8_t _result = SPI1_transmit_byte(data);
	return _result;
	#endif	
	#ifdef DEVICE_SIGMA 
	uint8_t _result = SPI3_transmit_byte(data);
	return _result;
	#endif
}


uint8_t MX_SPI_recieve_byte(){
	#ifdef TEC_MODULE
	uint8_t _result = SPI1_recieve_byte();
	return _result;
	#endif
	#ifdef ALLIGATOR
	uint8_t _result = SPI1_recieve_byte();
	return _result;
	#endif	
	#ifdef DEVICE_2CAN
	uint8_t _result = SPI1_recieve_byte();
	return _result;
	#endif
	#ifdef DEVICE_2CAN_BOXED 
	uint8_t _result = SPI1_recieve_byte();
	return _result;
	#endif
	#ifdef DEVICE_2CAN_TJA1042 
	uint8_t _result = SPI1_recieve_byte();
	return _result;
	#endif
	#ifdef DEVICE_SIGMA 
	uint8_t _result = SPI3_recieve_byte();
	return _result;
	#endif
}

