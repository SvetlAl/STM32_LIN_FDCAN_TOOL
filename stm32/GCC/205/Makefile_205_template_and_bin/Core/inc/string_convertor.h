/****************************************************************
* 
* Some functions to work with the strings, arrays and calculations
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#ifndef STRING_CONVERTOR_H_INCLUDED
#define STRING_CONVERTOR_H_INCLUDED

#include "device_model.h"
#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif

#define SC_4BIT_TO_ASCII(x) (uint8_t) ((x >= 10) ? ('A' + x -10) : ('0' + x))

#define SC_BYTE_FROM32BIT(val32, x) (uint8_t)((uint32_t)val32 >> (24 - x*8)) 


uint8_t halfbyte_to_hexascii(uint8_t _halfbyte); // Translate a single hex (0-F) into an ascii symbol 
uint8_t hexascii_to_halfbyte(uint8_t _ascii);		 // Translate an ascii symbol into a hex (0-F)
void str_to_ascii(uint8_t *data_in, uint8_t *data_out, uint16_t length);
uint32_t str_to_uint32(uint8_t *data_in);
uint8_t str_to_uint8(uint8_t lowbyte, uint8_t highbyte);

void hexArray2asciiArray(uint8_t *in_buf, uint8_t *out_buf, uint32_t input_length);

#endif /* STRING_CONVERTOR_H_INCLUDED*/
