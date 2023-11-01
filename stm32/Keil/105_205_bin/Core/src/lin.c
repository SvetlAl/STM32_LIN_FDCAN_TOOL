/****************************************************************************
* 	LIN BUS
*
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
* ===========================================================================
* ================================== Start ==================================
* ===========================================================================
*
* I.   After USART is inited start LIN with "enable_lin" function
*
* II.  Then "reset"/"set_lin_mode". Available modes: gateway, filter, device, scanner.
*
* ===========================================================================
* ================================= Operation ===============================
* ===========================================================================
*
* Change baudrate with lin_select_spd(uint8_t preset).
*
* Change master poll period with set_poll_period(uint16_t period).
*
* Change LIN mode with "reset"/"set_lin_mode". Available modes: gateway, filter, device, scanner.
*
* ===========================================================================
* ================================= Process =================================
* ===========================================================================
*
* @DEVICE mode explanation
*  !!! This mode is incompatible with use together with the other modes !!!
*  Master TX device is sending messages (data or requests) in TIMX_IRQHandler interrupt with a period defined in "GatewayLin.MasterLin.poll_period".
*  Master TX message transimssion is run in "gatewayLIN.masterLIN.poll()".
*                                                                       ==> poll procedure is defined in "__WEAK void master_poll()"
*                                                                                                                                  ==> master device tx procedure is defined "__WEAK void master_device_tx()"
*                                                                                                                                  in default demonstration a device is sending:
*                                                                                                                                  ID range 0x01 to 0x3F  (except 0x02 and 0x3A) REQUESTS
*                                                                                                                                  ID's 0x02 DATA 0x00, 0x01, CRC
*                                                                                                                                  ID's 0x3A DATA 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 CRC
*
*                                                                                                                                  In the first place, a message is scheduled in IRQ,
*                                                                                                                                  then the USART transmission is done in "process_lin_engine()" in the main loop
*
*
*  Master RX procedure is processed in USARTX_IRQHandler. If Master is waiting for slave response, incoming data is written into RX buffer, and then processed in "process_lin_engine()" in the main loop while(1)
*
*
*
*
*  Slave RX procedure is processed in USARTX_IRQHandler.
*                                                      ==> first, if LIN break detected, Slave goes into a wait-state for a master header. LIN_STATUS_WAIT_HDR flag on.
*                                                            ==> if a header is recieved, "__WEAK void slave_device_rx()" function processes the data. In device demonstration mode
*                                                                Slave ignores all id's exept 0x1A, 0x2A and 0x3A. If the id 0x1A and 0x2A recieved, Slave sends back a dummy response.
*                                                                For example. if the id is 0x3A, It keeps recieveing data with a flag LIN_STATUS_WAIT_DATA, after all 9 bytes are recieved, a flag LIN_STATUS_READ_DATA is set
*                                                                and then this data is processed in "process_lin_engine()" in the main loop while(1).
*
*                                                                In the first place, a message is scheduled in IRQ,
*                                                                then the USART transmission is done in "process_lin_engine()" in the main loop
*
*
*
*
* @DEVICEDEMO
*  Master is sending requests with id range: 0x01-0x3F (except 0x02 and 0x3A)
*                    data msg with id      : 0x02 and 0x3A
*
*  Slave accepts data         with id        0x02 and 0x3A
*       responses to requests with ids       0x03, 0x1A and 0x2A
*
*
* @GATEWAY mode explanation
*  Slave wire is connected to a target Master output
*  Master wire is connected to a target Slave output
*  
*  
*  GatewayLin.SlaveLin is supposed to recieve all data coming from a target netwotk (Master) and re-transmit it through GatewayLin.MasterLin.
*  GatewayLin.MasterLin is supposed to recieve responses coming from a target netwotk (Slave).
*
*  Slave RX procedure is processed in USARTX_IRQHandler.
*                                                        After consequently a LIN break and then a header recieved, the header is re-transmitted through GatewayLin.MasterLin immediately.
*                                                        It is unknown, whether this is a request or data coming from Master to a Slave.
*                                                        Therefore a gateway keeps accepting forecoming data bytes. (From both Master and Slave).
*                                                        In case this is a data message, a completely recieved message is processed in "process_lin_engine()" in the main loop while(1).
*  Master RX procedure is also processed in a corresponding USARTX_IRQHandler.
*
*
* @SCANNER mode explanation (designed for use along with the @GATEWAY mode)
*  Slave reports all detected Headers and Master data.
*  Master reports all data coming from Slave Network.
*
*
* @FILTER mode explanation
*  Master HEADER request =============================================> Slave
*  Master <====================== FILTER changes byte values  <======== Slave response data
*
*  Master HEADER+DATA ==========> FILTER changes byte values  ========> Slave
*
*
*
*
*
* ===========================================================================
* ================================= Polling =================================
* ===========================================================================
* Master periodic messages schema
*  gatewayLIN.masterLIN.start_polling (start_master_polling)               ==>
*                                                                              startBasicTimer
*                                                          TIMX_IRQHandler <==                            
*  gatewayLIN.masterLIN.poll (__WEAK void master_poll) <==
*  ==>
*  ==> DEVICE mode : gatewayLIN.masterLIN.device_tx ==> gatewayLIN.masterLIN.start_polling
*
*
*
******************************************************************************/

