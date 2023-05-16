//*****************************************************************
// 
// STM32F105/205
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************

#include "can.h"
#include "device_model.h"


/**
* brief  Can1_Initializate_Pins : Initializes pins for CAN1        
* param  Remap configuration
* param  
* retval 0 - OK  1 - Err
*/

uint32_t Can1_Init_Pins(uint32_t remapConfig){
	if(remapConfig==REMAP_CAN1){
		#ifdef STM32F105
		GPIOB->CRH	&= ~GPIO_CRH_CNF8;	//  PA11--RX  PA12--TX  for stm32f103  B8--RX  B9--TX  for stm32f105
		GPIOB->CRH 	&= ~GPIO_CRH_MODE8;	 		
		GPIOB->CRH	&= ~GPIO_CRH_CNF9;	 		
		GPIOB->CRH	|= GPIO_CRH_CNF8_0;	 
		GPIOB->CRH	|= GPIO_CRH_CNF9_1;	 
		GPIOB->CRH 	|= GPIO_CRH_MODE9;	 
		AFIO->MAPR  |= AFIO_MAPR_CAN_REMAP_REMAP2;
		#endif
		#ifdef STM32F205
		GPIOB->MODER &= ~GPIO_MODER_MODER8;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD8;
		GPIOB->MODER |= GPIO_MODER_MODER8_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED8;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_0;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL8_3;
		
		GPIOB->MODER &= ~GPIO_MODER_MODER9;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED9;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD9;
		GPIOB->MODER |= GPIO_MODER_MODER9_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED9;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_0;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL9_3;
		#endif		
	}
	else if(remapConfig==NO_REMAP_CAN1){
		//todo: add pin initialization if not remapped
	}			
	return 0;
}

/**
* brief  Can2_Initializate_Pins : Initializes pins for CAN2        
* param  Remap configuration
* param  
* retval 0 - OK  1 - Err
*/

uint32_t Can2_Init_Pins(uint32_t remapConfig){
	#ifdef STM32F105
	if(remapConfig==REMAP_CAN2){
		GPIOB->CRL	&= ~GPIO_CRL_CNF5;	// B5--RX 8  B6--TX  for stm32f105
		GPIOB->CRL 	&= ~GPIO_CRL_MODE5;	 		
		GPIOB->CRL	&= ~GPIO_CRL_CNF6;	 		
		GPIOB->CRL	|= GPIO_CRL_CNF5_0;	 
		GPIOB->CRL	|= GPIO_CRL_CNF6_1;	 
		GPIOB->CRL 	|= GPIO_CRL_MODE6;	
		AFIO->MAPR  |= AFIO_MAPR_CAN2_REMAP;
		
	}
	else if(remapConfig==NO_REMAP_CAN2){
		//todo: add pin initialization if aint remapped  	
		GPIOB->CRH	&= ~GPIO_CRH_CNF12;	// B5--RX 8  B6--TX  for stm32f105  b12 rx b13 tx
		GPIOB->CRH 	&= ~GPIO_CRH_MODE12;	 		
		GPIOB->CRH	&= ~GPIO_CRH_CNF13;	 		
		GPIOB->CRH	|= GPIO_CRH_CNF12_0;	 
		GPIOB->CRH	|= GPIO_CRH_CNF13_1;	 
		GPIOB->CRH 	|= GPIO_CRH_MODE13;	
	//	AFIO->MAPR  |= AFIO_MAPR_CAN2_REMAP;
	}				
	#endif
	#ifdef STM32F205
	if(remapConfig==REMAP_CAN2){
		GPIOB->MODER &= ~GPIO_MODER_MODER5;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;
		GPIOB->MODER |= GPIO_MODER_MODER5_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5;
		GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_0;
		GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_3;
		
		GPIOB->MODER &= ~GPIO_MODER_MODER6;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED6;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6;
		GPIOB->MODER |= GPIO_MODER_MODER6_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
		GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_0;
		GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_3;
	}
	else if(remapConfig==NO_REMAP_CAN2){
		//todo: add pin initialization if aint remapped  
		GPIOB->MODER &= ~GPIO_MODER_MODER12;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED12;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD12;
		GPIOB->MODER |= GPIO_MODER_MODER12_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED12;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL12_0;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL12_3;
		
		GPIOB->MODER &= ~GPIO_MODER_MODER13;
		GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD13;
		GPIOB->MODER |= GPIO_MODER_MODER13_1;
		GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_0;
		GPIOB->AFR[1] |= GPIO_AFRH_AFSEL13_3;
	}	
	#endif
		
	return 0;
}

