//*****************************************************************
// 
// STM32F105/205
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************


#include "device_model.h"
#ifdef SUPPORT_BXCAN
#include "BxCAN/can.h"

//extern CanBufferStruct CAN_buffer[CAN_INTERFACES_USED];

/**
* brief  Can1_Initializate_Pins : Initializes pins for CAN1        
* param 
* param  
* retval
*/

static void Can1_Init_Pins(void){
	CAN1_INIT_PINS
}

/**
* brief  Can2_Initializate_Pins : Initializes pins for CAN2        
* param 
* param  
* retval
*/

static void Can2_Init_Pins(void){
	CAN2_INIT_PINS
}

/**
* brief  calculate baud settings       
* param  APB freq
* param baudrate (250, 500, 1000)
* BTR register values
*/
can_btr_setting calculate_baudrate(uint32_t baudRate){
	can_btr_setting _val;
	_val.psc = 0x00;
	_val.bs1 = 0x00;
	_val.bs2 = 0x00;
	_val.sjw = 0x00;
	
	if(APB1_FREQ_MHZ == 24000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 0x02;
			_val.bs1 = 0x06;
			_val.bs2 = 0x07;
			_val.sjw = 0x00;
		}
	}
	else if(APB1_FREQ_MHZ == 36000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 0x03;
			_val.bs1 = 0x08;
			_val.bs2 = 0x07;
			_val.sjw = 0x00;
		}
	}
	else if(APB1_FREQ_MHZ == 30000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 3; //0x02;
			_val.bs1 = 11; //0x0D;
			_val.bs2 = 1; // 0x04;
			_val.sjw = 0x00;
		}
	}
	else if(APB1_FREQ_MHZ == 42000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 5;  //  6;
			_val.bs1 = 9; // 10;
			_val.bs2 = 2;  //  3;
			_val.sjw = 0x00;
		}
	}
	return _val;
	// @TODO : add some more baudRate configurations
}

static void can_enable_buffers(){
	can_buffer_init();
	CAN1->IER |= CAN_IER_ERRIE;
	CAN1->IER |= CAN_IER_TMEIE;
	CAN1->IER |= CAN_IER_LECIE;
	
	NVIC_EnableIRQ(CAN1_TX_IRQn);
	NVIC_SetPriority(CAN1_TX_IRQn, CAN1_TX_IRQ_P);
	NVIC_EnableIRQ(CAN1_SCE_IRQn);
	NVIC_SetPriority(CAN1_SCE_IRQn, CAN1_SCE_IRQ_P);
		
	#ifndef DEVICE_1CAN2LIN
	CAN2->IER |= CAN_IER_ERRIE;
	CAN2->IER |= CAN_IER_TMEIE;
	CAN2->IER |= CAN_IER_LECIE;
	

	NVIC_EnableIRQ(CAN2_TX_IRQn);
	NVIC_SetPriority(CAN2_TX_IRQn, CAN2_TX_IRQ_P);
	NVIC_EnableIRQ(CAN2_SCE_IRQn);
	NVIC_SetPriority(CAN2_SCE_IRQn, CAN2_SCE_IRQ_P);
	#endif
	
}

/**
* brief  Can_Configure_BaudRate : COnfiguring BaudRate for CAN1        
* param  BaudRate configuration
* param  CAN_TypeDef
* retval 0 - OK  1 - Err
*/
static uint32_t Can_Configure_BaudRate(CAN_TypeDef* _CAN_TP, can_btr_setting _btr_set){
	_CAN_TP->BTR &= ~CAN_BTR_TS1; // reset value
	_CAN_TP->BTR &= ~CAN_BTR_TS2; // reset value
	_CAN_TP->BTR &= ~CAN_BTR_SJW; // reset value
	
	_CAN_TP->BTR |= (uint32_t) _btr_set.psc;       //Prescaler	
	_CAN_TP->BTR |= (uint32_t)(_btr_set.bs1 << 16); //BS1
	_CAN_TP->BTR |= (uint32_t)(_btr_set.bs2 << 20); //BS2
	_CAN_TP->BTR |= (uint32_t)(_btr_set.sjw << 24); //SJW
	return OPERATION_OK;
}