#include "lin.h"
#include "tim.h"
#include "watchdog.h"
#include "stm32f105_usbdfs_cdc.h"
#include "string_convertor.h"
#include "lin_device.h"

#define LIN_ITEM(it_raw)     it_raw.info.lin_msg.item
#define LIN_ITEM_RAW(it_raw) it_raw.info.lin_msg
#define _LIN_ITEM(it_raw)     it_raw->info.lin_msg.item
#define _LIN_ITEM_RAW(it_raw) it_raw->info.lin_msg

//================================ Main var ===================================
GatewayLin gatewayLIN;

#define MASTER   gatewayLIN.masterLIN
#define SLAVE    gatewayLIN.slaveLIN
#define GATEWAY  gatewayLIN

//=========================== Initial declaration =============================

#define LIN_PROC_DEFAULT          (uint8_t)0x00
#define LIN_PROC_READ_MSG         (uint8_t)0x01
#define LIN_PROC_MS_SND_MSG       (uint8_t)0x02
#define LIN_PROC_MS_SND_HDR       (uint8_t)0x03
#define LIN_PROC_SL_SND_MSG       (uint8_t)0x04
#define RESET_MASTER_TX (MASTER.process_item.role = LIN_PROC_DEFAULT)
#define RESET_SLAVE_TX (SLAVE.process_item.role = LIN_PROC_DEFAULT)

#define IS_LIN_MODE(_mode)  (*gatewayLIN.mode &   _mode)
#define LIN_MODE_ON(_mode)  (*gatewayLIN.mode |=  _mode)
#define LIN_MODE_OFF(_mode) (*gatewayLIN.mode &= (uint8_t)~_mode)


#define IS_VALIDATION_MODE  (*gatewayLIN.mode &   (uint8_t)(LIN_STATUS_ON << 4))
#define LIN_VALIDATION_ON   *gatewayLIN.mode |=  (uint8_t)(LIN_STATUS_ON << 4);
#define LIN_VALIDATION_OFF  *gatewayLIN.mode &=~ (uint8_t)(LIN_STATUS_ON << 4);

#ifdef SUPPORT_LIN
//=========================== Initialization ==================================
static void init_lin_hardware(void);
static void init_lin_instances(uint16_t poll_period);
static void reinit_baudrates(void);
static eUsartBaudrate calculate_lin_baudrate(uint8_t setting);

//=========================== Hardware specific ===============================
static void switch_cp1117(void);
static void switch_pullup(void);
static void tja_wakeup(void);

//================================ Master =====================================
static void start_master_polling(uint16_t poll_period);
static void stop_master_polling (void);

static void reset_master(void);
static void master_send(LinItem *_item);
static void master_send_header(uint8_t header_id);
static void master_read_msg(LinItemRaw *_item);
static inline void set_master_status(uint8_t status);

static void reset_master(){
	set_master_status(LIN_STATUS_IDLE);
	RESET_MASTER_TX;
	MASTER.rx_cnt = 0;
	MASTER._usart_rx_buffer->write_pos = 0;
}


//================================ Slave ======================================
static void reset_slave(void);
static void slave_send(LinItem *_item);
static void slave_read_msg(LinItemRaw *_item);
static inline void set_slave_status(uint8_t status);

static void reset_slave(){
	RESET_SLAVE_TX;
	SLAVE.rx_cnt = 0;
	SLAVE._usart_rx_buffer->write_pos = 0;
}


//========================== Validation and CRC ===============================
static inline uint8_t get_byte_count(uint8_t id);
static void calculate_parity(LinFrameHeader* _header);
static uint8_t calculate_lin_checksum_13 (LinItem* _item, uint8_t length);
static void set_timestamp(lin_message_info_raw* _item);

//== void process_lin_engine() - general processing function in the main loop =
typedef enum{
	VALID_OK = 0,
	VALID_FAIL = 1 } eLinCrcValidation;

static inline void proc_read_pending_message(lin_message_info_raw* _item);
static uint8_t proc_get_lin_operation(void);
static eLinCrcValidation proc_validate_crc(lin_message_info_raw* _pending_lin_item);
static void proc_process_incoming_msg(lin_message_info_raw* _lin_item);	


//=============================================================================
//=============================================================================
//=================================== Init ====================================
//=============================================================================
//=============================================================================
/**
* brief  Enable LIN
* param  baudrate, poll period for master periodic transmissions
* param  Timer (used for scanner timestamps) for example, TIM1
* param  A pointer to a uint32_t value, that stores timer seconds count
* retval 
*/
void enable_lin(volatile uint8_t *_mode, volatile uint8_t *_baudrate_preset, volatile uint8_t *_filter_preset, TIM_TypeDef* _TIM_TP, volatile uint32_t *sec){
	GATEWAY.seconds = sec;
	GATEWAY.TIM_TP = _TIM_TP;
	GATEWAY.mode = _mode;
	GATEWAY.baudrate_preset = _baudrate_preset;
	GATEWAY.filter_preset = _filter_preset;
	init_lin_hardware();
	init_lin_instances(LIN_MASTER_DEFAULT_POLL_PERIOD);
	GATEWAY.reinit_baudrate();
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn, LIN_MS_POLLING_TIM_IRQ_P);
	#ifdef DEVICE_2CAN
	NVIC_SetPriority(USART2_IRQn, LIN_MASTER_USART_IRQ_P);
	NVIC_SetPriority(USART3_IRQn, LIN_SLAVE_USART_IRQ_P);
	#endif
	if(IS_LIN_MODE(LIN_MODE_DEVICE)){
		#ifdef LIN_DEMO
			MASTER.current_id = 0x01;
			MASTER.start_polling(MASTER.poll_period);
		#endif
	}
}

