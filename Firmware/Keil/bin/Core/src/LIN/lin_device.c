/****************************************************************
* 
* LIN device
* 
* Defines LIN device behaviour
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/

#include "LIN/lin_device.h"
#include "string_convertor.h"
#include "USB_CDC/stm32f105_usbdfs_cdc.h"

#define LIN_ITEM(it_raw)     it_raw->info.lin_msg.item
#define LIN_ITEM_RAW(it_raw) it_raw->info.lin_msg


/**
* brief  This is a demo function. Reports received data via USB
* param  
* retval 
*/
void lin_device_report(lin_message_info_raw *_item){
	#ifdef LIN_DEVICE_SUPPORT
	if(LIN_ITEM(_item).role == LIN_ITEM_ROLE_MS_IN){
					/************ DEFAULT DEMO *************/
		uint8_t data_byte_cnt = (uint8_t)(LIN_ITEM(_item).length + 1);
		uint8_t demo_report[128];
		uint8_t i = 0;
		demo_report[i++] = 'M';
		demo_report[i++] = 'a';
		demo_report[i++] = 's';
		demo_report[i++] = 't';
		demo_report[i++] = 'e';
		demo_report[i++] = 'r';
		demo_report[i++] = ' ';
		demo_report[i++] = 'r';
		demo_report[i++] = 'e';
		demo_report[i++] = 'c';
		demo_report[i++] = 'e';
		demo_report[i++] = 'i';
		demo_report[i++] = 'v';
		demo_report[i++] = 'e';
		demo_report[i++] = 'd';
		demo_report[i++] = ' ';
		demo_report[i++] = 'i';
		demo_report[i++] = 'd';
		demo_report[i++] = ' ';
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).id >> 4) &~0xF0) );
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).id >> 0) &~0xF0) );
		demo_report[i++] = ' ';
		demo_report[i++] = 'l';
		demo_report[i++] = 'n';
		demo_report[i++] = 'g';
		demo_report[i++] = 't';
		demo_report[i++] = 'h';
		demo_report[i++] = ' ';
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).length >> 4) &~0xF0) );
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).length >> 0) &~0xF0) );
		demo_report[i++] = ' ';
		demo_report[i++] = 'd';
		demo_report[i++] = 'a';
		demo_report[i++] = 't';
		demo_report[i++] = 'a';
		demo_report[i++] = ' ';
		
		uint8_t message_data_pos = 0;
		while(message_data_pos < (data_byte_cnt)){
			demo_report[i++] = ' ';
			demo_report[i++] = '0';
			demo_report[i++] = 'x';
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).data[message_data_pos] >> 4) &~0xF0) );
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).data[message_data_pos++] >> 0) &~0xF0) );
			demo_report[i++] = ' ';
		}
		while( i < 127){
			demo_report[i++] = ' ';
		}
		demo_report[126] = 0x0A;
		demo_report[127] = 0x0A;	
		USB_CDC_send_data(demo_report, 128);

	}
	else if(LIN_ITEM(_item).role == LIN_ITEM_ROLE_SL_IN){
			/************ DEFAULT DEMO *************/
		uint8_t data_byte_cnt = (uint8_t)(LIN_ITEM(_item).length + 1);
		uint8_t demo_report[128];
		uint8_t i = 0;
		demo_report[i++] = 'S';
		demo_report[i++] = 'l';
		demo_report[i++] = 'a';
		demo_report[i++] = 'v';
		demo_report[i++] = 'e';
		demo_report[i++] = ' ';
		demo_report[i++] = 'r';
		demo_report[i++] = 'e';
		demo_report[i++] = 'c';
		demo_report[i++] = 'e';
		demo_report[i++] = 'i';
		demo_report[i++] = 'v';
		demo_report[i++] = 'e';
		demo_report[i++] = 'd';
		demo_report[i++] = ' ';
		demo_report[i++] = 'i';
		demo_report[i++] = 'd';
		demo_report[i++] = ' ';
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).id >> 4) &~0xF0) );
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).id >> 0) &~0xF0) );
		demo_report[i++] = ' ';
		demo_report[i++] = 'l';
		demo_report[i++] = 'n';
		demo_report[i++] = 'g';
		demo_report[i++] = 't';
		demo_report[i++] = 'h';
		demo_report[i++] = ' ';
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).length >> 4) &~0xF0) );
		demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).length >> 0) &~0xF0) );
		demo_report[i++] = ' ';
		demo_report[i++] = 'd';
		demo_report[i++] = 'a';
		demo_report[i++] = 't';
		demo_report[i++] = 'a';
		demo_report[i++] = ' ';
		
		uint8_t message_data_pos = 0;
		while(message_data_pos < (data_byte_cnt)){
			demo_report[i++] = ' ';
			demo_report[i++] = '0';
			demo_report[i++] = 'x';
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).data[message_data_pos] >> 4) &~0xF0) );
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((LIN_ITEM(_item).data[message_data_pos++] >> 0) &~0xF0) );
			demo_report[i++] = ' ';
		}
		while( i < 127){
			demo_report[i++] = ' ';
		}
		demo_report[126] = 0x0A;
		demo_report[127] = 0x0A;	
		USB_CDC_send_data(demo_report, 128);
	}
		/************ DEFAULT DEMO *************/
		#else
		(void)_item;
		#endif
}