/**
* brief  calculate baud settings       
* param  APB freq
* param baudrate (250, 500, 1000)
* BTR register values
*/
can_btr_setting calculate_baudrate(uint32_t baudRate){
	can_btr_setting _val;
	_val.psc = 0x0000;
	_val.bs1 = 0x00;
	_val.bs2 = 0x00;
	
	if(APB1_FREQ_MHZ == 24000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 0x0002;
			_val.bs1 = 0x06;
			_val.bs2 = 0x07;
		}
	}
	else if(APB1_FREQ_MHZ == 36000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 0x0003;
			_val.bs1 = 0x08;
			_val.bs2 = 0x07;
		}
	}
	else if(APB1_FREQ_MHZ == 60000){
		if(baudRate == CAN_BAUDRATE_500KB){
			_val.psc = 0x0002;
			_val.bs1 = 0x0D;
			_val.bs2 = 0x04;
		}
	}
	return _val;
	// @TODO : add some more baudRate configurations
}

/**
* brief  Can1_Configure_BaudRate : COnfiguring BaudRate for CAN1        
* param  BaudRate configuration
* param  
* retval 0 - OK  1 - Err
*/

uint32_t Can1_Configure_BaudRate(uint32_t baudRate){
	can_btr_setting _btr_stt = calculate_baudrate(baudRate);
	
	if((_btr_stt.bs1 != 0x0) & (_btr_stt.bs2 != 0x0)){
		CAN1->BTR &= ~CAN_BTR_TS1; // reset value
		CAN1->BTR &= ~CAN_BTR_TS2; // reset value
		CAN1->BTR &= ~CAN_BTR_SJW; // reset value

		CAN1->BTR |= _btr_stt.psc;       //Prescaler	
		CAN1->BTR |= (_btr_stt.bs1 << 16); //BS1
		CAN1->BTR |= (_btr_stt.bs2 << 20); //BS2
		return 0;
	}
	else return 1;
}

/**
* brief  Can2_Configure_BaudRate : COnfiguring BaudRate for CAN2        
* param  BaudRate configuration
* param  
* retval 0 - OK  1 - Err
*/

uint32_t Can2_Configure_BaudRate(uint32_t baudRate){	
	can_btr_setting _btr_stt = calculate_baudrate(baudRate);
	
	if((_btr_stt.bs1 != 0x0) & (_btr_stt.bs2 != 0x0)){
		CAN2->BTR &= ~CAN_BTR_TS1; // reset value
		CAN2->BTR &= ~CAN_BTR_TS2; // reset value
		CAN2->BTR &= ~CAN_BTR_SJW; // reset value

		CAN2->BTR |= _btr_stt.psc;       //Prescaler	
		CAN2->BTR |= (_btr_stt.bs1 << 16); //BS1
		CAN2->BTR |= (_btr_stt.bs2 << 20); //BS2
		return 0;
	}
	else return 1;
}

