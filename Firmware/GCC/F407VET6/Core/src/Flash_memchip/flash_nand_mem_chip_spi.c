/****************************************************************
* 
* NAND MemChip memory chip library
*
* Alex Svetlichnyy 2024 svetlal@outlook.com
*
* TODO add DMA
*****************************************************************/
#include "device_model.h"
#ifdef MEMCHIP_NAND_FLASH
#include "Flash_memchip/flash_nand_mem_chip_spi.h"

#define VALIDATE_WRITE					    1U			/* validation mode */
#define FAST_WRITE							    0U			/* validation mode */

//=========================================================================================================
//========================================   Misc. functions   ============================================
static void _timeout(uint32_t val){
	for(uint32_t i=0; i<val; i++){__NOP();}
}


static nand_index  the_nand_index;
static nand_index cache_nand_index;
static memchip_status memory_chip_status;

//===============================================================================================================
//==========================================   Static functions    ==============================================
//===============================================================================================================
static uint32_t status_timeout_and(uint8_t feature, uint8_t bit, uint32_t timeout);
static uint32_t status_timeout_nor(uint8_t feature, uint8_t bit, uint32_t timeout);

static nand_12bit_address make_12bit_address(uint16_t byte_pos, uint16_t wrap_msk);
static nand_24bit_address make_24bit_address(uint16_t block, uint16_t page);

static uint32_t disable_w_protection(void);
static uint32_t memchip_write_disable(void);
static uint32_t memchip_write_enable(void);
	
static void memchip_nand_make_index(uint32_t addr, nand_index *index, eNandAccessMode _access_mode);
static void memchip_nand_make_start_index(uint16_t block, uint16_t page, uint16_t byte, nand_index *index, eNandAccessMode _access_mode);
static void increase_index(uint16_t value, nand_index *index, eNandAccessMode _access_mode, uint8_t read_pg_flag);

static void memchip_increase_index(uint16_t value, nand_index *index, eNandAccessMode _access_mode);
static void memchip_increase_index_dummy(uint16_t value, nand_index *index, eNandAccessMode _access_mode);


static void memchip_read_page(uint16_t block, uint16_t page);
static void memchip_read_from_cache(uint16_t byte_pos, uint8_t* output, uint16_t wrap_msk, uint16_t size);
static uint32_t memchip_read_from_nand(uint8_t *output, uint16_t length, uint16_t max_chunk, nand_index *index, eNandAccessMode _access_mode);

static uint32_t memchip_programm_execute(nand_index *index);

static uint8_t memchip_nand_get_feature(uint8_t address);
static uint8_t memchip_nand_set_feature(uint8_t address, uint8_t bit);
static uint8_t memchip_nand_reset_feature(uint8_t address, uint8_t bit);


//===============================================================================================================
//========================================== SPI periphery linking ==============================================
//===============================================================================================================
/**** byte ****/
static uint8_t memchip_SPI_transmit_byte(uint8_t data);
static uint8_t memchip_SPI_receive_byte(void);
/**** data ****/
static void memchip_SPI_transmit_receive_data(uint8_t *rx_data, uint8_t *tx_data, uint16_t size);
static void memchip_SPI_receive_data(uint8_t *rx_data, uint16_t size);
static void memchip_SPI_transmit_data(uint8_t *tx_data, uint16_t size);



/**********************************************************************************/
/********************       Static functions        *******************************/
/**********************************************************************************/

/********************** Make timeout until a bit is set **************************/
static uint32_t status_timeout_and(uint8_t feature, uint8_t bit, uint32_t timeout){
	uint8_t result = 0;
	volatile uint32_t counter = timeout;
	while((counter-- > 0) && (result!=bit)){
		result = (memchip_nand_get_feature(feature) &  bit);
	}
	if(result==bit) return OPERATION_OK;
	else return OPERATION_FAIL;
}

