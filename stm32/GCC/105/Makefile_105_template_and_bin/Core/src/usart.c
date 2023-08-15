//*****************************************************************
// USART functions
// 
// 
// 
//*****************************************************************
#include "usart.h"

// **************************** USART 1 *******************************

/**
* brief   Usart1PinConfig : Initializes pins for USART1 controller        
* param   CTS/RTS enable, Remap configuration
* param  
* retval 
 */
void Usart1PinConfig(uint32_t remapConfig, uint32_t ctsrtsConfig){
	if(remapConfig==NO_REMAP_USART1_RX_TX_PORTS){// "RX as PA10 TX as PA9"
	//********** NOT FINISHED********************
	// todo: if we don't do remapping for RX/TX, configure RX as PA10 and TX as PA9
	}
	if(remapConfig==REMAP_USART1_RX_TX_PORTS){// "RX as PB7 TX as PB6"
		// **************  RX TX Pins  **************  	
// TX must be set to Push-Pull Alnernate function	
		GPIOB->CRL	&= ~GPIO_CRL_CNF6;
		GPIOB->CRL	&= ~GPIO_CRL_MODE6; // reseting GPIO Config bits for PB6
		GPIOB->CRL	|= GPIO_CRL_CNF6_1;				// 10 AFIO Push-Pull
		GPIOB->CRL	|= GPIO_CRL_MODE6_0;			// 01 10MHz	
// The same procedure for RX. No need for Alnernate function	
		GPIOB->CRL	&= ~GPIO_CRL_CNF7;
		GPIOB->CRL	|= GPIO_CRL_CNF7_0;	// 01 General purpose open drain
		GPIOB->CRL	&= ~GPIO_CRL_MODE7;	// 00 input mode	
		AFIO->MAPR |= AFIO_MAPR_USART1_REMAP; //remapping RX and TX
	}
	
	if (ctsrtsConfig==USART1_CTS_RTS_ENABLED){// **************  RTS CST Pins  **************
		GPIOA->CRH	&= ~(uint32_t)0x000FF000; // reset PA11 and PA12 configuration 
		GPIOA->CRH	|=  (uint32_t)0x000B4000;	// configuring PA11 and PA12 pins	
		AFIO->MAPR |= (uint32_t)0x02006004;  // ***Errata*** remapping CAN off the PA11 and PA12 pins according to ERRATA claims
		USART1->CR3   |= USART_CR3_CTSE | USART_CR3_RTSE; // CTS RTS Enable
	}	
}


/**
* brief   Usart1Config : Initializes the USART1 controller registers        
* param   Interrupt on/off, Dma on/off,  BaudRate
* param  
* retval 
*/
void Usart1Config(uint32_t isIrqOn, uint32_t isDmaOn, uint32_t baudRate){
	// Baud Rate, Initial USART Config  	
	USART1->BRR 	= baudRate; 
	USART1->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	// Enable/Disable DMA
	if(isDmaOn==USART1_DMA_ON){
		USART1->CR3 |=USART_CR3_DMAR;		
		USART1->CR3 |=USART_CR3_DMAT;		
	}
	//Configure interrupts
	if(isIrqOn==USART1_IRQ_ON){
		USART1->CR1 	|=  USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
	}
}

/**
* brief  Usart1Start : Turn USART1 on        
* param   Interrupt on/off
* param  
* retval 
*/
void Usart1Start(uint32_t isIrqOn)
{
	USART1->CR1 |= USART_CR1_UE; //Enable Peripheral
	if(isIrqOn==USART1_IRQ_ON){
		NVIC_EnableIRQ (USART1_IRQn); //If Interrupts used, enable them
	}
}

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


/**
* brief   Usart2Config : Initializes the USART2 controller registers        
* param   Interrupt on/off, Dma on/off,  BaudRate
* param  
* retval 
*/
void Usart2Config(uint32_t isIrqOn, uint32_t isDmaOn, uint32_t baudRate){
	// Baud Rate, Initial USART Config  	
	USART2->BRR 	= baudRate; 
	USART2->CR1 	|= USART_CR1_TE | USART_CR1_RE;  //USART Enable, RX Enable, TX Enable, RX Interrupts enable
	// Enable/Disable DMA
	if(isDmaOn==USART2_DMA_ON){
		USART2->CR3 |=USART_CR3_DMAR;		
		USART2->CR3 |=USART_CR3_DMAT;		
	}
	//Configure interrupts
	if(isIrqOn==USART2_IRQ_ON){
		USART2->CR1 	|=  USART_CR1_RXNEIE ; //USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR3_EIE | 
	}
}

/**
* brief  Usart1Start : Turn USART1 on        
* param   Interrupt on/off
* param  
* retval 
*/
void Usart2Start(uint32_t isIrqOn)
{
	USART2->CR1 |= USART_CR1_UE; //Enable Peripheral
	if(isIrqOn==USART2_IRQ_ON){
		NVIC_EnableIRQ (USART2_IRQn); //If Interrupts used, enable them
	}
}

/**
* brief  Dma1Usart2_SendByte : Send a single byte via DMA1 and Usart2     
* param  a pointer to a byte
* param  
* retval 
*/
void Dma1Usart2_SendByte(uint8_t *pdata){
	while(!(USART2->SR & USART_SR_TC)); 			  //wait until last transmission complete	
	DMA_Disable(DMA1_Channel7); 				 				// USART1 TX is linked to DMA1 Ch4
	DMA_DeInit(DMA1_Channel7);
	DMA_Init( DMA1_Channel7,										// Channel4 is used for USART1
              (uint32_t)&(USART2->DR),				// Data register (peripherals)
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
 
	DMA1->IFCR = DMA_IFCR_CTCIF7;								// Reset an empty register flag to prevent zero-byte transmission
  DMA_Enable(DMA1_Channel7);									// Start
}

/**
* brief  Dma1Usart1_SendByteArray : Send a byte array via DMA1 and Usart1     
* param  a pointer to a byte array, array size
* param  
* retval 
*/
void Dma1Usart2_SendByteArray(uint8_t *pdata, uint32_t ArraySize){
	while(!(USART2->SR & USART_SR_TC));				//wait until last transmission complete	
	DMA_Disable(DMA1_Channel7);  					  	// USART1 TX is linked to DMA1 Ch4
	DMA_DeInit(DMA1_Channel7);
	DMA_Init( DMA1_Channel7,									// Channel4 is used for USART1
              (uint32_t)&(USART2->DR),			// Data register (peripherals)
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

	DMA1->IFCR = DMA_IFCR_CTCIF7;		// Reset an empty register flag to prevent zero-byte transmission
  DMA_Enable(DMA1_Channel7);	
}



















/*
USART1->DR = data;      
tmp = USART1->DR;        
USART_CR1_IDLEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_EIE |  USART_CR1_RXNEIE   ****** | USART_CR3_CTSE  USART_CR3_CTSIE    USART_CR3_RTSE
*/

