/****************************************************************
* 
* NOR MemChip memory chip library
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
* TODO add DMA
*****************************************************************/
#include "device_model.h"
#ifdef MEMCHIP_NOR_FLASH

#include "Flash_memchip/flash_nor_mem_chip_spi.h"

#define VALIDATE_WRITE					    1U			/* validation mode */
#define FAST_WRITE							    0U			/* validation mode */

#define MEMCHIP_ERASE_USE_ADDRESS		0xFFFFFFFF

//=================================== read functions =========================================
static void read_memchip(uint32_t address, uint8_t *buff, uint32_t length, eSpiDmaMode dma_mode);

//==================================== erase functions =======================================
static uint32_t erase_sector_memchip(uint32_t sector_num, uint32_t address_input);

//=================================== programm functions =====================================
static uint32_t programm_memchip(uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode);
static uint32_t programm_memchip_long(uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode);

//==================================== index handlers ========================================

static uint8_t memchip_read_status_reg(void);
#ifdef UNUSED_EXTRA
static uint8_t memchip_read_rdcr_reg(void);
#endif // UNUSED_EXTRA

//====================================== SPI link ============================================
static uint8_t memchip_SPI_transmit_byte(uint8_t data);
static uint8_t memchip_SPI_receive_byte(void);


static memchip_status status;


/**
* brief  Read RDSR 
* param  
* param  
* param  
* retval RDSR 
*/
uint8_t memchip_read_status_reg(void){
	uint8_t result = 0;
	CS_RESET	
	u_memchip_cmd_data rdsr_cmd;
	
	rdsr_cmd.cmd.cmd_name = MEMCHIP_CMD_RDSR;

	memchip_SPI_transmit_byte(rdsr_cmd.raw_data[0]);
	result = memchip_SPI_receive_byte();
	CS_SET
	return result;
}

static void write_enable_memchip(void){		
	u_memchip_cmd_data read_cmd;
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_WREN;
 // 	status.memchip_state = length;
	CS_RESET
	memchip_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
}


static void write_disable_memchip(void){
	u_memchip_cmd_data read_cmd;
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_WRDI;
	
	CS_RESET
	memchip_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
}

/**
* brief  Make sure RDSR bit indicates that programming is finished
* param  
* param 
* param  
* retval OK/Failed
*/
static uint32_t write_timeout_memchip(void){
	uint8_t result = 0xFF;
	uint32_t timeout = MEMCHIP_WR_TIMEOUT;
	
	while((timeout!=0) & (result & MEMCHIP_RDSR_WIP)){
		timeout--;
		result = memchip_read_status_reg();
	}
	if(!(result & MEMCHIP_RDSR_WIP)){
		return OPERATION_OK;
	}
	else return OPERATION_FAIL;
}

/**
* brief  Make sure RDSR bit indicates that erasing is finished
* param  
* param 
* param  
* retval OK/Failed
*/
static uint32_t erase_timeout_memchip(uint32_t timeout){
	uint8_t result = 0xFF;

	while((timeout!=0) & (result & MEMCHIP_RDSR_WIP)){
		timeout--;
		result = memchip_read_status_reg();
	}
	if(!(result & MEMCHIP_RDSR_WIP)){
		return OPERATION_OK;
	}
	
	else return OPERATION_FAIL;
}

/**
* brief  Erase sector in memchip
* param  sector number or exact address
* param  if sector_num is not used leave as MEMCHIP_ERASE_SECTOR_REF
* param  
* retval 
*/

