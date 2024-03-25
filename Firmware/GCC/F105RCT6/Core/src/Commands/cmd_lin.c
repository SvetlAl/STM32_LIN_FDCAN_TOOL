#include "Commands/cmd_lin.h"
#include "Commands/user_cmd.h"


#ifdef SUPPORT_LIN
#include "LIN/lin.h"

static inline void cmd_set_lin_period(uint32_t value){     /* @S00000C02#XX#YY@E   0xXXYY - is an uint16_t poll period */
	lin_select_poll_period((uint16_t) value);
	protocol_response(ELP_OK);
	el_reset_state();
}

void process_lin_cmd(elp_cmd *com){
	uint32_t response = ELP_OK;
	switch(com->cmd){
		case(ELP_LIN_POLL_PERIOD):{     /* @S00000C02#XX#YY@E   0xXXYY - is an uint16_t poll period */
			uint32_t value = str_to_uint32(&com->string_buffer.raw_data8[0]);	
			cmd_set_lin_period(value);
			break;
		}
		case(ELPR_LIN_GET_POLL_PERIOD):{ /* @S00000C07@E   */
			uint16_t pollp = lin_get_poll_period();
			uint8_t data_to_send[2];
			uint8_t pos = 0;
			data_to_send[pos++] = (uint8_t)((pollp >> 8) &~0xFF00);
			data_to_send[pos++] = (uint8_t)(pollp &~ 0xFF00);
			USB_CDC_send_data(data_to_send, 2);
			el_reset_state();
			break;
		}
		case(ELPR_LIN_GET_MOSI_FILTER):  /* @S00000C08@E   */
		case(ELPR_LIN_GET_MISO_FILTER):{ /* @S00000C09@E   */
			uint8_t *mosi_f = com->cmd == ELPR_LIN_GET_MOSI_FILTER ? lin_get_mosi_filter() : lin_get_miso_filter();
			uint8_t data_to_send[sizeof(lin_filter_raw)];
			uint8_t pos = 0;
			while(pos < sizeof(lin_filter_raw)){
				data_to_send[pos++] = *mosi_f++;
			}
			USB_CDC_send_data(data_to_send, sizeof(lin_filter_raw));
			el_reset_state();
			break;
		}		
		case(ELP_LIN_SET_FILTER):{ /* @S00000C0A#NN#01#02#03#04#05#06#07#08#09#0A#0B#0C@E  NN - if 0x00, MOSI,  else - MISO 01-0C the lin_filter_raw bytes */
			lin_set_user_filter(com->param);
			response = ELP_OK;
			protocol_response(response);
			el_reset_state();
			break;
		}
		default:
			response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
	}
}


#endif