/**
* brief  Can1_Init : Initializes registers for CAN1 and starts controller        
* param  remapConfig, baudRate
* param  
* retval 0 - OK  1 - Err
*/
static  uint32_t Can1_Init(can_btr_setting _btr_set){
	volatile uint32_t timeout = 0;             // Timeout counter
	Can1_Init_Pins();                      // Configure pins
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;               // Enable peripheral clock
	CAN1->MCR |= CAN_MCR_INRQ;                        // Entering Initialization mode
	CAN1->MCR &= (uint32_t)~CAN_MCR_SLEEP;            // Quitting Sleep mode
	
	timeout=0;
	while(!(CAN1->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;	// Waiting for a flag CAN_MSR_INAK (This means, Initialization mode started)			
	} 
	if(!(CAN1->MSR & CAN_MSR_INAK)){ // If a timeout passed away and CAN_MSR_INAK had not come up - Error
		return 1;
	}	
	Can_Configure_BaudRate(CAN1, _btr_set);	//Configuring BaudRate
	CAN1->IER |= CAN_IER_FMPIE0; 				// Enable FIFO-0 Pending interrupt
//	CAN1->IER |= CAN_IER_FMPIE1; 				// Enable FIFO-1 Pending interrupt
	CAN1->MCR |= CAN_MCR_ABOM;					// Enable auto recovery out from Buss-off	
	
	CAN1->MCR |= CAN_MCR_NART;
	//CAN1->MCR |= CAN_MCR_TXFP;
	
	CAN1->MCR &= (uint32_t)~CAN_MCR_INRQ;    			// Quit Initialization mode
	
	timeout=0;
	while((CAN1->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;			
	} // Waiting for both CAN_MSR_SLAK and CAN_MSR_INAK flags down(This means, Normal mode started) 
	
	if((!(CAN1->MSR & CAN_MSR_INAK)) && (!(CAN1->MSR & CAN_MSR_SLAK))){ 
	//Check SLAK and INAK flags. If they are reset, Controller has entered normal mode
		return 0;
	}
	else return 1;		
}

/**
* brief  Can2_Init : Initializes registers for CAN2 and starts controller        
* param  remapConfig, baudRate
* param  
* retval 0 - OK  1 - Err
*/
static uint32_t Can2_Init(can_btr_setting _btr_set){
	volatile uint32_t timeout = 0;											// Timeout counter
	Can2_Init_Pins();	// Configure pins	
	RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;		// Enable peripheral clock
	CAN1->MCR |= CAN_MCR_INRQ;   					// Entering Initialization mode
	CAN2->MCR |= CAN_MCR_INRQ;   					// Entering Initialization mode
	CAN2->MCR &= (uint32_t)~CAN_MCR_SLEEP;   				// Quitting Sleep mode
	
	timeout=0;
	while(!(CAN2->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;	// Waiting for a flag CAN_MSR_INAK (This means, Initialization mode started)			
	} 
	if(!(CAN2->MSR & CAN_MSR_INAK)){ // If a timeout passed away and CAN_MSR_INAK had not come up - Error
		return 1;
	}	
	Can_Configure_BaudRate(CAN2, _btr_set);	//Configuring BaudRate
	CAN2->IER |= CAN_IER_FMPIE0; 				// Enable FIFO-0 Pending interrupt
	CAN2->MCR |= CAN_MCR_ABOM;					// Enable auto recovery out from Buss-off	
	
	CAN2->MCR |= CAN_MCR_NART;
	//CAN2->MCR |= CAN_MCR_TXFP;
	
	CAN2->MCR &= (uint32_t)~CAN_MCR_INRQ;    			// Quit Initialization mode
	CAN1->MCR &= (uint32_t)~CAN_MCR_INRQ;    			// Quit Initialization mode

	timeout=0;
	while((CAN2->MSR & CAN_MSR_INAK) && (timeout < CAN_INIT_TIMEOUT_MAX)){
		timeout++;			
	} // Waiting for both CAN_MSR_SLAK and CAN_MSR_INAK flags down(This means, Normal mode started) 
	
	if((!(CAN2->MSR & CAN_MSR_INAK)) && (!(CAN2->MSR & CAN_MSR_SLAK))){ 
	//Check SLAK and INAK flags. If they are reset, Controller has entered normal mode
		CAN2->RF1R|=CAN_RF0R_RFOM0;
		return 0;
	}
	else return 1;		
}



static void Can_InitFilters_GatewayTemplate(void){	
	//todo: add some more features 	
	CAN1->FMR &= (uint32_t)~0x3F00; // 11111100000000  reset CAN2SB
	CAN1->FMR |= CAN_FMR_FINIT; // This bit starts Filter Initialization
	CAN1->FMR |= 0xE00; // CAN2SB   CAN2 starts from 14
	CAN1->FM1R &= ~0xFFFFFFFF;
	CAN1->FS1R &= ~0xFFFFFFFF;
	CAN1->FFA1R &= ~0xFFFFFFFF;
	CAN1->FA1R	&= ~0xFFFFFFFF;
	CAN1->sFilterRegister[0].FR1 &= ~0xFFFFFFFF; // CAN->F0R1
	CAN1->sFilterRegister[0].FR2 &= ~0xFFFFFFFF; // CAN->F0R2
	
	CAN1->sFilterRegister[14].FR1 &= ~0xFFFFFFFF; // CAN->F14R1
	CAN1->sFilterRegister[14].FR2 &= ~0xFFFFFFFF; // CAN->F14R2
	
	
	CAN1->FS1R |= CAN_FS1R_FSC0; // 1 - 32-bit
	CAN1->FS1R |= 0x4000; // 100000000000000  14 bit		

	CAN1->FFA1R |=  0x00; // 0 - FIFO 0
	CAN1->FA1R	|=  0x01;	// 1 - Active		
	CAN1->FA1R	|= 0x4000; // 100000000000000  14 bit		
	
	CAN1->sFilterRegister[0].FR1 |=  0x00; // As long as we accept all the traffic filter value is 0
	CAN1->sFilterRegister[0].FR2 |=  0x00;		
	//Filter Initialization completed		
	CAN1->FMR &= (uint32_t)~CAN_FMR_FINIT;	
}



/**
 * brief  Can_SetTxMessage: set up an empty mailbox with a single message (with dlc, id and data) 
 * param  CanMessage, Mailbox number
 * param  
 * retval 0 - OK, 1 - Err
 */	
static uint32_t Can_SetTxMessage(CAN_TypeDef* _CAN_TP, can_message *canMessage, uint32_t mailboxNo){
	_CAN_TP->sTxMailBox[mailboxNo].TIR	  &= ~ 0xFFFFFFFF;  // Clean up
	_CAN_TP->sTxMailBox[mailboxNo].TDTR  &= ~ 0xFFFFFFFF;	// Clean up
	_CAN_TP->sTxMailBox[mailboxNo].TDLR  &= ~ 0xFFFFFFFF;  // Clean up
	_CAN_TP->sTxMailBox[mailboxNo].TDHR  &= ~ 0xFFFFFFFF;  // Clean up
	
	if(canMessage->ide == STD_ID){
		// ID value is set within 31-21 bit range. First set bits 28-21
		_CAN_TP->sTxMailBox[mailboxNo].TIR  |= (uint32_t)(canMessage->id.std_id.id_lowbyte << 21);
		canMessage->id.std_id.id_highbyte &=0x1F;	// Discard bits 7-3 of the second identificator part
		//set bits 31-28		
		_CAN_TP->sTxMailBox[mailboxNo].TIR  |= (uint32_t)(canMessage->id.std_id.id_highbyte << 29);
	}
	else{
		_CAN_TP->sTxMailBox[mailboxNo].TIR  |= (canMessage->id.ext_id << 3);
		_CAN_TP->sTxMailBox[mailboxNo].TIR  |= 0x04; /* set IDE bit */
	}	
	_CAN_TP->sTxMailBox[mailboxNo].TDTR |= canMessage->dlc; 
	uint16_t MessageSize;
	MessageSize = canMessage->dlc;	// Data fields assignation is based on the message size																				
	if(MessageSize>8){		
		return 1;  //make sure DLC is not greater, than 8
	}	
//	if(MessageSize>=1){
		_CAN_TP->sTxMailBox[mailboxNo].TDLR |= canMessage->data[0];
//}					  	 						// DATA0
//	if(MessageSize>=2){
		_CAN_TP->sTxMailBox[mailboxNo].TDLR |= (uint32_t)(canMessage->data[1] << 8);
//} 				// DATA1	
//	if(MessageSize>=3){
		_CAN_TP->sTxMailBox[mailboxNo].TDLR |= (uint32_t)(canMessage->data[2] << 16);
//} 				// DATA2
//	if(MessageSize>=4){	
		_CAN_TP->sTxMailBox[mailboxNo].TDLR |= (uint32_t)(canMessage->data[3] << 24);
//} 				// DATA3
//	if(MessageSize>=5){
		_CAN_TP->sTxMailBox[mailboxNo].TDHR |= canMessage->data[4];
//} 													// DATA4	
//	if(MessageSize>=6){
		_CAN_TP->sTxMailBox[mailboxNo].TDHR |= (uint32_t)(canMessage->data[5] << 8);
//} 				// DATA5
//	if(MessageSize>=7){
		_CAN_TP->sTxMailBox[mailboxNo].TDHR |= (uint32_t)(canMessage->data[6] << 16);
//} 				// DATA6		
//	if(MessageSize==8){
		_CAN_TP->sTxMailBox[mailboxNo].TDHR |= (uint32_t)(canMessage->data[7] << 24);
//} 				// DATA7 	
	return 0;		
}
	
	
	/**
* brief  Can_GetEmptyMailbox: find an empty mailbox
* param  CAN1/CAN2
* param  
* retval Empty mailbox number otherwise - Error number
*/
static uint32_t Can_GetEmptyMailbox(CAN_TypeDef* _CAN_TP){		
	uint32_t EmptyMailBoxNo;

	if(_CAN_TP->TSR & (CAN_TSR_TME)){
		EmptyMailBoxNo = (_CAN_TP->TSR & CAN_TSR_CODE) >> 24;
	}else{ // no free mailboxes
		EmptyMailBoxNo=ERR_CAN_NO_EMPTY_MAILBOX;
	}
	return EmptyMailBoxNo;
}

	
	
/**
* brief  Can_Transmit_StdMessage : transmit a 8-byte message via CAN       
* param  CanMessage
* param  
* retval mailbox number, 4,5 - err
*/
uint32_t Can_Transmit_Message(CAN_TypeDef* _CAN_TP, can_message *canMessage){
	for (uint32_t i = 0; i < CAN_INTERFACES_USED; i++){
		if(CAN_buffer[i].PeriphLink == _CAN_TP){
			CAN_buffer[i].write_item(canMessage);
		}
	}
	//process_buffered_can_tx();
	return CAN_TX_OK;
}


static void Can_Transmit_BufferedMessage(CAN_TypeDef* _CAN_TP, uint8_t mailbox, struct can_message *canMessage){
	Can_SetTxMessage(_CAN_TP, canMessage, mailbox);
	_CAN_TP->sTxMailBox[mailbox].TIR  |= CAN_TI0R_TXRQ; // Command to send
	
	volatile uint32_t timeout = 0;
	while ((timeout++ < CAN_BUFFERED_TRANSMIT_TIMEOUT)){}
}



/**
* brief  After an attempt to send a can message, check transmission status
* param  CAN periph number and mailbox number
* param  
* retval values of CAN TSR register
*/	
static can_tx_result check_mailbox_status(CAN_TypeDef* _CAN_TP, uint32_t mailboxNo){
	can_tx_result result = {0};
	uint32_t shift = 8*mailboxNo;
	result.u.rqcp = (_CAN_TP->TSR & (CAN_TSR_RQCP0 << shift)) == 0 ? 0 : 1;
	if(result.u.rqcp == 0) return result;
	result.u.alst = (_CAN_TP->TSR & (CAN_TSR_ALST0 << shift)) == 0 ? 0 : 1;
	result.u.terr = (_CAN_TP->TSR & (CAN_TSR_TERR0 << shift)) == 0 ? 0 : 1;
	result.u.txok = (_CAN_TP->TSR & (CAN_TSR_TXOK0 << shift)) == 0 ? 0 : 1;
	return result;
}


/**
* brief  Can1_Recieve_StdMessage_8b : transmit a 8-byte standart id message via CAN1        
* param  FifoNo Fifo number 0 or 1
* param  
* retval
*/	
	
void Can_Recieve_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo, can_message *outup_msg){
	if(_CAN_TP->sFIFOMailBox[FifoNo].RIR & 0x04){
		outup_msg->id.ext_id = (_CAN_TP->sFIFOMailBox[FifoNo].RIR >> 3);
		outup_msg->ide = EXT_ID;
	}
	else{
		outup_msg->id.std_id.id_lowbyte  = (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RIR >> 21);
		outup_msg->id.std_id.id_highbyte = (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RIR >> 29);
		outup_msg->ide = STD_ID;
	}
	
	outup_msg->dlc         = (uint16_t)_CAN_TP->sFIFOMailBox[FifoNo].RDTR; 
//	uint16_t MessageSize;
//	MessageSize = outup_msg->dlc;	// Data fields assignation is based on the message size

	//if(MessageSize>=1){
		outup_msg->data[0]			= (uint8_t)_CAN_TP->sFIFOMailBox[FifoNo].RDLR;
 //}					 		 	 // DATA0
//	if(MessageSize>=2){
		outup_msg->data[1]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDLR >> 8);
//} 					// DATA1	
//	if(MessageSize>=3){
		outup_msg->data[2]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDLR >> 16);
//} 					// DATA2
//	if(MessageSize>=4){	
		outup_msg->data[3]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDLR >> 24);
