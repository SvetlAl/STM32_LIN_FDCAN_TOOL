#ifndef LIN_ITEM_H_INCLUDED
#define LIN_ITEM_H_INCLUDED

#include "device_model.h"

//=======================  General LIN items =====================

#define LIN_ITEM_DEFAULT      (uint8_t)0x00
#define LIN_ITEM_ROLE_MS_DATA (uint8_t)0x01
#define LIN_ITEM_ROLE_MS_RQST (uint8_t)0x02
#define LIN_ITEM_ROLE_SL_DATA (uint8_t)0x03
#define LIN_ITEM_ROLE_MS_IN   (uint8_t)0x04
#define LIN_ITEM_ROLE_SL_IN   (uint8_t)0x05

typedef struct LinItem {
	uint8_t role;
	uint8_t length;
	uint8_t id;
	uint8_t data[9];
} LinItem;

typedef union LinItemRaw {
	LinItem item;
	uint8_t data[12];
} LinItemRaw;


//=======================  LIN scanner items =====================
#define LIN_MSG_INFO_SZ        20

typedef struct lin_message_info{
	uint8_t start_char; // '@'
	uint8_t unused;
	uint16_t msec;
	uint32_t seconds;
	LinItemRaw lin_msg;
} lin_message_info; //creating new type

typedef union lin_message_info_raw{
	lin_message_info info;
	uint8_t raw_msg_data[LIN_MSG_INFO_SZ];
}lin_message_info_raw;

#endif /* LIN_ITEM_H_INCLUDED*/
