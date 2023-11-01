#ifndef LIN_FILTER_H_INCLUDED
#define LIN_FILTER_H_INCLUDED

#include "device_model.h"
#include "lin_item.h"

//===========================  Filter masks =======================
//#define LIN_FILTER_MOSI_MSK  0
//#define LIN_FILTER_MISO_MSK  1

//===========================  Filter modes =======================

#define LIN_FILTER_OFF              0
#define LIN_FILTER_USER_MODE        1
#define LIN_FILTER_MMC_PAJERO_TYRES 2
#define LIN_FILTER_COUNT            3

//===========================  LIN filter =========================

typedef struct lin_filter{
	uint8_t id;  // if id == 0, a filter is disabled
	uint8_t msk; // this mask defines what bytes (1st, 2nd, 3rd....) are to be changed
	uint8_t length; // not used in ui
	uint8_t unused;
	uint8_t data[8];
} lin_filter; //creating new type

typedef union lin_filter_raw {
	lin_filter filter;
	uint8_t data[12];
} lin_filter_raw;

//===================  LIN filter functions =======================
void implement_lin_dummy_filter(LinItem *item, lin_filter_raw* filter);
void implement_lin_user_filter(LinItem *item, lin_filter_raw* filter);
#ifdef LIN_PROGRAMM_PRESETS
void calibrate_lin_mmc_pajero_tyres(LinItem *item, lin_filter_raw* filter);
#endif

#endif /* LIN_FILTER_H_INCLUDED*/
