/****************************************************************
* 
* User interface command parser
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "Commands/user_cmd.h"
#include "main.h"
#ifdef NAND_FLASH_DEBUG
#include "Commands/test_cmd_nand.h"
#endif // NAND_FLASH_DEBUG
	

/*****************************************************************/
/*****************************************************************/
/**************   The protocol command processing ****************/
/*****************************************************************/
/*****************************************************************/


/**
* brief  After user interface command processed, send a response
* param  param
* param  
* param  
* retval 
*/

void protocol_response(uint32_t param){
	static uint8_t ok___response[4] = {'$','O','K','$'};
	static uint8_t erro_response[4] = {'$','E','R','$'};
	static uint8_t busy_response[4] = {'$','B','S','$'};
	static uint8_t idle_response[4] = {'$','D','L','$'};
	
	switch(param){
		case ELP_OK:
			USB_CDC_send_data(ok___response, 4); break;
		case ELP_ERROR:
			USB_CDC_send_data(erro_response, 4); break;
		case ELP_BUSY:
			USB_CDC_send_data(busy_response, 4); break;
		default:
			USB_CDC_send_data(idle_response, 4); break;	
	}
}




/**
* brief  Process user interface command
* param  command
* param  
* param  
* retval 
*/

void process_protocol_cmd(elp_cmd *com){
	uint32_t response = ELP_OK;
	if(com->cmd <= ELP_MEMCHIP_BASE_RANGE_END){
		cmd_memchip_base_process(com);
	}
	else if(com->cmd <=  ELP_SPECIFIC_RANGE_END){
		cmd_specific_process(com);
	}
	
	#ifdef SUPPORT_LIN
	else if(com->cmd <=  ELP_LIN_RANGE_END){
		process_lin_cmd(com);
	}
	#endif // SUPPORT_LIN
	
	#ifdef SUPPORT_FDCAN
	else if((com->cmd & ELP_FDCAN_MSK) == ELP_FDCAN_MSK){
		process_fdcan_cmd(com);
	}
	#endif // SUPPORT_FDCAN
	
	#ifdef NAND_FLASH_DEBUG
	else if((com->cmd & ELP_TEST_NAND_MSK) == ELP_TEST_NAND_MSK){
		process_test_cmd_nand(com);
	}
	#endif // NAND_FLASH_DEBUG
		
	else if((com->cmd & ELP_RAW_DATA_MSK) == ELP_RAW_DATA_MSK){
		process_raw_cmd(com);
	}
	
	else{
		switch(com->cmd){
			default:
				response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
		}
	}
}

















		//========================================================================================================
		//================================================ DEBUG =================================================
		//========================================================================================================
	/*	
	#if defined(DEBUG_MODE) && defined(SUPPORT_USART)
		case(ELP_CMD_SEND_W_USART):{							// @SD0000000#02@?04@!Test@E --> Send 4 bytes of "Test" through USART2  
			uint8_t usart_num[2];
			usart_num[0] = SC_4BIT_TO_ASCII(((com->param[0] << 8) &~0xFF00));
			usart_num[1] = SC_4BIT_TO_ASCII(((com->param[0] << 0) &~0xFF00));
			uint8_t data_to_send[64];
			uint8_t pos = 0;
			data_to_send[pos++] = 'U';
			data_to_send[pos++] = 'S';
			data_to_send[pos++] = 'A';
			data_to_send[pos++] = 'R';
			data_to_send[pos++] = 'T';
			data_to_send[pos++] = usart_num[0];
			data_to_send[pos++] = usart_num[1];
			data_to_send[pos++] = 'T';
			data_to_send[pos++] = 'X';
			data_to_send[pos++] = ' ';
			uint32_t com_pos = 0;
			while((pos < 64) && (com_pos < com->string_siz)){
				data_to_send[pos++] = com->string_buffer.raw_data8[com_pos++];
			}
			usart_send_byte_array(com->param[0], data_to_send, pos);
			
			el_reset_state();
			break;
		}
		#endif
			
		case(ELP_TEST):{	
		uint8_t test_string[MAX_CDC_EP1_TX_SIZ] = {0xCE};
		USB_CDC_send_data(test_string, MAX_CDC_EP1_TX_SIZ);
		el_reset_state();
		break;
	}
		*/	

