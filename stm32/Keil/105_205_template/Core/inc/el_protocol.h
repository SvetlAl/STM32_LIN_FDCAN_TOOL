/****************************************************************
* Embedded light protocol
* Set of commands used for interface implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*
* The command protocol for user interface implementation
* 
* How to use:
*
*
* @I. A command is send (via COM-port or any other periphery) form user side to a device
* 
*
*
* Command format:
* @S0000000A#01@?40@!1234567890123456789012345678901234567890123456789012345678901234@E
* |	|       |  |   |                                                                 |  
* @S - indicates the beginning of a command
*   0000000A 	- command itself 
*           #01 - parameter
*              @?40 - char string length 64 bytes (0x40)
*                  @! - char string start
*                    1234567890123456789012345678901234567890123456789012345678901234 - char string itself
*                                                                                     @E - indicates the end of a command
*
*
* @II. Microcontroller periphery fills   elp_cmd_buffer[ELP_MAX_STR_CMD_LENGTH]   with recieved data (function uint32_t fill_elp_buffer(uint8_t *data, uint16_t length))
* fill_elp_buffer(uint8_t *data, uint16_t length) inside its routine has overflow protection and checks if a previous command was parsed. (status ELP_IDLE) 
* fill_elp_buffer(uint8_t *data, uint16_t length) also returns a result (if recieved string contains a command) 
* The result is written into    uint32_t cmd_fll     var.
*
* @III. User application (RTOS or main cycle) checks   cmd_fll    var.
* it can show, if a recieved command is pending. If this is true, the application invokes   proccess_protocol_cmd   function to process a command.
*
* @IV proccess_protocol_cmd   function processes a command, and then resets command state
*
*****************************************************************/
#ifndef EL_PROTOCOL_H_INCLUDED
#define EL_PROTOCOL_H_INCLUDED

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


/* function return values */
#define ELP_OK 			1
#define ELP_IDLE 		2
#define ELP_BUSY		3
#define ELP_ERROR		0


#define ELP_QUADRO_BUF_SIZE									128	/* el_quadro_buffer structure size. bytes */
//#define ELP_MAX_STR_INPUT_LENGTH						64	/* TODO add anno */
#define ELP_MAX_STR_CMD_LENGTH							64 + 	ELP_QUADRO_BUF_SIZE/* Buffer size to store incoming data, that needs to be processed. MAX - 256 */
#define ELP_CMD_STRING_LENGTH								8		/* Command symbols count "FFFFFFFF" - 8 bytes */
#define ELP_CMD_START_CMD_LENGTH						2		/* @S */
#define ELP_CMD_END_CMD_LENGTH							2		/* @E */	
#define ELP_CMD_START_STRING_CMD_LENGTH			2		/* @! */
#define ELP_CMD_STRING_CMD_SIZ							4	  /* @?XX */

//#define ELP_CMD_RESET_CMD_STRING_LENGTH	/* 8+2+2=12 */	ELP_CMD_START_CMD_LENGTH + ELP_CMD_END_CMD_LENGTH + ELP_CMD_STRING_LENGTH
//#define ELP_CMD_COUNT /* 128 -8 - 2 - 2 - 2 - 4 - 64 -2 = 46 */(ELP_MAX_STR_CMD_LENGTH - ELP_CMD_STRING_LENGTH - ELP_CMD_START_CMD_LENGTH - ELP_CMD_END_CMD_LENGTH - ELP_CMD_START_STRING_CMD_LENGTH - ELP_CMD_STRING_CMD_SIZ - ELP_QUADRO_BUF_SIZE - 2 /*alignment */)
#define ELP_MAX_CMD_PARAMS 16 /* 110/2=55 */ /*(ELP_MAX_STR_CMD_LENGTH - ELP_CMD_STRING_LENGTH - ELP_CMD_START_CMD_LENGTH - ELP_CMD_END_CMD_LENGTH - ELP_CMD_START_STRING_CMD_LENGTH - ELP_CMD_STRING_CMD_SIZ)/2 */

/***************** Special symbols *****************/

/***************** Dividers symbols ****************/
#define ELP_SPECIAL_SYMBOL_DIVIDER '@'
#define ELP_SPECIAL_SYMBOL_PARAM_DIVIDER '#'
/***************** Dividers values *******************/
#define ELP_SPECIAL_SYMBOL_DIVIDER_START 'S'
#define ELP_SPECIAL_SYMBOL_DIVIDER_END 'E'

#define ELP_SPECIAL_SYMBOL_DIVIDER_START_STRING '!'
#define ELP_SPECIAL_SYMBOL_DIVIDER_STRING_SIZE '?'

/***************** Response values *******************/
//#define ELP_RESPONSE_OK_SYMBOL 'O'


/* An application reads a command string and converts it into a cmd structure */
/* quad_buffer allows treat a byte array as 32-bit array */
typedef union{
	uint32_t raw_data32[ELP_QUADRO_BUF_SIZE/4];
	uint8_t raw_data8[ELP_QUADRO_BUF_SIZE];
} el_quadro_buffer;


/*****************************************/
/************* Command structure *********/
/*****************************************/
typedef struct {
	uint32_t cmd;													/* actually command itself */
	uint32_t string_siz;									/* string length (if a command provides a char string) */
	el_quadro_buffer string_buffer;				/* char string itself. If data length is 4-byte divisible, an application can work faster */ 
	uint32_t param_counter;								/* how many parameters are in a command (if a command provides any parameters)  */
	uint8_t param[ELP_MAX_CMD_PARAMS];		/* parameters array (if a command provides any parameters) */
} elp_cmd;


/**** index of the first and the last bytes  of the cmd line ****/
typedef struct {
	uint8_t  firstByte;
	uint8_t  lastByte;                                                       
} elp_cmd_BufferAddress;


extern elp_cmd global_el_command; /* A global var to store a current cmd readings */

uint32_t fill_elp_buffer(uint8_t *data, uint16_t length);
uint32_t find_and_parse_elp_cmd(void);
uint32_t elp_parse_cmd(elp_cmd_BufferAddress addr);
uint32_t pick_cmd(elp_cmd_BufferAddress addr);
uint32_t el_reset_state(void);
elp_cmd *el_get_current_cmd(void);

void elp_quadro_copy(el_quadro_buffer *qbuf_in, el_quadro_buffer *qbuf_out);

#endif /* EL_PROTOCOL_H_INCLUDED*/
