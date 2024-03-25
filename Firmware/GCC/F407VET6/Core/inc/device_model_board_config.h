#ifndef DEVICE_MODEL_BOARD_CONFIG_H_INCLUDED
#define DEVICE_MODEL_BOARD_CONFIG_H_INCLUDED
/****************************************************************
* 
* Device Model include config
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "project_settings.h"

//=========================================================================================================
//============================ Includes dependencies. Do not change. ======================================
#ifdef DEVICE_TEC_MODULE
#include "Board_models/F205/DEVICE_TEC_MODULE.h"
#endif
#ifdef DEVICE_ALLIGATOR
#include "Board_models/F205/DEVICE_ALLIGATOR.h"
#endif
#ifdef DEVICE_2CAN
#include "Board_models/F105/DEVICE_2CAN.h"
#endif
#ifdef DEVICE_2CAN_TJA1042
#include "Board_models/F105/DEVICE_2CAN_TJA1042.h"
#endif
#ifdef DEVICE_2CAN_BOXED
#include "Board_models/F105/DEVICE_2CAN_BOXED.h"
#endif
#ifdef DEVICE_SIGMA
#include "Board_models/F105/DEVICE_SIGMA.h"
#endif
#ifdef DEVICE_1CAN2LIN
#include "Board_models/F105/DEVICE_1CAN2LIN.h"
#endif
#ifdef DEVICE_FCAN_V6
#include "Board_models/F205/DEVICE_FCAN_V6.h"
#endif
#ifdef DEVICE_PRZRK8XL
#include "Board_models/H730/DEVICE_PRZRK8XL.h"
#endif
#ifdef DEVICE_DEVBOARD_F407VET_A
#include "Board_models/F407/DEVICE_DEVBOARD_F407VET_A.h"
#endif

#endif /* DEVICE_MODEL_BOARD_CONFIG_H_INCLUDED*/
