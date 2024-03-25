#ifndef LIN_MACROS_H_INCLUDED
#define LIN_MACROS_H_INCLUDED
/*****************************************************************
* 
* LIN
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*
* DEVICE_2CAN:
* USART3 C10 C11 LIN2 wire next to LIN1    Pullup - B0   Slave
* USART2 A2  A3  LIN1 wire next to 2CANH   Pullup - C4   Master
*
******************************************************************/
#include "lin_item.h"

//=========================================================================================================
//============================== Comment/uncomment pre-compiler settings ==================================
#define LIN_DEMO   // A test LIN device
#define LIN1DEBUG

//=========================================================================================================
//============================================== ON/OFF masks =============================================
#define LIN_STATUS_OFF                    (uint8_t)0x00
#define LIN_STATUS_ON                     (uint8_t)0x0F

//=========================================================================================================
//========================================= LIN standart values ===========================================
#define LIN_SYNC_VAL                      (uint8_t)0x55

//=========================================================================================================
//======================================= Application values ==============================================
#define LIN_MASTER_DEFAULT_POLL_PERIOD    (uint16_t)0x2500*2
#define LIN_MAX_RX_BUF_SZ                 (uint8_t) 0x0A // bytes

#define LIN_HDR_SEND_TIMEOUT              (uint32_t)0x0FFF

//=========================================================================================================
//==================================== LIN engine mode masks ==============================================
#define LIN_MODE_DEFAULT                  (uint8_t)0x00
#define LIN_MODE_GATEWAY                  (uint8_t)0x01
#define LIN_MODE_SCANNER                  (uint8_t)0x02
#define LIN_MODE_FILTER                   (uint8_t)0x04
#define LIN_MODE_DEVICE                   (uint8_t)0x08
#define LIN_MODE_ALL                      (uint8_t)(LIN_MODE_GATEWAY | LIN_MODE_SCANNER | LIN_MODE_FILTER | LIN_MODE_DEVICE)

//=========================================================================================================
//==================================== LIN procedure status ===============================================
#define LIN_STATUS_IDLE                   (uint8_t)0x00
#define LIN_STATUS_WAIT_DATA              (uint8_t)0x01
#define LIN_STATUS_READ_DATA              (uint8_t)0x02
#define LIN_STATUS_SEND_DATA              (uint8_t)0x03
#define LIN_STATUS_WAIT_HDR               (uint8_t)0x04
#define LIN_STATUS_WAIT_SYNC              (uint8_t)0x05
#define LIN_STATUS_SEND_HDR               (uint8_t)0x06
#define LIN_STATUS_SEND_SYNC              (uint8_t)0x07
#define LIN_STATUS_STOPPED                (uint8_t)0xFF

//=========================================================================================================
//==================================== LIN baudrate presets ===============================================
#define LIN_1200                          (uint8_t)0x00
#define LIN_2400                          (uint8_t)0x01
#define LIN_4800                          (uint8_t)0x02
#define LIN_9600                          (uint8_t)0x03
#define LIN_19200                         (uint8_t)0x04
#define LIN_38400                         (uint8_t)0x05
#define LIN_57600                         (uint8_t)0x06
#define LIN_115200                        (uint8_t)0x07
#define LIN_921600                        (uint8_t)0x08

//=========================================================================================================
//============================================== Master ===================================================
//=========================================================================================================
typedef struct MasterLin{
	volatile uint8_t status;        // IDLE, WAIT_RESPONSE
	uint8_t usart_num;              // USART 1, 2 or 3....
	
	uint8_t current_id;
	uint8_t rx_cnt;
	
	uint16_t poll_period;           // msecs*10
	uint8_t unused_0;
	uint8_t unused_1;
	
	LinItem process_item;
	
	//=============== Periph links ===============
	USART_TypeDef * usart_ptr;      // USART1, USART2, USART3....
	//================= Polling ==================
	void (*poll)(void);                                     // a procedure that sends periodic requests into a LIN network
	void (*start_polling)(uint16_t poll_period);
	void (*stop_polling)(void);	
	
	void (*send)(LinItem *_item);      	                    // send data/request
	void (*read_out)(LinItemRaw *_item);      	            // send data/request
	
	//============== Device methods ==============
	void (*device_rx)(void);                                // process incoming data in device mode
	void (*device_tx)(void);                                // process outcoming data in device mode

	//============== USART buffer ================
	usart_rx_buffer * _usart_rx_buffer;
	void (*reset)(void);	
} MasterLin;

//=========================================================================================================
//============================================== Slave ====================================================
//=========================================================================================================
typedef struct SlaveLin{
	volatile uint8_t status;       // IDLE, READ_MESSAGE
	uint8_t usart_num;    // USART 1, 2 or 3....
	uint8_t current_id;
	uint8_t rx_cnt;
	LinItem process_item;
	
	//=============== Periph links ===============
	USART_TypeDef * usart_ptr; // USART1, USART2, USART3....
	/* functions */
	//void (*handle_header)(LinFrameHeader _header);
	//void (*send_response)(void);
	
	void (*send)(LinItem *_item);      	                   // send data/request
	void (*read_out)(LinItemRaw *_item);
	
	
	//============== Device methods ==============
	void (*device_rx)(void);                                // process incoming data in device mode
	void (*device_tx)(void);                                // process outcoming data in device mode
	
	/* USART buffer */
	usart_rx_buffer * _usart_rx_buffer;
	void (*reset)(void);
} SlaveLin;


//=========================================================================================================
//===================================== Master + Slave GATEWAY ============================================
//=========================================================================================================
typedef struct GatewayLin{
	volatile uint8_t *mode;
	volatile uint8_t *baudrate_preset;
	volatile uint8_t *filter_preset;
	
	uint8_t (*calculate_crc)(LinItem* _item, uint8_t length);
	void (*reinit_baudrate)(void);
	void (*gateway_filter)(LinItem *item, lin_filter_raw* filter);
	
	TIM_TypeDef* TIM_TP;     // a pointer to a timer, that generates timestamps
	volatile uint32_t *seconds;       // a pointer to timestamps seconds 
	
	lin_filter_raw mosi_filter;
	lin_filter_raw miso_filter;
	MasterLin masterLIN;
	SlaveLin   slaveLIN;
} GatewayLin;


//=========================================================================================================
//======================================= LIN frame header ================================================
typedef struct LinFrameHeaderBits {
	uint8_t ID0 : 1;
	uint8_t ID1 : 1;
	uint8_t ID2 : 1;
	uint8_t ID3 : 1;
	uint8_t ID4 : 1;
	uint8_t ID5 : 1;
	uint8_t P0  : 1;
	uint8_t P1  : 1;
} LinFrameHeaderBits;

#define LIN_FRAME_ID(byte) (uint8_t)(byte &~0xC0)

typedef union LinFrameHeader {
	LinFrameHeaderBits bits;
	uint8_t header;
}LinFrameHeader;

#endif /* LIN_MACROS_H_INCLUDED*/