uint32_t erase_sector_memchip(uint32_t sector_num, uint32_t address_input){
	/* Enable write */	
		// CHK
	write_timeout_memchip();
	
	write_enable_memchip();
	u_memchip_cmd_data read_cmd;

	read_cmd.cmd.cmd_name = MEMCHIP_CMD_SE;

	
	if(sector_num != MEMCHIP_ERASE_USE_ADDRESS){ // TODO
		
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
	
	memchip_SPI_transmit_byte(read_cmd.raw_data[0]);
	memchip_SPI_transmit_byte(read_cmd.raw_data[3]);	/* 03 */
	memchip_SPI_transmit_byte(read_cmd.raw_data[2]);	/* 02 */
	memchip_SPI_transmit_byte(read_cmd.raw_data[1]);	/* 01 */
	
	CS_SET
	/* Disable write */	
	write_disable_memchip();
	
	write_timeout_memchip();
	uint32_t result = erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
	return result;
}


/**
* brief  Write data into mx25l323
* param  address 0xXXXXXX
* param  buffer
* param  length
* retval MEMCHIP_OK/FAIL
*/

static uint32_t programm_memchip(uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode){
	/* Enable write */
		// CHK
	write_timeout_memchip();
	
	u_memchip_cmd_data write_cmd;
	write_enable_memchip();
	status.memchip_state = length;
	
	write_cmd.cmd.cmd_name = MEMCHIP_CMD_PP;

	write_cmd.cmd.address[0] = (uint8_t)(address & 0xFF);						/* 03 */
	write_cmd.cmd.address[1] = (uint8_t)((address >> 8) & 0xFF);		/* 02 */
	write_cmd.cmd.address[2] = (uint8_t)((address >> 16) & 0xFF); 	/* 01 */
	CS_RESET
	
	memchip_SPI_transmit_byte(write_cmd.raw_data[0]);
	memchip_SPI_transmit_byte(write_cmd.raw_data[3]);	/* 03 */
	memchip_SPI_transmit_byte(write_cmd.raw_data[2]);	/* 02 */
	memchip_SPI_transmit_byte(write_cmd.raw_data[1]);	/* 01 */
	
	
	/***********************/
	/*****    No DMA   *****/
	/***********************/
	if(dma_mode == SPI_no_Dma){
		for(uint32_t i = 0; i < length; i++){
			memchip_SPI_transmit_byte(*buff_input++);
		}	
		CS_SET	
		/* Disable write */
		
		write_disable_memchip();
		uint32_t result = write_timeout_memchip();
		if(result == OPERATION_OK){
			status.memchip_state = 0;
		}
		return result;
	}
	
	/****************************/
	/*****   TX DMA   TODO ******/
	/****************************/	
	else if(dma_mode & SPI_DmaTx){
		return OPERATION_OK;		
	}
		
	else return OPERATION_FAIL;
}
/* programming with more than 256 */
static uint32_t programm_memchip_long(uint32_t address, uint8_t *buff_input, uint32_t length, eSpiDmaMode dma_mode){
	uint32_t addr_pos = address;
	uint32_t total_length = length;
	while(total_length > MEMCHIP_MAX_WRITE_CHUNK){
		programm_memchip(addr_pos, buff_input, MEMCHIP_MAX_WRITE_CHUNK, dma_mode);
		addr_pos += MEMCHIP_MAX_WRITE_CHUNK;
		buff_input += MEMCHIP_MAX_WRITE_CHUNK;
		total_length -= MEMCHIP_MAX_WRITE_CHUNK;
	}
	if(total_length != 0) programm_memchip(addr_pos, buff_input, total_length, dma_mode);
	return OPERATION_OK;
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

uint32_t erase_chip_memchip(void){
	write_enable_memchip();
	u_memchip_cmd_data read_cmd;
	
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_CE ;

	CS_RESET
	memchip_SPI_transmit_byte(read_cmd.raw_data[0]);
	CS_SET
	
	write_disable_memchip();	
	uint32_t result = erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
	return result;
}


/**  .memchip_state = LENGTH;  -  required before use
* brief  Read an adrdress in mx25l323
* param  address 0xXXXXXX
* param  buffer
* param  length
* retval 
*/

void read_memchip(uint32_t address, uint8_t *buff, uint32_t length, eSpiDmaMode dma_mode){
	if(status.memchip_state == 0){
		return;
	}
	else{
		status.memchip_state = length;
	}
	
	u_memchip_cmd_data read_cmd;
	
	read_cmd.cmd.cmd_name = MEMCHIP_CMD_READ;

	read_cmd.cmd.address[0] = (uint8_t)(address & 0xFF);					/* 03 */
	read_cmd.cmd.address[1] = (uint8_t)((address >> 8) & 0xFF);		/* 02 */
	read_cmd.cmd.address[2] = (uint8_t)((address >> 16) & 0xFF); 	/* 01 */
	CS_RESET
	
	memchip_SPI_transmit_byte(read_cmd.raw_data[0]);
	memchip_SPI_transmit_byte(read_cmd.raw_data[3]);	/* 03 */
	memchip_SPI_transmit_byte(read_cmd.raw_data[2]);	/* 02 */
	memchip_SPI_transmit_byte(read_cmd.raw_data[1]);	/* 01 */
	

	/***********************/
	/*****    No DMA   *****/
	/***********************/
	if(dma_mode == 0){						
		for(uint32_t i = 0; i < length; i++){
			*buff++ = memchip_SPI_receive_byte();
		}
	CS_SET
	status.memchip_state = 0;
	}
	/***************************/
	/*****   RX DMA  TODO ******/
	/***************************/		
	else if(dma_mode & SPI_DmaRx){
		/* CS_SET would be set in DMA_IRQ */
	}
}

//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_read(uint32_t address, uint8_t *output, uint32_t length){
	status.memchip_state = length;
	read_memchip(address, output, length, SPI_no_Dma);
	return OPERATION_OK;
}

//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_write(uint32_t address, uint8_t *buf, uint32_t length){
	uint32_t result = programm_memchip_long(address, buf, length, SPI_no_Dma);
	return result;
}

