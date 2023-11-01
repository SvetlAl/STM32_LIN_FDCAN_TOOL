#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define STARTUP_TIMEOUT 0x1FFF

/****************************************************************
* A device based on STM32F205
*
*
* Library code is mostly standalone except marked as @DD
*
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*****************************************************************/

#include "device_model.h"
#ifdef STM32F205
#include "stm32f205xx.h"
#include "stm32f205_clock.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#include "stm32f105xc.h"
#include "stm32f105_clock.h"
#endif


#include "stm32f105_usbdfs_cdc.h"
#include "stm32f105_usbdfs_macros.h"
#include "el_protocol.h"
#include "flash_mem_chip_spi.h"
#include "spi.h"
#include "string_convertor.h"
#include "user_cmd.h"
#include "watchdog.h"
#include "vehicle.h"
#include "tim.h"
#include "can_override.h"
#include "runtime.h"
#include "can_buffer.h"
#include "extras.h"

#include "lin.h"

#include <string.h>

/****************************************************************
* 											SETTINGS
*****************************************************************/

#define MAIN_TIMER	TIM1


/****************************************************************
* 												Extern vars
*****************************************************************/
extern void process_protocol_cmd(elp_cmd *command);
extern memchip_status memory_chip_status;
extern VehicleStructData theVehicle;
extern uDeviceModel theDeviceModel;
extern u_can_override_status theOverrideStatus;
volatile uint32_t *get_main_tim_sec_ptr(void);
	
/****************************************************************
* 												Functions
*****************************************************************/
	
uint8_t *get_vehicle_settings_data(void);
uint8_t *get_device_modes_data(void);
uint8_t *get_override_settings_data(void);
uint8_t *getCanOverrideStatus_data(void);
can_override_status *getCanOverrideStatus(void);

void set_vehicle_value(uint32_t cmd, uint32_t _value);


void resetCanTimer(TIM_TypeDef * TIM_n);
	
#endif /* MAIN_H_INCLUDED*/