/********************** Make timeout until a bit is reset ************************/
static uint32_t status_timeout_nor(uint8_t feature, uint8_t bit, uint32_t timeout){
	uint8_t result = bit;
	volatile uint32_t counter = timeout;
	while((counter-- > 0) && (result==bit)){
		result = (memchip_nand_get_feature(feature) &  bit);
	}
	if(result!=bit) return OPERATION_OK;
	else return OPERATION_FAIL;
}

/*************************** Make 12 bit address **********************************/
static nand_12bit_address        make_12bit_address(uint16_t byte_pos, uint16_t wrap_msk){
	nand_12bit_address address;
	address.word16 = byte_pos;
	address.word16 = address.word16 & 0xFFF;
	address.word16 &= ~NAND_12BIT_ADDRESS_WRAP_MSK;
	//address.word16 = address.word16 | wrap_msk;
	
	return address;
}

/*************************** Make 24 bit address **********************************/
static nand_24bit_address make_24bit_address(uint16_t block, uint16_t page){
	uint32_t address =  NAND_ROW_ADDRESS_FROM_BLK_AND_PAGE(block, page);
	address = (uint16_t)(address & NAND_24BIT_ADDRESS_MSK);
	nand_24bit_address result;
	result.word32 = address;
	return result;
}

/*************************** Disable write protection *****************************/
static uint32_t disable_w_protection(void){
	volatile uint32_t result = OPERATION_FAIL;

	memchip_nand_reset_feature(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP0);
	result = status_timeout_nor(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP0, NAND_WEL_SET_TIMEOUT);
	
	memchip_nand_reset_feature(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP1);
	result = status_timeout_nor(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP1, NAND_WEL_SET_TIMEOUT);
	
	memchip_nand_reset_feature(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP2);
	result = status_timeout_nor(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_BP2, NAND_WEL_SET_TIMEOUT);
	
	memchip_nand_reset_feature(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_INVERT);
	result = status_timeout_nor(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_INVERT, NAND_WEL_SET_TIMEOUT);
	
	memchip_nand_reset_feature(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_COMPLEMENT);	
	result = status_timeout_nor(NAND_CMD_FEATURE_BLOCK_PROTEC, NAND_CMD_FEATURE_BLOCK_PROTEC_COMPLEMENT, NAND_WEL_SET_TIMEOUT);

	return result;
}
/**
* brief Increase a nand index by a byte value
* param byte count value
* param index pointer 
* param  
* retval
*/
static void increase_index(uint16_t value, nand_index *index, eNandAccessMode _access_mode, uint8_t read_pg_flag){
	const uint16_t page_size = (_access_mode == Nand_data_mode) ? index->data_page_size : index->full_page_size;
	
	if(value > page_size) return;
	
	index->byte_pos = (uint16_t)(index->byte_pos + value);
	
	while(index->byte_pos >= page_size ){
		//make sure, this is not the last page of the last block
		if((index->block_pos >= (NAND_SIZ_BLOCKS - 1)) && (index->page_pos >= (NAND_BLOCK_SIZ_PAGES - 1))) return;
		
		index->byte_pos = (uint16_t)(index->byte_pos - page_size);
		index->page_pos = (uint16_t)(index->page_pos + 1);
		
		if(index->page_pos >= index->page_count){
			index->page_pos = 0;
			index->block_pos = (uint16_t)(index->block_pos + 1);
		}
		if((index->block_pos >= (NAND_SIZ_BLOCKS - 1)) && (index->page_pos >= (NAND_BLOCK_SIZ_PAGES - 1))) return;
		
		if(read_pg_flag != MEMCHIP_DUMMY_OP){
			memchip_read_page(index->block_pos,  index->page_pos);
			_timeout(NAND_READ_PAGE_TIMEOUT);
		}
	}
}


/********************************************************************************************/
/********************************      Index handlers      **********************************/
/********************************************************************************************/

