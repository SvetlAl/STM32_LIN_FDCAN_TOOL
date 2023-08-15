#ifndef CAN_OVERRIDE_H_INCLUDED
#define CAN_OVERRIDE_H_INCLUDED

/****************************************************************
* 
* Can override and scanner functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"

#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif

#include "stm32f105_usbdfs_cdc.h"
#include "can.h"
#include "tim.h"

extern uDeviceModel theDeviceModel;

/****************************************************************************************/
/*************************************** Main format settings. **************************/
/****************************************************************************************/

#define CAN_INJECTION_MEMCHIP_ADDR	FREE_MEMSPACE_ADDRESS
#define MSG_INFO_START_CHAR		'@'

/****************************************************************************************/
/****** User settings customized here. Comment/uncomment unused/used configurations *****/
/****************************************************************************************/

#define MAX_OVERRIDE_FILTERS 16
#define MAX_IGNORED_IDS			 16

#define FOCRED_DELAY_STEP 				10 // 0x3E8 // (100.0) msecs

#define BUFFER_OVERFLOW_CTR_LEVEL_PRCNT 75    // percents
#define BUFFER_OVERFLOW_CTR_LEVEL (CDC_CAN_INJECTION_BUFFER_SIZE*BUFFER_OVERFLOW_CTR_LEVEL_PRCNT)/100

/****************************************************************************************/
/*******************					 Command definitions 								 **********************/
/****************************************************************************************/
	/* @S00000B08#X0
																																							00 - ignored id
																																							01 - override id ------.
																																							  #X1									 |
																																								 00 remove					 |
																																								 01 add ---.				 |
																																									 #X2 <---'				 |
																																									  01 CAN 1				 |
																																										02 CAN 2				 |
																																										  #X3 CAN Id		 |
																																											#X4						 |
																																											#X5						 |
																																											#X6						 |----.
																																											   #X7 flt_msk <    |
																																													  #X8		<-------'
																																														#X9
																																														#XA
																																														#XB
																																														#XC
																																														#XD
																																														#XE
																																														#XF Filter */
																																														
#define OVERRIDE_CMD_BYTE0_IGNORE_ID	(uint8_t)0x00
#define OVERRIDE_CMD_BYTE0_OVERRD_ID	(uint8_t)0x01

#define OVERRIDE_CMD_BYTE1_RMV	(uint8_t)0x00
#define OVERRIDE_CMD_BYTE1_ADD	(uint8_t)0x01

#define OVERRIDE_CMD_BYTE2_CAN1	(uint8_t)0x01
#define OVERRIDE_CMD_BYTE2_CAN2	(uint8_t)0x02


#define DISCARD_MSG 0
#define PROCESS_MSG 1


/* CAN override filter */
typedef struct can_override_filter{	
	can_id id;
	uint8_t override_data[8];
} can_override_filter; //creating new type

/* STATUS CAN override */
typedef struct can_override_status{	
	uint16_t ignored_id_num;
	uint16_t overrided_id_num;
	uint16_t ignored_id_dirs_msk;   // 0 - CAN1, 1 - CAN2
	uint16_t overrided_id_dirs_msk; // 0 - CAN1, 1 - CAN2
	can_override_filter filters[MAX_OVERRIDE_FILTERS];
	can_id ignored_ids[MAX_IGNORED_IDS];
	uint8_t override_msks[MAX_OVERRIDE_FILTERS];
} can_override_status; //creating new type

typedef union u_can_override_status{	
	can_override_status status;
	uint8_t raw_data[sizeof(can_override_status)];
} u_can_override_status; //creating new type


/* Used for serial data trasmission */
typedef struct can_message_info{
	uint8_t start_char; // '@'
	uint8_t can_number;
	uint16_t msec;
	uint32_t seconds;
	can_message msg;
} can_message_info; //creating new type

typedef union can_message_info_raw{
	can_message_info info;
	uint8_t raw_msg_data[24];
}can_message_info_raw;

/* Used for timer settings */
typedef struct can_inj_tim_settings{
	uint16_t ref_seconds;
	uint16_t ref_milseconds;
	uint16_t prescaler;
	uint16_t reloadValue;
} can_inj_tim_settings; //creating new type

/* STATUS CAN injection */
typedef struct can_injection_status{	
	can_message_info_raw msg;                                // current message to inject
	uint32_t current_address;
	can_inj_tim_settings tim_val;// includes the values below
	                             // uint16_t ref_seconds;       previous timestamp second
	                             // uint16_t ref_milseconds;    previous timestamp milsecond
	                             // uint16_t prescaler;         PSC value used for TIM IRQ
	                             // uint16_t reloadValue;       reload value used for TIM IRQ
	
	uint8_t  lower_timer_threshold;
	uint8_t  forced_sec_delay;
	uint16_t forced_msec_delay;
} can_injection_status; //creating new type



//=========================================================================================================
//====================================   The Vehicle global var  ==========================================
//=========================================================================================================

extern can_injection_status theCanInjectionStatus;

/*******************************************************
* 								Override
*******************************************************/
void initModelOverrideSettings(can_override_status *_ovr_status);

/*******************************************************
* 								Injection from memory chip
*******************************************************/

void initMessageInjectionStatus(can_injection_status *_status);
void startMessageInjection(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode);
void stopMessageInjection(void);
void setInjectionMsg(can_injection_status *_status, eDeviceFunctionMode _canInjectionMode);
void setInjectionMsgTimer(can_injection_status *_status);
void injectPresetMessage(can_injection_status *_status,eDeviceFunctionMode _canInjectionMode);
void injection_timer_procedure(void);

/*******************************************************
* 								Injection from USB CDC
*******************************************************/
void CDC_startMessageInjection(void);
void CDC_stopMessageInjection(void);
void CDC_initMessageInjection(void);
void CDC_can_inj_recieve_data( uint8_t *data, uint32_t length);
void CDC_setInjectionMsg(can_injection_status *_status);
void calculate_tim_settings(can_injection_status *_status);
void handle_buffer_overflow(void);




/*******************************************************
* 								Scanner
*******************************************************/
uint32_t can_recieve_and_usb_transmit_msg(CAN_TypeDef* _CAN_TP, TIM_TypeDef* _TIM_TP, uint32_t FifoNo, can_message_info_raw *outup_msg, uint32_t sec);



#endif /* CAN_OVERRIDE_H_INCLUDED*/
