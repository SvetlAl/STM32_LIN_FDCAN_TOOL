/****************************************************************
* 
* "External memory chip" user command handler
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
* 
*****************************************************************/
#include "Commands/cmd_memchip_base.h"

#include "Commands/cmd_spi_memchip_read.h"

static inline void erase_memchip_area(elp_cmd *com){
	#ifdef MEMCHIP_NOR_FLASH
	uint32_t start_address = extract_address_from_cmd(com);
	uint32_t pos = 0;
	uint32_t length = extract_length_from_cmd(com);
	while(pos < length){
		memchip_erase_block_within_address(start_address);
		pos += MEMCHIP_CMD_SECTOR_SIZE;
		start_address += MEMCHIP_CMD_SECTOR_SIZE;
	}
	#endif
	#ifdef MEMCHIP_NAND_FLASH
	uint16_t start_block = (uint16_t) (com->param[0]) | (uint16_t) (com->param[1] << 8) | (uint16_t) (com->param[2] << 16);
	uint16_t end_block   = (uint16_t) (com->param[3]) | (uint16_t) (com->param[4] << 8) | (uint16_t) (com->param[5] << 16);
	if(start_block >= end_block) return;
	for(uint16_t i = start_block; i < end_block; i++){
		if(memchip_check_bad_block(i) == OPERATION_OK) memchip_erase_block(i);
	}
	#endif
}




void cmd_memchip_base_process(elp_cmd *com){
	uint32_t response = ELP_OK;
	switch(com->cmd){
		//***** Load a data from a certain address of size X bytes ********	
		case(ELP_CMD_SPI_MEMCHIP_READ32):
		case(ELP_CMD_SPI_MEMCHIP_READ):
			read_mem_data_and_usb_send(extract_length_from_cmd(com), extract_address_from_cmd(com));
			el_reset_state();
			break;
		
		//****************	ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR	**************
		case(ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR):
			protocol_response(erase_sector(com));
			el_reset_state();
			break;
		/****************	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP	****************/		
		case(ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP):
			response = memchip_write(extract_address_from_cmd(com), &com->string_buffer.raw_data8[0], (uint32_t)com->string_siz);
			protocol_response(response);
			el_reset_state();
			break;	
		
		/****************	ELP_CMD_SPI_MEMCHIP_ERASE_CHIP	****************/		
		case(ELP_CMD_SPI_MEMCHIP_ERASE_CHIP):
		/********************************************************/
		/* IMPORTANT! Full chip erase can take up to 30 seconds */
		/********************************************************/
		#ifdef MEMCHIP_NOR_FLASH
			protocol_response(erase_chip_memchip());
		#endif // MEMCHIP_NOR_FLASH
		#ifdef MEMCHIP_NAND_FLASH
			for(uint16_t i = VEHICLE_SETTINGS_BLOCK_ADDRESS; i < (BOOTLOADER_UPDATE_PROGRAMM_BLOCK_ADDR + NAND_APPLICATION_AREA); i++){
				if(memchip_check_bad_block(i) == OPERATION_OK) memchip_erase_block(i);
			}
		#endif // MEMCHIP_NAND_FLASH
			el_reset_state();
			break;	
		case(ELP_ERASE_AREA): {      //  @00000010#00#01#40#00#02#80@E -->  NOR: Erase data starting from address -0x000140 0x000280 bytes 
			erase_memchip_area(com);   //                                    NAND: from BLOCK 00#01#40 to 00#02#80
			protocol_response(ELP_OK);
			el_reset_state();
			break;
		}
		
		case(ELP_CMD_RESET):
			el_reset_state();
			protocol_response(response);
			break;
		
		case(ELP_CMD_ERROR):
			response = ELP_ERROR;
			protocol_response(response);
			el_reset_state();
			break;
				
		default:
			response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
	}
}






















#ifdef UNUSED_EXTRA
		#ifdef MEMCHIP_NOR_FLASH
		/****************	ELP_TEST_CMD_SPI_MX25_GET_RDCR	****************/		
		case(ELP_TEST_CMD_SPI_MX25_GET_RDCR):{	
			uint8_t result = memchip_read_rdcr_reg();
			USB_CDC_send_data(&result, 0x01);
			el_reset_state();
			break;}
		
		/****************	ELP_TEST_CMD_SPI_MX25_GET_RDSR	****************/		
		case(ELP_TEST_CMD_SPI_MX25_GET_RDSR):{
			uint8_t result = memchip_read_status_reg();
			USB_CDC_send_data(&result, 0x01);
			el_reset_state();
			break;}

		#endif // MEMCHIP_NOR_FLASH
#endif