/**
* brief Make index (block num, page num, byte num) out of address
* param uint32_t address
* param index pointer 
* param access mode
* retval
*/
static void memchip_nand_make_index(uint32_t addr, nand_index *index, eNandAccessMode _access_mode){
	uint16_t block_pos = 0; 
	uint16_t page_pos = 0;  
	
	uint32_t addr_pos = addr;
	
	while(addr_pos >= NAND_BLOCK_SIZE_DATA_SPARE){
		block_pos = (uint16_t)(block_pos + 1);
		addr_pos = (uint32_t)(addr_pos - NAND_BLOCK_SIZE_DATA_SPARE); 
	}
	while(addr_pos >= NAND_PAGE_SIZ_DATA_SPARE){
		page_pos = (uint16_t)(page_pos + 1);
		addr_pos = (uint32_t)(addr_pos - NAND_PAGE_SIZ_DATA_SPARE); 
	}
	
	uint16_t byte_pos = addr_pos;
	
	if(_access_mode == Nand_data_mode){
		if(byte_pos >= NAND_PAGE_SIZ_DATA){
			page_pos = (uint16_t)(page_pos + 1);
			if(page_pos == NAND_BLOCK_SIZ_PAGES){
				block_pos = (uint16_t)(block_pos + 1);
				page_pos = 0;
			}
			byte_pos = 0;
		}
	}
	
	if(block_pos >= NAND_SIZ_BLOCKS) block_pos = 0;
	
	index->block_pos = block_pos;
	index->page_pos = page_pos;
	index->byte_pos = byte_pos;
	index->full_page_size = (uint16_t)NAND_PAGE_SIZ_DATA_SPARE;
	index->data_page_size = (uint16_t)NAND_PAGE_SIZ_DATA;
	index->page_count = (uint32_t)NAND_BLOCK_SIZ_PAGES;
}

/**
* brief Make index (block num, page num, byte num) out of block num, page num, byte num
* param  block num, page num, byte num
* param  index pointer 
* param  access mode
* retval
*/

static void memchip_nand_make_start_index(uint16_t block, uint16_t page, uint16_t byte, nand_index *index, eNandAccessMode _access_mode){
	index->block_pos = block;
	index->page_pos = page;
	index->byte_pos = byte;
	index->full_page_size = (uint16_t)NAND_PAGE_SIZ_DATA_SPARE;
	index->data_page_size = (uint16_t)NAND_PAGE_SIZ_DATA;
	index->page_count = (uint32_t)NAND_BLOCK_SIZ_PAGES;
	
	if(_access_mode == Nand_data_mode){
		if(index->byte_pos >= NAND_PAGE_SIZ_DATA) index->byte_pos = 0;
	}
}


/**
* memchip_increase_index        uses READ PAGE command (Affects memory chip cache)
* memchip_increase_index_dummy  doesn't use READ PAGE command
*
* brief Increase a nand index by a byte value
* param byte count value
* param index pointer 
* param  
* retval
*/
static void memchip_increase_index(uint16_t value, nand_index *index, eNandAccessMode _access_mode){
	increase_index(value, index, _access_mode, MEMCHIP_NORML_OP);
}
static void memchip_increase_index_dummy(uint16_t value, nand_index *index, eNandAccessMode _access_mode){
	increase_index(value, index, _access_mode, MEMCHIP_DUMMY_OP);
}

/**
* brief  Find a first good block within a range
* param  block_begin
* param  block_end
* param  index ptr 
* retval block num
*/
uint16_t memchip_find_good_block(uint16_t block_begin, uint16_t length){
	for(uint16_t i = block_begin; i <=  (block_begin + length); i++){
		if(memchip_check_bad_block(i) == OPERATION_OK) {
			return i;
		}
	}
	return 0;
}


/********************************************************************************************/
/********************************      Read  functions     **********************************/
/********************************************************************************************/
/**
* brief  Read a page into cache PAGE READ (13h)
* param  Block number
* param  Page number
* param  
* retval result
*/