#ifdef LIN_DEVICE_SUPPORT
/**
* brief  This is a service function for demo mode, increases broadcasted id
* param  
* retval 
*/
static void lin_device_increment_master_id(void){
	gatewayLIN.masterLIN.current_id = (uint8_t) (gatewayLIN.masterLIN.current_id + 1);
	if(gatewayLIN.masterLIN.current_id == 0x40) gatewayLIN.masterLIN.current_id = 0x01;
}
#endif


/**
* brief  Master behaviour on transmit
* param  
* retval 
*/
void lin_device_master_tx(){
	#ifdef LIN_DEVICE_SUPPORT
	LinItem tx_message;
	tx_message.id = gatewayLIN.masterLIN.current_id;
	
	/************ DEFAULT DEMO *************/
	
	// Send test data with id's 0x3A and 0x02
	if((gatewayLIN.masterLIN.current_id == 0x3A) | (gatewayLIN.masterLIN.current_id == 0x02)){
		tx_message.role = LIN_ITEM_ROLE_MS_DATA;
		tx_message.length = (tx_message.id < 0x20) ? 2 : (tx_message.id < 0x30) ? 4 : 8;
		for(uint8_t i = 0; i < tx_message.length; i++){
			tx_message.data[i] = i; 
		}
		tx_message.data[tx_message.length] = gatewayLIN.calculate_crc(&tx_message, tx_message.length); 
		// master_schedule_item(&tx_message);
	}
	// Send requests with all other id's
	else{
		tx_message.role = LIN_ITEM_ROLE_MS_RQST;
		gatewayLIN.masterLIN._usart_rx_buffer->write(&tx_message.id, 1);
	}
	
	master_schedule_item(&tx_message);
	
	lin_device_increment_master_id();
	/************ DEFAULT DEMO *************/
	#endif
}


/**
* brief  Master behaviour on receive
* param  
* retval 
*/
void lin_device_slave_rx(){
	#ifdef LIN_DEVICE_SUPPORT
	//====================== Slave reads a data ======================
	if((gatewayLIN.slaveLIN.current_id == 0x3A) | (gatewayLIN.slaveLIN.current_id == 0x02)){
		gatewayLIN.slaveLIN.rx_cnt = (gatewayLIN.slaveLIN.current_id < 0x20) ? 2 : (gatewayLIN.slaveLIN.current_id < 0x30) ? 4 : 8;
		gatewayLIN.slaveLIN.rx_cnt = (uint8_t)(gatewayLIN.slaveLIN.rx_cnt + 1); //crc
		gatewayLIN.slaveLIN.status = LIN_STATUS_WAIT_DATA;
	}
	
	//====================== Slave sends a response ======================
	else if((gatewayLIN.slaveLIN.current_id == 0x1A) | (gatewayLIN.slaveLIN.current_id == 0x2A) | (gatewayLIN.slaveLIN.current_id == 0x03)){
		LinItem slave_data;
		slave_data.role = LIN_ITEM_ROLE_SL_DATA;
		slave_data.id = gatewayLIN.slaveLIN.current_id;
		slave_data.length = (gatewayLIN.slaveLIN.current_id < 0x20) ? 2 : (gatewayLIN.slaveLIN.current_id < 0x30) ? 4 : 8;
		
		for(uint8_t i = 0; i < slave_data.length; i++){
			slave_data.data[i] = gatewayLIN.slaveLIN.current_id;
		}
		slave_data.data[slave_data.length] = gatewayLIN.calculate_crc(&slave_data, slave_data.length);
		slave_schedule_item(&slave_data);
	}
	else 
	gatewayLIN.slaveLIN.status = LIN_STATUS_IDLE;
	#endif
}

