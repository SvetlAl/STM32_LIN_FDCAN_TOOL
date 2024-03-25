#ifndef FLASH_NOR_MEM_CHIP_H_INCLUDED
#define FLASH_NOR_MEM_CHIP_H_INCLUDED

/****************************************************************
* 
* NOR memory chip library
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
* 
* TODO add SPI3 DMA support
*
*****************************************************************/
#include "device_model.h"
#include "SPI/spi.h"

#ifdef MEMCHIP_NOR_FLASH

#ifdef MEMCHIP_MX25L323
#include "Mem_chip/Presets/MX25L323.h" 
#endif
#ifdef MEMCHIP_MX25L16 
#include "Mem_chip/Presets/MX25L16.h" 
#endif
#ifdef MEMCHIP_M45PE16
#include "Mem_chip/Presets/M45PE16.h" 
#endif

/******************************************************************
*							                Settings
******************************************************************/
#define VALIDATED_MAX_SIZE			    0x40    /* Max chunk size that can be written along with validation */

/******************************************************************
                            MemChip status
******************************************************************/
typedef struct {
	uint32_t stream_address;							
	uint32_t stream_pending_data;		
	uint32_t memchip_state;											/* How many bytes are pending to read/write. If state==0, a chip is ready */
} memchip_status;

/******************************************************************
                    MemChip command structure  
                      cmd + 3-bytes address 
******************************************************************/
typedef struct {
	uint8_t cmd_name;
	uint8_t address[3];
} memchip_cmd;

/******************************************************************
                    Memchip command union  
             to access as byte array or as a structure 
******************************************************************/
typedef union{
	memchip_cmd cmd;
	uint8_t raw_data[4];
} u_memchip_cmd_data;


//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_read(uint32_t address, uint8_t *output, uint32_t length);

//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_write(uint32_t address, uint8_t *buf, uint32_t length);
uint32_t memchip_rewrite(uint32_t address, uint8_t *buf, uint32_t length);
uint32_t memchip_erase_block_within_address(uint32_t address);
void memchip_erase_data_within_address(uint32_t start_address, uint32_t end_address);

uint32_t erase_chip_memchip(void);

//============================================================================================
//==================================== Application function ==================================
uint32_t memchip_get_address(void);
uint32_t memchip_get_pending_length(void);
void memchip_set_pending_data(uint32_t length);
void memchip_set_address(uint32_t address);
void memchip_deduct_pending_data(uint32_t length);





#endif // MEMCHIP_NOR_FLASH

#endif /* FLASH_NOR_MEM_CHIP_H_INCLUDED*/
