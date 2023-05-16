/****************************************************************
* 
* User interface command parser
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "user_cmd.h"
#include "main.h"

/*****************************************************************/
/*****************************************************************/
/**************   The protocol command processing ****************/
/*****************************************************************/
/*****************************************************************/


/***  @DD ***/
extern VehicleStructData theVehicle;
/***  @DD ***/
extern memchip_status memory_chip_status;

extern uDeviceModel theDeviceModel;
/***  @DD ***/
extern can_injection_status theCanInjectionStatus;

//extern el_quadro_buffer quadro_buf;
static uint8_t spi_buf[CMD_CDC_TRANSACTION_SZ]; /* Memory chip data --> temp_spi_buf --> USB_send */


static inline uint32_t assert_cmd_length(uint16_t proper_length, elp_cmd *com){
	if(com->string_siz != proper_length) return ELP_ERROR;
	return ELP_OK;
}

/*
static inline uint32_t extract_can_id_from_cmd(elp_cmd *com){
	uint32_t id = 0x00;
	id |= com->param[6]; 
	id |= (uint32_t)(com->param[5] << 8); 
	id |= (uint32_t)(com->param[4] << 16); 
	id |= (uint32_t)(com->param[3] << 24);
	return id;
}
*/

static inline uint32_t extract_address_from_cmd(elp_cmd *com){
	uint32_t addr = 0x00;
	addr |= com->param[2]; /* 01 80*/
	addr |= (uint32_t)(com->param[1] << 8); /* 02 00*/
	addr |= (uint32_t)(com->param[0] << 16); /* 03 00*/
	return addr;
}

static inline uint32_t extract_length_from_cmd(elp_cmd *com){
	uint32_t length = 0x00;
	length |= com->param[5]; /* 01 */
	length |= (uint32_t)(com->param[4] << 8); /* 02 */
	length |= (uint32_t)(com->param[3] << 16); /* 02 */
	return length;
}

static inline void read_vehicleStatus_and_usb_send_HEX(){
	uint8_t *status = get_vehicle_settings_data();
	USB_CDC_send_data(status, VEHICLE_STATUS_SETTINGS_LENGTH);
}

static inline void read_vehicleStatus_and_usb_send_ASCII(){
	uint8_t *status = get_vehicle_settings_data();
	uint8_t temp[VEHICLE_STATUS_SETTINGS_LENGTH*2];
	
	hexArray2asciiArray((status + 1), &temp[0], 1);
	hexArray2asciiArray((status), &temp[2], 1);
	hexArray2asciiArray((status + 2), &temp[4], VEHICLE_STATUS_SETTINGS_LENGTH - 2);
	
	USB_CDC_send_data(temp, VEHICLE_STATUS_SETTINGS_LENGTH*2);
}

static inline uint32_t save_vehicleStatus(){
	erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, VEHICLE_SETTINGS_ADDRESS);		
		/* Make timeout and report the result */
	erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
	
	uint8_t *status = get_vehicle_settings_data();		
	return programm_memchip(&memory_chip_status, VEHICLE_SETTINGS_ADDRESS, status, (uint16_t)VEHICLE_STATUS_SETTINGS_LENGTH, SPI_no_Dma);
}

static inline uint32_t save_deviceStatus(){
	erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, DEVICE_MODES_ADDRESS);		
		/* Make timeout and report the result */
	erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
	
	uint8_t *dev_modes_status = get_device_modes_data();
	programm_memchip(&memory_chip_status, DEVICE_MODES_ADDRESS, dev_modes_status, (uint16_t)DEVICE_MODES_SETTINGS_LENGTH, SPI_no_Dma);
	
	
	uint8_t *ovr_status = get_override_settings_data();
	uint32_t addr = DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS;
	return programm_memchip_long(&memory_chip_status, addr, ovr_status, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH, SPI_no_Dma);
}


static inline void parse_and_set_calibrator_value(uint32_t PARAMETER, uint32_t value){
	//value &= ~0xFFFFFF00;
	set_vehicle_value(PARAMETER, value);
	protocol_response(ELP_OK);
	el_reset_state();
}		
		