static void memchip_read_page(uint16_t block, uint16_t page){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	nand_24bit_address addr24bit = make_24bit_address(block, page);

	memchip_SPI_transmit_byte(NAND_CMD_PAGE_READ);
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_0(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_1(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_2(addr24bit)); // dummy

	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	status_timeout_nor(NAND_CMD_FEATURE_STATUS, NAND_CMD_FEATURE_STATUS_OIP, NAND_READ_PAGE_TIMEOUT);
}

/**
* brief  Read out a cached page READ FROM CACHE 03h
* param  Byte position (address)
* param  output buffer
* param  Wrap settings
* param  Size
* retval result
*/

static void memchip_read_from_cache(uint16_t byte_pos, uint8_t* output, uint16_t wrap_msk, uint16_t size){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);

	nand_12bit_address addr12bit = make_12bit_address(byte_pos, wrap_msk);

	memchip_SPI_transmit_byte(NAND_CMD_READ_FROM_CACHE);
	memchip_SPI_transmit_byte(NAND_12_BIT_BYTE_0(addr12bit));
	memchip_SPI_transmit_byte(NAND_12_BIT_BYTE_1(addr12bit));
	memchip_SPI_transmit_byte(NAND_CMD_DUMMY_BYTE);
	
	memchip_SPI_receive_data(output, size);
	
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
}

/** "Make index" required before usage
* brief Read data from the memchip
* param (uint8_t)output buffer
* param length
* param max chunk size
* param index pointer
* param
* retval
*/
static uint32_t memchip_read_from_nand(uint8_t *output, uint16_t length, uint16_t max_chunk, nand_index *index, eNandAccessMode _access_mode){
	if(length > max_chunk) return OPERATION_FAIL;
	// page size - is 2048 (data only) or 2112 (data + spare) MX35LF1GE4AB
	const uint16_t page_size = (_access_mode == Nand_data_mode) ? index->data_page_size : index->full_page_size;
	// wrap mask for page size
	const uint16_t wrap_msk  = (_access_mode == Nand_data_mode) ? NAND_CMD_READ_WRAP_DATAPAGE_MSK : NAND_CMD_READ_WRAP_FULLPAGE_MSK;
	
	
	uint16_t buf_pos = 0;
	uint16_t bytes_to_send_total = length; 
	uint16_t bytes_to_send_in_current_page = 0;
	
	memchip_read_page(index->block_pos, index->page_pos);
	
	while(bytes_to_send_total > 0){
		uint16_t bytes_in_line_after_pos = (uint16_t)(page_size - index->byte_pos); // How many bytes from the byte position to the end of the page
		
		if(bytes_to_send_total > bytes_in_line_after_pos) bytes_to_send_in_current_page = bytes_in_line_after_pos;
		else bytes_to_send_in_current_page = bytes_to_send_total;
		
		// Data is read by chunks
		if(bytes_to_send_in_current_page == max_chunk){
			memchip_read_from_cache(index->byte_pos, &output[buf_pos], wrap_msk, max_chunk);
			buf_pos = (uint16_t)(buf_pos + max_chunk);
			memchip_increase_index(max_chunk, index, _access_mode);
			bytes_to_send_total = (uint16_t)(bytes_to_send_total - max_chunk);
		}
		if(bytes_to_send_in_current_page < max_chunk){
			memchip_read_from_cache(index->byte_pos, &output[buf_pos], wrap_msk, bytes_to_send_in_current_page);
			buf_pos = (uint16_t)(buf_pos + bytes_to_send_in_current_page);
			memchip_increase_index(bytes_to_send_in_current_page, index, _access_mode);
			bytes_to_send_total = (uint16_t)(bytes_to_send_total - bytes_to_send_in_current_page);
		}
	}
	return OPERATION_OK;
}


/********************************************************************************************/
/********************************      Write functions     **********************************/
/********************************************************************************************/