//} 					// DATA3
//	if(MessageSize>=5){
		outup_msg->data[4]			= (uint8_t)_CAN_TP->sFIFOMailBox[FifoNo].RDHR;
//} 								// DATA4	
//	if(MessageSize>=6){
		outup_msg->data[5]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDHR >> 8);
//} 					// DATA5
//	if(MessageSize>=7){
		outup_msg->data[6]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDHR >> 16);
//} 					// DATA6		
//	if(MessageSize==8){
		outup_msg->data[7]			= (uint8_t)(_CAN_TP->sFIFOMailBox[FifoNo].RDHR >> 24);
//} 					// DATA7 	
		
//	uint8_t regCounter; 															// Set all unused fields with 0xff		
//	for(regCounter = 8; regCounter > MessageSize;){
//		outup_msg->data[--regCounter]=0xff;
//	}				
}
	



uint32_t Can_Init(can_btr_setting _btr_set1, can_btr_setting _btr_set2){
	Can_InitFilters_GatewayTemplate();
	can_enable_buffers();
	
	uint32_t result = Can1_Init(_btr_set1);
	#if CAN_INTERFACES_USED > 1
	result |= Can2_Init(_btr_set2);
	#endif
	return result;
}

/**
* brief  Reset a mailbox status
* param  RQCP_STATUS, ALST_STATUS, TERR_STATUS, TXOK_STATUS
* param  
* retval 
*/	
static void reset_mailbox_status(CAN_TypeDef* _CAN_TP, uint32_t mailboxNo, uint32_t status){
	uint32_t shift = 8*mailboxNo;
	_CAN_TP->TSR |= (status << shift);
}



