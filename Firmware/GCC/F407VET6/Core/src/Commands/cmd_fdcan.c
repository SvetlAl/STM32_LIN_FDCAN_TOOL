/****************************************************************
* 
* FD CAN user command handler
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
* 
*****************************************************************/
#include "Commands/cmd_fdcan.h"
#include "ram_updater.h"

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan.h"



static inline void start_upd_fdcan_settings_procedure(void){ /* @S00000BA2@E Start FD CAN settings update */
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FDCAN_SETTINGS_UPD);
	ram_upd_set_size(DEVICE_FDCAN_SETTINGS_LENGTH);
	
	protocol_response(ELP_OK);
	el_reset_state();
}

static inline uint32_t save_fdcan_settings(void){ 
	uint32_t result = OPERATION_FAIL;
	uint8_t *status = fdcan_get_settings_ptr();
	
	uint32_t _addr = memchip_make_app_address (memchipFdcanSettings);
	const uint32_t length = sizeof(u_fdcan_settings);
	
	result = memchip_rewrite(_addr, status, length);
	
	return result;
}




void process_fdcan_cmd(elp_cmd *com){
	uint32_t response = ELP_OK;
	switch(com->cmd){
		
		/****************	ELP_UPDATE_FDCAN_STNGS	****************/		
		case(ELP_UPDATE_FDCAN_STNGS):{				/* @S00000BA2@E ASCII Start FD CAN settings update */
			start_upd_fdcan_settings_procedure();
		break;}
		
		/****************	ELP_RESTART_FDCAN	****************/		
		case(ELP_RESTART_FDCAN):{				/* @S00000BA3@E Restart FD CAN  */
			restart_fd_can();
		break;}
		
		/****************	ELP_SAVE_FDCAN_STNGS	****************/		
		case(ELP_SAVE_FDCAN_STNGS):{				/* @S00000BA4@E Save FD CAN Settings */
			uint32_t result = save_fdcan_settings();
			if(result == OPERATION_FAIL) response = ELP_ERROR;
			else response = ELP_OK;
			
			protocol_response(response);
			el_reset_state();
		break;}
		
		default:
			response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
	}
}


#endif

