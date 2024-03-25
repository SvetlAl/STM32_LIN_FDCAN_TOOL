/****************************************************************
* 
* "Raw data" user command handler
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
* 
*****************************************************************/
#include "Commands/cmd_raw.h"
#include "ram_updater.h"

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan.h"
#endif


static inline void read_vehicleStatus_and_usb_send_HEX(){
	uint8_t *status = get_vehicle_settings_data();
	USB_CDC_send_data(status, VEHICLE_STATUS_SETTINGS_LENGTH);
}

#ifdef SUPPORT_FDCAN
static inline void start_fdcan_single_msg_injection(uint8_t can, uint16_t siz){ /* @S00000AB2#SI#ZE@E start recieving SIZE bytes of data and use this to make and transmit an fdcan message */
	uint16_t lock_sts = fdcan_buf_w_lock(&fdcan_bufs_tx.buf[can]);
	if(lock_sts == FDCAN_BUFFER_STS_FAIL){
		protocol_response(ELP_BUSY);
		el_reset_state();
		return;
	}
	
	if(can == FDCAN1_E){
		SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_1);
	}
	else if(can == FDCAN2_E){
		SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FDCAN_SINGLE_MSG_INJ_2);
	}
	else{
		protocol_response(ELP_ERROR);
		el_reset_state();
	}

	ram_upd_set_size(siz);
	FDCAN_TX_BUF_PTR(can)->tmp_write_pos = 0;
	
	protocol_response(ELP_OK);
	el_reset_state();
}
#endif


static inline void start_hex_programm_procedure(elp_cmd *com){ 
	
	uint32_t programm_size = 0x00;	
	
	if(com->cmd == ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP){ /* @SF0000008#00#01#02#12#23#45@E Start programming procedure at addr 0x000102 with 0x122345 bytes */
		programm_size |= com->param[5]; /* 01 80*/
		programm_size |= (uint32_t)(com->param[4] << 8); /* 02 00*/
		programm_size |= (uint32_t)(com->param[3] << 16); /* 03 00*/
	}
	else if(com->cmd == ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32){ // @SF0000008 #00 #00 #01 #02 #12 #00 #23 #45 #FF @E
		programm_size |= (uint32_t)(com->param[7] << 0); 
		programm_size |= (uint32_t)(com->param[6] << 8);
		programm_size |= (uint32_t)(com->param[5] << 16);
		programm_size |= (uint32_t)(com->param[4] << 24); 
	}
	
	if(programm_size == 0 ){
		protocol_response(ELP_IDLE);
		el_reset_state();
	}
	uint32_t address = extract_address_from_cmd(com);
	#ifdef MEMCHIP_NAND_FLASH 
	if(address >=  NAND_CHIP_VOLUME){
		protocol_response(ELP_ERROR);
		el_reset_state();
	}
	uint32_t empty_space = NAND_CHIP_VOLUME - address;
	
	#endif //MEMCHIP_NAND_FLASH 
	#ifdef MEMCHIP_NOR_FLASH 
	uint32_t sectors_address_step = MEMCHIP_CMD_SECTOR_SIZE;
	uint32_t sectors_count =  MEMCHIP_CMD_SECTOR_COUNT;
	
	uint32_t empty_space = (sectors_count*sectors_address_step) - address;
	#endif // MEMCHIP_NOR_FLASH		
	
	if(empty_space <  programm_size){
		protocol_response(ELP_ERROR);
		el_reset_state();
	}
	uint8_t rewrite_marker = 0x00;
	if(com->cmd == ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP){ 
		rewrite_marker = com->param[6];
	}
	else if(com->cmd == ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32){ 
		rewrite_marker = com->param[8];
	}
	
	#ifdef MEMCHIP_NOR_FLASH
	// FF - rewrite 00 append
	if(rewrite_marker != 0x00){	// 		FF - rewrite
		uint32_t residue = ((programm_size % sectors_address_step)==0) ? 0 : 1 ;
		uint32_t sectors_to_erase_count = programm_size / sectors_address_step + residue;
		
		for(uint32_t i = 0; i < sectors_to_erase_count; i++){
			memchip_erase_block_within_address((address + sectors_address_step*i));
		}
	}
	#endif // MEMCHIP_NOR_FLASH	

	#ifdef MEMCHIP_NAND_FLASH
	// FF - rewrite 00 append
	if(rewrite_marker != 0x00){	// 		FF - rewrite
		const uint16_t start_block = memchip_nand_addr_to_block(address);
		const uint16_t blocks_to_erase = memchip_blocks_within_range(address, programm_size);
		const uint16_t last_block = start_block + blocks_to_erase;
				
		for(uint16_t i = start_block; i <= last_block; i++){
			uint32_t result = memchip_erase_block(i);
			if(result == OPERATION_FAIL){
				protocol_response(ELP_ERROR);
				el_reset_state();
				return;
			}
		}
	}
	#endif // MEMCHIP_NAND_FLASH

	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_ON);
	memchip_set_pending_data(programm_size);
	memchip_set_address(address);
	
	protocol_response(ELP_OK);
	el_reset_state();

}

