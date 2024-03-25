#ifndef CAN_BUFFER_H_INCLUDED
#define CAN_BUFFER_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can_macros.h"

#define CAN1_BUF_NUM              0U
#define CAN2_BUF_NUM              1U
#define CAN_MAX_MAILBOXES_USED    3 //

#define CB_MAILBOX_IDLE  (uint8_t)0x00
#define CB_MAILBOX_BUSY  (uint8_t)0x01
#define CB_MAILBOX_RETRY (uint8_t)0x02

/***************************************************
* 		Buffer structure
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

extern CanBufferStruct CAN_buffer[CAN_INTERFACES_USED];

//=================================================================================================
//=================================== Initialization ==============================================
void can_buffer_init(void);

#endif //CAN_BUFFER_H_INCLUDED