/**
* brief Disable LIN
* param 
* param  
* retval 
*/
void disable_lin(){
	LIN_MODE_OFF(LIN_MODE_ALL);
	stopBasicTimer(TIM3);
	set_master_status(LIN_STATUS_STOPPED);
	set_slave_status(LIN_STATUS_STOPPED);
	NVIC_DisableIRQ(TIM3_IRQn);
}

void restart_lin(){
	disable_lin();
	enable_lin(GATEWAY.mode,
             GATEWAY.baudrate_preset,
	           GATEWAY.filter_preset,
	           GATEWAY.TIM_TP, 
	           GATEWAY.seconds);
}

/**
* brief Select poll period
* param Poll period used for LIN device.
* param  
* retval 
*/
void lin_select_poll_period (uint16_t poll_period){
	MASTER.poll_period = poll_period;
}

/**
* brief Set LIN filter mode
* brief It could be a custom user preset or a custom programm for a particular vehicle model
* brief 
* param modes and functions are defined in lin_filter.h
* param  
* retval 
*/
void set_lin_filter_mode(uint8_t mode){
	
	switch(mode){
		case LIN_FILTER_OFF:{
			GATEWAY.gateway_filter = &implement_lin_dummy_filter;
			return;
		}
		case LIN_FILTER_USER_MODE:{
			GATEWAY.gateway_filter = &implement_lin_user_filter;
			return;
		}
		#ifdef LIN_PROGRAMM_PRESETS
		case LIN_FILTER_MMC_PAJERO_TYRES:{
			GATEWAY.gateway_filter = &calibrate_lin_mmc_pajero_tyres;
			return;
		}
		#endif
		default:{
			GATEWAY.gateway_filter = &implement_lin_user_filter;
			return;
		}
	}
}

uint16_t lin_get_poll_period (void){
	return MASTER.poll_period;
}


uint8_t *lin_get_mosi_filter(){
	return GATEWAY.mosi_filter.data;
}
uint8_t *lin_get_miso_filter(void){
	return GATEWAY.miso_filter.data;
}
void lin_set_user_filter(uint8_t* bytes){
	uint8_t *target_filter = bytes[0] ? GATEWAY.mosi_filter.data : GATEWAY.miso_filter.data;
	uint16_t k = 1;
	for(uint16_t i = 0; i < sizeof(lin_filter_raw); i++){
		*target_filter++ = bytes[k++];
	}
}

//=============================================================================
//=============================================================================
//=================================== Main ====================================
//=============================================================================
//=============================================================================

/**
* brief  LIN engine processing.
* brief  This function is supposed to be placed in the main loop "while(1)",
* brief  here the engine checks the LIN engine's flags and process incoming data
* param  
* retval 
*/


static inline void send_scanner_report(lin_message_info_raw* report){
	report->info.start_char = '@';
	set_timestamp(report); // set msec and msec
	if(_LIN_ITEM(report).role == LIN_ITEM_ROLE_MS_RQST){
		report->info.lin_msg.item.length = 0;
	}
	USB_CDC_send_data(&report->raw_msg_data[0], LIN_MSG_INFO_SZ);
}
	
static lin_message_info_raw _pending_lin_item = {0};

void process_lin_engine(){
 //=============================================================================
 //======================== Decide, what operation to do =======================
 //=============================================================================
	uint8_t operation = proc_get_lin_operation();
	
	switch(operation){
		case LIN_PROC_DEFAULT:{
			return;
		}
 //=============================================================================
 //=========== If LIN has received a message, read out incoming data ===========
 //=============================================================================
		case LIN_PROC_READ_MSG:{
			proc_read_pending_message(&_pending_lin_item);
			/*
					eLinkState _link_status = USB_CDC_process_watchdog();
		if(_link_status == LINK_STATE_CONNECTED){
	
		uint8_t demo_report[128];
		uint8_t i = 0;
		demo_report[i++] = 'L';
		demo_report[i++] = 'I';
		demo_report[i++] = 'N';
		demo_report[i++] = ' ';
		demo_report[i++] = 'P';
		demo_report[i++] = 'R';
		demo_report[i++] = 'O';
		demo_report[i++] = 'C';
		demo_report[i++] = ' ';
		demo_report[i++] = 'M';
		demo_report[i++] = 'S';
		demo_report[i++] = 'G';
		demo_report[i++] = ' ';
		uint8_t k = 0;	
			while(k < sizeof(lin_message_info_raw)){
			demo_report[i++] = ' ';
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((_pending_lin_item.raw_msg_data[k] >> 4) &~0xF0) );
			demo_report[i++] = halfbyte_to_hexascii( (uint8_t)((_pending_lin_item.raw_msg_data[k++] >> 0) &~0xF0) );
			demo_report[i++] = ' ';
			}
		demo_report[127] = 0x0A;	
		USB_CDC_send_data(demo_report, 128);
	}*/
		
   //============================= Validate a checksum ===========================
			if(IS_VALIDATION_MODE){
				eLinCrcValidation valid_sts = proc_validate_crc(&_pending_lin_item);
				if(valid_sts == VALID_FAIL) return;
			}
	 //============================= Process the message ===========================
			proc_process_incoming_msg(&_pending_lin_item); // MASTER.reset() IDLE or SLAVE.reset()
			if(IS_LIN_MODE(LIN_MODE_SCANNER)){		
				 send_scanner_report(&_pending_lin_item);
			}
			break;
		}
		case LIN_PROC_MS_SND_HDR:{
			_pending_lin_item.info.lin_msg.item.role = LIN_ITEM_ROLE_MS_RQST;
			_pending_lin_item.info.lin_msg.item.id = MASTER.process_item.id;
			if(IS_LIN_MODE(LIN_MODE_SCANNER)){		
				 send_scanner_report(&_pending_lin_item);
			}
			__attribute__ ((fallthrough));
		}
		case LIN_PROC_MS_SND_MSG:{
			MASTER.send(&MASTER.process_item);
			RESET_MASTER_TX;			
			break;
		}
		case LIN_PROC_SL_SND_MSG:{
			SLAVE.send(&SLAVE.process_item);
			break;
		}
		default:
			return;
	}
}

