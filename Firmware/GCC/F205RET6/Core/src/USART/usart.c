/****************************************************************
* 
* USART
*
* Alex Svetlichnyy 2018 svetlal@outlook.com
*
*
* TODO: add STM32F205 DMA support
*
*****************************************************************/
#include "USART/usart.h"

#ifdef SUPPORT_USART

#define USART_TXE_TIMEOUT     0xFFF

//=========================================================================================================
//========================================== Static functions =============================================
#ifdef SUPPORT_USART1
static void urb1_write_data(uint8_t *data, uint8_t length);
static void urb1_read_data(uint8_t *dest_data);
#endif // SUPPORT_USART1

#ifdef SUPPORT_USART2
static void urb2_write_data(uint8_t *data, uint8_t length);
static void urb2_read_data(uint8_t *dest_data);
#endif // SUPPORT_USART2

#ifdef SUPPORT_USART3
static void urb3_write_data(uint8_t *data, uint8_t length);
static void urb3_read_data(uint8_t *dest_data);
#endif // SUPPORT_USART3

static inline USART_TypeDef * getUsartBase(uint8_t usart_num);
// Baudrate
static uint32_t usart_make_baudrate(uint8_t usart_num, eUsartBaudrate kb_p_sec_value);
static uint32_t usart_calculate_baudrate_reg(uint32_t freq, eUsartBaudrate kb_p_sec_value);
// Buffers
static void init_usart_rx_buffer(uint8_t usart_num);

//=========================================================================================================
//============================================ Static vars ================================================

//============================================ Buffers declaration ========================================

#ifdef SUPPORT_USART1
static uint8_t usart1_data[USART_BUF_SZ];
usart_rx_buffer usart1_rx_buf;
#endif // SUPPORT_USART1

#ifdef SUPPORT_USART2
static uint8_t usart2_data[USART_BUF_SZ];
usart_rx_buffer usart2_rx_buf;
#endif // SUPPORT_USART2

#ifdef SUPPORT_USART3
static uint8_t usart3_data[USART_BUF_SZ];
usart_rx_buffer usart3_rx_buf;
#endif // SUPPORT_USART3


uint32_t usart_get_rx_buf_ptr(uint8_t usart_num, usart_rx_buffer* target){
	if(usart_num == 1){
		#ifdef SUPPORT_USART1
		target = &usart1_rx_buf;
		return OPERATION_OK;
		#endif // SUPPORT_USART1
		}
	else if(usart_num == 2){
		#ifdef SUPPORT_USART2
		target = &usart2_rx_buf;
		return OPERATION_OK;
		#endif // SUPPORT_USART2
		}
	else if(usart_num == 3){
		#ifdef SUPPORT_USART3
		target = &usart3_rx_buf;
		return OPERATION_OK;
		#endif // SUPPORT_USART3
		}
	(void)(target);
	return OPERATION_FAIL;
}

//=========================================================================================================
//============================================ Interrupts =================================================

#if ((defined(SUPPORT_USART1)) && !(defined(SUPPORT_USART1_LIN)))
extern void USART1_IRQHandler(void);
void USART1_IRQHandler(void){
	uint8_t receivedByte;
	if (USART1->SR & USART_SR_RXNE){
		receivedByte = (uint8_t)(USART1->DR); 					// Recieve a byte	
	}
	usart1_rx_buf.write(&receivedByte, 1);
	usart_receive_data(1, usart1_rx_buf.write_pos);
}
#endif

#if ((defined(SUPPORT_USART2)) && !(defined(SUPPORT_USART2_LIN)))
extern void USART2_IRQHandler(void);
void USART2_IRQHandler(void){
	
	uint8_t receivedByte;
	if (USART2->SR & USART_SR_RXNE){
		receivedByte = (uint8_t)(USART2->DR); 					// Recieve a byte	
	}
	usart2_rx_buf.write(&receivedByte, 1);
	usart_receive_data(2, usart2_rx_buf.write_pos);
}
#endif

