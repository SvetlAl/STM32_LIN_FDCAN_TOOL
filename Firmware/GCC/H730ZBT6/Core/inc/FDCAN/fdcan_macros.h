#ifndef FDCAN_MACROS_H_INCLUDED
#define FDCAN_MACROS_H_INCLUDED

/****************************************************************
*
* FD CAN
*
* Structures
* Macros
* Defs
*
*
*****************************************************************/

#include "device_model.h"
#include "fdcan_ram_config.h"

#if defined BOARD_MK_STM32H730
#include "stm32h730xx.h"
#endif

//=========================================================================================================
//===================================  FDCAN 1/2 enumeration   ============================================

#define FDCAN1_E             0  // FD CAN 1 array pos
#define FDCAN2_E             1  // FD CAN 2 array pos

#define FDCANC_E             CAN_INTERFACES_USED //2  // FD CAN count. Two CANs used

//=========================================================================================================
//=============================  FDCAN configuration structures and defs   ================================

typedef struct fdcan_cccr_config {
	uint8_t ASM   : 1; //0x01
	uint8_t DAR   : 1; //0x02
	uint8_t FDOE  : 1; //0x04
	uint8_t BRSE  : 1; //0x08
	uint8_t PXHD  : 1; //0x10
	uint8_t EFBI  : 1; //0x20
	uint8_t TXP   : 1; //0x40
	uint8_t NISO  : 1; //0x80
} fdcan_cccr_config;

//==================================  FDCAN configuration flags position   ================================
#define FDCAN_SETTINGS_CCCR_CFG_ASM_POS                             (uint32_t)0x01
#define FDCAN_SETTINGS_CCCR_CFG_DAR_POS                             (uint32_t)0x02
#define FDCAN_SETTINGS_CCCR_CFG_FDOE_POS                            (uint32_t)0x04
#define FDCAN_SETTINGS_CCCR_CFG_BRSE_POS                            (uint32_t)0x08
#define FDCAN_SETTINGS_CCCR_CFG_PXHD_POS                            (uint32_t)0x10
#define FDCAN_SETTINGS_CCCR_CFG_EFBI_POS                            (uint32_t)0x20
#define FDCAN_SETTINGS_CCCR_CFG_TXP_POS                             (uint32_t)0x40
#define FDCAN_SETTINGS_CCCR_CFG_NISO_POS                            (uint32_t)0x80

//====================================  Is a config flag set   ============================================
#define FDCAN_SETTINGS_CCCR_CFG_ASM(BYTE)                            BYTE & FDCAN_SETTINGS_CCCR_CFG_ASM_POS
#define FDCAN_SETTINGS_CCCR_CFG_DAR(BYTE)                            BYTE & FDCAN_SETTINGS_CCCR_CFG_DAR_POS
#define FDCAN_SETTINGS_CCCR_CFG_FDOE(BYTE)                           BYTE & FDCAN_SETTINGS_CCCR_CFG_FDOE_POS
#define FDCAN_SETTINGS_CCCR_CFG_BRSE(BYTE)                           BYTE & FDCAN_SETTINGS_CCCR_CFG_BRSE_POS
#define FDCAN_SETTINGS_CCCR_CFG_PXHD(BYTE)                           BYTE & FDCAN_SETTINGS_CCCR_CFG_PXHD_POS
#define FDCAN_SETTINGS_CCCR_CFG_EFBI(BYTE)                           BYTE & FDCAN_SETTINGS_CCCR_CFG_EFBI_POS
#define FDCAN_SETTINGS_CCCR_CFG_TXP(BYTE)                            BYTE & FDCAN_SETTINGS_CCCR_CFG_TXP_POS
#define FDCAN_SETTINGS_CCCR_CFG_NISO(BYTE)                           BYTE & FDCAN_SETTINGS_CCCR_CFG_NISO_POS

//====================================  Set a config flag   ===============================================
#define FDCAN_SETTINGS_CCCR_CFG_SET_ASM(BYTE)                        BYTE |= FDCAN_SETTINGS_CCCR_CFG_ASM_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_DAR(BYTE)                        BYTE |= FDCAN_SETTINGS_CCCR_CFG_DAR_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_FDOE(BYTE)                       BYTE |= FDCAN_SETTINGS_CCCR_CFG_FDOE_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_BRSE(BYTE)                       BYTE |= FDCAN_SETTINGS_CCCR_CFG_BRSE_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_PXHD(BYTE)                       BYTE |= FDCAN_SETTINGS_CCCR_CFG_PXHD_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_EFBI(BYTE)                       BYTE |= FDCAN_SETTINGS_CCCR_CFG_EFBI_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_TXP(BYTE)                        BYTE |= FDCAN_SETTINGS_CCCR_CFG_TXP_POS
#define FDCAN_SETTINGS_CCCR_CFG_SET_NISO(BYTE)                       BYTE |= FDCAN_SETTINGS_CCCR_CFG_NISO_POS