/**
* brief  Disable write and wait, until WEL is set
* param  
* param 
* param  
* retval OK / Fail
*/
static uint32_t memchip_write_disable(void){
	volatile uint32_t result = OPERATION_FAIL;
	
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	
	memchip_SPI_transmit_byte(NAND_CMD_WRITE_DISABLE);
	
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	
	result = status_timeout_nor(NAND_CMD_FEATURE_STATUS, NAND_CMD_FEATURE_STATUS_WEL, NAND_WEL_SET_TIMEOUT);
	return result;
}
/**
* brief  Enable write and wait, until WEL is set
* param  
* param 
* param  
* retval OK / Fail
*/
static uint32_t memchip_write_enable(void){
	volatile uint32_t result = OPERATION_FAIL;
	result = disable_w_protection();
	if(result == OPERATION_FAIL) return result;
	
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	
	memchip_SPI_transmit_byte(NAND_CMD_WRITE_ENABLE);
	
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	
	result = status_timeout_and(NAND_CMD_FEATURE_STATUS, NAND_CMD_FEATURE_STATUS_WEL, NAND_WEL_SET_TIMEOUT);
	
	return result;
}


/** "Make index" required before usage
* brief PROGRAMM EXECUTE 10h
* param index pointer
* param
* retval OK/Fail
*/
uint32_t memchip_programm_execute(nand_index *index){
	volatile uint32_t result = OPERATION_FAIL;
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
		
	nand_24bit_address addr24bit = make_24bit_address(index->block_pos, index->page_pos);
		
	memchip_SPI_transmit_byte(NAND_CMD_PROGRAM_EXECUTE);
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_0(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_1(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_2(addr24bit)); // dummy
		
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
		
	_timeout(NAND_PROG_PAGE_TIMEOUT);
		
	result =  status_timeout_nor(NAND_CMD_FEATURE_STATUS, NAND_CMD_FEATURE_STATUS_OIP, NAND_PROG_PAGE_TIMEOUT);
	return result;
}

/** "Make index" required before usage
* brief PROGRAMM LOAD 02h
* param index pointer
* param data ptr
* param length
* retval 
*/

void memchip_programm_load(nand_index *index, uint8_t *data, uint16_t length, uint16_t wrap_msk){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
			
	nand_12bit_address addr12bit = make_12bit_address(index->byte_pos, wrap_msk);

	memchip_SPI_transmit_byte(NAND_CMD_PROGRAM_LOAD_RND_DAT);
	memchip_SPI_transmit_byte(NAND_12_BIT_BYTE_0(addr12bit));
	memchip_SPI_transmit_byte(NAND_12_BIT_BYTE_1(addr12bit));

	memchip_SPI_transmit_data(data, length);
		
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
}

/** "Make index" required before usage
* brief Write data into the memchip
* param (uint8_t)data buffer
* param length
* param access mode (data area or data+spare)
* param index pointer
* param
* retval
*/

static uint8_t validation_buffer[VALIDATED_MAX_SIZE];
static nand_index validate_index;
	
static uint32_t validate_programmed_data(uint8_t *initial_data, uint16_t size, nand_index *index, eNandAccessMode _access_mode){
	validate_index = *index;
	uint16_t validated_data_cnt = 0;
	while(validated_data_cnt != size){
		uint16_t bytes_to_validate = (size > VALIDATED_MAX_SIZE) ? VALIDATED_MAX_SIZE : size;
		memchip_read_from_nand(validation_buffer, bytes_to_validate, VALIDATED_MAX_SIZE, &validate_index, _access_mode);
		for(uint16_t i = 0; i < bytes_to_validate; i++){
			if(validation_buffer[i] != initial_data[i]) return OPERATION_FAIL;
		}
		validated_data_cnt = (uint16_t)(validated_data_cnt + bytes_to_validate);
	}
	return OPERATION_OK;
}


uint32_t memchip_write_data(nand_index *index, uint8_t *data, uint16_t length, eNandAccessMode _access_mode, eWriteValidateMode _validate_mode){
	// "Make index" required before usage
	volatile uint32_t result = OPERATION_FAIL;
	const uint16_t page_size = (_access_mode == Nand_data_mode) ? index->data_page_size : index->full_page_size;
//	const uint16_t max_chunk = page_size;
	const uint16_t wrap_msk  = (_access_mode == Nand_data_mode) ? NAND_CMD_READ_WRAP_DATAPAGE_MSK : NAND_CMD_READ_WRAP_FULLPAGE_MSK;
	
	uint16_t buf_pos = 0;
	uint16_t bytes_to_send_total = length;
	uint16_t bytes_to_send_in_current_page = 0;
	
	while(bytes_to_send_total > 0){
                
		uint16_t bytes_in_line_after_pos = (uint16_t)(page_size - index->byte_pos);
		
		if(bytes_to_send_total > bytes_in_line_after_pos) bytes_to_send_in_current_page = bytes_in_line_after_pos;
		
		else bytes_to_send_in_current_page = bytes_to_send_total;
		/*************************** PROGRAMM LOAD 02h ***************************************/
		memchip_read_page(index->block_pos, index->page_pos);
		
		result =  memchip_write_enable();
		if(result == OPERATION_FAIL){
			memchip_write_disable();
			return result;
		}
		
		memchip_programm_load(index, &data[buf_pos], bytes_to_send_in_current_page, wrap_msk);
		
		/**************************** PROGRAMM EXECUTE 10h ***********************************/
		
		result = memchip_programm_execute(index);
		if(result == OPERATION_FAIL){
			memchip_write_disable();
			return result;
		}
		
		/********************************** Validation ***************************************/
		if(_validate_mode == Nand_validate_mode){
			result = validate_programmed_data(&data[buf_pos], bytes_to_send_in_current_page, index, _access_mode);
			if(result == OPERATION_FAIL){
				memchip_write_disable();
				return result;
			}
		}
		
		buf_pos = (uint16_t)(buf_pos + bytes_to_send_in_current_page);
		bytes_to_send_total = (uint16_t)(bytes_to_send_total - bytes_to_send_in_current_page);
		memchip_increase_index(bytes_to_send_in_current_page, index, _access_mode);
	} // while(bytes_to_send_total > 0)
	
	result =  memchip_write_disable();
	return result;
}

/**
* brief  Erase a block
* param 
* param  
* param  
* retval OK/Failed
*/

uint32_t memchip_erase_block(uint16_t block_num){
	uint32_t result = memchip_check_bad_block(block_num);
	if(result == OPERATION_FAIL) return result;
	
	result =  memchip_write_enable();
	if(result == OPERATION_FAIL){
		memchip_write_disable();
		return result;
	}
	
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	
	nand_24bit_address addr24bit = make_24bit_address(block_num, 0);
	
	memchip_SPI_transmit_byte(NAND_CMD_ERASE_BLOCK);
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_0(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_1(addr24bit));
	memchip_SPI_transmit_byte(NAND_24_BIT_BYTE_2(addr24bit)); // dummy
	
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	result =  status_timeout_nor(NAND_CMD_FEATURE_STATUS, NAND_CMD_FEATURE_STATUS_OIP, NAND_BLOCK_ERASE_TIMEOUT);
	if(result == OPERATION_FAIL) return result;
	
	result =  memchip_write_disable();
	return result;
}


/*
* brief  Erase all data within the address range
* param  start address
* param  end address
* param 
* retval 
*/
void memchip_erase_data_within_address(uint32_t start_address, uint32_t end_address){
	if(end_address <= start_address) return;
	
	const uint32_t programm_size = end_address - start_address;
	const uint16_t start_block = memchip_nand_addr_to_block(start_address);
	const uint16_t blocks_to_erase = memchip_blocks_within_range(start_address, programm_size);
	const uint16_t last_block = start_block + blocks_to_erase;
	
	for(uint16_t i = start_block; i <= last_block; i++){
		uint32_t result = memchip_erase_block(i);
		if(result == OPERATION_FAIL){
			return;
		}
	}
}


/********************************************************************************************/
/********************************         Features         **********************************/
/********************************************************************************************/
/**
* brief  Set a feature bit 
* param  address
* param  bit to set
* param  
* retval current feature value
*/
uint8_t memchip_nand_set_feature(uint8_t address, uint8_t bit){
	volatile uint8_t feature_value = memchip_nand_get_feature(address);
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	feature_value |= bit;
	memchip_SPI_transmit_byte(NAND_CMD_SET_FEATURE);
	memchip_SPI_transmit_byte(address);
	memchip_SPI_transmit_byte(feature_value);
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	feature_value = memchip_nand_get_feature(address);
	return feature_value;
}

/**
* brief  Reset a feature bit 
* param  address
* param  bit to reset
* param  
* retval current feature value
*/
uint8_t memchip_nand_reset_feature(uint8_t address, uint8_t bit){
	volatile uint8_t feature_value = memchip_nand_get_feature(address);
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	feature_value &= ~bit;
	memchip_SPI_transmit_byte(NAND_CMD_SET_FEATURE);
	memchip_SPI_transmit_byte(address);
	memchip_SPI_transmit_byte(feature_value);
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	feature_value = memchip_nand_get_feature(address);
	return feature_value;
}

/**
* brief  Read and return a feature
* param  
* param 
* param  
* retval feature
*/
uint8_t memchip_nand_get_feature(uint8_t address){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	memchip_SPI_transmit_byte(NAND_CMD_GET_FEATURE);
	memchip_SPI_transmit_byte(address);
	uint8_t byte0 = memchip_SPI_receive_byte();
	CS_RESET
	_timeout(SPI_CS_TIMEOUT);
	return byte0;
}


/********************************************************************************************/
/********************************   Service functions      **********************************/
/********************************************************************************************/

/**
* brief  Check a block for Bad Block markers
* param 
* param  
* param  
* retval OK/Failed
*/
uint32_t memchip_check_bad_block(uint16_t block_num){
	cache_nand_index = the_nand_index;
	uint8_t mark[2] = {0x00, 0x00};
	for(uint16_t i = NAND_BAD_BLOCK_PAGE_POS_1; i < (NAND_BAD_BLOCK_PAGE_POS_1 + 2); i++){  // page 1, page 2
		for(uint16_t k = 0; k < 2; k++){
			memchip_nand_make_start_index(block_num, i, (NAND_PAGE_SIZ_DATA + k), &the_nand_index, Nand_data_and_spare_mode);	// bytes 0 and 1
			memchip_read_from_nand(&mark[k], 1, 1, &the_nand_index, Nand_data_and_spare_mode);
		}
		if((mark[0] == 0x00) || (mark[1] == 0x00)){
			the_nand_index = cache_nand_index;
			return OPERATION_FAIL;
		}
	}
	the_nand_index = cache_nand_index;
	return OPERATION_OK;
}

/**
* brief  Calculate, how many blocks (to be erased) within an address area
* param  address
* param  length
* param  
* retval block num
*/
uint16_t memchip_blocks_within_range(uint32_t address, uint32_t length){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_mode);
	uint16_t start_block = the_nand_index.block_pos;
	
	memchip_increase_index_dummy(length, &the_nand_index, Nand_data_mode);
	uint16_t blocks_to_erase = the_nand_index.block_pos - start_block + 1;
	return blocks_to_erase;
}