#if ((defined(SUPPORT_USART3)) && !(defined(SUPPORT_USART3_LIN)))
extern void USART3_IRQHandler(void);
void USART3_IRQHandler(void){
	uint8_t receivedByte;
	if (USART3->SR & USART_SR_RXNE){
		receivedByte = (uint8_t)(USART3->DR); 					// Recieve a byte	
	}
	usart3_rx_buf.write(&receivedByte, 1);
	usart_receive_data(3, usart3_rx_buf.write_pos);
}
#endif



/**
* brief   Configure all USART1 params and start
* param   baudrate
* param  
* retval  
 */
void usart1_configure_periph(eUsartBaudrate _baudRate){
	USART1_INIT_PINS
	const uint8_t usart_num = 1;
	uint32_t _irq_n = (uint32_t)(usart_num + 36);
	uint32_t baudRate = usart_make_baudrate(usart_num, _baudRate);
	USART1->BRR = (uint16_t)baudRate; 
	USART1->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	#ifdef SUPPORT_USART1_IRQ
	USART1->CR1 |= USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
	NVIC_EnableIRQ (_irq_n);
	NVIC_SetPriority(_irq_n, USART_IRQ_P);
	#ifdef SUPPORT_USART1_LIN
	USART1->CR2 |= USART_CR2_LINEN;
	USART1->CR2 |= USART_CR2_LBDIE;
	USART1->CR2 |= USART_CR2_LBDL;
	#endif // SUPPORT_USART1_LIN
	#else
	(void)_irq_n;
	#endif // SUPPORT_USART1_IRQ
	
	/*
	USART1->CR3 |= USART_CR3_RTSE; 
	USART1->CR3 |= USART_CR3_CTSE;
	*/
	init_usart_rx_buffer(usart_num);
	USART1->CR1 |= USART_CR1_UE; //Enable Peripheral
}

/**
* brief   Configure all USART2 params and start
* param   baudrate
* param  
* retval  
 */
void usart2_configure_periph(eUsartBaudrate _baudRate){
	USART2_INIT_PINS
	const uint8_t usart_num = 2;
	uint32_t _irq_n = (uint32_t)(usart_num + 36);
	uint32_t baudRate = usart_make_baudrate(usart_num, _baudRate);
	USART2->BRR = (uint16_t)baudRate; 
	USART2->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	#ifdef SUPPORT_USART2_IRQ
	USART2->CR1 |= USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
	NVIC_EnableIRQ (_irq_n);
	NVIC_SetPriority(_irq_n, USART_IRQ_P);
	#ifdef SUPPORT_USART2_LIN
	USART2->CR2 |= USART_CR2_LINEN;
	USART2->CR2 |= USART_CR2_LBDIE;
	USART2->CR2 |= USART_CR2_LBDL;
	#endif // SUPPORT_USART2_LIN
	#endif // SUPPORT_USART2_IRQ
	
	/*
	USART2->CR3 |= USART_CR3_RTSE; 
	USART2->CR3 |= USART_CR3_CTSE;
	*/
	init_usart_rx_buffer(usart_num);
	USART2->CR1 |= USART_CR1_UE; //Enable Peripheral
}


/**
* brief   Configure all USART3 params and start
* param   baudrate
* param  
* retval  
 */
