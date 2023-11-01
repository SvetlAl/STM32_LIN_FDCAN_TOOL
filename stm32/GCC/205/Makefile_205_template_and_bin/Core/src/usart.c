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
#include "usart.h"

#ifdef SUPPORT_USART

//=============================== Baudrate ==================================
static uint32_t usart_calculate_baudrate(uint8_t usart_num, eUsartBaudrate kb_p_sec_value);

//================================= Pinout ==================================
static void usart_configure_rx_tx_pinout(usart_gpio_init_preset *rx_preset, usart_gpio_init_preset *tx_preset);
static void usart_configure_pinout(uint8_t usart_num);

//=============================== Buffers ===================================
static void init_usart_rx_buffer(uint8_t usart_num);

//============================ Buffers declaration ==========================

#if USART_USED(1) 
static uint8_t usart1_data[USART1_BUF_SZ];
usart_rx_buffer usart1_rx_buf;
static void urb1_write_data(uint8_t *data, uint8_t length){
	urb_write_data(&usart1_rx_buf, data, length);
}
static void urb1_read_data(uint8_t *dest_data){
	urb_read_data(&usart1_rx_buf, dest_data);
}
#endif

#if USART_USED(2) 
static uint8_t usart2_data[USART2_BUF_SZ];
usart_rx_buffer usart2_rx_buf;
static void urb2_write_data(uint8_t *data, uint8_t length){
	urb_write_data(&usart2_rx_buf, data, length);
}
static void urb2_read_data(uint8_t *dest_data){
	urb_read_data(&usart2_rx_buf, dest_data);
}
#endif

#if USART_USED(3) 
static uint8_t usart3_data[USART3_BUF_SZ];
usart_rx_buffer usart3_rx_buf;
static void urb3_write_data(uint8_t *data, uint8_t length){
	urb_write_data(&usart3_rx_buf, data, length);
}
static void urb3_read_data(uint8_t *dest_data){
	urb_read_data(&usart3_rx_buf, dest_data);
}
#endif

//============================ Buffer pointers ==============================
usart_rx_buffer *usart_bufs[] = {
	//====== dummy 0 =========
	#if USART_USED(1)
	&usart1_rx_buf,
	#elif USART_USED(2)
	&usart2_rx_buf,
	#elif USART_USED(3)
	&usart3_rx_buf,
	#endif
	
	//====== USART 1 =========
	#if USART_USED(1)
	&usart1_rx_buf,
	#elif USART_USED(2)
	&usart2_rx_buf, // dummy
	#elif USART_USED(3)
	&usart3_rx_buf, // dummy
	#endif
	
	//====== USART 2 =========
	#if USART_USED(2)
	&usart2_rx_buf,
	#elif USART_USED(1)
	&usart1_rx_buf, // dummy
	#elif USART_USED(3)
	&usart3_rx_buf, // dummy
	#endif
	
	//====== USART 3 =========
	#if USART_USED(3)
	&usart3_rx_buf
	#elif USART_USED(1)
	&usart1_rx_buf // dummy
	#elif USART_USED(2)
	&usart2_rx_buf // dummy
	#endif
};

//===========================================================================
//===========================================================================
//======================= USART control registers presets ===================
//===========================================================================
//===========================================================================
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

static inline uint16_t isUsart_Enabled(uint8_t usart_num){
	switch(usart_num){
		case 1: return USART_USED(1);
		case 2: return USART_USED(2);
		case 3: return USART_USED(3);
		default: return USART_FUNC_OFF;
	}
	return USART_FUNC_OFF;
}

static inline uint16_t isIRQ_Enabled(uint8_t usart_num){
	switch(usart_num){
		case 1: return USART_IRQ_ENABLE(1);
		case 2: return USART_IRQ_ENABLE(2);
		case 3: return USART_IRQ_ENABLE(3);
		default: return USART_FUNC_OFF;
	}
	return USART_FUNC_OFF;
}