//=============================================================================
//=============================================================================
//=================================== Master ==================================
//=============================================================================
//=============================================================================
#if defined(DEVICE_2CAN)
extern void TIM3_IRQHandler(void);
void TIM3_IRQHandler(void){
	if(TIM3->SR & TIM_SR_UIF){
		stopBasicTimer(TIM3);
		TIM3->SR &= ~TIM_SR_UIF; // Flag down

		// If master hasn't recieved response yet, reset status and continue polling.
		if(MASTER.status != LIN_STATUS_STOPPED){
			if(IS_LIN_MODE(LIN_MODE_DEVICE)){
				MASTER.reset(); // MASTER.reset() IDLE
			}
			else RESET_MASTER_TX;
		}
		gatewayLIN.masterLIN.poll(); //lin_device_master_tx();
		IWDG_reset();
	}
}
#endif

#if ((USART_USED(2)) && (USART_LIN_ENABLE(2)))
extern void USART2_IRQHandler(void);
void USART2_IRQHandler(void){
	
	uint8_t recievedByte;
	
	if (USART2->SR & USART_SR_LBD){
		USART2->SR &= ~USART_SR_LBD;                    // Break flag is ignored, in the master's IRQ
		volatile uint16_t temp_recievedByte = (uint16_t)(USART3->DR); // Clear LIN break received bits
		USART2->SR &= ~USART_SR_RXNE;
		(void)temp_recievedByte;
		if(IS_LIN_MODE(LIN_MODE_GATEWAY)){
			RESET_MASTER_TX;
			MASTER._usart_rx_buffer->write_pos = 0;
		}
		return;
	}
	if (USART2->SR & USART_SR_RXNE){
		USART2->SR &= ~USART_SR_RXNE;
		
 //=============================================================================
 //====================== Mater recieves an incoming byte ======================
 //=============================================================================
		
		recievedByte = (uint8_t)(USART2->DR);
		
		// If RX buffer is full, reset Master state
		if(MASTER._usart_rx_buffer->write_pos >= LIN_MAX_RX_BUF_SZ)
			MASTER.reset();
		
   //=============================================================================
   //=========================== Process the byte ================================
   //=============================================================================
//		if(IS_LIN_MODE(LIN_MODE_DEVICE)){
		
		if(MASTER.status == LIN_STATUS_WAIT_DATA){
			if(MASTER.rx_cnt!=0){
				MASTER._usart_rx_buffer->write(&recievedByte, 1);
				MASTER.rx_cnt = (uint8_t) (MASTER.rx_cnt - 1);
					// If scheduled data length has come, set corresponding flag 
				if(MASTER.rx_cnt==0){
					set_master_status(LIN_STATUS_READ_DATA);
				} // cnt == 0
			} // cnt!= 0
		} // LIN_STATUS_WAIT_DATA
		
		// The "SEND SYNC" or "SEND HEADER" statuses mean, that MASTER must ignore its own SYNC and ID 
		else if(MASTER.status == LIN_STATUS_SEND_SYNC){
			if(recievedByte == LIN_SYNC_VAL) set_master_status(LIN_STATUS_SEND_HDR); 
		} // LIN_STATUS_SEND_SYNC
		else if(MASTER.status == LIN_STATUS_SEND_HDR){
			set_master_status(LIN_STATUS_WAIT_DATA); 
			
			if(IS_LIN_MODE(LIN_MODE_GATEWAY)){
				MASTER._usart_rx_buffer->write(&MASTER.current_id, 1);
			}
			
		} // LIN_STATUS_SEND_SYNC
		
	 //=============================================================================
   //====== These procedures prevent the Master from receiving its own data ======
   //=============================================================================	
	}
}
#endif

/**
* brief  This functions defines device mode behavior for master tx
* brief  Master DEVICE TX
* param  
* retval 
*/
__WEAK void master_device_tx(){
	#ifdef LIN_DEMO
	lin_device_master_tx();
	#endif
}
/**
* brief  This functions defines device mode behavior for master rx
* param  
* retval 
*/
__WEAK void master_device_rx(){
}

