#include "Commands/common_cmd.h"
#include "Commands/user_cmd.h"

//=========================================================================================================
//========================================  Address handle ================================================
uint32_t extract_address_from_cmd(elp_cmd *com){
	uint32_t addr = 0x00;
	uint8_t pos = 0;
	uint8_t cnt = 0;
	
	if(com->cmd == ELP_CMD_SPI_MEMCHIP_READ32){
		pos = 3;
		cnt = 4;
	}
	else if(com->cmd == ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32){
		pos = 7;
		cnt = 4;
	}
	else{
		pos = 2;
		cnt = 3;
	}
	for(uint8_t i = 0; i < cnt; i++){
		addr |= (uint32_t)(com->param[pos] << (i*8)); 
		pos   = (uint8_t)(pos - 1);
	}
	return addr;
}

uint32_t extract_length_from_cmd(elp_cmd *com){
	uint32_t length = 0x00;
	if(com->cmd == ELP_CMD_SPI_MEMCHIP_READ32){
		length |= (uint32_t)(com->param[7] << 0); 
		length |= (uint32_t)(com->param[6] << 8); 
		length |= (uint32_t)(com->param[5] << 16); 
		length |= (uint32_t)(com->param[4] << 24); 
	}
	else{
		length |= com->param[5]; /* 01 */
		length |= (uint32_t)(com->param[4] << 8); /* 02 */
		length |= (uint32_t)(com->param[3] << 16); /* 02 */
	}
	return length;
}

//=========================================================================================================
//=============================================  Misc. ====================================================
uint16_t extract_2bytes_cmd(elp_cmd *com){
	uint16_t dbytes = 0x00;
	/*
	dbytes |= (uint16_t)(com->param[0] << 8);
	dbytes |= (uint16_t)(com->param[1] << 0);
	*/
	dbytes = (uint16_t)((uint16_t)(com->param[0] << 8) | ((uint8_t)com->param[1] & 0xFF));

	return dbytes;
}



uint32_t erase_sector(elp_cmd *com){
	#ifdef MEMCHIP_NOR_FLASH
	uint32_t addr = extract_address_from_cmd(com);
	uint32_t result = memchip_erase_block_within_address(addr);	
	return result;
	#endif
	#ifdef MEMCHIP_NAND_FLASH
	uint8_t addr_0 = com->param[1];
	uint8_t addr_1 = com->param[2];
	uint16_t address =  (uint16_t)((uint16_t)((addr_0 << 8) & 0xFF00 ) | (uint16_t)(addr_1 & 0x00FF));
	uint32_t result = memchip_erase_block(address);
	if(result == OPERATION_FAIL){
		return ELP_ERROR;
	}
	else if(result == OPERATION_OK){
		return ELP_OK;
	}
	return ELP_OK;
	#endif
}

uint32_t assert_cmd_length(uint16_t proper_length, elp_cmd *com){
	if(com->string_siz != proper_length) return ELP_ERROR;
	return ELP_OK;
}

void cmd_send_raw_data(uint8_t *start_addr, uint32_t total_length){
	uint8_t* vers = start_addr;
	uint32_t length = total_length;
	
	while((length >= CMD_CDC_TRANSACTION_SZ) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){		
		uint32_t send_status = USB_CDC_send_data(vers, CMD_CDC_TRANSACTION_SZ);	
		if(send_status == EP_FAILED) return;
		length-=CMD_CDC_TRANSACTION_SZ;
		vers+=CMD_CDC_TRANSACTION_SZ;
	}
	if((length > 0) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){
		USB_CDC_send_data(vers, (uint16_t)length);
	}
	el_reset_state();
}