static inline uint16_t isDMA_Enabled(uint8_t usart_num){
	switch(usart_num){
		case 1: return USART_DMA_ENABLE(1);
		case 2: return USART_DMA_ENABLE(2);
		case 3: return USART_DMA_ENABLE(3);
		default: return USART_FUNC_OFF;
	}
	return USART_FUNC_OFF;
}

static inline uint16_t isCTS_Enabled(uint8_t usart_num){
	switch(usart_num){
		case 1: return USART_CTS_ENABLE(1);
		case 2: return USART_CTS_ENABLE(2);
		case 3: return USART_CTS_ENABLE(3);
		default: return USART_FUNC_OFF;
	}
	return USART_FUNC_OFF;
}

static inline uint16_t isRTS_Enabled(uint8_t usart_num){
	switch(usart_num){
		case 1: return USART_RTS_ENABLE(1);
		case 2: return USART_RTS_ENABLE(2);
		case 3: return USART_RTS_ENABLE(3);
		default: return USART_FUNC_OFF;
	}
	return USART_FUNC_OFF;
}

static inline uint16_t isLIN_Enabled(uint8_t usart_num){
	#if defined(SUPPORT_LIN)
	switch(usart_num){
		case 1: return USART_LIN_ENABLE(1);
		case 2: return USART_LIN_ENABLE(2);
		case 3: return USART_LIN_ENABLE(3);
		default: return USART_FUNC_OFF;
	}
	#else
	(void)usart_num;
	#endif
	return USART_FUNC_OFF;
}







/**
* brief   Calculate kb/s baudate for USART
* param   usart X num 
* param  
* retval  USARTX->BRR value
 */
	
static uint32_t get_baudrate_preset(uint32_t freq, eUsartBaudrate kb_p_sec_value){
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
			if     (freq == 30) return 0xC35;
			else if(freq == 36) return 0xEA6;
			else if(freq == 60) return 0x186A;
			break;
		}
	}
	return 0;
}
	
static uint32_t usart_calculate_baudrate(uint8_t usart_num, eUsartBaudrate kb_p_sec_value){
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
	return get_baudrate_preset(freq, kb_p_sec_value);
}

/**
* brief   Init GPIO settings for RX and TX pins
* param   RX and TX ports, pins
* param  
* retval  
 */

static void usart_configure_rx_tx_pinout(usart_gpio_init_preset *rx_preset, usart_gpio_init_preset *tx_preset){
	uint32_t pos = 0;
	const uint8_t shift = 4;
	//A3
	if(rx_preset->pin <= 7){
		pos = rx_preset->pin*shift;
		rx_preset->port->CRL &= ~(uint32_t)(GPIO_CRL_CNF0   << pos);
		rx_preset->port->CRL |=  (uint32_t)(GPIO_CRL_CNF0_0 << pos);
		rx_preset->port->CRL &= ~(uint32_t)(GPIO_CRL_MODE0  << pos);
	}
	else if((rx_preset->pin > 7) & (rx_preset->pin <= 15)){
		pos = (rx_preset->pin - 8)*shift;
		rx_preset->port->CRH &= ~(uint32_t)(GPIO_CRH_CNF8   << pos);
		rx_preset->port->CRH |=  (uint32_t)(GPIO_CRH_CNF8_0 << pos);
		rx_preset->port->CRH &= ~(uint32_t)(GPIO_CRH_MODE8  << pos);
	}
	//A2
	if(tx_preset->pin <= 7){
		pos = tx_preset->pin*shift;
		tx_preset->port->CRL	&= ~(uint32_t)(GPIO_CRL_CNF0   << pos); 
		tx_preset->port->CRL	&= ~(uint32_t)(GPIO_CRL_MODE0  << pos); 
		tx_preset->port->CRL	|= (uint32_t)(GPIO_CRL_CNF0_1  << pos); 
		tx_preset->port->CRL	|= (uint32_t)(GPIO_CRL_MODE0 << pos);
	}
	else if((tx_preset->pin > 7) & (tx_preset->pin <= 15)){
		pos = (tx_preset->pin - 8)*shift;
		tx_preset->port->CRH	&= ~(uint32_t)(GPIO_CRH_CNF8   << pos); 
		tx_preset->port->CRH	&= ~(uint32_t)(GPIO_CRH_MODE8  << pos); 
		tx_preset->port->CRH	|= (uint32_t)(GPIO_CRH_CNF8_1  << pos); 
		tx_preset->port->CRH	|= (uint32_t)(GPIO_CRH_MODE8 << pos);
	}
}