__WEAK void master_poll(){
	// If the scanner mode is on, keep sending headers with id range 0x00-0x3FC
	// and set recieve counter according to byte count incorporated in id
	// 0x00-0x1F - 2 bytes
	// 0x20-0x2F - 4 bytes
	// 0x30-0x3F - 8 bytes
	if(IS_LIN_MODE(LIN_MODE_DEVICE)){
		if(MASTER.status == LIN_STATUS_IDLE){
			MASTER.device_tx();
		}
		MASTER.start_polling(MASTER.poll_period);
	}
}


//=============================================================================
//=============================================================================
//=================================== Slave  ==================================
//=============================================================================
//=============================================================================
__WEAK void slave_device_rx(){
	#ifdef LIN_DEMO
	lin_device_slave_rx();
	#else 
	gatewayLIN.slaveLIN.status = LIN_STATUS_IDLE;
	#endif 
}

__WEAK void slave_device_tx(){
}

#if ((USART_USED(3)) && (USART_LIN_ENABLE(3)))
extern void USART3_IRQHandler(void);
void USART3_IRQHandler(void){
	
	uint8_t recievedByte;
	
	//=============================================================================
  //========================= Slave detects a LIN break =========================
  //=============================================================================
	if (USART3->SR & USART_SR_LBD){
		USART3->SR &= ~USART_SR_LBD;
		USART3->SR &= ~USART_SR_RXNE;
		
		if(SLAVE.status == LIN_STATUS_STOPPED) return;
		volatile uint16_t temp_recievedByte = (uint16_t)(USART3->DR); // Clear LIN break received bits
		(void)temp_recievedByte;
		set_slave_status(LIN_STATUS_WAIT_SYNC); // If LIN break detected, wait for a SYNC            
		SLAVE.reset();
	}
	
	//=============================================================================
  //====================== Slave recieves an incoming byte ======================
  //=============================================================================
	else if (USART3->SR & USART_SR_RXNE){
		USART3->SR &= ~USART_SR_RXNE;
		
		recievedByte = (uint8_t)(USART3->DR);                        // Recieve a byte
		
		//=============================================================================
    //============================  Check conditions  =============================
    //=============================================================================
		
		if(SLAVE.status == LIN_STATUS_STOPPED) return;
		// If RX buffer is full, reset Slave state
		if(SLAVE._usart_rx_buffer->write_pos >= LIN_MAX_RX_BUF_SZ){
			SLAVE.reset();
			set_slave_status(LIN_STATUS_IDLE);
		}
			
		//=============================================================================
    //======================  Slave recieves the SYNC bits  =======================
    //=============================================================================
		if(SLAVE.status == LIN_STATUS_WAIT_SYNC){
			if(recievedByte == LIN_SYNC_VAL){
				set_slave_status(LIN_STATUS_WAIT_HDR);
			}
			else{
				set_slave_status(LIN_STATUS_IDLE);
			}
			return;
		}

	 //=============================================================================
   //=========================== Process the byte ================================
   //=============================================================================
		
	 //=============================================================================
   //=========================== A header recieved ===============================
   //=============================================================================
		if(SLAVE.status == LIN_STATUS_WAIT_HDR){       // If a header recieved
			LinFrameHeader rec_header;
			rec_header.header = recievedByte;
	
			// validation
			if(IS_VALIDATION_MODE){
				LinFrameHeader ref_header;
				ref_header.header = LIN_FRAME_ID(rec_header.header);
				calculate_parity(&ref_header);
				if(ref_header.header != rec_header.header){
					set_slave_status(LIN_STATUS_IDLE);
					return;
				}
			}//
			
			SLAVE.current_id = LIN_FRAME_ID(rec_header.header);		
			SLAVE._usart_rx_buffer->write(&SLAVE.current_id, 1);
			
      /******************   @DEVICE   ******************/
			if(IS_LIN_MODE(LIN_MODE_DEVICE)){
				SLAVE.device_rx();
			}
			/******************   @GATEWAY   *****************/
			else if(IS_LIN_MODE(LIN_MODE_GATEWAY)){
				MASTER.current_id = LIN_FRAME_ID(rec_header.header);
				
				// re-transmit a header, then be ready to recieve data bytes (In case this is a data message)
				
				// Since this is unknown what network (Master or Slave) will send data, set recieve mode for both (Master and Slave) 
				set_slave_status(LIN_STATUS_WAIT_DATA);

				SLAVE.rx_cnt =  (uint8_t)(get_byte_count(SLAVE.current_id) + 1);
				
				LinItem ms_rqst;
				ms_rqst.id = MASTER.current_id;
				ms_rqst.role = LIN_ITEM_ROLE_MS_RQST;
				master_schedule_item(&ms_rqst);
				
				//master_send_header(MASTER.current_id);
			}
		} //LIN_STATUS_WAIT_HDR
		
		
	 //=============================================================================
   //=========================== A data byte recieved ============================
   //=============================================================================
		
		else if(SLAVE.status == LIN_STATUS_WAIT_DATA){       // If data byte recieved		
			
			if(SLAVE.rx_cnt!=0){
				SLAVE._usart_rx_buffer->write(&recievedByte, 1);
				SLAVE.rx_cnt = (uint8_t)(SLAVE.rx_cnt - 1);
				// If scheduled data length has come, set corresponding flag 
				if(SLAVE.rx_cnt==0){
					set_slave_status(LIN_STATUS_READ_DATA);
				} // cnt == 0
			} // cnt!= 0

		} // LIN_STATUS_WAIT_DATA
		
	}
}
#endif