uint16_t memchip_nand_addr_to_block(uint32_t address){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_mode);
	uint16_t start_block = the_nand_index.block_pos;
	return start_block;
}



//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_get_pending_length(void){
	return memory_chip_status.stream_pending_data;
}
uint32_t memchip_get_address(void){
	return memory_chip_status.stream_address;
}
void memchip_set_pending_data(uint32_t length){
	memory_chip_status.stream_pending_data = length;
}
void memchip_deduct_pending_data(uint32_t length){
	memory_chip_status.stream_address += length;
	memory_chip_status.stream_pending_data -= length;
}
void memchip_set_address(uint32_t address){
	memory_chip_status.stream_address = address;
}



//===============================================================================================================
//============================================ Application function =============================================
//===============================================================================================================

uint32_t memchip_write(uint32_t address, uint8_t *buf, uint32_t length){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_mode);
	uint32_t result = memchip_write_data(&the_nand_index, buf, length, Nand_data_mode, Nand_fast_mode);
	if(result == length) return OPERATION_OK;
	else return OPERATION_FAIL;
}

uint32_t memchip_rewrite(uint32_t address, uint8_t *buf, uint32_t length){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_mode);
	
	uint32_t result = memchip_check_bad_block(the_nand_index.block_pos);
	if(result == OPERATION_FAIL){
		return result;
	}
	result = memchip_erase_block(the_nand_index.block_pos);
	if(result == OPERATION_FAIL){
		return result;
	}
	result = memchip_write_data(&the_nand_index, buf, length, Nand_data_mode, Nand_fast_mode);
	return result;
}