uint32_t process_buffered_can_tx(){
	uint32_t mailboxNo = ERR_CAN_NO_EMPTY_MAILBOX;
	uint32_t sent_msgs = 0;
	
	for (uint16_t i = 0; i < CAN_INTERFACES_USED; i++){  // пробежаться по интерфейсам
		if(CAN_buffer[i].read_free_size() == CAN_TX_BUFFER_SIZE) continue;
		
		mailboxNo = Can_GetEmptyMailbox(CAN_buffer[i].PeriphLink);
		if(mailboxNo ==	ERR_CAN_NO_EMPTY_MAILBOX) continue;
			
		if(CAN_buffer[i].mailbox_status[mailboxNo] == CB_MAILBOX_IDLE){
			CAN_buffer[i].mailbox_status[mailboxNo] = CB_MAILBOX_BUSY;
			CAN_buffer[i].read_item((uint8_t)mailboxNo);
			Can_Transmit_BufferedMessage(CAN_buffer[i].PeriphLink, (uint8_t)mailboxNo, &CAN_buffer[i].msg[mailboxNo]);
			sent_msgs++;
		}
		else{
			CAN_buffer[i].mailbox_status[mailboxNo] = CB_MAILBOX_RETRY;
			Can_Transmit_BufferedMessage(CAN_buffer[i].PeriphLink, (uint8_t)mailboxNo, &CAN_buffer[i].msg[mailboxNo]);
			sent_msgs++;
		}
	}	// пробежаться по интерфейсам
	return sent_msgs;
}