void process_raw_cmd(elp_cmd *com){
	uint32_t response = ELP_OK;
	switch(com->cmd){
		/**********	Quick send theVehicle data  NOT ASCII ***********/
		case(ELPR_VEHICLE_GET_CURRENT_STATUS):
			read_vehicleStatus_and_usb_send_HEX();
			el_reset_state();
			break;
		
		case(ELPR_OVR_FLTR_GET_CURRENT_STATUS):{				/* @SF0000BB1@E ASCII Get sizeof(can_override_status) of current override settings in raw data*/
			#if defined(SUPPORT_BXCAN)
			uint8_t* vers = can_override_get_dataptr();
			uint32_t length = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
			#endif
			#if defined(SUPPORT_FDCAN)
			uint8_t* vers = fdcan_get_filter_ptr();
			uint32_t length = sizeof(fdcan_filter);
			#endif // STM32H730
			
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
			break;}	
		
			
			#ifdef SUPPORT_BXCAN
			/****************	ELPR_OVR_FLTR_GET_FILTER_NUMS	****************/		
		case(ELPR_OVR_FLTR_GET_FILTER_NUMS):{				/* @SF0000BB2@E ASCII Get 4 bytes of current override settings in raw data*/
			uint8_t* vers = can_override_get_dataptr();
			USB_CDC_send_data(vers, 4);
			el_reset_state();
			break;}		
			#endif // SUPPORT_BXCAN
			
		case(ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32):
		case(ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP): /* @SF0000008#00#01#02#12#23#45#FF@E Start programming procedure at addr 0x000102 with 0x122345 bytes  FF - append or 00 rewrite */
			start_hex_programm_procedure(com);
			break;
			
		
			#ifdef SUPPORT_FDCAN
		/****************	ELPR_SEND_CUSTOM_FDCAN_MSG	****************/		
		case(ELPR_SEND_CUSTOM_FDCAN_MSG):{				/* @S00000AB2#SI#ZE#CN@E start recieving SIZE bytes of data and use this to make and transmit an fdcan message CN: 0 - CAN1, 1 - CAN2 */
			uint16_t siz = extract_2bytes_cmd(com);
			uint8_t can_n = (uint8_t)(com->param[2]);
			start_fdcan_single_msg_injection(can_n, siz);
		break;}

		
				/****************	ELPR_FDCAN_GET_SETTINGS	****************/		
		case(ELPR_FDCAN_GET_SETTINGS):{				/* @S00000AB1@E ASCII Send u_fdcan_settings in raw data from device to host */
			uint8_t *fdcan_stngs_addr = fdcan_get_settings_ptr();
			cmd_send_raw_data(fdcan_stngs_addr, DEVICE_FDCAN_SETTINGS_LENGTH);
			el_reset_state();
		break;}
		#endif // SUPPORT_FDCAN
		
		case(ELPR_DEVICE_GET_CURRENT_STATUS):{				/* @SF0000BB0@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
			uint8_t* vers = get_device_modes_data();
			USB_CDC_send_data(vers, DEVICE_MODES_SETTINGS_LENGTH);
			el_reset_state();
		break;}		
		
		default:
			response = ELP_IDLE;
			protocol_response(response);
			el_reset_state();
			break;
	}
}


