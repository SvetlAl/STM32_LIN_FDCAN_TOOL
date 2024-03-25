#ifndef TEST_CMD_NAND_H_INCLUDED
#define TEST_CMD_NAND_H_INCLUDED

#include "device_model.h"

#ifdef NAND_FLASH_DEBUG
#include "user_cmd.h"

void process_test_cmd_nand(elp_cmd *com);

#endif // NAND_FLASH_DEBUG

#endif // TEST_CMD_NAND_H_INCLUDED