//=============================================================================
//=============================================================================
//=================             Static functions                 ==============
//=============================================================================
//=============================================================================


//=========================== Initialization ==================================
//b0 c4
void init_lin_hardware(){
	#ifdef DEVICE_2CAN
	switch_cp1117();
	switch_pullup();
	tja_wakeup();
	#endif
}

/**
* brief  Init masterLIN and slaveLIN structs
* param  
* param  
* retval 
*/
static void init_lin_instances(uint16_t poll_period){
	#if defined(DEVICE_2CAN)
	gatewayLIN.masterLIN.usart_num = 2;
	gatewayLIN.masterLIN.usart_ptr = USART2;
	gatewayLIN.masterLIN._usart_rx_buffer = &usart2_rx_buf;
	
	gatewayLIN.slaveLIN.usart_ptr = USART3;
	gatewayLIN.slaveLIN.usart_num = 3;
	gatewayLIN.slaveLIN._usart_rx_buffer = &usart3_rx_buf;
	
	//gatewayLIN.filter_preset = LIN_FILTER_USER_MODE;
	
	gatewayLIN.gateway_filter = &implement_lin_user_filter;
	#endif
	
	//================= 2LIN ==================
	//gatewayLIN.mode = LIN_MODE_DEFAULT;
	//gatewayLIN.validate_response_mode = LIN_STATUS_OFF;
	
	//gatewayLIN.baudrate_preset = baudrate_preset;
	gatewayLIN.calculate_crc = &calculate_lin_checksum_13;
	gatewayLIN.reinit_baudrate = &reinit_baudrates;

	//================= Master ================
	gatewayLIN.masterLIN.status = LIN_STATUS_IDLE;
	gatewayLIN.masterLIN.rx_cnt = 0;
	gatewayLIN.masterLIN.current_id = 0x01;
	gatewayLIN.masterLIN.poll_period = poll_period;
	gatewayLIN.slaveLIN.process_item.role = LIN_ITEM_DEFAULT;
	
	gatewayLIN.masterLIN.start_polling = &start_master_polling;
	gatewayLIN.masterLIN.stop_polling = &stop_master_polling;
	gatewayLIN.masterLIN.poll = &master_poll;
	gatewayLIN.masterLIN.reset = &reset_master;
	gatewayLIN.masterLIN.device_tx = &master_device_tx;
	gatewayLIN.masterLIN.device_rx = &master_device_rx;
	gatewayLIN.masterLIN.send = &master_send;
	gatewayLIN.masterLIN.read_out = &master_read_msg;

	//================= Slave ================
	gatewayLIN.slaveLIN.status = LIN_STATUS_IDLE;
	gatewayLIN.slaveLIN.rx_cnt = 0;
	gatewayLIN.slaveLIN.current_id = 0x00;
	gatewayLIN.slaveLIN.process_item.role = LIN_ITEM_DEFAULT;
	gatewayLIN.slaveLIN.reset = &reset_slave;
	gatewayLIN.slaveLIN.device_rx = &slave_device_rx;
	gatewayLIN.slaveLIN.device_tx = &slave_device_tx;
	gatewayLIN.slaveLIN.send = &slave_send;
	gatewayLIN.slaveLIN.read_out = &slave_read_msg;
}

static void reinit_baudrates(){
	eUsartBaudrate br = calculate_lin_baudrate(*gatewayLIN.baudrate_preset);
	usart_reinit_baudrate(MASTER.usart_num, br);
	usart_reinit_baudrate (SLAVE.usart_num, br);
}

/**
* brief  Change USART LIN baudrate
* param  Settings baudrate preset number
* param  i.e 0 means 1200 kb/s, 1 means 2400 kb/s, 2 means 4800 kb/s
* retval baudrate enum value
*/
static eUsartBaudrate calculate_lin_baudrate(uint8_t setting){
	switch(setting){
		case LIN_1200:   return Baudrate_1200;
		case LIN_2400:   return Baudrate_2400;
		case LIN_4800:   return Baudrate_4800;
		case LIN_9600:   return Baudrate_9600;
		case LIN_19200:  return Baudrate_19200;
		case LIN_38400:  return Baudrate_38400;
		case LIN_57600:  return Baudrate_57600;
		case LIN_115200: return Baudrate_115200;
		case LIN_921600: return Baudrate_921600;
		default: return Baudrate_9600;
	}
}
//================================= Master ====================================
static inline void set_master_status(uint8_t status){
	MASTER.status = status;
}

void start_master_polling(uint16_t poll_period){
	startBasicTimer(CAN_INJ_TIM_PSC, poll_period, TIM3);
}

void stop_master_polling (void){
	stopBasicTimer(TIM3);
}

static void master_send_header(uint8_t header_id){
	set_master_status(LIN_STATUS_SEND_SYNC);
	LinFrameHeader _header;
	_header.header = header_id;
	calculate_parity(&_header);
	uint8_t data[2] = {LIN_SYNC_VAL, _header.header};
	MASTER.usart_ptr->CR1 |= USART_CR1_SBK;
	usart_send_byte_array(MASTER.usart_num, &data[0], 2);
	while ((MASTER.usart_ptr->SR & USART_SR_TXE) == 0) {}
}

static void master_read_msg(LinItemRaw *_item){
	MASTER._usart_rx_buffer->read(&_item->data[2]);
	_item->item.length = get_byte_count(_item->item.id);
	MASTER.rx_cnt = 0;
}