/**
* TODO function is not complete
* brief   Init GPIO settings for CTS, RTS
* param   CTS, RTS ports, pins
* param  
* retval  
 */

static void usart_configure_rs232_pinout(uint32_t usart_num){
	(void)(usart_num);
}


static void usart_remap_gpio(uint32_t remap_cfg){
	if(remap_cfg != 0){
		AFIO->MAPR |= remap_cfg;
	}
}

/**
* brief   Configure all GPIOs for a usart periph
* param   usart num
* param  
* retval  
 */
static void usart_configure_pinout(uint8_t usart_num){
	if(usart_num == 1){
		usart_gpio_init_preset tx_preset = {USART1_TX_PORT, USART1_TX_PIN};
		usart_gpio_init_preset rx_preset = {USART1_RX_PORT, USART1_RX_PIN};
		usart_configure_rx_tx_pinout(&rx_preset, &tx_preset);
		usart_configure_rs232_pinout(1);
		usart_remap_gpio(USART1_REMAP);
	}
	else if(usart_num == 2){
		usart_gpio_init_preset tx_preset = {USART2_TX_PORT, USART2_TX_PIN};
		usart_gpio_init_preset rx_preset = {USART2_RX_PORT, USART2_RX_PIN};
		usart_configure_rx_tx_pinout(&rx_preset, &tx_preset);
		usart_configure_rs232_pinout(2);
		usart_remap_gpio(USART2_REMAP);
	}
	else if(usart_num == 3){
		usart_gpio_init_preset tx_preset = {USART3_TX_PORT, USART3_TX_PIN};
		usart_gpio_init_preset rx_preset = {USART3_RX_PORT, USART3_RX_PIN};
		usart_configure_rx_tx_pinout(&rx_preset, &tx_preset);
		usart_configure_rs232_pinout(3);
		usart_remap_gpio(USART3_REMAP);
	}
}

/**
* brief   Configure all USART params and start
* param   usart num, baudrate
* param  
* retval  
 */



void usart_configure_periph(uint8_t usart_num, eUsartBaudrate _baudRate){
	if((usart_num < 1) || (usart_num > MAX_USART_NUM_USED)) return;
	if(!isUsart_Enabled(usart_num)) return;
	USART_TypeDef * _usart = getUsartBase(usart_num);
	uint32_t _irq_n = (uint32_t)(usart_num + 36);
	
	usart_configure_pinout(usart_num);
	uint32_t baudRate = usart_calculate_baudrate(usart_num, _baudRate);
	_usart->BRR = (uint16_t)baudRate; 
	_usart->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	
	if(isIRQ_Enabled(usart_num)){
		_usart->CR1 |= USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
		NVIC_EnableIRQ (_irq_n);
		NVIC_SetPriority(_irq_n, 15);
		if(isLIN_Enabled(usart_num)){
			_usart->CR2 |= USART_CR2_LINEN;
			_usart->CR2 |= USART_CR2_LBDIE;
			_usart->CR2 |= USART_CR2_LBDL;
			//_usart->CR3 |= USART_CR3_HDSEL;
		}
	}
	
	if(isDMA_Enabled(usart_num)){
		_usart->CR3 |=USART_CR3_DMAR;		
		_usart->CR3 |=USART_CR3_DMAT;
		#ifdef STM32F105 
		RCC->AHBENR |=RCC_AHBENR_DMA1EN;
		#endif
	}
	if(isRTS_Enabled(usart_num)){
		_usart->CR3 |= USART_CR3_RTSE; 
	}
	if(isCTS_Enabled(usart_num)){
		_usart->CR3 |= USART_CR3_CTSE;
	}
	init_usart_rx_buffer(usart_num);
	_usart->CR1 |= USART_CR1_UE; //Enable Peripheral
}


