//*****************************************************************
//
// Data buffer used to store messages coming from USB host
// for injection into a CAN network
//
//
//*****************************************************************
#ifndef CDC_FLOW_CAN_BUFFER_H_INCLUDED
#define CDC_FLOW_CAN_BUFFER_H_INCLUDED

#include "device_model.h"
#include "can_override.h"

//============== Single buffer modes ======================
/*
#define CDC_CAN_BUF_DEFAULT_MODE (uint32_t)0x00000000000000000000000000000001
#define CDC_CAN_BUF_INIT_MODE    (uint32_t)0x00000000000000000000000000000010
#define CDC_CAN_BUF_FILL_MODE	   (uint32_t)0x00000000000000000000000000000100 // buffer is being filled with data
*/
//============== Dual buffer modes ======================
// 0x0A = DUAL_CCB_A_READ_B_WRITE + DUAL_CCB_INITED_FLAG
#define DUAL_CCB_DEFAULT_MODE        (uint32_t)0x00000000 // 00000000
#define DUAL_CCB_INIT_MODE           (uint32_t)0x00000001 // 00000001 
#define DUAL_CCB_INITED_FLAG         (uint32_t)0x00000002 // 00000010 //
#define DUAL_CCB_INJECTION_STARTED   (uint32_t)0x00000004 // 00000100 
#define DUAL_CCB_A_READ_B_WRITE      (uint32_t)0x00000008 // 00001000 //
#define DUAL_CCB_B_READ_A_WRITE      (uint32_t)0x00000010 // 00010000
#define DUAL_CCB_STOP                (uint32_t)0x00000020 // 00100000

/*
enum cdc_flow_can_buffer_status{
	cdc_flow_buf_fill = (uint8_t)0x00,
  cdc_flow_buf_inject = (uint8_t)0x01
};
*/

typedef struct cdc_flow_can_buffer{
//	uint32_t status;
	
	uint32_t write_pos;
	uint32_t read_pos;
	
	uint8_t data[CDC_CAN_INJECTION_BUFFER_SIZE];
}cdc_flow_can_buffer;


typedef struct dual_cdc_can_buff{
	cdc_flow_can_buffer buffer_A;
	cdc_flow_can_buffer buffer_B;
	uint32_t status;
}dual_cdc_can_buff;



uint32_t init_dual_cc_buf(dual_cdc_can_buff *dbl_buf);
void deinit_dual_cc_buf(dual_cdc_can_buff *dbl_buf);

uint32_t get_ccb_freespace(cdc_flow_can_buffer *buf);
uint32_t get_available_ccb_bytes(cdc_flow_can_buffer *buf);

uint32_t fill_single_cc_buf(cdc_flow_can_buffer *buf, uint8_t *data, uint32_t length);
uint32_t fill_dual_cc_buf(dual_cdc_can_buff *dual_buf, uint8_t *data, uint32_t length);

uint32_t pop_dual_cc_buf_item(can_message_info_raw *msg, dual_cdc_can_buff *dual_buf);
uint32_t pop_single_cc_buf_item(can_message_info_raw *msg, cdc_flow_can_buffer *buf);

uint32_t get_current_READ_buf_read_level(dual_cdc_can_buff *dual_buf);
uint32_t get_current_WRITE_buf_fill_level(dual_cdc_can_buff *dual_buf);

/*
typedef union u_cdc_flow_can_buffer{
}u_cdc_flow_can_buffer;
*/
	
#endif /* CDC_FLOW_CAN_BUFFER_H_INCLUDED*/
