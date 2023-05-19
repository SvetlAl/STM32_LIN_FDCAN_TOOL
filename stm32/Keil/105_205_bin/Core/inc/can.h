//*****************************************************************
// 
// STM32F105
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************
#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

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


#define NO_REMAP_CAN1								0
#define REMAP_CAN1									1
#define NO_REMAP_CAN2								0
#define REMAP_CAN2									1
#define CAN_INIT_TIMEOUT_MAX	    	0xfff
#define CAN_BAUDRATE_1000KB    	  	1000
#define CAN_BAUDRATE_500KB    	  	500
#define CAN_BAUDRATE_250KB    	  	250
#define CAN_BAUDRATE_125KB    	  	125
#define CAN_BAUDRATE_83KB    	  	  83

#define CAN_TX_MAILBOX_0 					0
#define CAN_TX_MAILBOX_1 					1	
#define CAN_TX_MAILBOX_2 					2	

#ifdef STM32F205
#define CAN_EMPTY_MAILBOX_TIMEOUT		0xFF // 0xffff
#elif defined(STM32F105)
#define CAN_EMPTY_MAILBOX_TIMEOUT		0xFF
#endif

#define CAN_TRANSMIT_TIMEOUT				0xFF // 0x01
#define ERR_CAN_NO_EMPTY_MAILBOX		4
#define CAN_TX_OK										5


#define CAN_FIFO_0 0	
#define CAN_FIFO_1 1

#define STD_ID	0
#define EXT_ID	1

#define STD_CAN_ID(msg) (uint32_t)((msg->id.std_id.id_highbyte << 8) | msg->id.std_id.id_lowbyte)
#define EXT_CAN_ID(msg) (uint32_t)(msg->id.ext_id)
#define CAN_ID(msg) (uint32_t)(msg->ide == EXT_ID ? EXT_CAN_ID(msg) : STD_CAN_ID(msg))


typedef struct can_btr_setting{
	uint32_t psc;	
	uint32_t bs1;
	uint32_t bs2;		
}can_btr_setting;

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


can_btr_setting calculate_baudrate(uint32_t baudRate); 									// Configure CAN1 pins

uint32_t Can1_Init_Pins(uint32_t remapConfig); 									// Configure CAN1 pins
uint32_t Can1_Configure_BaudRate(uint32_t baudRate);			// Configure CAN1 baud rate
uint32_t Can1_Init(uint32_t remapConfig, uint32_t baudRate);		// General CAN1 initialization	


uint32_t Can2_Init_Pins(uint32_t remapConfig); 									// Configure CAN2 pins
uint32_t Can2_Configure_BaudRate(uint32_t baudRate);						// Configure CAN2 baud rate
uint32_t Can2_Init(uint32_t remapConfig, uint32_t baudRate);		// General CAN2 initialization	


void Can_InitFilters(void);																		// Initialize CAN1 filters
void Can_InitFilters_GatewayTemplate(void);


/******************** CAN1 and CAN2 ******************************/ 
uint32_t Can_SetTxMessage(CAN_TypeDef* _CAN_TP, can_message *canMessage, uint32_t mailboxNo);
uint32_t Can_GetEmptyMailbox(CAN_TypeDef* _CAN_TP);
uint32_t Can_Transmit_Message(CAN_TypeDef* _CAN_TP, can_message *canMessage);		// Transmit a CAN message
uint32_t Can_Check_FifoPending_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo);
void Can_Recieve_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo, can_message *outup_msg);
	
#endif /* CAN_H_INCLUDED*/