void master_schedule_item(LinItem *_item){
	MASTER.process_item = *_item;
}

static void master_send(LinItem *_item){

	switch(_item->role){
		case LIN_ITEM_ROLE_MS_DATA:{
			master_send_header(_item->id);
			set_master_status(LIN_STATUS_SEND_DATA);
			usart_send_byte_array(MASTER.usart_num, &_item->data[0], (uint8_t)(_item->length + 1)); // length + crc
			MASTER.reset();
			break;
		}
		case LIN_ITEM_ROLE_MS_RQST:{
			MASTER.rx_cnt = (uint8_t)(get_byte_count(_item->id) + 1);
			master_send_header(_item->id);
			//set_master_status(LIN_STATUS_WAIT_DATA);
			break;
		}
		default:
			break;
	}
}




//=================================== Slave ===================================
static inline void set_slave_status(uint8_t status){
	SLAVE.status = status;
}

void slave_schedule_item(LinItem *_item){
	SLAVE.process_item = *_item;
}

static void slave_send(LinItem *_item){
	switch(_item->role){
		case LIN_ITEM_ROLE_SL_DATA:{
			set_slave_status(LIN_STATUS_SEND_DATA);
			usart_send_byte_array(SLAVE.usart_num, &_item->data[0], (uint8_t)(_item->length + 1)); // length + crc
			SLAVE.reset();
			break;
		}
		default:
			break;
	}
	while ((SLAVE.usart_ptr->SR & USART_SR_TXE) == 0) {}
}

static void slave_read_msg(LinItemRaw *_item){
	SLAVE._usart_rx_buffer->read(&_item->data[2]);
	_item->item.length = get_byte_count(_item->item.id);
	SLAVE.rx_cnt = 0;	
}


//=========================== Hardware specific ===============================
static void switch_cp1117(){
	#ifdef DEVICE_2CAN
	GPIOA->CRL	&= ~GPIO_CRL_CNF0;						
	GPIOA->CRL 	|= GPIO_CRL_MODE0_0;					
	GPIOA->CRL 	|= GPIO_CRL_MODE0_1;
	GPIOA->BSRR |= GPIO_BSRR_BS0;
	#endif
}

static void switch_pullup(){
	#ifdef DEVICE_2CAN
	// LIN1 Master
	GPIOC->CRL	&= ~GPIO_CRL_CNF4;						
	GPIOC->CRL 	|= GPIO_CRL_MODE4_0;					
	GPIOC->CRL 	|= GPIO_CRL_MODE4_1;
	GPIOC->BSRR |= GPIO_BSRR_BS4;
	/*
	GPIOB->CRL	&= ~GPIO_CRL_CNF0;						
	GPIOB->CRL 	|= GPIO_CRL_MODE0_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE0_1;
	GPIOB->BSRR |= GPIO_BSRR_BS0;
	*/
	#endif
}

static void tja_wakeup(){
	#ifdef DEVICE_2CAN
	GPIOB->CRL	&= ~GPIO_CRL_CNF1;						
	GPIOB->CRL 	|= GPIO_CRL_MODE1_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE1_1;
	GPIOB->BSRR |= GPIO_BSRR_BS1;
	
	GPIOC->CRL	&= ~GPIO_CRL_CNF5;						
	GPIOC->CRL 	|= GPIO_CRL_MODE5_0;					
	GPIOC->CRL 	|= GPIO_CRL_MODE5_1;
	GPIOC->BSRR |= GPIO_BSRR_BS5;
	#endif
}

//========================== Validation and CRC ===============================
// How many bytes are supposed to be transmitted
static inline uint8_t get_byte_count(uint8_t id){
	uint8_t byte_cnt = (id < 0x20) ? 2 : (id < 0x30) ? 4 : 8;
	return (byte_cnt); // + 1 byte CRC
}
	
static void calculate_parity(LinFrameHeader* _header) {
	uint8_t parity = 0;
    // Calculate P0 parity bit
	parity = (uint8_t)(parity ^(_header->bits.ID0));
	parity = (uint8_t)(parity ^(_header->bits.ID1));
	parity = (uint8_t)(parity ^(_header->bits.ID2));
	parity = (uint8_t)(parity ^(_header->bits.ID4));
	_header->bits.P0 = (parity == 0) ? 0 : 1;
    
    // Calculate P1 parity bit
	parity = (uint8_t)(parity ^(_header->bits.ID1));
	parity = (uint8_t)(parity ^(_header->bits.ID3));
	parity = (uint8_t)(parity ^(_header->bits.ID4));
	parity = (uint8_t)(parity ^(_header->bits.ID5));
	
	_header->bits.P1 = (parity == 0) ? 0 : 1;
}


static uint8_t calculate_lin_checksum_13 (LinItem* _item, uint8_t length){
    uint32_t res = 0;
    for (uint8_t i = 0; i < length; i++){
			res += _item->data[i];
        if (res & 0x100){
					res++;
					res &= 0xFF;
				}
		}
    res ^= 0xFF;    // inverting result
		return (uint8_t)res;
}

static void set_timestamp(lin_message_info_raw* _item){
	_item->info.seconds = *(gatewayLIN.seconds);
	_item->info.msec = (uint16_t)gatewayLIN.TIM_TP->CNT / 2;
}