uint32_t memchip_read(uint32_t address, uint8_t *output, uint32_t length){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_mode);
	uint32_t result = memchip_read_from_nand(output, length, MEMCHIP_DEFAULT_CHUNK_SIZE, &the_nand_index, Nand_data_mode);
	return result;
}

uint32_t memchip_read_spare(uint32_t address, uint8_t *output, uint32_t length){
	memchip_nand_make_index(address, &the_nand_index, Nand_data_and_spare_mode);
	uint32_t result = memchip_read_from_nand(output, length, MEMCHIP_DEFAULT_CHUNK_SIZE, &the_nand_index, Nand_data_and_spare_mode);
	return result;
}







//===============================================================================================================
//========================================== SPI periphery linking ==============================================
//===============================================================================================================
/**
* brief  standardization function for SPI
* param 
* param  
* param  
* retval OK/Failed
*/
static uint8_t memchip_SPI_transmit_byte(uint8_t data){
	return SPI_transmit_byte(MEMCHIP_SPI, data);
}

static uint8_t memchip_SPI_receive_byte(void){
	return SPI_receive_byte(MEMCHIP_SPI);
}


static void memchip_SPI_transmit_receive_data(uint8_t *rx_data, uint8_t *tx_data, uint16_t size){
	SPI_transmit_receive_data(MEMCHIP_SPI, rx_data, tx_data, size);
}

