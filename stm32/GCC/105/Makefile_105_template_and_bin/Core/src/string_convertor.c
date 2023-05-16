/****************************************************************
* 
* Some functions to work with the strings, arrays and calculations
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "string_convertor.h"
	
/**
* brief  Translate a single hex (0-F) into an ascii symbol
* param  0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
* param 
* retval   'A'  'B'  'C'  'D'  'E'  'F'
*/

uint8_t halfbyte_to_hexascii(uint8_t _halfbyte){
	uint8_t _ascii;
	_halfbyte &= 0x0F;
	if(_halfbyte >= 10){
		_ascii = (uint8_t)('A' + _halfbyte -10);
	} 
	else{ 
		_ascii = (uint8_t)('0' + _halfbyte);
	}
	return _ascii;	
}

/**
* brief  Translate an ascii symbol into a hex (0-F)
* param    'A'  'B'  'C'  'D'  'E'  'F' 
* param 
* retval 0x0A 0x0B 0x0C 0x0D 0x0E 0x0F
*/

// Translate an ascii symbol into a hex (0-F)
uint8_t hexascii_to_halfbyte(uint8_t _ascii){
	uint8_t _halfbyte;
	if((_ascii >= '0') && (_ascii <= '9')){
	_halfbyte= (uint8_t)(_ascii - '0');}
	else if((_ascii >= 'a') && (_ascii <= 'f')){
//	_halfbyte=(_ascii - 'a');}
	_halfbyte = (uint8_t)(_ascii - 87);}
	else if((_ascii >= 'A') && (_ascii <= 'F')){
//	_halfbyte=(_ascii - 'A');}
	_halfbyte = (uint8_t)(_ascii - 55);}
	else{
		return(0xFF);
	}	
	return _halfbyte;
}

/**
* brief  Translate an ascii symbol string into a hex (0-F) array
* param   uint8_t array 'A'  'B'  'C'  'D'  'E'  'F' 
* param 	length
* retval  uint8_t array 0xAB 0xCD 0xEF 
*/

void str_to_ascii(uint8_t *data_in, uint8_t *data_out, uint16_t length){
	uint8_t cmd_byte = 0;
	
	uint32_t i = 0;
	for(uint32_t k = 0; k < length; k+=2){
		cmd_byte = hexascii_to_halfbyte(data_in[k+1]);
		data_out[i] = cmd_byte;	
		cmd_byte = hexascii_to_halfbyte(data_in[k]);				
		data_out[i] = (uint8_t)(data_out[i] | (uint8_t)((cmd_byte << 4) & ~0x0F));
		i++;
		} 	
}

/**
* brief  Translate an ascii symbol string into a hex (0-F) uint32
* param   uint8_t array 'A'  'B'  'C'  'D'  'E'  'F' 
* param 	
* retval  uint32_t 0xABCDEF
*/

uint32_t str_to_uint32(uint8_t *data_in){
	uint32_t ret_val = 0;	
	
	uint8_t shift_cnt =0;	
	uint8_t cmd_byte = 0;
	data_in+=7;

	for(uint32_t k = 0; k < 8; k++){
		cmd_byte = hexascii_to_halfbyte(*data_in--);
		ret_val |= (uint32_t)(cmd_byte << shift_cnt);
		shift_cnt = (uint8_t)(shift_cnt + 4);
		}
	return ret_val; 	
}


/**
* brief  Translate an ascii symbol string into a hex (0-F) 
* param   uint8_t 'A'  'F'
* param 	
* retval  uint8_t 0xAF
*/

uint8_t str_to_uint8(uint8_t lowbyte, uint8_t highbyte){
	uint8_t ret_val = hexascii_to_halfbyte(lowbyte) | ((uint8_t)(hexascii_to_halfbyte(highbyte) << 4));	
	return ret_val; 	
}

/**
* brief  Translate bytes array into a char string
* param uint8_t array {0x01 0x02 0x03 0x04 }
* param 	
* retval array {'0' '1' '0' '2' '0' '3' '0' '4'}
*/

void hexArray2asciiArray(uint8_t *in_buf, uint8_t *out_buf, uint32_t input_length){
	uint8_t i2 = 0;
	for(uint32_t i = 0; i < input_length; i++){
		out_buf[i2++] = halfbyte_to_hexascii((in_buf[i]>> 4));
		out_buf[i2++] = halfbyte_to_hexascii((in_buf[i]));		
	}	
}


