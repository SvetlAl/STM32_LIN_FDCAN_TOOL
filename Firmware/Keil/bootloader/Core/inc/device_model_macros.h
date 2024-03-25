#ifndef DEVICE_MODEL_MACROS_H_INCLUDED
#define DEVICE_MODEL_MACROS_H_INCLUDED
/****************************************************************
* 
* Device Model structures
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
//#include "project_settings.h"
#include "device_model_board_config.h"

#define LOBYTE(x) (uint8_t)(x & ~0xFF00)
#define HIBYTE(x) (uint8_t)((x >> 8) & ~0xFF00)


#endif /* DEVICE_MODEL_MACROS_H_INCLUDED*/
