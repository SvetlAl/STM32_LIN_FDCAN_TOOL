#ifndef CAN_BUFFER_H_INCLUDED
#define CAN_BUFFER_H_INCLUDED

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

#define CAN1_BUF_NUM 0
#define CAN2_BUF_NUM 1
#define CAN_MAX_MAILBOXES_USED 3 //
#define CAN_TX_BUFFER_SIZE 512*2

#define CB_MAILBOX_IDLE  (uint8_t)0x00
#define CB_MAILBOX_BUSY  (uint8_t)0x01
#define CB_MAILBOX_RETRY (uint8_t)0x02

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

/***************************************************
* 		Endpoint structure
***************************************************/

typedef struct CanBufferStruct{
	can_message data[CAN_TX_BUFFER_SIZE];
	CAN_TypeDef* PeriphLink;
	
	uint16_t read_pos;
	uint16_t write_pos;
	uint32_t overrun_cnt;
	uint32_t err_cnt;
	void (*write_item)(can_message *msg);
	void (*read_item)(uint8_t mailbox_num);
	can_message msg[CAN_MAX_MAILBOXES_USED];
	
	uint8_t mailbox_status[CAN_MAX_MAILBOXES_USED];
	uint8_t unused;
	
	uint32_t (*read_free_size)(void);	
} CanBufferStruct; //creating new type

#ifdef CAN_TX_BUFFER_ENABLED
extern CanBufferStruct CAN_buffer[CAN_INTERFACES_USED];
#endif

void initCanBuffers(void);

/************ Write ************/
void write_can_msg (can_message *msg, CanBufferStruct* buf);

void write_can1_buffer (can_message *msg);
void write_can2_buffer (can_message *msg);
/************ Read ************/
void read_can_msg(CanBufferStruct* buf,uint8_t mailbox_num);

void read_can1_buffer(uint8_t mailbox_num);
void read_can2_buffer(uint8_t mailbox_num);

/************ Freesize ************/
uint32_t read_can_buf_free_size(CanBufferStruct* buf);	

uint32_t read_can1_buf_free_size(void);	
uint32_t read_can2_buf_free_size(void);	



#endif //CAN_BUFFER_H_INCLUDED