void usart3_configure_periph(eUsartBaudrate _baudRate){
	USART3_INIT_PINS
	const uint8_t usart_num = 3;
	uint32_t _irq_n = (uint32_t)(usart_num + 36);
	uint32_t baudRate = usart_make_baudrate(usart_num, _baudRate);
	USART3->BRR = (uint16_t)baudRate; 
	USART3->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	#ifdef SUPPORT_USART3_IRQ
	USART3->CR1 |= USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
	NVIC_EnableIRQ (_irq_n);
	NVIC_SetPriority(_irq_n, USART_IRQ_P);
	#ifdef SUPPORT_USART3_LIN
	USART3->CR2 |= USART_CR2_LINEN;
	USART3->CR2 |= USART_CR2_LBDIE;
	USART3->CR2 |= USART_CR2_LBDL;
	#endif // SUPPORT_USART2_LIN
	#endif // SUPPORT_USART2_IRQ
	
	/*
	USART3->CR3 |= USART_CR3_RTSE; 
	USART3->CR3 |= USART_CR3_CTSE;
	*/
	init_usart_rx_buffer(usart_num);
	USART3->CR1 |= USART_CR1_UE; //Enable Peripheral
}


/**
* brief  Init and start USART according to a device model
* param  
* param  
* retval 
*/
void init_device_usart(eUsartBaudrate _baudRate){
	#if defined(SUPPORT_USART1)
	usart2_configure_periph(_baudRate);
	#elif defined(SUPPORT_USART2)
	usart2_configure_periph(_baudRate);
	#elif defined(SUPPORT_USART3)
	usart3_configure_periph(_baudRate);
	#endif
}


/**
* brief   Set different baudrate and restart
* param   usart num, baudrate
* param  
* retval  
 */

void usart_reinit_baudrate(uint8_t usart_num, eUsartBaudrate _baudRate){
	USART_TypeDef * _usart = getUsartBase(usart_num);
	_usart->CR1 &= ~USART_CR1_UE; // Disable Peripheral
	uint32_t baudRate = usart_make_baudrate(usart_num, _baudRate);
	_usart->BRR = (uint16_t)baudRate; 
	_usart->CR1 |= USART_CR1_UE; //Enable Peripheral
}



/**
* brief  Send data without DMA 
* param  USART 1, 2, 3
* param  data pointer
* param  length
* retval 
*/
static inline void send_byte(uint8_t usart_num, uint8_t byte){
	USART_TypeDef * _usart = getUsartBase(usart_num);
	volatile uint16_t timeout = USART_TXE_TIMEOUT;
	while ((timeout-- != 0) &&  (_usart->SR & USART_SR_TXE) == 0) {}
	_usart->DR = byte;
}

__WEAK uint32_t usart_receive_data(uint8_t usart_num, uint16_t length){
	(void)(usart_num);
	return length;
}

void usart_send_byte_array(uint8_t usart_num, uint8_t *data, uint8_t length){
	uint8_t pos = length;
	while(pos--){
		send_byte(usart_num, *data++);
	}
}


//=========================================================================================================
//===================================== Static functions explained  =======================================
//=========================================================================================================
/**
* brief  Get a periphery pointer with a USART num, i.e. can_num == 1 >> USART1
* param  USART number
* param   
* retval 
 */
static inline USART_TypeDef * getUsartBase(uint8_t usart_num){
	USART_TypeDef * _usart = USART1;
	if(usart_num == 1){
		_usart = USART1;
	}
	else if(usart_num == 2){
		_usart = USART2;
	}
	else if(usart_num == 3){
		_usart = USART3;
	}
	return _usart;
}

/**
* brief   Calculate kb/s baudate for USART
* param   Periph frequency
* param   Baudrate preset
* retval  USARTX->BRR value
 */
