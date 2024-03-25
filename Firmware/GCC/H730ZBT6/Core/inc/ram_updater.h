#ifndef RAM_UPDATER_H_INCLUDED
#define RAM_UPDATER_H_INCLUDED
/****************************************************************
* 
* RAM updater
*
* This structure handles manual override update of the vars located in RAM
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

typedef struct ram_updater{
	uint32_t pending_byte_count;
	uint8_t *write_address;
}ram_updater;

//============================================================================================
//==================================== Application function ==================================
uint32_t ram_upd_get_pending_size(void);
void     ram_upd_set_size(uint32_t size);
void     ram_upd_record_written_size(uint32_t size);

#endif /* RAM_UPDATER_H_INCLUDED */
