//*****************************************************************
// 
// STM32F105
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************
#ifndef CAN_MACROS_H_INCLUDED
#define CAN_MACROS_H_INCLUDED

#include "device_model.h"

#define CAN_FIFO_0         0U	
#define CAN_FIFO_1         1U

#define STD_ID             0U
#define EXT_ID             1U

#define STD_CAN_ID(msg) (uint32_t)((msg->id.std_id.id_highbyte << 8) | msg->id.std_id.id_lowbyte)
#define EXT_CAN_ID(msg) (uint32_t)(msg->id.ext_id)
#define CAN_ID(msg) (uint32_t)(msg->ide == EXT_ID ? EXT_CAN_ID(msg) : STD_CAN_ID(msg))

/***************************************************
* 		CAN message
***************************************************/
typedef struct std_can_id{
	uint8_t id_highbyte;	// First number of an id 					(BXX)
	uint8_t id_lowbyte; 	// Second, third numbers of an id (XBB)
	uint16_t unused;		
}std_can_id;

typedef union can_id{
	std_can_id std_id;
	uint32_t ext_id;
}can_id;

// Structure of a  CAN message 
typedef struct can_message{	
	can_id id;
	uint16_t ide;
	uint16_t dlc;					// Message size, number of bytes
	uint8_t data[8];			// Data
} can_message; //creating new type

typedef struct can_btr_setting{
	uint8_t psc;	
	uint8_t bs1;
	uint8_t bs2;
	uint8_t sjw;	
}can_btr_setting;

typedef union{
	struct{
		uint8_t rqcp : 1;
		uint8_t txok : 1;
		uint8_t alst : 1;
		uint8_t terr : 1;
		uint8_t unused4 : 1;
		uint8_t unused5 : 1;
		uint8_t unused6 : 1;
		uint8_t unused7 : 1;
  }u;
  uint8_t result;
}can_tx_result;


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




#endif /* CAN_MACROS_H_INCLUDED*/
