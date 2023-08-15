#ifndef RUNTIME_H_INCLUDED
#define RUNTIME_H_INCLUDED

#include "device_model.h"
#include "stm32f105_usbdfs_cdc.h"
#include "watchdog.h"
#include "el_protocol.h"
#include "flash_mem_chip_spi.h"
#include "user_cmd.h"
#include "main.h"

/********************************************************************************************/
/************************************ 		Global vars			 **********************************/
/********************************************************************************************/

#if defined(ALLIGATOR) | defined(TEC_MODULE) | defined(DEVICE_FCAN_V6)
extern volatile uint8_t blink_timeout;
extern volatile uint8_t blink_switch;
#endif

extern volatile uint32_t cmd_fll;
extern memchip_status memory_chip_status;


/****************************************************************
* 												Functions
*****************************************************************/
void runWatchdogProcedure(void);
void findAndProcess_cmd(void);

/********************************************************************************************/
/************************************ Device modes handler **********************************/
/********************************************************************************************/
uint32_t process_override_procedure(can_message *newMessage, uint32_t _can_num /* CAN1 or CAN2 */);
void process_calibrator_procedure(can_message *newMessage);


#endif /* RUNTIME_H_INCLUDED */