/**
* brief  Init and start USART according to a device model
* param  
* param  
* retval 
*/
void init_device_usart(eUsartBaudrate default_baudRate){
	#if defined(DEVICE_2CAN)
	usart_configure_periph(2, default_baudRate);
	usart_configure_periph(3, default_baudRate);
	#endif
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
	while ((_usart->SR & USART_SR_TXE) == 0) {}
	_usart->DR = byte;
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
	uint32_t baudRate = usart_calculate_baudrate(usart_num, _baudRate);
	_usart->BRR = (uint16_t)baudRate; 
	_usart->CR1 |= USART_CR1_UE; //Enable Peripheral
}


/**
* brief  Init rx_buffers
* param  
* param  
* retval 
*/
static void init_usart_rx_buffer(uint8_t usart_num){
	if((usart_num < 1) || (usart_num > MAX_USART_NUM_USED)) return;
	
	#if USART_USED(1)
	usart1_rx_buf.data = usart1_data;
	usart1_rx_buf.write_pos = 0;
	usart1_rx_buf.status = URB_STATUS_IDLE;
	usart1_rx_buf.max_size = USART1_BUF_SZ;
	usart1_rx_buf.read = &urb1_read_data;
	usart1_rx_buf.write = &urb1_write_data;
	#endif

	#if USART_USED(2)
	usart2_rx_buf.data = usart2_data;
	usart2_rx_buf.write_pos = 0;
	usart2_rx_buf.status = URB_STATUS_IDLE;
	usart2_rx_buf.max_size = USART2_BUF_SZ;
	usart2_rx_buf.read = &urb2_read_data;
	usart2_rx_buf.write = &urb2_write_data;
	#endif

	#if USART_USED(3)
	usart3_rx_buf.data = usart3_data;
	usart3_rx_buf.write_pos = 0;
	usart3_rx_buf.status = URB_STATUS_IDLE;
	usart3_rx_buf.max_size = USART3_BUF_SZ;
	usart3_rx_buf.read = &urb3_read_data;
	usart3_rx_buf.write = &urb3_write_data;
	#endif
}

#if ((USART_USED(1)) && !(USART_LIN_ENABLE(1)))
extern void USART1_IRQHandler(void);
void USART1_IRQHandler(void){
	uint8_t recievedByte;
	if (USART1->SR & USART_SR_RXNE){
		recievedByte = (uint8_t)(USART1->DR); 					// Recieve a byte	
	}
	usart1_rx_buf.write(&recievedByte, 1);
	usart_recieve_data(1, usart1_rx_buf.write_pos);
}
#endif

#if ((USART_USED(2)) && !(USART_LIN_ENABLE(2)))
extern void USART2_IRQHandler(void);
void USART2_IRQHandler(void){
	
	uint8_t recievedByte;
	if (USART2->SR & USART_SR_RXNE){
		recievedByte = (uint8_t)(USART2->DR); 					// Recieve a byte	
	}
	usart2_rx_buf.write(&recievedByte, 1);
	usart_recieve_data(2, usart2_rx_buf.write_pos);
}
#endif

#if ((USART_USED(3)) && !(USART_LIN_ENABLE(3)))
extern void USART3_IRQHandler(void);
void USART3_IRQHandler(void){
	uint8_t recievedByte;
	if (USART3->SR & USART_SR_RXNE){
		recievedByte = (uint8_t)(USART3->DR); 					// Recieve a byte	
	}
	usart3_rx_buf.write(&recievedByte, 1);
	usart_recieve_data(3, usart3_rx_buf.write_pos);
}
#endif


__WEAK uint32_t usart_recieve_data(uint8_t usart_num, uint16_t length){
	(void)(usart_num);
	return length;
}

void usart_send_byte_array(uint8_t usart_num, uint8_t *data, uint8_t length){
	uint8_t pos = length;
	while(pos--){
		send_byte(usart_num, *data++);
	}
}












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
              MemoryInc_Enable            +	// Memory address is increased with every recieved byte 
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
#endif
#endif /* SUPPORT_USART */