//=================================================================================================
//=================================== Interrupt on transmit =======================================
//=================================================================================================
extern void CAN1_TX_IRQHandler(void);
void CAN1_TX_IRQHandler(void){
	for (uint32_t i = 0; i < CAN_MAX_MAILBOXES_USED; i++){
		can_tx_result result = check_mailbox_status(CAN1, i);
		if(result.u.rqcp == 1){
			if(result.u.txok == 1){
				
				reset_mailbox_status(CAN1, i, RQCP_STATUS);
				CAN_buffer[CAN1_BUF_NUM].mailbox_status[i] = CB_MAILBOX_IDLE;
			}
			else{
				reset_mailbox_status(CAN1, i, RQCP_STATUS);
				CAN_buffer[CAN1_BUF_NUM].mailbox_status[i] = CB_MAILBOX_RETRY;
				Can_Transmit_BufferedMessage(CAN_buffer[CAN1_BUF_NUM].PeriphLink, (uint8_t)i, &CAN_buffer[CAN1_BUF_NUM].msg[i]);
			}
		}
	}
}

//=================================================================================================
//=================================== Interrupt on transmit =======================================
//=================================================================================================
extern void CAN2_TX_IRQHandler(void);
void CAN2_TX_IRQHandler(void){
	#if CAN_INTERFACES_USED > 1
	for (uint32_t i = 0; i < CAN_MAX_MAILBOXES_USED; i++){
		can_tx_result result = check_mailbox_status(CAN2, i);
		if(result.u.rqcp == 1){
			if(result.u.txok == 1){
				
				reset_mailbox_status(CAN2, i, RQCP_STATUS);
				CAN_buffer[CAN2_BUF_NUM].mailbox_status[i] = CB_MAILBOX_IDLE;
			}
			else{
				reset_mailbox_status(CAN2, i, RQCP_STATUS);
				CAN_buffer[CAN2_BUF_NUM].mailbox_status[i] = CB_MAILBOX_RETRY;
				Can_Transmit_BufferedMessage(CAN_buffer[CAN2_BUF_NUM].PeriphLink, (uint8_t)i, &CAN_buffer[CAN2_BUF_NUM].msg[i]);
			}
		}
	}
	#endif
}