static uint32_t usart_calculate_baudrate_reg(uint32_t freq, eUsartBaudrate kb_p_sec_value){
	switch(kb_p_sec_value){
		case(Baudrate_1200):{
			if     (freq == 30) return 0x61A8;
			else if(freq == 36) return 0x7530;
			else if(freq == 60) return 0xC350;
			break;
		}
		case(Baudrate_2400):{
			if     (freq == 30) return 0x30D4;
			else if(freq == 36) return 0x3A98;
			else if(freq == 60) return 0x61A8;
			break;
		}		
		case(Baudrate_4800):{
			if     (freq == 30) return 0x186A;
			else if(freq == 36) return 0x1D4C;
			else if(freq == 60) return 0x30D4;
			break;
		}
		case(Baudrate_9600):{
			if     (freq == 30) return 0xC35;
			else if(freq == 36) return 0xEA6;
			else if(freq == 60) return 0x186A;
			break;
		}	
		case(Baudrate_19200):{
			if     (freq == 30) return 0x61A;
			else if(freq == 36) return 0x753;
			else if(freq == 60) return 0xC35;
			break;
		}	
		case(Baudrate_38400):{
			if     (freq == 30) return 0x30D;
			else if(freq == 36) return 0x3A9;
			else if(freq == 60) return 0x61A;
			break;
		}	
		case(Baudrate_57600):{
			if     (freq == 30) return 0x208;
			else if(freq == 36) return 0x271;
			else if(freq == 60) return 0x411;
			break;
		}	
		case(Baudrate_115200):{
			if     (freq == 30) return 0x104;
			else if(freq == 36) return 0x138;
			else if(freq == 60) return 0x208;
			break;
		}			
		case(Baudrate_921600):{
			if     (freq == 30) return 0x20;
			else if(freq == 36) return 0x27;
			else if(freq == 60) return 0x41;
			break;
		}
		default:{
			if     (freq == 30) return 0x20;
			else if(freq == 36) return 0x27;
			else if(freq == 60) return 0x41;
			break;
		}
	}
	if     (freq == 30) return 0xC35;
	else if(freq == 36) return 0xEA6;
	else if(freq == 60) return 0x186A;
	return 0;
}



/**
* brief   This is a "wrap" upon "usart_calculate_baudrate_reg(uint32_t freq, eUsartBaudrate kb_p_sec_value)"
* brief   calculates baudrate reg value using usart number and baudrate preset
* param   USART num
* param   Baudrate preset
* retval  USARTX->BRR value
 */
static uint32_t usart_make_baudrate(uint8_t usart_num, eUsartBaudrate kb_p_sec_value){
	uint32_t freq = 0;
	if(usart_num == 1){
		#ifdef APB2_FREQ_60MHZ
		freq = 60;
		#elif defined(APB2_FREQ_36MHZ)
		freq = 36;
		#endif
	}
	else if(usart_num == 2){
		#ifdef APB1_FREQ_30MHZ
		freq = 30;
		#elif defined(APB1_FREQ_36MHZ)
		freq = 36;
		#endif
	}
	return usart_calculate_baudrate_reg(freq, kb_p_sec_value);
}

/**
* brief  Init USART RX buffers according to device settings
* param 
* param  
* retval 
*/
static void init_usart_rx_buffer(uint8_t usart_num){
	if(usart_num == 1){
		#ifdef SUPPORT_USART1
		usart1_rx_buf.data = usart1_data;
		usart1_rx_buf.write_pos = 0;
		usart1_rx_buf.status = URB_STATUS_IDLE;
		usart1_rx_buf.max_size = USART_BUF_SZ;
		usart1_rx_buf.read = &urb1_read_data;
		usart1_rx_buf.write = &urb1_write_data;
		#endif
	}
	else if(usart_num == 1){
		#ifdef SUPPORT_USART2
		usart2_rx_buf.data = usart2_data;
		usart2_rx_buf.write_pos = 0;
		usart2_rx_buf.status = URB_STATUS_IDLE;
		usart2_rx_buf.max_size = USART_BUF_SZ;
		usart2_rx_buf.read = &urb2_read_data;
		usart2_rx_buf.write = &urb2_write_data;
		#endif
	}
	else if(usart_num == 1){
		#ifdef SUPPORT_USART3
		usart3_rx_buf.data = usart3_data;
		usart3_rx_buf.write_pos = 0;
		usart3_rx_buf.status = URB_STATUS_IDLE;
		usart3_rx_buf.max_size = USART_BUF_SZ;
		usart3_rx_buf.read = &urb3_read_data;
		usart3_rx_buf.write = &urb3_write_data;
		#endif
	}
}


