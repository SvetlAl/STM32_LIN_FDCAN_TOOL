/****************************************************************************
* 	LIN BUS filters
*
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
******************************************************************************/

#include "LIN/lin_filter.h"

/**
* brief  Look through a filter set, find engaged id's and roles.
* brief  If provided item's id and role matches any engaged filter, implement changes.
* param  A pointer to a LIN item.
* param  A pointer to a LIN filter set.
* param  
* retval 
*/

void implement_lin_user_filter(LinItem *item, lin_filter_raw* _filter){
	if(item->id != _filter->filter.id) return;
	
	for(uint8_t i = 0; i < item->length; i++){
		// Does this [i] byte needs to be changed?
		if((uint8_t)((_filter->filter.msk >> i) &~0xFE) != 0){
			// replace the byte value
			item->data[i] = _filter->filter.data[i];
		}
	}
}

void implement_lin_dummy_filter(LinItem *item, lin_filter_raw* filter){
	(void)(item);
	(void)(filter);
}


#ifdef LIN_PROGRAMM_PRESETS
/**
* brief  A program preset for MMC Pajero tyre pressure 
* param  
* retval 
*/
void calibrate_lin_mmc_pajero_tyres(LinItem *item, lin_filter_raw* filter){
	(void)(item);
	(void)(filter);
}
#endif



