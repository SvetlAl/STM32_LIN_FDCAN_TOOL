/****************************************************************
* Embedded light protocol
* Set of commands used for interface implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "el_protocol.h"
#include "main.h"
#include "string_convertor.h"

static uint8_t elp_cmd_buffer[ELP_MAX_STR_CMD_LENGTH]; /* A global var to store data before processing */
static uint32_t elp_cmd_buffer_index = 0;
elp_cmd global_el_command; /* A global var to store a current cmd readings */

elp_cmd *el_get_current_cmd(){
	return &global_el_command;
}

/**
* brief Reset command status, set cmd as ELP_CMD_IDLE (0x00000000)
* param  
* param 	
* retval  
*/

uint32_t el_reset_state(){
	elp_cmd_buffer_index = 0;
	memset((void *)&global_el_command, 0x00, sizeof(elp_cmd));
	return ELP_OK;
}
/**
* brief   Pick a command from    @elp_cmd_buffer
* param   address (the first and the last bytes of a command string in @elp_cmd_buffer)
* param 	
* retval  Puts a cmd into @command, and returns OK or ERROR
*/

uint32_t pick_cmd(elp_cmd_BufferAddress addr){
	if((addr.lastByte - addr.firstByte) < (ELP_CMD_STRING_LENGTH -1)){
		global_el_command.cmd = ELP_CMD_ERROR;
		return ELP_ERROR;
	}
	else{
		for(uint32_t i = addr.firstByte; i < (uint32_t)(addr.firstByte + ELP_CMD_STRING_LENGTH); i++){
			/***********  if a predicted string contains @ or # special symbols, cmd is error *****/
			if((elp_cmd_buffer[i] == ELP_SPECIAL_SYMBOL_PARAM_DIVIDER) | (elp_cmd_buffer[i] == ELP_SPECIAL_SYMBOL_DIVIDER)){
				global_el_command.cmd = ELP_CMD_ERROR;
				return ELP_ERROR;
			}
		}
		uint32_t temp = str_to_uint32(&elp_cmd_buffer[addr.firstByte]);
		global_el_command.cmd = temp;
		return ELP_OK;
	}
}

/**
* brief   Run through the recieved data in @elp_cmd_buffer and pick all the parameters
* brief		like @params, @param_counter and @string
* param   
* param 	address (the first and the last bytes of a command string in @elp_cmd_buffer)
* retval  Fill the @command with data, and returns OK or ERROR
*/

uint32_t elp_parse_cmd(elp_cmd_BufferAddress addr){
	/****** pick a command *********/
	uint32_t p_cmd = pick_cmd(addr);	
	if(p_cmd == ELP_ERROR){		
		return ELP_ERROR;
	}
	
	/********* handle the rest of data, after CMD ********/
	for(uint32_t i = (uint32_t)(addr.firstByte + ELP_CMD_STRING_LENGTH); i <= addr.lastByte; i++){
		/********* found something after '#' *********/
		if(elp_cmd_buffer[i-2] == ELP_SPECIAL_SYMBOL_PARAM_DIVIDER /* # */){
								
			if(global_el_command.param_counter >= ELP_MAX_CMD_PARAMS){
				global_el_command.cmd = ELP_CMD_ERROR;
				return ELP_ERROR;
			}
			else {				
				global_el_command.param[global_el_command.param_counter] = str_to_uint8(elp_cmd_buffer[i], elp_cmd_buffer[i-1]);
				global_el_command.param_counter++;				
			} 
		}

		/*********** found a string start @!, make sure the size format is XX (two ascii) ***********/
		else if(elp_cmd_buffer[i] == ELP_SPECIAL_SYMBOL_DIVIDER_START_STRING /* ! */){
			/***** make sure the size format is XX (two ascii) and preceding 4 bytes match @?XX  ******/
			uint32_t test_mask = 0;
			test_mask |= (ELP_SPECIAL_SYMBOL_DIVIDER /* @ */ << 24); 
			test_mask |= (ELP_SPECIAL_SYMBOL_DIVIDER_STRING_SIZE /* ? */ << 16); 
			/* test_mask @?00X*/
			
			uint32_t tmp = (uint32_t )((elp_cmd_buffer[i - (ELP_CMD_STRING_CMD_SIZ /* 4 */ + 1)]) << 24);
			tmp |= (uint32_t )((elp_cmd_buffer[i - (ELP_CMD_STRING_CMD_SIZ /* 4 */)]) << 16);
			tmp |= (uint32_t )((elp_cmd_buffer[i - (ELP_CMD_STRING_CMD_SIZ - 1  /* 4 */)]) << 8);
			tmp |= (uint32_t )((elp_cmd_buffer[i - (ELP_CMD_STRING_CMD_SIZ - 2/* 4 */)]) << 0);
		
		if((test_mask & tmp) != test_mask){
			global_el_command.cmd = ELP_CMD_ERROR;
			return ELP_ERROR;
		}
			uint8_t temp = str_to_uint8(elp_cmd_buffer[i-(ELP_CMD_STRING_CMD_SIZ-2)], elp_cmd_buffer[i-(ELP_CMD_STRING_CMD_SIZ-1)]);	
			global_el_command.string_siz = temp;
			
			/***** make sure the rest of the data is the same as 'string size'   ******/
			if((addr.lastByte - i) != global_el_command.string_siz){
				global_el_command.cmd = ELP_CMD_ERROR;
				return ELP_ERROR;
			}
			uint32_t start_string_byte = 0;
				
			for(uint32_t j = i+1; j <= (global_el_command.string_siz + i); j++){
				global_el_command.string_buffer.raw_data8[start_string_byte++] = elp_cmd_buffer[j];
			}
				break; /* exit cycle */
	
		}/****** @! *****/	
	}
	return ELP_OK;	
}

