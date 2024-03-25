//#include "Commands/cmd_general.h"
#include "Commands/user_cmd.h"
#include "Commands/test_cmd_nand.h"

#include "Flash_memchip/flash_nand_mem_chip_spi.h"


#ifdef NAND_FLASH_DEBUG
uint8_t TEST_READ[2112];


volatile uint16_t TEST_BBD = NAND_PAGE_SIZ_DATA;

void process_test_cmd_nand(elp_cmd *com){
	uint32_t response = ELP_OK;
		switch(com->cmd){
			case(ELP_NAND_TEST_READ_ID):{ // @S000F0000@E Read memchip ID 
				volatile uint16_t result = memchip_nand_read_id();
				uint8_t report[2] = { (uint8_t)((result >> 8) & 0xFF ), (uint8_t)(result & 0xFF)};
				USB_CDC_send_data(report, 2);
				el_reset_state();
				break;
			}
			case(ELP_NAND_TEST_RESET):{ // @S000F0001#OP@E Get feature  OP - "address" 
				memchip_reset();
				el_reset_state();
				break;
			}
			
			case(ELP_NAND_TEST_GET_FEATURE):{ // @S000F0001#OP@E Get feature  OP - "address" 
				uint8_t param = com->param[0];
				
				uint8_t result = memchip_nand_get_feature(param);
				USB_CDC_send_data(&result, 1);
				el_reset_state();
				break;
			}
			
			case(ELP_NAND_TEST_READ_FROM_CACHE):{ //  @S000F0002#AD#DR#WR#SZ@E 
				uint8_t addr_0 = com->param[0];
				uint8_t addr_1 = com->param[1];
				uint8_t wrap = com->param[2];
				uint8_t sz = com->param[3];
				
				uint16_t wrap_msk = NAND_CMD_READ_WRAP_FULLPAGE;
					
				if(wrap == NAND_CMD_READ_WRAP_FULLPAGE)
				wrap_msk = NAND_CMD_READ_WRAP_FULLPAGE_MSK;
				else if(wrap == NAND_CMD_READ_WRAP_DATAPAGE)
				wrap_msk = NAND_CMD_READ_WRAP_DATAPAGE_MSK;
				else if(wrap == NAND_CMD_READ_WRAP_64)
				wrap_msk = NAND_CMD_READ_WRAP_64_MSK;
				else if(wrap == NAND_CMD_READ_WRAP_16)
				wrap_msk = NAND_CMD_READ_WRAP_16_MSK;
				
				uint16_t address =  (uint16_t)((uint16_t)((addr_0 << 8) & 0xFF00 ) | (uint16_t)(addr_1 & 0x00FF));
	//			memchip_read_from_cache(address, &TEST_READ[0], wrap_msk, 2112);
				USB_CDC_send_array(TEST_READ, 2112);
				el_reset_state();
				break;
			}
			
			case(ELP_NAND_TEST_READ_PAGE):{ //   @S000F0003#AD#DR@E 
				uint8_t blk = com->param[0];
				uint8_t page = com->param[1];
								
	//			memchip_read_page(blk, page);
				el_reset_state();
				break;
			}
			
			case(ELP_NAND_TEST_SET_FEATURE):{ // @S000F0005#AD#VL@E
				uint8_t addr = com->param[0];
				uint8_t bit = com->param[1];
				
				uint8_t result = memchip_nand_set_feature(addr, bit);
				USB_CDC_send_data(&result, 1);
				el_reset_state();
				break;
			}
			case(ELP_NAND_TEST_RST_FEATURE):{ // @S000F0006#AD#VL@E
				uint8_t addr = com->param[0];
				uint8_t bit = com->param[1];
				
				uint8_t result = memchip_nand_reset_feature(addr, bit);
				USB_CDC_send_data(&result, 1);
				el_reset_state();
				break;
			}
			
			case(ELP_NAND_TEST_READ_BADBLK_MRK):{ // @S000F0007@E
				
//				memchip_nand_make_index(0x000000, &the_nand_index, Nand_data_and_spare_mode);
				
//				the_nand_index.byte_pos = NAND_PAGE_SIZ_DATA;
				
				uint16_t page_cnt = 0;
				for(uint16_t i = 0; i < NAND_SIZ_BLOCKS; i++){
					
					uint32_t result = memchip_check_bad_block(i);
					if(result == OPERATION_FAIL){
						TEST_READ[page_cnt++] = (i >> 8)& 0x00FF;
						TEST_READ[page_cnt++] = i & 0x00FF;
					}
				}
				/*		
					the_nand_index.block_pos = i;
					the_nand_index.page_pos = 0;
					the_nand_index.byte_pos = TEST_BBD;
					memchip_read_from_nand(&TEST_READ[page_cnt++], 1, 1, &the_nand_index, Nand_data_and_spare_mode);
					the_nand_index.page_pos = 1;

					the_nand_index.byte_pos = TEST_BBD;
					memchip_read_from_nand(&TEST_READ[page_cnt++], 1, 1, &the_nand_index, Nand_data_and_spare_mode);
					the_nand_index.page_pos = 2;

					the_nand_index.byte_pos = TEST_BBD;
					memchip_read_from_nand(&TEST_READ[page_cnt++], 1, 1, &the_nand_index, Nand_data_and_spare_mode);
*/
				
				
				USB_CDC_send_array(TEST_READ, page_cnt);
				el_reset_state();
				break;
			}
			case(ELP_NAND_TEST_ERASE_BLOCK):{ // @S000F0008#BL#CK@E
				uint8_t addr_0 = com->param[0];
				uint8_t addr_1 = com->param[1];
				
				uint16_t address =  (uint16_t)((uint16_t)((addr_0 << 8) & 0xFF00 ) | (uint16_t)(addr_1 & 0x00FF));
				uint32_t result = memchip_erase_block(address);
				if(result == OPERATION_FAIL){
					response = ELP_ERROR;
				}
				else if(result == OPERATION_OK){
					response = ELP_OK;
				}
				protocol_response(response);
				el_reset_state();
				break;
			}
			case(ELP_NAND_TEST_24_BIT_ADDR):{ // @S000F0009#BL#CK@E
				uint8_t addr_0 = com->param[0];
				uint8_t addr_1 = com->param[1];
			
				uint8_t addr_2 = com->param[2];
				uint8_t addr_3 = com->param[3];
				
				uint16_t baddress =  (uint16_t)((uint16_t)((addr_0 << 8) & 0xFF00 ) | (uint16_t)(addr_1 & 0x00FF));
				uint16_t paddress =  (uint16_t)((uint16_t)((addr_2 << 8) & 0xFF00 ) | (uint16_t)(addr_3 & 0x00FF));
				
				//volatile nand_24bit_address  ad =    make_24bit_address(baddress, paddress);
				el_reset_state();
				break;
			}
			
		case(ELP_NAND_TEST_MAKE_INDEX):{ // @S000F000A#AD#DR#ES#S @E 
			uint8_t addr_0 = com->param[0];
			uint8_t addr_1 = com->param[1];
			uint8_t addr_2 = com->param[2];
			uint8_t addr_3 = com->param[3];
			uint32_t addr = 0x00;
			uint8_t pos = 3;
			uint8_t cnt = 4;
			for(uint8_t i = 0; i < cnt; i++){
				addr |= (uint32_t)(com->param[pos] << (i*8)); 
				pos   = (uint8_t)(pos - 1);
			}
		//	memchip_nand_make_index(addr, &the_nand_index, Nand_data_mode);
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_MAKE_START):{ // @S000F000B#BL#CK#PA#GE#BY#TE@E
			uint8_t blk_0 = com->param[0];
			uint8_t blk_1 = com->param[1];
			
			uint8_t pg_0 = com->param[2];
			uint8_t pg_1 = com->param[3];
			
			uint8_t bt_0 = com->param[4];
			uint8_t bt_1 = com->param[5];
			
			uint16_t baddress =  (uint16_t)((uint16_t)((blk_0 << 8) & 0xFF00 ) | (uint16_t)(blk_1 & 0x00FF));
			uint16_t paddress =  (uint16_t)((uint16_t)((pg_0 << 8) & 0xFF00 ) | (uint16_t)(pg_1 & 0x00FF));
			uint16_t btaddress =  (uint16_t)((uint16_t)((bt_0 << 8) & 0xFF00 ) | (uint16_t)(bt_1 & 0x00FF));
			
		//	memchip_nand_make_start_index(baddress, paddress, btaddress, &the_nand_index, Nand_data_mode);
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_PROGRAMM_LOAD):{ /* @S000F000C@!Test@E -->*/
	//		memchip_programm_load(&the_nand_index, &com->string_buffer.raw_data8[0], (uint16_t)com->string_siz, NAND_CMD_READ_WRAP_DATAPAGE_MSK);
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_PROGRAMM_EXEC):{ /* @S000F000D@E memchip_programm_execute(index) */
//			memchip_programm_execute(&the_nand_index);
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_WREN):{ /* @S000F000E@E  */
//			memchip_write_enable();
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_WRDIS):{ /* @S000F000F@E */
//			memchip_write_disable();
			el_reset_state();
			break;
		}
		case(ELP_NAND_TEST_LOAD_PRESET):{ /* @S000F0010#PR@E */
			el_reset_state();
			break;
		}

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
#endif // NAND_FLASH_DEBUG