//=============================================================================
//== void process_lin_engine() - general processing function in the main loop =
//=============================================================================

static inline void proc_read_pending_message(lin_message_info_raw* _item){
	if(MASTER.status == LIN_STATUS_READ_DATA){
		set_master_status(LIN_STATUS_IDLE);
		MASTER.read_out(&_LIN_ITEM_RAW(_item));
		_LIN_ITEM(_item).role = LIN_ITEM_ROLE_MS_IN;
	}
	else if(SLAVE.status == LIN_STATUS_READ_DATA){
		set_slave_status(LIN_STATUS_IDLE);
		SLAVE.read_out(&_LIN_ITEM_RAW(_item));
		_LIN_ITEM(_item).role = LIN_ITEM_ROLE_SL_IN;
	}
	else return; // If no messages pending, quit the function.
	_LIN_ITEM(_item).length = get_byte_count(_LIN_ITEM(_item).id);
}

static uint8_t proc_get_lin_operation(){
	if((MASTER.status == LIN_STATUS_READ_DATA) | (SLAVE.status == LIN_STATUS_READ_DATA))
		return LIN_PROC_READ_MSG;
	
	else if(MASTER.process_item.role == LIN_ITEM_ROLE_MS_DATA)
		return LIN_PROC_MS_SND_MSG;
	
	else if(MASTER.process_item.role == LIN_ITEM_ROLE_MS_RQST)
		return LIN_PROC_MS_SND_HDR;
	
	else if(SLAVE.process_item.role == LIN_ITEM_ROLE_SL_DATA)
		return LIN_PROC_SL_SND_MSG;
	
	else return LIN_PROC_DEFAULT;
}

static eLinCrcValidation proc_validate_crc(lin_message_info_raw* _lin_item){
	uint8_t _lin_item_crc = _LIN_ITEM(_lin_item).data[_LIN_ITEM(_lin_item).length];
	uint8_t _ref_item_crc = GATEWAY.calculate_crc(&_LIN_ITEM(_lin_item), _LIN_ITEM(_lin_item).length);
	// If there is a CRC mismatch, make reset
	if(_lin_item_crc != _ref_item_crc){
		if(_LIN_ITEM(_lin_item).role == LIN_ITEM_ROLE_MS_IN) MASTER.reset();
		return VALID_FAIL;
	}
	else return VALID_OK;
}

static void proc_process_incoming_msg(lin_message_info_raw* _lin_item){
 //=============================================================================
 //====================== Process a message in DEVICE mode =====================
 //=============================================================================
	
	if(IS_LIN_MODE(LIN_MODE_DEVICE)){
					/************ DEFAULT DEMO *************/
		#ifdef LIN_DEMO
		lin_device_report(_lin_item);
		if(_LIN_ITEM(_lin_item).role == LIN_ITEM_ROLE_SL_IN){
			SLAVE.reset();
			if(SLAVE.status == LIN_STATUS_READ_DATA) set_slave_status(LIN_STATUS_IDLE);
		}
		else if(_LIN_ITEM(_lin_item).role == LIN_ITEM_ROLE_MS_IN){
			MASTER.reset();
			//if(MASTER.status == LIN_STATUS_READ_DATA) set_master_status(LIN_STATUS_IDLE);
		}
		#endif
	}
	
 //=============================================================================
 //====================== Process a message in GATEWAY mode ====================
 //=============================================================================
	else if(IS_LIN_MODE(LIN_MODE_GATEWAY)){
		
		if(_LIN_ITEM(_lin_item).role == LIN_ITEM_ROLE_SL_IN){
			
			if(*GATEWAY.filter_preset != LIN_FILTER_OFF){
				GATEWAY.gateway_filter(&_LIN_ITEM(_lin_item), &GATEWAY.miso_filter);
				if(IS_VALIDATION_MODE){
					_LIN_ITEM(_lin_item).data[_LIN_ITEM(_lin_item).length] = gatewayLIN.calculate_crc(&_LIN_ITEM(_lin_item), _LIN_ITEM(_lin_item).length);
				}
			}
			
			set_master_status(LIN_STATUS_SEND_DATA);
			usart_send_byte_array(MASTER.usart_num, &_LIN_ITEM(_lin_item).data[0], (uint8_t)(_LIN_ITEM(_lin_item).length + 1)); // length + crc
			//SLAVE.reset();
			MASTER.reset();
		}
		else if(_LIN_ITEM(_lin_item).role == LIN_ITEM_ROLE_MS_IN){
			
			if(*GATEWAY.filter_preset != LIN_FILTER_OFF){
				GATEWAY.gateway_filter(&_LIN_ITEM(_lin_item), &GATEWAY.mosi_filter);
				if(IS_VALIDATION_MODE){
					_LIN_ITEM(_lin_item).data[_LIN_ITEM(_lin_item).length] = gatewayLIN.calculate_crc(&_LIN_ITEM(_lin_item), _LIN_ITEM(_lin_item).length);
				}
			}
			
			usart_send_byte_array(SLAVE.usart_num, &_LIN_ITEM(_lin_item).data[0], (uint8_t)(_LIN_ITEM(_lin_item).length + 1)); // length + crc
			SLAVE.reset();
			if(SLAVE.status == LIN_STATUS_READ_DATA) set_slave_status(LIN_STATUS_IDLE);
			MASTER.reset();
		}	
	}
}

#endif


