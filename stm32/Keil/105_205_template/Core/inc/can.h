//*****************************************************************
// 
// STM32F105
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************
#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include "can_buffer.h"

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

#define CAN_TX_MAILBOX_0            0
#define CAN_TX_MAILBOX_1            1	
#define CAN_TX_MAILBOX_2            2	
#define ERR_CAN_NO_EMPTY_MAILBOX    4
#define ERR_CAN_TX_ERROR            5
#define ERR_CAN_ARB_ERROR           6
#define CAN_TX_OK                   7
#define CAN_TX_IDLE                 8

#define RQCP_STATUS CAN_TSR_RQCP0
#define ALST_STATUS CAN_TSR_ALST0
#define TERR_STATUS CAN_TSR_TERR0
#define TXOK_STATUS CAN_TSR_TXOK0


#ifdef STM32F205
#define CAN_EMPTY_MAILBOX_TIMEOUT		0xFF // 0xffff
#elif defined(STM32F105)
#define CAN_EMPTY_MAILBOX_TIMEOUT		0xFF
#endif

#define CAN_TRANSMIT_TIMEOUT				0xFF // 0x01
#define CAN_BUFFERED_TRANSMIT_TIMEOUT	0x01 // 0x01
#define CAN_BUFFERED_EMPTY_MAILBOX_TIMEOUT	0xFFFFF // 0x01
#define CAN_BUFFERED_MAILBOX_STATUS_TIMEOUT	0xFFFFF // 0x01


#define CAN_FIFO_0 0	
#define CAN_FIFO_1 1

#define STD_ID	0
#define EXT_ID	1

#define STD_CAN_ID(msg) (uint32_t)((msg->id.std_id.id_highbyte << 8) | msg->id.std_id.id_lowbyte)
#define EXT_CAN_ID(msg) (uint32_t)(msg->id.ext_id)
#define CAN_ID(msg) (uint32_t)(msg->ide == EXT_ID ? EXT_CAN_ID(msg) : STD_CAN_ID(msg))

struct CanBufferStruct; // described in can_buffer.h
struct can_message; // described in can_buffer.h

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



can_btr_setting calculate_baudrate(uint32_t baudRate); 									// Configure CAN1 pins

uint32_t Can1_Init_Pins(uint32_t remapConfig);                      // Configure CAN1 pins
uint32_t Can1_Configure_BaudRate(can_btr_setting _btr_set);         // Configure CAN1 baud rate
uint32_t Can1_Init(uint32_t remapConfig, can_btr_setting _btr_set); // General CAN1 initialization	


uint32_t Can2_Init_Pins(uint32_t remapConfig);                      // Configure CAN2 pins
uint32_t Can2_Configure_BaudRate(can_btr_setting _btr_set);         // Configure CAN2 baud rate
uint32_t Can2_Init(uint32_t remapConfig, can_btr_setting _btr_set); // General CAN2 initialization	


void Can_InitFilters(void);																		// Initialize CAN1 filters
void Can_InitFilters_GatewayTemplate(void);
void Can_Init_Buffers(void);

/******************** CAN1 and CAN2 ******************************/ 

uint32_t Can_SetTxMessage(CAN_TypeDef* _CAN_TP, struct can_message *canMessage, uint32_t mailboxNo);
uint32_t Can_GetEmptyMailbox(CAN_TypeDef* _CAN_TP);
uint32_t Can_Check_FifoPending_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo);
void Can_Recieve_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo, struct can_message *outup_msg);


uint32_t Can_Transmit_Message(CAN_TypeDef* _CAN_TP, struct can_message *canMessage);		// Transmit a CAN message

/******************** Buffered transmission ******************************/ 

void Can_Transmit_BufferedMessage(CAN_TypeDef* _CAN_TP, uint8_t mailbox, struct can_message *canMessage);
can_tx_result check_mailbox_status(CAN_TypeDef* _CAN_TP, uint32_t mailboxNo);
void reset_mailbox_status(CAN_TypeDef* _CAN_TP, uint32_t mailboxNo, uint32_t status);
uint32_t process_buffered_can_tx(void);

uint32_t check_free_buffer_size(uint32_t can_num);

	
#endif /* CAN_H_INCLUDED*/