//====================================  Reset a config flag   =============================================
#define FDCAN_SETTINGS_CCCR_CFG_RST_ASM(BYTE)                        (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_ASM_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_DAR(BYTE)                        (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_DAR_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_FDOE(BYTE)                       (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_FDOE_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_BRSE(BYTE)                       (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_BRSE_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_PXHD(BYTE)                       (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_PXHD_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_EFBI(BYTE)                       (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_EFBI_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_TXP(BYTE)                        (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_TXP_POS)
#define FDCAN_SETTINGS_CCCR_CFG_RST_NISO(BYTE)                       (BYTE &= ~FDCAN_SETTINGS_CCCR_CFG_NISO_POS)

//====================  FDCAN CCCR register and bitrate configuration structure  ==========================
typedef union u_fdcan_cccr_config{
    fdcan_cccr_config cfg;
    uint8_t byte;
}u_fdcan_cccr_config;

typedef struct fdcan_bitrate_config {
	uint8_t PSC;
	uint8_t TSEG1;
	uint8_t TSEG2;
	uint8_t SJW;
} fdcan_bitrate_config;

//=========================================================================================================
//======================================  FDCAN bitrates macroses   =======================================

#define FDCAN_SETTINGS_BITRATE_PSC_POS                            (uint32_t)0x00
#define FDCAN_SETTINGS_BITRATE_TSEG1_POS                          (uint32_t)0x01
#define FDCAN_SETTINGS_BITRATE_TSEG2_POS                          (uint32_t)0x02
#define FDCAN_SETTINGS_BITRATE_SJW_POS                            (uint32_t)0x03

#define FDCAN_SETTINGS_NOM_BITRATE_OFFST                          (uint32_t)0x00
#define FDCAN_SETTINGS_NOM_BITRATE_SIZE                           sizeof(fdcan_bitrate_config)
#define FDCAN_SETTINGS_NOM_BITRATE_ADDR(can_num)                  FDCAN_SETTINGS_NOM_BITRATE_OFFST + (can_num * FDCAN_SETTINGS_NOM_BITRATE_SIZE)
#define FDCAN_SETTINGS_NOM_BITRATE(can_num, pos)                  FDCAN_SETTINGS_NOM_BITRATE_ADDR(can_num) + pos

#define FDCAN_SETTINGS_DAT_BITRATE_OFFST                          FDCAN_SETTINGS_NOM_BITRATE_OFFST + (FDCAN_SETTINGS_NOM_BITRATE_SIZE*2)
#define FDCAN_SETTINGS_DAT_BITRATE_SIZE                           sizeof(fdcan_bitrate_config)
#define FDCAN_SETTINGS_DAT_BITRATE_ADDR(can_num)                  FDCAN_SETTINGS_DAT_BITRATE_OFFST + (can_num * FDCAN_SETTINGS_DAT_BITRATE_SIZE)
#define FDCAN_SETTINGS_DAT_BITRATE(can_num, pos)                  FDCAN_SETTINGS_DAT_BITRATE_ADDR(can_num) + pos

#define FDCAN_SETTINGS_CCCR_CFG_OFFST                             FDCAN_SETTINGS_DAT_BITRATE_OFFST + (FDCAN_SETTINGS_DAT_BITRATE_SIZE*2)
#define FDCAN_SETTINGS_CCCR_CFG_SIZE                              sizeof(fdcan_cccr_config)
#define FDCAN_SETTINGS_CCCR_CFG_ADDR(can_num)                     FDCAN_SETTINGS_CCCR_CFG_OFFST + (can_num * FDCAN_SETTINGS_CCCR_CFG_SIZE)
#define FDCAN_SETTINGS_CCCR_CFG(can_num)                          FDCAN_SETTINGS_CCCR_CFG_ADDR(can_num)

typedef struct fdcan_settings{
	fdcan_bitrate_config nominal_bitrate[2];
	fdcan_bitrate_config data_bitrate[2];
	u_fdcan_cccr_config cccr_cfg[2];
} fdcan_settings;

typedef union u_fdcan_settings{
	fdcan_settings settings;
	uint8_t raw_data[sizeof(fdcan_settings)];
}u_fdcan_settings;