//=================================================================================================
//===================================== Interrupt on error ========================================
//=================================================================================================
extern void CAN1_SCE_IRQHandler(void);
void CAN1_SCE_IRQHandler(void){
	CAN1->IER &= ~CAN_IER_LECIE;
	CAN_buffer[CAN1_BUF_NUM].err_cnt++;
	
	for (uint32_t i = 0; i < CAN_MAX_MAILBOXES_USED; i++){
		can_tx_result result = check_mailbox_status(CAN1, i);
		if((result.u.alst == 1) || (result.u.terr == 1)){
			reset_mailbox_status(CAN1, i, (RQCP_STATUS | ALST_STATUS | TERR_STATUS | TXOK_STATUS));
			CAN_buffer[CAN1_BUF_NUM].mailbox_status[i] = CB_MAILBOX_RETRY;
			Can_Transmit_BufferedMessage(CAN_buffer[CAN1_BUF_NUM].PeriphLink, (uint8_t)i, &CAN_buffer[CAN1_BUF_NUM].msg[i]);
		}
	}
		
	if(CAN1->MSR & CAN_MSR_ERRI){
		CAN1->MSR |= CAN_MSR_ERRI;	
	}	
	if(CAN1->ESR & CAN_ESR_LEC){
		CAN1->ESR &= ~CAN_ESR_LEC;	
	}
	CAN1->IER |= CAN_IER_LECIE;
}


