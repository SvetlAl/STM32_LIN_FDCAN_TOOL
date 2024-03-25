#ifndef COMMON_CMD_H_INCLUDED
#define COMMON_CMD_H_INCLUDED

#include "device_model.h"
#include "Commands/user_cmd.h"

//=========================================================================================================
//========================================  Address handle ================================================
uint32_t extract_address_from_cmd(elp_cmd *com);
uint32_t extract_length_from_cmd(elp_cmd *com);

//=========================================================================================================
//=============================================  Misc. ====================================================
uint32_t erase_sector(elp_cmd *com);
uint32_t assert_cmd_length(uint16_t proper_length, elp_cmd *com);
void cmd_send_raw_data(uint8_t *start_addr, uint32_t total_length);
uint16_t extract_2bytes_cmd(elp_cmd *com);

#endif // COMMON_CMD_H_INCLUDED
