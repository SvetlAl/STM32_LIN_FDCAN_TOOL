#ifndef FLASH_NOR_MEM_CHIP_H_INCLUDED
#define FLASH_NOR_MEM_CHIP_H_INCLUDED

/****************************************************************
* 
* NAND memory chip library
*
* Alex Svetlichnyy 2024 svetlal@outlook.com
*
* 
*
*
*****************************************************************/
#include "device_model.h"

#ifdef MEMCHIP_NAND_FLASH
#include "SPI/spi.h"

#ifdef MEMCHIP_MX35LF1GE4A
#include "Mem_chip/Presets/MX35LF1GE4A.h" 
#endif

/******************************************************************
*							                Settings
******************************************************************/
#define VALIDATED_MAX_SIZE			    0x40    /* Max chunk size that can be written along with validation */
#define MEMCHIP_DEFAULT_CHUNK_SIZE  0x100

#define MEMCHIP_DUMMY_OP						0x00
#define MEMCHIP_NORML_OP						0xFF

/******************************************************************
                            MemChip status
******************************************************************/
typedef struct {
	uint32_t stream_address;							
	uint32_t stream_pending_data;		
	uint32_t memchip_state;											/* How many bytes are pending to read/write. If state==0, a chip is ready */
} memchip_status;


/******************************************************************
                            Memchip index
******************************************************************/

typedef struct nand_index{
	uint16_t block_pos;
	uint16_t page_pos;
	uint16_t byte_pos;
	uint16_t full_page_size;
	uint16_t data_page_size;
	uint16_t page_count;
}nand_index;

/******************************************************************
                            Memchip modes
******************************************************************/
typedef enum{
	Nand_data_mode           = (uint8_t)0,
	Nand_data_and_spare_mode = (uint8_t)1
} eNandAccessMode;

typedef enum{
	Nand_fast_mode           = (uint8_t)0,
	Nand_validate_mode       = (uint8_t)1
} eWriteValidateMode;


//============================================================================================
//====================================     Read function    ==================================
uint32_t memchip_read(uint32_t address, uint8_t *output, uint32_t length);
uint32_t memchip_read_spare(uint32_t address, uint8_t *output, uint32_t length);

//============================================================================================
//====================================    Write function    ==================================
uint32_t memchip_write(uint32_t address, uint8_t *buf, uint32_t length);
uint32_t memchip_rewrite(uint32_t address, uint8_t *buf, uint32_t length);


uint32_t memchip_erase_block_within_address(uint32_t address);
uint32_t memchip_erase_block(uint16_t block_num);

uint32_t memchip_check_bad_block(uint16_t block_num);
uint16_t memchip_find_good_block(uint16_t block_begin, uint16_t length);
uint32_t erase_chip_memchip(void);

//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_get_address(void);
uint32_t memchip_get_pending_length(void);
void memchip_set_pending_data(uint32_t length);
void memchip_set_address(uint32_t address);
void memchip_deduct_pending_data(uint32_t length);

uint16_t memchip_blocks_within_range(uint32_t address, uint32_t length);
uint16_t memchip_nand_addr_to_block(uint32_t address);

void memchip_erase_data_within_address(uint32_t start_address, uint32_t end_address);



/*
uint8_t memchip_nand_get_feature(uint8_t address);
uint8_t memchip_nand_set_feature(uint8_t address, uint8_t bit);
uint8_t memchip_nand_reset_feature(uint8_t address, uint8_t bit);
void memchip_reset(void);
uint16_t memchip_nand_read_id(void);
*/

#endif // MEMCHIP_NAND_FLASH 

#endif /* FLASH_NOR_MEM_CHIP_H_INCLUDED*/