/**
* brief  Can1_Init : Initializes registers for CAN1 and starts controller        
* param  remapConfig, baudRate
* param  
* retval 0 - OK  1 - Err
*/
uint32_t Can1_Init(uint32_t remapConfig, uint32_t baudRate){
	static volatile uint32_t timeout = 0;             // Timeout counter
	Can1_Init_Pins(remapConfig);                      // Configure pins
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
	Can1_Configure_BaudRate(baudRate);	//Configuring BaudRate
	CAN1->IER |= CAN_IER_FMPIE0; 				// Enable FIFO-0 Pending interrupt
//	CAN1->IER |= CAN_IER_FMPIE1; 				// Enable FIFO-1 Pending interrupt
	CAN1->MCR |= CAN_MCR_ABOM;					// Enable auto recovery out from Buss-off	
	
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
uint32_t Can2_Init(uint32_t remapConfig, uint32_t baudRate){
	static volatile uint32_t timeout = 0;											// Timeout counter
	Can2_Init_Pins(remapConfig);	// Configure pins	
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
	Can2_Configure_BaudRate(baudRate);	//Configuring BaudRate
	CAN2->IER |= CAN_IER_FMPIE0; 				// Enable FIFO-0 Pending interrupt
	CAN2->MCR |= CAN_MCR_ABOM;					// Enable auto recovery out from Buss-off	
	
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


/**
* brief  Can1_InitializateFilters : Initializes CAN1 filters        
* param  Remap configuration
* param  
* retval
*/


void Can_InitFilters(void){	
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



void Can_InitFilters_GatewayTemplate(void){	
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
uint32_t Can_SetTxMessage(CAN_TypeDef* _CAN_TP, can_message *canMessage, uint32_t mailboxNo){
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
/* This function is designed to be able to work with a continuous CAN-traffic flow */
/* With every new transmission in the first place this function checks for the next mailbox free*/
/* E.g. If mailbox0 was used for a previous transmission, this function looks for 	*/
/* an empty mailbox starting from mailbox1,then mailbox2, then mailbox0	*/
uint32_t Can_GetEmptyMailbox(CAN_TypeDef* _CAN_TP){		
	uint32_t EmptyMailBoxNo;
  if(_CAN_TP->TSR == 0x1C000000){ //The very first message after reset
		EmptyMailBoxNo=CAN_TX_MAILBOX_0;
		return EmptyMailBoxNo;
	}			
	for (int i=0; i < CAN_EMPTY_MAILBOX_TIMEOUT; i++){
		if((_CAN_TP->TSR & CAN_TSR_TME0) && (_CAN_TP->TSR & CAN_TSR_RQCP2)  && (_CAN_TP->TSR & CAN_TSR_TXOK2)) {EmptyMailBoxNo= CAN_TX_MAILBOX_0;
			_CAN_TP->TSR |= CAN_TSR_RQCP2;
			_CAN_TP->TSR |= CAN_TSR_TXOK2;
			return EmptyMailBoxNo;
			}
		if((_CAN_TP->TSR & CAN_TSR_TME1) && (_CAN_TP->TSR & CAN_TSR_RQCP0)  && (_CAN_TP->TSR & CAN_TSR_TXOK0)) {EmptyMailBoxNo= CAN_TX_MAILBOX_1; 
			_CAN_TP->TSR |= CAN_TSR_RQCP0;
			_CAN_TP->TSR |= CAN_TSR_TXOK0;
			return EmptyMailBoxNo;
			}
		if((_CAN_TP->TSR & CAN_TSR_TME2) && (_CAN_TP->TSR & CAN_TSR_RQCP1)  && (_CAN_TP->TSR & CAN_TSR_TXOK1)) {EmptyMailBoxNo= CAN_TX_MAILBOX_2; 
			_CAN_TP->TSR |= CAN_TSR_TXOK1;
			_CAN_TP->TSR |= CAN_TSR_RQCP1;
			return EmptyMailBoxNo;
			}			
	}
	
	if(!(_CAN_TP->TSR & CAN_TSR_TME0) && !(_CAN_TP->TSR & CAN_TSR_TME1) && !(_CAN_TP->TSR & CAN_TSR_TME2)){
		EmptyMailBoxNo=ERR_CAN_NO_EMPTY_MAILBOX;//no empty mailbox found
	}			
	EmptyMailBoxNo=ERR_CAN_NO_EMPTY_MAILBOX;
	return EmptyMailBoxNo;
}




	
	
/**
* brief  Can_Transmit_StdMessage : transmit a 8-byte message via CAN       
* param  CanMessage
* param  
* retval mailbox number, 4,5 - err
*/
	
uint32_t Can_Transmit_Message(CAN_TypeDef* _CAN_TP, can_message *canMessage){
//	volatile uint32_t timeout = 0;
	uint32_t mailboxNo;
	
	mailboxNo =	Can_GetEmptyMailbox(_CAN_TP);	
	if(mailboxNo==ERR_CAN_NO_EMPTY_MAILBOX){
		return ERR_CAN_NO_EMPTY_MAILBOX;
	}
	
	Can_SetTxMessage(_CAN_TP, canMessage, mailboxNo);
	
	_CAN_TP->sTxMailBox[mailboxNo].TIR  |= CAN_TI0R_TXRQ; // Command to send
	/*
	while (timeout < CAN_TRANSMIT_TIMEOUT){
		timeout++;
	}
	*/
		
	for (int i=0; i < CAN_EMPTY_MAILBOX_TIMEOUT; i++){	
	if((mailboxNo==CAN_TX_MAILBOX_0) && (_CAN_TP->TSR & CAN_TSR_TXOK0) && (_CAN_TP->TSR & CAN_TSR_TME0) && (_CAN_TP->TSR & CAN_TSR_RQCP0)){
		return CAN_TX_MAILBOX_0;}	
	if((mailboxNo==CAN_TX_MAILBOX_1) && (_CAN_TP->TSR & CAN_TSR_TXOK1) && (_CAN_TP->TSR & CAN_TSR_TME1) && (_CAN_TP->TSR & CAN_TSR_RQCP1)){
		return CAN_TX_MAILBOX_1;}
	if((mailboxNo==CAN_TX_MAILBOX_2) && (_CAN_TP->TSR & CAN_TSR_TXOK2) && (_CAN_TP->TSR & CAN_TSR_TME2) && (_CAN_TP->TSR & CAN_TSR_RQCP2)){
		return CAN_TX_MAILBOX_2;}
	}
	return ERR_CAN_NO_EMPTY_MAILBOX;
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
	if(FifoNo==CAN_FIFO_0){
		_CAN_TP->RF0R |= CAN_RF0R_RFOM0; //release		
		}
	else{
		_CAN_TP->RF1R |= CAN_RF1R_RFOM1; //release		
		}
}
	

/**
* brief  Can_Check_FifoPending_StdMessage : check if FIFO N is empty        
* param  
* param  
* retval 0 empty 1 - not empty
*/	
	

uint32_t Can_Check_FifoPending_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo){
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

	