static inline void read_mem_data_and_usb_send(uint32_t length, uint32_t addr){
	uint32_t send_status = EP_OK;
	
	while((length >= CMD_CDC_TRANSACTION_SZ) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){		
		memory_chip_status.memchip_state = CMD_CDC_TRANSACTION_SZ;		
		read_memchip(&memory_chip_status, addr, spi_buf, CMD_CDC_TRANSACTION_SZ, SPI_no_Dma);
		send_status = USB_CDC_send_data(spi_buf, CMD_CDC_TRANSACTION_SZ);	

		if(send_status == EP_FAILED) return;
		
		length-=CMD_CDC_TRANSACTION_SZ;
		addr+=CMD_CDC_TRANSACTION_SZ;
	}
	if((length > 0) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){
		memory_chip_status.memchip_state = length;	
		read_memchip(&memory_chip_status, addr, spi_buf, length, SPI_no_Dma);
		USB_CDC_send_data(spi_buf, (uint16_t)length);
	}
}

static inline uint32_t erase_sector(elp_cmd *com){
	uint32_t addr = extract_address_from_cmd(com);
	erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, addr);		
		/* Make timeout and report the result */
	return erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
}

static inline void erase_memchip_area(uint32_t addr, uint32_t length){
	uint32_t start_address = addr;
	uint32_t pos = 0;
	while(pos < length){
		erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, start_address);
		erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
		pos += MEMCHIP_CMD_SECTOR_SIZE;
		start_address += MEMCHIP_CMD_SECTOR_SIZE;
	}
}

static inline void start_hex_programm_procedure(elp_cmd *com){ /* @SF0000008#00#01#02#12#23#45@E Start programming procedure at addr 0x000102 with 0x122345 bytes */
	uint32_t programm_size = 0x00;			
	programm_size |= com->param[5]; /* 01 80*/
	programm_size |= (uint32_t)(com->param[4] << 8); /* 02 00*/
	programm_size |= (uint32_t)(com->param[3] << 16); /* 03 00*/
	
	if(programm_size == 0 ){
		protocol_response(ELP_IDLE);
		el_reset_state();
	}
	uint32_t sectors_address_step = MEMCHIP_CMD_SECTOR_SIZE;
	uint32_t sectors_count =  MEMCHIP_CMD_SECTOR_COUNT;
	uint32_t address = extract_address_from_cmd(com);
	
	uint32_t empty_space = (sectors_count*sectors_address_step) - address;
			
	if(empty_space <  programm_size){
		protocol_response(ELP_ERROR);
		el_reset_state();
	}
	
	// FF - rewrite 00 append
	if(com->param[6] != 0x00){	// 		FF - rewrite
		uint32_t residue = ((programm_size % sectors_address_step)==0) ? 0 : 1 ;
		uint32_t sectors_to_erase_count = programm_size / sectors_address_step + residue;
		
		for(uint32_t i = 0; i < sectors_to_erase_count; i++){
			erase_sector_memchip(&memory_chip_status, MEMCHIP_ERASE_USE_ADDRESS, (address + sectors_address_step*i));		
			erase_timeout_memchip(MEMCHIP_ER_TIMEOUT);
		}
	}
	
	/*  */
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_ON);
	memory_chip_status.stream_pending_data = programm_size;
	memory_chip_status.stream_address = address;
	
	protocol_response(ELP_OK);
	el_reset_state();
}