/**
* brief  "Wrap" functions to read/write a specidied buffer
* param   data ptr
* param   (length)
* retval 
 */
#ifdef SUPPORT_USART1
static void urb1_write_data(uint8_t *data, uint8_t length){urb_write_data(&usart1_rx_buf, data, length); }
static void urb1_read_data(uint8_t *dest_data){ urb_read_data(&usart1_rx_buf, dest_data); }
#endif // SUPPORT_USART1

#ifdef SUPPORT_USART2
static void urb2_write_data(uint8_t *data, uint8_t length){urb_write_data(&usart2_rx_buf, data, length); }
static void urb2_read_data(uint8_t *dest_data){urb_read_data(&usart2_rx_buf, dest_data); }
#endif // SUPPORT_USART2

#ifdef SUPPORT_USART3
static void urb3_write_data(uint8_t *data, uint8_t length){urb_write_data(&usart3_rx_buf, data, length); }
static void urb3_read_data(uint8_t *dest_data){urb_read_data(&usart3_rx_buf, dest_data); }
#endif // SUPPORT_USART3






#ifdef USART_DEBUG
/**
* brief  Dma1Usart1_SendByte : Send a single byte via DMA1 and Usart1     
* param  a pointer to a byte
* param  
* retval 
*/
void Dma1Usart1_SendByte(uint8_t *pdata){
	while(!(USART1->SR & USART_SR_TC)); 			  //wait until last transmission complete	
	DMA_Disable(DMA1_Channel4); 				 				// USART1 TX is linked to DMA1 Ch4
	DMA_DeInit(DMA1_Channel4);
	DMA_Init( DMA1_Channel4,										// Channel4 is used for USART1
              (uint32_t)&(USART1->DR),				// Data register (peripherals)
              (uint32_t)pdata,								// Buffer address(memory)
              0x1,														// Buffer size 
              TransCompl_Int_Disable      +		// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +		// Half data completed interrupt disabled 
              TransError_Int_Disable      +		// Error interrupt disabled
              ReadMemory                  +		// Reading from memory, writing to peripheral
              CircularMode_Disable        +		// Circular mode disabled 
              PeripheralInc_Disable       +		// Peripheral address not increased 
              MemoryInc_Disable           +		// Memory address not increased 
              PDataSize_B                 +		// One-Byte sized data in the peripherals
              MDataSize_B                 +		// One-Byte sized data in the memory
              DMA_Priority_Hi             +		// Priority
              M2M_Disable                 );	// Not from memory to memory
 
	DMA1->IFCR = DMA_IFCR_CTCIF4;								// Reset an empty register flag to prevent zero-byte transmission
  DMA_Enable(DMA1_Channel4);									// Start
}

/**
* brief  Dma1Usart1_SendByteArray : Send a byte array via DMA1 and Usart1     
* param  a pointer to a byte array, array size
* param  
* retval 
*/
void Dma1Usart1_SendByteArray(uint8_t *pdata, uint32_t ArraySize){
	while(!(USART1->SR & USART_SR_TC));				//wait until last transmission complete	
	DMA_Disable(DMA1_Channel4);  					  	// USART1 TX is linked to DMA1 Ch4
	DMA_DeInit(DMA1_Channel4);
	DMA_Init( DMA1_Channel4,									// Channel4 is used for USART1
              (uint32_t)&(USART1->DR),			// Data register (peripherals)
              (uint32_t)pdata,							// Buffer address(memory)
              ArraySize,										// Buffer size (param uint32_t ArraySize)
              TransCompl_Int_Disable      +	// Transmission complete interrupt disabled 
              HalfCompl_Int_Disable       +	// Half data completed interrupt disabled 
              TransError_Int_Disable      +	// Error interrupt disabled
              ReadMemory                  +	// Reading from memory, writing to peripheral
              CircularMode_Disable        +	// Circular mode disabled 
              PeripheralInc_Disable       +	// Peripheral address not increased 
              MemoryInc_Enable            +	// Memory address is increased with every received byte 
              PDataSize_B                 +	// One-Byte sized data in the peripherals
              MDataSize_B                 +	// One-Byte sized data in the memory
              DMA_Priority_Hi            +	// Priority
              M2M_Disable                 );// Not from memory to memory

	DMA1->IFCR = DMA_IFCR_CTCIF4;		// Reset an empty register flag to prevent zero-byte transmission
  DMA_Enable(DMA1_Channel4);	
}

