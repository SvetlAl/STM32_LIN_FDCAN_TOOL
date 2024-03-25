/****************************************************************
* 
* RAM updater
*
* This structure handles manual override update of the vars located in RAM
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "ram_updater.h"

static ram_updater the_ram_updater;

/** 
* brief  Set transmission pending size before start
* param  size
* param  
* retval
*/	
void ram_upd_set_size(uint32_t size){
	the_ram_updater.pending_byte_count = size;
}

/** 
* brief  Read out transmission pending size
* param  
* param  
* retval size
*/	
uint32_t ram_upd_get_pending_size(void){
	return the_ram_updater.pending_byte_count;
}

/** 
* brief  Update out transmission pending size
* param  size
* param  
* retval 
*/
void ram_upd_record_written_size(uint32_t size){
	if(size >= the_ram_updater.pending_byte_count) the_ram_updater.pending_byte_count = 0;
	else the_ram_updater.pending_byte_count = the_ram_updater.pending_byte_count - size;
}