//=========================================================================================================
//======================================      FDCAN messages        =======================================
typedef struct fdcan_msg_flags {
    uint8_t ESI        : 1; // 0x01
    uint8_t XTD        : 1; // 0x02
    uint8_t FDF        : 1; // 0x04
    uint8_t BRS        : 1; // 0x08
    uint8_t unused4    : 1;
    uint8_t unused5    : 1;
    uint8_t unused6    : 1;
    uint8_t unused7    : 1;
} fdcan_msg_flags;

typedef union u_fdcan_flags{
    fdcan_msg_flags flags;
    uint8_t byte;
}u_fdcan_flags;

typedef struct fdcan_message_hdr{
    uint32_t id;
    uint8_t dlc;
    u_fdcan_flags fdflags;
    uint16_t rxts;
}fdcan_message_hdr;

typedef union u_fdcan_message_hdr{
    fdcan_message_hdr msg_hdr;
    uint8_t data[sizeof(fdcan_message_hdr)];
}u_fdcan_message_hdr;

typedef struct fdcan_message_info{
    uint8_t start_char; // '#'
    uint8_t can_number;
    uint16_t msec;
    uint32_t seconds;
    u_fdcan_message_hdr msg;
} fdcan_message_info;

typedef union fdcan_message_info_raw{
    fdcan_message_info info;
    uint8_t raw_msg_data[sizeof(fdcan_message_info)];
}fdcan_message_info_raw;


typedef struct fdcan_message_info_short{
    uint8_t start_char; // '#'
    uint8_t can_number;
    uint16_t msec;
    uint32_t seconds;
} fdcan_message_info_short;

typedef union u_fdcan_message_info_short{
    fdcan_message_info_short info_short;
    uint8_t raw_msg_data[sizeof(fdcan_message_info_short)];
}u_fdcan_message_info_short;


#define FDCAN_FLAG_RST 0x00
#define FDCAN_FLAG_SET 0x01

#define FDCAN_IS_MSG_ESI(msg_hdr) msg_hdr->fdflags.flags.ESI ? FDCAN_FLAG_SET : FDCAN_FLAG_RST
#define FDCAN_IS_MSG_XTD(msg_hdr) msg_hdr->fdflags.flags.XTD ? FDCAN_FLAG_SET : FDCAN_FLAG_RST
#define FDCAN_IS_MSG_FDF(msg_hdr) msg_hdr->fdflags.flags.FDF ? FDCAN_FLAG_SET : FDCAN_FLAG_RST
#define FDCAN_IS_MSG_BRS(msg_hdr) msg_hdr->fdflags.flags.BRS ? FDCAN_FLAG_SET : FDCAN_FLAG_RST

#define FDCAN_SET_MSG_ESI(msg_hdr, val) msg_hdr->fdflags.flags.ESI = (val == FDCAN_FLAG_RST) ? FDCAN_FLAG_RST : (val == FDCAN_FLAG_SET) ? FDCAN_FLAG_SET : msg_hdr->fdflags.flags.ESI
#define FDCAN_SET_MSG_XTD(msg_hdr, val) msg_hdr->fdflags.flags.XTD = (val == FDCAN_FLAG_RST) ? FDCAN_FLAG_RST : (val == FDCAN_FLAG_SET) ? FDCAN_FLAG_SET : msg_hdr->fdflags.flags.XTD
#define FDCAN_SET_MSG_FDF(msg_hdr, val) msg_hdr->fdflags.flags.FDF = (val == FDCAN_FLAG_RST) ? FDCAN_FLAG_RST : (val == FDCAN_FLAG_SET) ? FDCAN_FLAG_SET : msg_hdr->fdflags.flags.FDF
#define FDCAN_SET_MSG_BRS(msg_hdr, val) msg_hdr->fdflags.flags.BRS = (val == FDCAN_FLAG_RST) ? FDCAN_FLAG_RST : (val == FDCAN_FLAG_SET) ? FDCAN_FLAG_SET : msg_hdr->fdflags.flags.BRS


#define FDCAN_FD_MSG_LENGTH(msg_hdr)    (msg_hdr->dlc == 0x08) ? 8 :   \
                                        (msg_hdr->dlc == 0x09) ? 12 : \
                                        (msg_hdr->dlc == 0x0A) ? 16 : \
                                        (msg_hdr->dlc == 0x0B) ? 20 : \
                                        (msg_hdr->dlc == 0x0C) ? 24 : \
                                        (msg_hdr->dlc == 0x0D) ? 32 : \
                                        (msg_hdr->dlc == 0x0E) ? 48 : \
                                        (msg_hdr->dlc == 0x0F) ? 64 : \
                                        (msg_hdr->dlc == 0x07) ? 7 : \
                                        (msg_hdr->dlc == 0x06) ? 6 : \
                                        (msg_hdr->dlc == 0x05) ? 5 : \
                                        (msg_hdr->dlc == 0x04) ? 4 : \
                                        (msg_hdr->dlc == 0x03) ? 3 : \
                                        (msg_hdr->dlc == 0x02) ? 2 : \
                                        (msg_hdr->dlc == 0x01) ? 1 : 0