// **************************** USART 2 *******************************

/**
* brief   Usart2PinConfig : Initializes pins for USART2 controller        
* param   CTS/RTS enable, Remap configuration
* param  
* retval 
 */ // Usart1PinConfig(REMAP_USART1_RX_TX_PORTS, USART1_CTS_RTS_DISABLED)
void Usart2PinConfig(uint32_t remapConfig, uint32_t ctsrtsConfig){
	if(remapConfig==NO_REMAP_USART2_RX_TX_PORTS){// "RX as PA3 TX as PA2"
		// TX must be set to Push-Pull Alnernate function	
		GPIOA->CRL	&= ~GPIO_CRL_CNF2;
		GPIOA->CRL	&= ~GPIO_CRL_MODE2; // reseting GPIO Config bits for PB6
		GPIOA->CRL	|= GPIO_CRL_CNF2_1;				// 10 AFIO Push-Pull
		GPIOA->CRL	|= GPIO_CRL_MODE2_0;			// 01 10MHz	
		// The same procedure for RX. No need for Alnernate function	
		GPIOA->CRL	&= ~GPIO_CRL_CNF3;
		GPIOA->CRL	|= GPIO_CRL_CNF3_0;	// 01 General purpose open drain
		GPIOA->CRL	&= ~GPIO_CRL_MODE3;	// 00 input mode	
		
	}
	if(remapConfig==REMAP_USART1_RX_TX_PORTS){// "RX as PB7 TX as PB6"
		// **************  RX TX Pins  **************  	
	//********** NOT FINISHED********************
	}
	
	if (ctsrtsConfig==USART2_CTS_RTS_ENABLED){// **************  RTS CST Pins  **************
	//********** NOT FINISHED********************
	}	
}





/********************************************************************************************/
/********************************************************************************************/
/***********                    USART data received                               ***********/
/********************************************************************************************/
/********************************************************************************************/

#if defined(DEBUG_MODE) && defined(SUPPORT_USART) && !defined(SUPPORT_LIN)
static uint8_t received_from_usart[64];

uint32_t usart_receive_data(uint8_t usart_num, uint16_t length){
	if(usart_num < 1 || usart_num > 3) return 0;
	
	if(length >= 4){
		usart_bufs[usart_num]->read(received_from_usart);
		
		uint8_t data_to_send[64];
		uint8_t pos = 0;
		data_to_send[pos++] = 'U';
		data_to_send[pos++] = 'S';
		data_to_send[pos++] = 'A';
		data_to_send[pos++] = 'R';
		data_to_send[pos++] = 'T';
		data_to_send[pos++] = SC_4BIT_TO_ASCII(((usart_num << 0) &~0xFF00));
		data_to_send[pos++] = 'R';
		data_to_send[pos++] = 'X';
		data_to_send[pos++] = ' ';
		
		uint32_t com_pos = 0;
		while((pos < 64) && (com_pos < length)){
			// data_to_send[pos++] = received_from_usart[com_pos++];
			data_to_send[pos++] = received_from_usart[com_pos++];
		}
		USB_CDC_send_data(data_to_send, pos);
		
	}
	return length;
}
#endif

#endif
#endif /* SUPPORT_USART */
