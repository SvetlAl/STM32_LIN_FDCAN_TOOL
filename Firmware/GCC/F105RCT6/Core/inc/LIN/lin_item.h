#ifndef LIN_ITEM_H_INCLUDED
#define LIN_ITEM_H_INCLUDED

#include "device_model.h"

//=========================================================================================================
//============================================ Base LIN unit ==============================================
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

//=========================================================================================================
//========================================== LIN Scanner item =============================================
#define LIN_MSG_INFO_SZ              20U

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


//===========================  Filter masks =======================
//#define LIN_FILTER_MOSI_MSK  0
//#define LIN_FILTER_MISO_MSK  1

//=========================================================================================================
//========================================== LIN filter modes =============================================
#define LIN_FILTER_OFF              0
#define LIN_FILTER_USER_MODE        1
#define LIN_FILTER_MMC_PAJERO_TYRES 2
#define LIN_FILTER_COUNT            3

//=========================================================================================================
//============================================== LIN filter ===============================================

typedef struct lin_filter{
	uint8_t id;  // if id == 0, a filter is disabled
	uint8_t msk; // this mask defines what bytes (1st, 2nd, 3rd....) are to be changed
	uint8_t length; // not used in ui
	uint8_t unused;
	uint8_t data[8];
} lin_filter; //creating new type

typedef union lin_filter_raw {
	lin_filter filter;
	uint8_t data[12];
} lin_filter_raw;


#endif /* LIN_ITEM_H_INCLUDED*/
