#ifndef RUNTIME_H_INCLUDED
#define RUNTIME_H_INCLUDED

#include "main.h"
#include "device_model.h"

//=========================================================================================================
//============================================== Functions ================================================
//=========================================================================================================
void runWatchdogProcedure(void);
void findAndProcess_cmd(void);

void extra_broadcast(void);
void main_led_blink(void);


#ifdef SUPPORT_FDCAN
void fdcan_can_override_calibrate(uint8_t* msg);
#endif // SUPPORT_FDCAN




#endif /* RUNTIME_H_INCLUDED */