static void memchip_SPI_receive_data(uint8_t *rx_data, uint16_t size){
	SPI_receive_data(MEMCHIP_SPI, rx_data, size);
}

void memchip_SPI_transmit_data(uint8_t *tx_data, uint16_t size){
	SPI_transmit_data(MEMCHIP_SPI, tx_data, size);
}




/**
* brief  Memchip reset
* param  
* param 
* param  
* retval 
*/
static void memchip_reset(void){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	memchip_SPI_transmit_byte(NAND_CMD_RESET_DEVICE);
	CS_RESET

}

/**
* brief  Read two bytes of NAND Flash memory chip ID
* param  
* param 
* param  
* retval Byte0 + Byte1
*/

static uint16_t memchip_nand_read_id(void){
	CS_SET
	_timeout(SPI_CS_TIMEOUT);
	uint8_t pos = 0;
	memchip_SPI_transmit_byte(NAND_CMD_READ_ID);
	memchip_SPI_transmit_byte(NAND_CMD_DUMMY_BYTE);
	uint8_t byte0 = memchip_SPI_receive_byte();
	uint8_t byte1 = memchip_SPI_receive_byte();
	
	uint16_t result = (uint16_t) (  (uint16_t)((byte0 << 8) & 0xFF00)  |  (uint16_t)((byte1 << 0) & 0x00FF) );
	CS_RESET
	return result;
}




#endif // MEMCHIP_NAND_FLASH