#define FDCAN_STD_MSG_LENGTH(msg_hdr)     (msg_hdr->dlc == 0x08) ? 8 : \
                                          (msg_hdr->dlc == 0x07) ? 7 : \
                                          (msg_hdr->dlc == 0x06) ? 6 : \
                                          (msg_hdr->dlc == 0x05) ? 5 : \
                                          (msg_hdr->dlc == 0x04) ? 4 : \
                                          (msg_hdr->dlc == 0x03) ? 3 : \
                                          (msg_hdr->dlc == 0x02) ? 2 : \
                                          (msg_hdr->dlc == 0x01) ? 1 : \
                                          (msg_hdr->dlc == 0x00) ? 0 : 8

#define FDCAN_MSG_LENGTH(msg_hdr) (FDCAN_IS_MSG_FDF(msg_hdr) == FDCAN_FLAG_SET) ? FDCAN_FD_MSG_LENGTH(msg_hdr) : FDCAN_STD_MSG_LENGTH(msg_hdr)


//=========================================================================================================
//======================================       FDCAN buffers        =======================================
//================   RX/TX buffers are the same structures, but different size  ===========================
#define FDCAN_BUFFER_LOCK_TIMEOUT       0xFFFF
#define FDCAN_BUFFER_STS_FREE           0x00
#define FDCAN_BUFFER_W_STS_LOCKED       0x01
#define FDCAN_BUFFER_R_STS_LOCKED       0x02


#define FDCAN_BUFFER_STS_FAIL           0xFF

typedef struct fdcan_buffer{
	uint16_t read_pos;
	uint16_t write_pos;
	uint8_t overrun_cnt;
	uint8_t err_cnt;
	uint16_t max_size;
	uint16_t status;
	uint16_t tmp_write_pos;
	uint8_t *data;
} fdcan_buffer; //creating new type

typedef struct fdcan_buffers{
	fdcan_buffer buf[FDCANC_E];
} fdcan_buffers; //creating new type

//======================================      FDCAN RAM element     ======================================																																	
typedef struct fdcan_fifo_element{
	uint32_t word[FDCAN_TX_FIFO_EL_W_SIZE];
}fdcan_fifo_element;

typedef union u_fdcan_fifo_element{
	fdcan_fifo_element word_arr;
	uint8_t data[sizeof(fdcan_fifo_element)];
}u_fdcan_fifo_element;

//======================================      FDCAN Filter          ======================================
typedef enum{
	FDCAN_filter_status_default = (uint8_t)0x00, // off
	FDCAN_filter_status_on      = (uint8_t)0x01  // on
} eFdcanFilterStatus;

typedef enum{
	FDCAN_filter_dir_1i2o = (uint8_t)0x00, // From FDCAN1 to FDCAN2
	FDCAN_filter_dir_2i1o = (uint8_t)0x01, // From FDCAN2 to FDCAN1
	FDCAN_filter_dir_both = (uint8_t)0x02  // From FDCAN1 to FDCAN2 and from FDCAN2 to FDCAN1
} eFdcanFilterDir;

typedef struct fdcan_filter_hdr{
	uint32_t id_begin;
	uint32_t id_end;
	eFdcanFilterDir input_dir;
	eFdcanFilterStatus status;
	
	uint8_t unused0;
	uint8_t unused1;
}fdcan_filter_hdr;

typedef enum{
	FDCAN_filter_method_default = (uint8_t)0x00,  // off
	FDCAN_filter_method_inc     = (uint8_t)0x01,  // increment
	FDCAN_filter_method_dec     = (uint8_t)0x02,  // decrement
	FDCAN_filter_method_const   = (uint8_t)0x03   // const
} eFdcanByteFilterMethod;

typedef struct fdcan_filter_byte{
	eFdcanByteFilterMethod method;
	uint8_t from_value;
	uint8_t to_value;
	uint8_t step;
	uint8_t tmp;
}fdcan_filter_byte;

typedef struct fdcan_filter{
	fdcan_filter_hdr hdr;
	fdcan_filter_byte filter_byte[64];
}fdcan_filter;

typedef union u_fdcan_filter{
	fdcan_filter filter;
	uint8_t data[sizeof(fdcan_filter)];
}u_fdcan_filter;






#endif