//=================================================================================================
//===================================== Interrupt on error ========================================
//=================================================================================================
extern void CAN2_SCE_IRQHandler(void);
void CAN2_SCE_IRQHandler(void){
#if CAN_INTERFACES_USED > 1
	CAN2->IER &= ~CAN_IER_LECIE;
	CAN_buffer[CAN2_BUF_NUM].err_cnt++;
	
	for (uint32_t i = 0; i < CAN_MAX_MAILBOXES_USED; i++){
		can_tx_result result = check_mailbox_status(CAN2, i);
		if((result.u.alst == 1) || (result.u.terr == 1)){
			reset_mailbox_status(CAN2, i, (RQCP_STATUS | ALST_STATUS | TERR_STATUS | TXOK_STATUS));
			CAN_buffer[CAN2_BUF_NUM].mailbox_status[i] = CB_MAILBOX_RETRY;
			Can_Transmit_BufferedMessage(CAN_buffer[CAN2_BUF_NUM].PeriphLink, (uint8_t)i, &CAN_buffer[CAN2_BUF_NUM].msg[i]);
		}
	}
		
	if(CAN2->MSR & CAN_MSR_ERRI){
		CAN2->MSR |= CAN_MSR_ERRI;	
	}	
	if(CAN2->ESR & CAN_ESR_LEC){
		CAN2->ESR &= ~CAN_ESR_LEC;	
	}
	CAN2->IER |= CAN_IER_LECIE;
	#endif
}

#endif // SUPPORT_BXCAN



#ifdef UNUSED_EXTRA
/**
* brief  Can1_InitializateFilters : Initializes CAN1 filters        
* param  Remap configuration
* param  
* retval
*/


static void Can_InitFilters(void){	
	//todo: add some more features 	
	CAN1->FMR |= CAN_FMR_FINIT; // This bit starts Filter Initialization
	CAN1->FM1R &= ~0xFFFFFFFF;
	CAN1->FS1R &= ~0xFFFFFFFF;
	CAN1->FFA1R &= ~0xFFFFFFFF;
	CAN1->FA1R	&= ~0xFFFFFFFF;
	CAN1->sFilterRegister[0].FR1 &= ~0xFFFFFFFF; // CAN->F0R1
	CAN1->sFilterRegister[0].FR2 &= ~0xFFFFFFFF;
			
	CAN1->FM1R  |=  CAN_FM1R_FBM0; 								// 1 - Id mode
	CAN1->FS1R  &=  (uint32_t)~CAN_FS1R_FSC0; 		// 0 - 16-bit
	CAN1->FFA1R &=  (uint32_t)~CAN_FFA1R_FFA0; 		// 0 - FIFO 0
	CAN1->FA1R	|=  CAN_FA1R_FACT0;								// 1 - Active	
	CAN1->sFilterRegister[0].FR1 |=  	0x215 << 5 | 0x215 << (16+5); 
	CAN1->sFilterRegister[0].FR2 |=  	0x215 << 5 | 0x215 << (16+5);	
	

	//Filter Initialization completed		
	CAN1->FMR &= (uint32_t)~CAN_FMR_FINIT;	
}


/*
static void FlushCanTxBuffers(CAN_TypeDef *_CAN_TP)	{
	for(int i=0; i<3; i++){
		_CAN_TP->sTxMailBox[i].TIR	 = 0; 
		_CAN_TP->sTxMailBox[i].TDTR = 0; 		
		_CAN_TP->sTxMailBox[i].TDLR = 0;  
		_CAN_TP->sTxMailBox[i].TDHR = 0;
	}
}
*/

/**
* brief  Can_Check_FifoPending_StdMessage : check if FIFO N is empty        
* param  
* param  
* retval 0 empty 1 - not empty
*/	
static uint32_t Can_Check_FifoPending_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo){
	if(FifoNo == CAN_FIFO_0){
		if(_CAN_TP->RF0R & CAN_RF0R_FMP0){
			return 1;
		}
		else return 0;
	}
	else {
		if(_CAN_TP->RF1R & CAN_RF1R_FMP1){
			return 1;
		}
		else return 0;
	}
}

static uint32_t check_free_buffer_size(uint32_t can_num){
	return CAN_buffer[can_num].read_free_size();
}


#endif // UNUSED_EXTRA