/**
* brief  Check, if a command has been recieved
* brief  If a recieved string contains symbols @S and @E and something in between these symbols
* param   
* param 
* retval Index of the first and the last bytes of stored command
*/

static elp_cmd_BufferAddress findElpCmd(){
	elp_cmd_BufferAddress cmdIndex;
	cmdIndex.firstByte = 0xFF;
	cmdIndex.lastByte = 0x00;
	
	for(uint8_t i = 0; i <= elp_cmd_buffer_index; i++){
		
		if(elp_cmd_buffer[i-1] == ELP_SPECIAL_SYMBOL_DIVIDER){
						
			if(elp_cmd_buffer[i] == ELP_SPECIAL_SYMBOL_DIVIDER_START){
				cmdIndex.firstByte = (uint8_t)(i+1);
			}
			
				/***** The last byte came ****/
			else if(elp_cmd_buffer[i] == ELP_SPECIAL_SYMBOL_DIVIDER_END){
				cmdIndex.lastByte = (uint8_t)(i-2);
			}				
		}
	}
	return cmdIndex;
}

/**
* brief  Write data into the cmd buffer and check, if a command has been recieved
* param  data
* param  length
* retval 
*/

uint32_t fill_elp_buffer(uint8_t *data, uint16_t length){
	if(elp_cmd_buffer_index == (ELP_MAX_STR_CMD_LENGTH - 1)){
		el_reset_state();
	}
	else{
		uint32_t predicted_index = elp_cmd_buffer_index + length;
		if(predicted_index >= ELP_MAX_STR_CMD_LENGTH){
			length = (uint16_t)(length - (predicted_index - ELP_MAX_STR_CMD_LENGTH));
		}
	}
	for(uint8_t i = 0; i < length; i++){
		elp_cmd_buffer[elp_cmd_buffer_index] = *data;
		data++;
		elp_cmd_buffer_index++;		
	}
	return ELP_OK;
}

/**
* brief  After some data is recieved look up through the buffer and try to find a command.
* brief  If found, process.
* param  
* param  
* retval 
*/

uint32_t find_and_parse_elp_cmd(){
	/*  Check, if a full string with both START and END symbols is recieved  */
	elp_cmd_BufferAddress cmdIndex = findElpCmd();
	
	/********** Amount of recieved bytes is enough to have a cmd  ********/
	if((cmdIndex.lastByte > cmdIndex.firstByte)){
		uint32_t pars = elp_parse_cmd(cmdIndex);	
		if(pars == ELP_ERROR){
			// el_reset_state();				
			return ELP_IDLE;
		}
	/********************************************************************/		
		return ELP_OK;
	}
	
		/***** buffer overflow check ******/	
	if(elp_cmd_buffer_index >= ELP_MAX_STR_CMD_LENGTH){
		el_reset_state();	
		return ELP_ERROR;	
	}
	
	else{ 		
		return ELP_IDLE;
	}
}


void elp_quadro_copy(el_quadro_buffer *qbuf_in, el_quadro_buffer *qbuf_out){
	for(uint32_t i = 0; i < ELP_QUADRO_BUF_SIZE/4; i++){
		qbuf_out->raw_data32[i] = qbuf_in->raw_data32[i];
	}
}
