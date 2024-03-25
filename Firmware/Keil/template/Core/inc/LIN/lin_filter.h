#ifndef LIN_FILTER_H_INCLUDED
#define LIN_FILTER_H_INCLUDED

#include "device_model.h"
#include "LIN/lin_item.h"

//=========================================================================================================
//=======================================  LIN filter functions ===========================================
void implement_lin_dummy_filter(LinItem *item, lin_filter_raw* filter);
void implement_lin_user_filter(LinItem *item, lin_filter_raw* filter);
#ifdef LIN_PROGRAMM_PRESETS
void calibrate_lin_mmc_pajero_tyres(LinItem *item, lin_filter_raw* filter);
#endif

#endif /* LIN_FILTER_H_INCLUDED*/