uint32_t memchip_rewrite(uint32_t address, uint8_t *buf, uint32_t length){
	uint32_t result = erase_sector_memchip(MEMCHIP_ERASE_USE_ADDRESS, address);
	if(result == OPERATION_FAIL) return result;
	result = programm_memchip_long(address, buf, length, SPI_no_Dma);
	return result;
}
uint32_t memchip_erase_block_within_address(uint32_t address){
	return erase_sector_memchip(MEMCHIP_ERASE_USE_ADDRESS, address);
}

//============================================================================================
//==================================== Application function ==================================
/*
* brief  Erase all data within the address range
* param  start address
* param  end address
* param 
* retval 
*/
void memchip_erase_data_within_address(uint32_t start_address, uint32_t end_address){
	if(end_address <= start_address) return;
	
	const uint32_t sectors_address_step = MEMCHIP_CMD_SECTOR_SIZE;
	const uint32_t sectors_count =  MEMCHIP_CMD_SECTOR_COUNT;
	const uint32_t programm_size =  end_address - start_address;
	
	const uint32_t empty_space = (sectors_count*sectors_address_step) - start_address;
	if(empty_space <  programm_size) return;
	
	uint32_t residue = ((programm_size % sectors_address_step)==0) ? 0 : 1 ;
	uint32_t sectors_to_erase_count = programm_size / sectors_address_step + residue;
	
	for(uint32_t i = 0; i < sectors_to_erase_count; i++){
		memchip_erase_block_within_address((start_address + sectors_address_step*i));
	}
}


uint32_t memchip_get_pending_length(void){
	return status.stream_pending_data;
}
uint32_t memchip_get_address(void){
	return status.stream_address;
}
void memchip_set_pending_data(uint32_t length){
	status.stream_pending_data = length;
}
void memchip_deduct_pending_data(uint32_t length){
	status.stream_address += length;
	status.stream_pending_data -= length;
}
void memchip_set_address(uint32_t address){
	status.stream_address = address;
}


//===============================================================================================================
//========================================== SPI periphery linking ==============================================
//===============================================================================================================
/**
* brief  Linking function for SPI
* param 
* param  
* param  
* retval 
*/
static uint8_t memchip_SPI_transmit_byte(uint8_t data){
	uint8_t _result = SPI_transmit_byte(MEMCHIP_SPI, data);
	return _result;
}


static uint8_t memchip_SPI_receive_byte(){
	uint8_t _result = SPI_receive_byte(MEMCHIP_SPI);
	return _result;
}






#ifdef UNUSED_EXTRA


/**
* brief  Read RDCR 
* param  
* param  
* param  
* retval RDCR 
*/
uint8_t memchip_read_rdcr_reg(void){
	uint8_t result = 0;
	#ifdef MEMCHIP_M45PE16
	#else
	CS_RESET	
	u_memchip_cmd_data rdsr_cmd;
	rdsr_cmd.cmd.cmd_name = MEMCHIP_CMD_RDCR;
	
	memchip_SPI_transmit_byte(rdsr_cmd.raw_data[0]);
	result = memchip_SPI_receive_byte();
	CS_SET
	#endif
	return result;
}
#endif // UNUSED_EXTRA

#endif // MEMCHIP_NOR_FLASH