static inline void start_override_filters_upd_procedure(void){ /* @SF0000008#00#01#02#12#23#45@E Start programming procedure at addr 0x000102 with 0x122345 bytes */
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_FILTR_UPD);
	memory_chip_status.stream_pending_data = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	
	protocol_response(ELP_OK);
	el_reset_state();
}



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
	
	switch(com->cmd){
		
	/*	case(ELP_TEST):{	
		uint8_t test_string[MAX_CDC_EP1_TX_SIZ] = {0xCE};
		USB_CDC_send_data(test_string, MAX_CDC_EP1_TX_SIZ);
		el_reset_state();
		break;
	}
		*/	
		/***********************  ELP_CMD_RESET **************************/
		case(ELP_CMD_RESET):
			el_reset_state();
			protocol_response(response);
			break;
		
		
		/********** ELPR_VEHICLE_GET_CURRENT_STATUS *****************/			/* HEX */
		/**********	Quick send theVehicle data  NOT ASCII ***********/
		case(ELPR_VEHICLE_GET_CURRENT_STATUS):
			read_vehicleStatus_and_usb_send_HEX();
			el_reset_state();
			break;
		
		
		/********** ELP_VEHICLE_GET_MEMORY_STATUS_STRING *****************/
		/**********	Get first 8 bytes of the first memory page ***********/
		/*
		case(ELP_VEHICLE_GET_MEMORY_STATUS_STRING_HEX):
			read_memorySnapshot_and_usb_send(STATUS_STRING_LENGTH*2, VEHICLE_SETTINGS_ADDRESS);
			el_reset_state();
			break;
		*/
		/********** ELP_VEHICLE_GET_CURRENT_STATUS_STRING ****************/
		/********** Get 8 bytes of current vehicle settings	**************/
		case(ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII):
			read_vehicleStatus_and_usb_send_ASCII();
			el_reset_state();
			break;
		
		/***************** ELP_VEHICLE_SAVE_STATUS **********************/
		/************ Save 8 bytes of current vehicle settings **********/
		case(ELP_VEHICLE_SAVE_STATUS):
			response = save_vehicleStatus();
			protocol_response(response);
			el_reset_state();
			break;	

		/*************** ELP_VEHICLE_SET_XXXXXXXXXXXXXX *****************/
		case(ELP_VEHICLE_SET_MODE/* ELP_VEHICLE_SET_ODOMETER_MODE */):
		case(ELP_VEHICLE_SET_TEST_MODE):
		case(ELP_VEHICLE_SET_MODEL):
		case(ELP_VEHICLE_SET_ODOMETER_MLT):
		case(ELP_VEHICLE_SET_TYRES_THRESHOLD):
		case(ELP_VEHICLE_SET_CRUISE_MLT):
		case(ELP_VEHICLE_SET_SPEEDOMETER_MLT):{
			response = assert_cmd_length(ELP_VEHICLE_SET_MODE_CMDSTR_LENGTH, com);
			
			if(response != ELP_ERROR){
				uint32_t value = str_to_uint32(&com->string_buffer.raw_data8[0]);
				parse_and_set_calibrator_value(com->cmd, value);
			}
			break;
		}
		
		/**********************	ELP_CMD_SPI_MEMCHIP_READ	****************/
		/***** Load a data from a certain address of size X bytes ********/		
		case(ELP_CMD_SPI_MEMCHIP_READ):
			read_mem_data_and_usb_send(extract_length_from_cmd(com), extract_address_from_cmd(com));
			el_reset_state();
			break;
		
		/****************	ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR	**************/
		case(ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR):
			protocol_response(erase_sector(com));
			el_reset_state();
			break;

		/****************	ELP_CMD_SPI_MEMCHIP_ERASE_CHIP	****************/		
		case(ELP_CMD_SPI_MEMCHIP_ERASE_CHIP):
		/********************************************************/
		/* IMPORTANT! Full chip erase can take up to 30 seconds */
		/********************************************************/
			protocol_response(erase_chip_memchip(&memory_chip_status));
			el_reset_state();
			break;	
		
		/****************	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP	****************/		
		case(ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP):	
			response = programm_memchip(&memory_chip_status, extract_address_from_cmd(com), &com->string_buffer.raw_data8[0], (uint16_t)com->string_siz, SPI_no_Dma);
			protocol_response(response);
			el_reset_state();
			break;		

		/****************	ELP_TEST_CMD_SPI_MX25_GET_RDCR	****************/		
		case(ELP_TEST_CMD_SPI_MX25_GET_RDCR):{	
			uint8_t result = read_rdcr_reg_memchip();
			USB_CDC_send_data(&result, 0x01);
			el_reset_state();
			break;}
		
		/****************	ELP_TEST_CMD_SPI_MX25_GET_RDSR	****************/		
		case(ELP_TEST_CMD_SPI_MX25_GET_RDSR):{
			uint8_t result = read_status_reg_memchip();
			USB_CDC_send_data(&result, 0x01);
			el_reset_state();
			break;}

		/****************	ELP_VEHICLE_GET_SW_VERSION	****************/		
		case(ELP_VEHICLE_GET_SW_VERSION):{
			uint8_t* sw_vers = getDeviceSoftwareVersion();
			USB_CDC_send_data(sw_vers, DEVICE_INFO_STRING_SZ);
			el_reset_state();
			break;}

		/****************	ELP_VEHICLE_GET_DEV_MODEL	****************/		
		case(ELP_VEHICLE_GET_DEV_MODEL):{
			uint8_t* sw_vers = getHardwareVersion();
			USB_CDC_send_data(sw_vers, DEVICE_INFO_STRING_SZ);
			el_reset_state();
			break;}	

		/****************	ELP_DEVICE_SET_MODE	****************/		
		case(ELP_DEVICE_SET_MODE):{									/* @S00000B07#00#00#01#02@E set the first (0x 000001)var in DeviceModel as 02 */	
			if(com->param_counter == 4){
				uint32_t dev_mode_num = extract_address_from_cmd(com);
				uint8_t value = com->param[3];
				if(dev_mode_num <= sizeof(DeviceModel)){
					
					theDeviceModel.data[dev_mode_num] = value;
					
					if(((dev_mode_num == Enm_canScannerMode) | (dev_mode_num == Enm_can2ScannerMode)) & (value == DEVICE_OPERATION_MODE_ON)){ /* If the command is to start scanner */
						resetCanTimer(MAIN_TIMER);
					}
					
					else if(dev_mode_num == Enm_canInjectionMode){
						if (value != DEVICE_OPERATION_MODE_OFF){ /* If the command is to start injection */
							startMessageInjection(&theCanInjectionStatus, value);
						}
						else if (value == DEVICE_OPERATION_MODE_OFF){ /* If the command is to start injection */
							stopMessageInjection();
						}
					}
					
					protocol_response(ELP_OK);
					el_reset_state();
					break;
				}
			}
			protocol_response(ELP_ERROR);
			el_reset_state();
			break;}	
																																																																																	
		/****************	ELP_UPDATE_OVR_FILTERS	****************/		
		case(ELP_UPDATE_OVR_FILTERS):{								/* @S00000BA1@E Start filter update procedure */
			start_override_filters_upd_procedure();
			break;}	
		
		/****************	ELP_DEVICE_SAVE_STATUS	****************/		
		case(ELP_DEVICE_SAVE_STATUS):{								/* @S00000BA0@E Save current device settings into (0x00FA00) DEVICE_MODES_ADDRESS */
			response = save_deviceStatus();
			protocol_response(response);
			el_reset_state();
			break;}	

		/****************	ELPR_DEVICE_GET_CURRENT_STATUS	****************/		
		case(ELPR_DEVICE_GET_CURRENT_STATUS):{				/* @SF0000BB0@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
			uint8_t* vers = get_device_modes_data();
			USB_CDC_send_data(vers, DEVICE_MODES_SETTINGS_LENGTH);
			el_reset_state();
			break;}		
		
				/****************	ELPR_OVR_FLTR_GET_FILTER_NUMS	****************/		
		case(ELPR_OVR_FLTR_GET_FILTER_NUMS):{				/* @SF0000BB2@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
			uint8_t* vers = get_override_settings_data();
			USB_CDC_send_data(vers, 4);
			el_reset_state();
			break;}		
		
		
				/****************	ELPR_OVR_FLTR_GET_CURRENT_STATUS	****************/		
		case(ELPR_OVR_FLTR_GET_CURRENT_STATUS):{				/* @SF0000BB1@E ASCII Get sizeof(can_override_status) of current override settings in raw data*/
			uint8_t* vers = get_override_settings_data();
			uint32_t length = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
			
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

		case(ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP): /* @SF0000008#00#01#02#12#23#45#FF@E Start programming procedure at addr 0x000102 with 0x122345 bytes  FF - append or 00 rewrite */
			start_hex_programm_procedure(com);
			break;
		
		case(ELP_ERASE_AREA): /*  @00000010#00#01#40#00#02#80@E --> Erase data starting from address -0x000140 0x000280 bytes */
		  erase_memchip_area(extract_address_from_cmd(com), extract_length_from_cmd(com));
			protocol_response(ELP_OK);
			el_reset_state();
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

void set_vehicle_value(uint32_t cmd, uint32_t _value){
	switch(cmd){
		case ELP_VEHICLE_SET_MODEL:
			theVehicle._vehicleStruct.model = (uint16_t)_value;
			initVehicle(&theVehicle._vehicleStruct, VEHICLE_INIT_DEFAULT);
			break;

		/* Applying a mask: uint32_t value 0x00001234, 0x12 - is a mask to "&= ~", 34 is a mask to "|= "*/
		case ELP_VEHICLE_SET_TEST_MODE:	/* deprecated */
		case ELP_VEHICLE_SET_MODE:{
			uint8_t setMask = SC_BYTE_FROM32BIT(_value, 3);
			uint8_t resetMask = SC_BYTE_FROM32BIT(_value, 2);			
			theVehicle._vehicleStruct.modes = (uint8_t)(theVehicle._vehicleStruct.modes & ~resetMask);
			theVehicle._vehicleStruct.modes |= setMask;
			break;}
			
			
		case ELP_VEHICLE_SET_SPEEDOMETER_MLT:
			theVehicle._vehicleStruct.speedometer_mlt = (uint8_t)(_value);
			break;
		
		case ELP_VEHICLE_SET_ODOMETER_MLT:
			theVehicle._vehicleStruct.odometer_mlt = (uint8_t)(_value);
			break;
		
		case ELP_VEHICLE_SET_CRUISE_MLT:
			theVehicle._vehicleStruct.cruise_mlt = (uint8_t)(_value);
			break;
		
		case ELP_VEHICLE_SET_TYRES_THRESHOLD:
			theVehicle._vehicleStruct.tyres_threshold = (uint8_t)(_value);
			break;
		
		default:
		break;			
	}
}









	/*****************************************************************/
	/*************************	ELP_CMD_PRINT	************************/
	/* Test function: a command string explained sent back					 */
	/*****************************************************************/	
	/*else if(com->cmd == ELP_CMD_PRINT){
		uint8_t print_buffer[27] = {' ', 'c', 'o', 'm', ' ', 
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 28)),
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 24)),
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 20)),	
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 16)),	
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 12)),
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 8)),
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 4)),
			halfbyte_to_hexascii((uint8_t)(com->cmd >> 0)),
			' ', 'p', 'a', 'r', 'a', 'm', '_', 'c', 'n', 't', ' ',
			halfbyte_to_hexascii((uint8_t)(com->param_counter >> 4)),
			halfbyte_to_hexascii((uint8_t)(com->param_counter >> 0)), ' '};
		
		USB_CDC_send_data(print_buffer, 27);
		el_reset_state();
	} */
	/*****************************************************************/
	/*************************	ELP_CMD_PRINT_STRING	****************/
	/* Test function: a string arg sent back												 */
	/*****************************************************************/		
	/*
	else if(com->cmd == ELP_CMD_PRINT_STRING){	
		USB_CDC_send_data(&com->string_buffer.raw_data8[0], (uint16_t)com->string_siz);
		el_reset_state();
	}
	*/
		/*****************************************************************/
	/********		ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_HEX		**************/
	/*****************************************************************/	
	/*
	else if(com->cmd == ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_HEX){
		if((uint16_t)com->string_siz <= ELP_MAX_STR_INPUT_LENGTH){
			
			uint32_t addr = extract_address_from_cmd(com);
			str_to_ascii(&com->string_buffer.raw_data8[0], spi_buf, (uint16_t)com->string_siz);
			
			response = programm_memchip(&memory_chip_status, addr, spi_buf, (uint16_t)com->string_siz/2, SPI_no_Dma);
			protocol_response(response);
			el_reset_state();
		}
	}
	
	*/
