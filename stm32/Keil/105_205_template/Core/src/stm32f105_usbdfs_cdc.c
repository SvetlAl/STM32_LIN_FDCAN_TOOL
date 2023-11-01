/****************************************************************
* STM32F105
* USB OTG FS device (CDC) implementation
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*****************************************************************/

#include <stm32f105_usbdfs_cdc.h>
#include <stm32f105_usbdfs_macros.h>
#include "usb_cdc_desc.h"



/****************************************************************
 * 		RX buffers for Endpoint structure
 * 		May be customized or exluded
*****************************************************************/

#define RX_BUFFER_EP0_SIZE 8U 										/* Enough to set linecoding */
#define RX_BUFFER_EP1_SIZE 128U

static uint8_t rxBufferEp0[RX_BUFFER_EP0_SIZE]; /* Recieved data is stored here after application reads DFIFO. RX FIFO is shared */
static uint8_t rxBufferEp1[RX_BUFFER_EP1_SIZE]; /* Recieved data is stored here after application reads DFIFO. RX FIFO is shared */

/****************************************************************
 * 		LineCoding
 * 		The application has to set linecoding
 * 		according to host requests
*****************************************************************/

static uint8_t lineCoding[CDC_LINE_CODING_LENGTH]={
	0x00, 
	0x00,	/* 0x01, */
	0x00, /* 0xC2, */
	0x00, /* 0X0001C200 -= 115200 Kb/s */
	0x00,
	0x00,
	0x00	/* 0x08 */
};


static uint32_t device_state = DEVICE_STATE_DEFAULT; /* Device state */
//static uint32_t getdevstat(){ return device_state;}

EndPointStruct EndPoint[EP_COUNT];	/* All the Enpoints are included in this array */

static USB_setup_req_data setup_pkt_data; /* Setup Packet var */

/****************************************************************
 * 		static functions' declarations
*****************************************************************/

/* Device state */
static inline void set_device_status(eDeviceState state);


/* FIFO handlers */
static inline uint32_t DTFXSTS_timeout(uint8_t Epnum, uint32_t dtxfsts_val);

static inline uint32_t check_free_space_inFifo(uint8_t dfifo, uint32_t space);

static inline uint32_t is_epena_stuck(uint8_t EPnum);

static inline uint32_t recovery_routine_EP_IN (uint8_t EPnum);

static uint32_t write_Fifo(uint8_t dfifo, uint8_t *src, uint16_t len);

static void read_Setup_Fifo(void);


/* Init EP */
static void initEndPoints(void);

static inline void set_FIFOs_sz(void);

/* EP routine */
static inline uint32_t is_tx_ep_fifo_ready(uint8_t EPnum, uint32_t param);

static inline void toggle_Rx_EP_Status(uint8_t EPnum, uint8_t param);

static uint32_t send_zlp(uint8_t EPnum);


/***************************************************
*
* 		Circular buffer example
* 		Customize it in the way you need
*
***************************************************/
#ifdef USB_CDC_CIRC_BUF_USED

static uint8_t circBufferTx[CIRC_BUFFER_TX_SIZE];
static uint16_t writePtrTxCbuf = 0U;
static uint16_t readPtrTxCbuf = 0U;


static inline uint32_t is_circBuffer_empty(){
	if(writePtrTxCbuf == readPtrTxCbuf) return 0;
	else return 1;
}

static inline uint32_t get_circBuffer_freeSize(){
	if(is_circBuffer_empty() ==0) return CIRC_BUFFER_TX_SIZE;
	uint32_t gap = (writePtrTxCbuf > readPtrTxCbuf) ? (uint32_t)(writePtrTxCbuf - readPtrTxCbuf) : (uint32_t)(readPtrTxCbuf - writePtrTxCbuf);

	uint32_t freeSz = (writePtrTxCbuf > readPtrTxCbuf) ? CIRC_BUFFER_TX_SIZE - gap : CIRC_BUFFER_TX_SIZE - gap;
	return freeSz;
}


void write_to_circBuffer(uint8_t *buf, uint16_t len){
	
	if((writePtrTxCbuf + len) >= CIRC_BUFFER_TX_SIZE){
		uint32_t write_tail = (uint32_t)((CIRC_BUFFER_TX_SIZE) - writePtrTxCbuf);
		memcpy(&circBufferTx[writePtrTxCbuf], buf, write_tail);
		memcpy(&circBufferTx[0], (buf+write_tail), (len - write_tail));		
		writePtrTxCbuf =  (uint16_t)((writePtrTxCbuf + len) - (uint16_t)CIRC_BUFFER_TX_SIZE);
	}
	else{
		memcpy(&circBufferTx[writePtrTxCbuf], buf, len);		
		writePtrTxCbuf = (uint16_t)(writePtrTxCbuf + len);
	}
}

/**
* brief  Get a string from the Circular buffer
* param  Maximum length to get. For Example, if len=256, the function returns 256 length string index, if used space > 256.
* param  If used space < 256, the function returns used space.
* retval First character's index and length
*/
static circBufferAddress read_circBuffer(uint16_t len){
	circBufferAddress result;
	if(is_circBuffer_empty() == 0){
		result.index = 0;
		result.len = 0;
		return result;
	}
	uint16_t writtenSize = (uint16_t)(CIRC_BUFFER_TX_SIZE - get_circBuffer_freeSize());
	len = (writtenSize > len) ? len : writtenSize;
	result.index = readPtrTxCbuf;
	
	if((readPtrTxCbuf + len) >= (CIRC_BUFFER_TX_SIZE)){
		uint16_t read_tail = (uint16_t)((CIRC_BUFFER_TX_SIZE) - readPtrTxCbuf);
		result.len = read_tail;
		readPtrTxCbuf = 0;		
	}
	else{
		uint16_t read_tail = len;
		result.len = read_tail;
		readPtrTxCbuf = (uint16_t)(readPtrTxCbuf + len);
	}
	return result;
}
#endif

/***************************************************
*
* 	Initialization functions
*
***************************************************/

/**
* brief  fill endpoint structures with initial data
* param  
* param 
* retval 
*/
static void initEndPoints(){
	for(uint32_t i = 0; i < EP_COUNT; i++){
		EndPoint[i].statusRx = EP_READY;
		EndPoint[i].statusTx = EP_READY;
		EndPoint[i].rxCounter = 0;
		EndPoint[i].txCounter = 0;
	//	EndPoint[i].errCode = 0;
		EndPoint[i].setTxBuffer = &USB_CDC_setTxBuffer;
		EndPoint[i].txCallBack = &USB_CDC_transferTXCallback;
				
		/* EndPoint 0 */
		if(i==0){
			EndPoint[i].rxBuffer_ptr = rxBufferEp0;  /* RX Buffer for EP0 */
			EndPoint[i].rxCallBack = &USB_CDC_transferRXCallback_EP0;
		}
		/* EndPoint 1 */
		else if(i==1){
			EndPoint[i].rxBuffer_ptr = rxBufferEp1;	/* RX Buffer for EP1 */
			EndPoint[i].rxCallBack = &USB_CDC_transferRXCallback_EP1;
		}
		else{
			EndPoint[i].rxBuffer_ptr = 0; /* TODO add EP2 support */
		}
	}	
}

/**
* brief  Set RX and TX FIFO size and offset for each EP
* param
* param
* retval
*/
static inline void set_FIFOs_sz(){
	USB_OTG_FS->GRXFSIZ = RX_FIFO_SIZE; /* all EPs RX FIFO RAM size */
	USB_OTG_FS->DIEPTXF0_HNPTXFSIZ = ((TX_EP0_FIFO_SIZE) << 16) | RX_FIFO_SIZE; /* EP0 TX FIFO RAM size */
	USB_OTG_FS->DIEPTXF[0] = ((TX_EP1_FIFO_SIZE) << 16) | (RX_FIFO_SIZE+TX_EP0_FIFO_SIZE); /* EP1 TX FIFO RAM size */
//	USB_OTG_FS->DIEPTXF[1] = ((TX_EP2_FIFO_SIZE) << 16) | (RX_FIFO_SIZE+TX_EP0_FIFO_SIZE+TX_EP1_FIFO_SIZE); 				/* EP2 TX FIFO RAM size */
//	USB_OTG_FS->DIEPTXF[2] = ((TX_EP3_FIFO_SIZE) << 16) | (RX_FIFO_SIZE+TX_EP0_FIFO_SIZE+TX_EP1_FIFO_SIZE+TX_EP2_FIFO_SIZE); /* EP3 TX FIFO RAM size */

	for(uint32_t i = 1; i < 0x10 ; i++){
		USB_OTG_FS->DIEPTXF[i] = 0;
	}
}

/**
* brief  Init GPIO to use USB OTG for stm32f205/207
* param
* param
* retval
* A11 and A12
*/
void USB_OTG_FS_init_pinout(){
	#ifdef STM32F205
	GPIOA->MODER &= ~GPIO_MODER_MODER11;
	GPIOA->MODER |= GPIO_MODER_MODER11_1;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED11;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED11;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD11;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL11_1;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL11_3;
	
	GPIOA->MODER &= ~GPIO_MODER_MODER12;
	GPIOA->MODER |= GPIO_MODER_MODER12_1;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED12;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED12;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD12;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL12_1;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL12_3;
	#endif
	
	#ifdef STM32F105
	GPIOA->CRH	&= ~GPIO_CRH_CNF11;
	GPIOA->CRH	|=  GPIO_CRH_CNF11_0;
	GPIOA->CRH 	&= ~GPIO_CRH_MODE11_0;

	GPIOA->CRH	&= ~GPIO_CRH_CNF12;
	GPIOA->CRH	|=  GPIO_CRH_CNF12_0;
	GPIOA->CRH 	&= ~GPIO_CRH_MODE12_0;
	#endif
}

/**
* brief  Init general settings of USB_OTG periph
* param
* param
* retval
*/
void USB_OTG_FS_init_device(){
	device_state = DEVICE_STATE_DEFAULT;
	USB_OTG_FS->GAHBCFG = USB_OTG_GAHBCFG_GINT; /* Enable Global Interrupt */
//	USB_OTG_FS->GAHBCFG |= USB_OTG_GAHBCFG_TXFELVL;
//	USB_OTG_FS->GAHBCFG |= USB_OTG_GAHBCFG_PTXFELVL;

	USB_OTG_FS->GINTMSK = USB_OTG_GINTMSK_USBRST |
										//		USB_OTG_GINTMSK_ENUMDNEM |
												USB_OTG_GINTMSK_SOFM   |
												USB_OTG_GINTMSK_OEPINT |
												USB_OTG_GINTMSK_IEPINT |
												USB_OTG_GINTSTS_RXFLVL;
	
	/* Enable Global Interrupt for Reset, IN, OUT, RX not empty */

	/* TEC */
	#ifdef STM32F205
	USB_OTG_FS->GCCFG = USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS; /* Power up */
	#endif
	#ifdef STM32F105
	USB_OTG_FS->GCCFG = USB_OTG_GCCFG_PWRDWN  | USB_OTG_GCCFG_VBUSBSEN; /* Power up */
	#endif
	
	USB_OTG_DEVICE->DCTL = USB_OTG_DCTL_SDIS;  /* Soft disconnect */
	USB_OTG_PCGCCTL->PCGCCTL = 0;
	USB_OTG_FS->GUSBCFG =  USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL; /* Force device mode */
	USB_OTG_FS->GUSBCFG &= ~(uint32_t)(0x0FUL << 10UL) ;  /* USB turnaround time (according to AHB and ReferenceManual) */
	USB_OTG_FS->GUSBCFG |= (0x6 << 10);

	set_FIFOs_sz();
	/* Init  EP0: 1 Packet, 3*8 bytes */
	USB_EP_OUT(0)->DOEPTSIZ = 0;
	USB_EP_OUT(0)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1 << 19)); /* This field is decremented to zero after a packet is written into the RxFIFO */
	USB_EP_OUT(0)->DOEPTSIZ |= USB_CDC_MAX_PACKET_SIZE; /* Set in descriptor  */
	USB_EP_OUT(0)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_STUPCNT;  /* STUPCNT==0x11 means, EP can recieve 3 packets. RM says to set STUPCNT = 3*/
	USB_EP_OUT(0)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA); /* Clear NAK and enable EP0 */

	USB_OTG_DEVICE->DCFG |= USB_OTG_DCFG_DSPD_Msk;  /* Device speed - FS */
	USB_OTG_FS->GINTSTS = 0xFFFFFFFF; /* Reset Global Interrupt status */
	USB_OTG_DEVICE->DCTL &= ~USB_OTG_DCTL_SDIS;   /* Soft connect */
	initEndPoints();
	

	NVIC_SetPriority(OTG_FS_IRQn, USB_FS_IRQ_P);
	NVIC_EnableIRQ(OTG_FS_IRQn);
}

/***************************************************
*
* 	Miscellaneous service functions
*
***************************************************/
/**
* brief  Send Zero Length Packet
* param
* param
* retval OK/FAILED
*/

static uint32_t send_zlp(uint8_t EPnum){
	USB_EP_IN(EPnum)->DIEPTSIZ = 0;
	USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((1) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))); /* One Packet */
	USB_EP_IN(EPnum)->DIEPTSIZ &= ~USB_OTG_DIEPTSIZ_XFRSIZ_Msk;  /* Zero Length */
	USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;

	while(USB_EP_IN(EPnum)->DIEPTSIZ!=0){} /* make sure zlp is gone */

	USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
	clear_USB_device_status(DEVICE_STATE_TX_PR);

	EndPoint[EPnum].statusTx = EP_READY;
	USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;

	if(is_epena_stuck(EPnum) == EP_OK){
		return EP_OK;
	}
	else return EP_FAILED;
}

 /**
 * brief  Flush TxFifo
 * param  Fifo number, 10 = all Tx Fifos,
 * param  timeout (default FLUSH_FIFO_TIMEOUT)
 * retval 1 = OK, 0 = Failed
 */
uint32_t USB_FlushTxFifo(uint32_t EPnum, uint32_t timeout){
	uint32_t count = 0;
	USB_OTG_FS->GRSTCTL = (USB_OTG_GRSTCTL_TXFFLSH | (EPnum << 6));
	do{
		if (++count > timeout){
			return EP_FAILED;
		}
	}
	while ((USB_OTG_FS->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);

   return EP_OK;
}

 /**
 * brief  Flush RxFifo
 * param  timeout (default FLUSH_FIFO_TIMEOUT)
 * param
 * retval 1 = OK, 0 = Failed
 */
uint32_t USB_FlushRxFifo(uint32_t timeout){
	uint32_t count = 0;
	USB_OTG_FS->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;
	do{
		if (++count > timeout){
			return EP_FAILED;
		}
	}
	while ((USB_OTG_FS->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);

	return EP_OK;
}


 /**
 * brief  Change EP OUT status
 * brief
 * param  EP number
 * param  READY/BUSY
 * retval
 */

static inline void toggle_Rx_EP_Status(uint8_t EPnum, uint8_t param){
	if(EndPoint[EPnum].statusRx == param) return;
 	EndPoint[EPnum].statusRx = param; /* toggle status*/

	if(param==EP_READY){
		USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
 	}
		else{
			USB_EP_OUT(EPnum)->DOEPCTL |= USB_OTG_DOEPCTL_SNAK;
		}
}


/***************************************************
*
* 		DFIFO read/write
*
***************************************************/
/**
* brief  Read Setup Packet EP0
* param  
* param 
* retval 
*/
static void read_Setup_Fifo(){
	/* Read Setup packet. Always 8 bytes */
	setup_pkt_data.raw_data[0] = USB_OTG_DFIFO(0);
	setup_pkt_data.raw_data[1] = USB_OTG_DFIFO(0);
}
	
/**
* brief  Read data from DFIFO (into rxBufferMain[RX_BUFFER_MAIN_SIZE] for EP1)
* brief  If you don't handle recieved data on OEPINT event, there is a risk that the data will be lost
* param  EP number, length
* param 
* retval 
*/
void read_Fifo(uint8_t dfifo, uint16_t len){
	uint16_t residue = (len%4==0) ? 0 : 1 ;
	uint32_t block_cnt = (uint32_t)((len/4) + residue);
	uint8_t *tmp_ptr = EndPoint[dfifo].rxBuffer_ptr;

	/* If unprocessed data length exceeds Max buffer length, it has to be rewritten */
	if((dfifo == 1) & ((EndPoint[dfifo].rxCounter + len) > RX_BUFFER_EP1_SIZE)){
		EndPoint[dfifo].rxBuffer_ptr = rxBufferEp1;
		EndPoint[dfifo].rxCounter = 0;
	}
	/********************************************************************************/
	
	for (uint32_t i = 0; i < block_cnt; i++){
		*(uint32_t *)(void *)EndPoint[dfifo].rxBuffer_ptr = USB_OTG_DFIFO(0);
		EndPoint[dfifo].rxBuffer_ptr = EndPoint[dfifo].rxBuffer_ptr + 4;
	}

	if(dfifo!=0){	
		USB_EP_OUT(dfifo)->DOEPTSIZ = 0;			
		USB_EP_OUT(dfifo)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (DOEPT_TRANSFER_PCT << USB_OTG_DOEPTSIZ_PKTCNT_Pos)); 
		USB_EP_OUT(dfifo)->DOEPTSIZ |= DOEPT_TRANSFER_SIZE; 
		USB_EP_OUT(dfifo)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
	}
	
	EndPoint[dfifo].rxBuffer_ptr = tmp_ptr + len;
	EndPoint[dfifo].rxCounter = (uint16_t)(EndPoint[dfifo].rxCounter + len);
}


/**
* brief  Write data into DFIFO
* param  EP number, TX Buffer, length 
* param 
* retval OK or FAILED (in case DFIFO overrun, for better details watch my youtube)
*/
static uint32_t write_Fifo(uint8_t dfifo, uint8_t *src, uint16_t len){ 

	uint16_t residue = (len%4==0) ? 0 : 1;
	uint32_t block_cnt = (uint32_t)((len/4) + residue);
	uint32_t dtxfsts_sample = USB_EP_IN(dfifo)->DTXFSTS;
		
	for (uint32_t i = 0; (i < block_cnt) ; i++){
		USB_OTG_DFIFO(dfifo) = *((uint32_t *)(void *)src);
		src+=4;	
	} 

	if(DTFXSTS_timeout(dfifo, dtxfsts_sample)==EP_OK){
		EndPoint[dfifo].txBuffer_ptr = EndPoint[dfifo].txBuffer_ptr + len;
		EndPoint[dfifo].txCounter = (uint16_t)(EndPoint[dfifo].txCounter - len);
		
		return EP_OK;	
	}
	
	else {
		return EP_FAILED;
	} 
}


/***************************************************
*
* 		EndPoints' Callbacks
*
***************************************************/

/**
* brief  Continue TX transaction for a certain EP
* brief  check Endpoint TX status 
* param  EP number
* param 
* retval 
*/
uint32_t USB_CDC_transferTXCallback(uint8_t EPnum){ 
	
	if(EndPoint[EPnum].statusTx == EP_BUSY){
		USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);	
		return EP_FAILED;
	}
	/************** EP is ready *****************/	
	/* No data in TX Buffer */
	if(EndPoint[EPnum].txCounter==0){
		if(EndPoint[EPnum].statusTx == EP_ZLP){			
			if(send_zlp(EPnum) == EP_OK){
				return EP_OK;
			}
			else return EP_FAILED;
		}
		USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);	
		clear_USB_device_status(DEVICE_STATE_TX_PR);			
		EndPoint[EPnum].statusTx = EP_READY;
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
		return EP_OK;
	}
	
	/************** Calculate packet(s) count *****************/
	uint16_t max_tx_sz; // max transfer size considering TX FIFO size
	if(EPnum==0){
		max_tx_sz = MAX_CDC_EP0_TX_SIZ;
	}
	else max_tx_sz = MAX_CDC_EP1_TX_SIZ;
	
	/* if FIFO size is 64 bytes, but transaction is 67 bytes (DevDescriptor)
	transaction would be split into two parts:
	first one : with 64 bytes length
	second one : with 3 bytes length */
	uint32_t len;
	uint32_t residue;
	uint32_t pct_cnt;
		
	if(EndPoint[EPnum].txCounter < USB_CDC_MAX_PACKET_SIZE){
		len = EndPoint[EPnum].txCounter;
		residue = 0;
		pct_cnt = 1;
	}
	else{
		len = (EndPoint[EPnum].txCounter > max_tx_sz) ? max_tx_sz : EndPoint[EPnum].txCounter ; 
		residue = ((len % USB_CDC_MAX_PACKET_SIZE)==0) ? 0 : 1 ;
		pct_cnt = (uint32_t)((len/USB_CDC_MAX_PACKET_SIZE) + residue);
	}

	/************** Set Busy flag and start transmission *****************/

	EndPoint[EPnum].statusTx = EP_BUSY;	

	/************** data >= USB_CDC_MAX_PACKET_SIZE *****************/

	if(EndPoint[EPnum].txCounter >= USB_CDC_MAX_PACKET_SIZE){  /* counter >= 64 */
	
		USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((pct_cnt) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))) /* One Packet */
		| ((USB_OTG_DIEPTSIZ_XFRSIZ_Msk & ((len) << USB_OTG_DIEPTSIZ_XFRSIZ_Pos)));			/* Max Size */
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;
		
		while(write_Fifo(EPnum, EndPoint[EPnum].txBuffer_ptr, (uint16_t)len) == EP_FAILED ){
		
			recovery_routine_EP_IN(EPnum); 
			USB_EP_IN(EPnum)->DIEPTSIZ = 0;
			USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((pct_cnt) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))) /* One Packet */
			| ((USB_OTG_DIEPTSIZ_XFRSIZ_Msk & ((len) << USB_OTG_DIEPTSIZ_XFRSIZ_Pos)));			/* Max Size */
			USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;
			
			if((EPnum == 1) & check_free_space_inFifo(EPnum, EP1_MIN_DTFXSTS_LVL)){
				USB_FlushTxFifo(1, FLUSH_FIFO_TIMEOUT);
			}
		}			
		USB_FlushTxFifo(1, FLUSH_FIFO_TIMEOUT);  //TODO delete

		if(EndPoint[EPnum].txCounter==0 && residue == 0){ /* was this packet of MaxSize the last one in the queue ? ZLP required? */
			EndPoint[EPnum].statusTx = EP_ZLP; /* change EP TX status to ZLP, thereafter ZLP will be sent in sequential function call */
			while(is_epena_stuck(EPnum) != EP_OK){}
			send_zlp(EPnum);
			return EP_OK;
		}
	}
	/************** data <  USB_CDC_MAX_PACKET_SIZE *****************/

	else if(EndPoint[EPnum].txCounter < USB_CDC_MAX_PACKET_SIZE){
	
		USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((1) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))) /* One Packet */
		| ((USB_OTG_DIEPTSIZ_XFRSIZ_Msk & ((uint32_t)(EndPoint[EPnum].txCounter) << USB_OTG_DIEPTSIZ_XFRSIZ_Pos)));	/*  Size */
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;

		while(write_Fifo(EPnum, EndPoint[EPnum].txBuffer_ptr, (uint16_t)len) == EP_FAILED ){
			recovery_routine_EP_IN(EPnum); 
			USB_EP_IN(EPnum)->DIEPTSIZ = 0;
			USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((1) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))) /* One Packet */
			| ((USB_OTG_DIEPTSIZ_XFRSIZ_Msk & ((uint32_t)(EndPoint[EPnum].txCounter) << USB_OTG_DIEPTSIZ_XFRSIZ_Pos)));			/* Max Size */
			USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;

			if((EPnum == 1) & check_free_space_inFifo(EPnum, EP1_MIN_DTFXSTS_LVL)){
				USB_FlushTxFifo(1, FLUSH_FIFO_TIMEOUT);
			}
		}			
	//	USB_FlushTxFifo(1, FLUSH_FIFO_TIMEOUT);  //TODO delete
		clear_USB_device_status(DEVICE_STATE_TX_PR);		
	} 
		
	else{
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK;		
	}
	/************** finish transmission and set Ready flag  *****************/
	USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
	EndPoint[EPnum].statusTx = EP_READY;
	clear_USB_device_status(DEVICE_STATE_TX_PR);
	return EP_OK;
}


/**
* brief  Set and start TX transaction
* param  EP number, TX Buffer, length 
* param 
* retval OK/FAILED
*/
uint32_t USB_CDC_setTxBuffer(uint8_t EPnum, uint8_t *txBuff, uint16_t len){
	/************** Previous transaction is not finished ****************/
	if((EndPoint[EPnum].txCounter != 0) || (EndPoint[EPnum].statusTx == EP_ZLP) || (check_USB_device_status(DEVICE_STATE_TX_PR) == EP_OK)){				
		return EP_FAILED;
	}

	/************** length exceeds max TX size in user settings ****************/
	uint32_t max_transfer_sz;
	if(EPnum == 0){
		max_transfer_sz = MAX_CDC_EP0_TX_SIZ + (USB_CDC_MAX_PACKET_SIZE - 1);
	}
	else max_transfer_sz = MAX_CDC_EP1_TX_SIZ + (USB_CDC_MAX_PACKET_SIZE - 1);
	
	if(len > max_transfer_sz) return EP_FAILED;
	
	/************** All conditions are OK ****************/
	
	if(len!=0){	/* Set data to send */	
//		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
		EndPoint[EPnum].txBuffer_ptr = txBuff;
		EndPoint[EPnum].txCounter = len;

		/* Send data */			
		set_device_status(DEVICE_STATE_TX_PR);
		EndPoint[EPnum].txCallBack(EPnum);
		
		return EP_OK;
	}
	
	else{ /* Zero-Length Packet */		
		USB_EP_IN(EPnum)->DIEPTSIZ = 0;
		USB_EP_IN(EPnum)->DIEPTSIZ = ((USB_OTG_DIEPTSIZ_PKTCNT_Msk & ((1) << USB_OTG_DIEPTSIZ_PKTCNT_Pos))); /* One Packet */
		USB_EP_IN(EPnum)->DIEPTSIZ &= ~USB_OTG_DIEPTSIZ_XFRSIZ_Msk;  /* Zero Length */
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA;
	
		USB_EP_OUT(EPnum)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
		return EP_OK;
	}
}

/**
* brief  Perform some action with recieved data (EP0) and refresh EP buffer counter
* brief  For EP0 - Set lineCoding
* param  command 
* param 
* retval 
*/

uint32_t USB_CDC_transferRXCallback_EP0(uint32_t param){
	uint16_t len = EndPoint[0].rxCounter;	
	if(len==0) return EP_OK;
	if(EndPoint[0].statusRx == EP_BUSY) return EP_FAILED;
	
	if(param == CDC_SET_LINE_CODING){
		
		toggle_Rx_EP_Status(0, EP_BUSY);
		
		uint8_t *data = EndPoint[0].rxBuffer_ptr - EndPoint[0].rxCounter;
		EndPoint[0].rxBuffer_ptr = data;
		uint8_t new_linecoding_settings[CDC_LINE_CODING_LENGTH];  
		
		for(int i = 0; i < len; i++){
			new_linecoding_settings[i] = *data++;
			EndPoint[0].rxCounter--;
		}
			
		// line coding 00 C2 01 00000000 000000000000 08
		for(uint32_t i = 0; i < CDC_LINE_CODING_LENGTH; i++){
			if(i==6 && lineCoding[i]==0x08){lineCoding[i] = 0x08;}
		else
			lineCoding[i] = new_linecoding_settings[i];
		}	
			/* Toggle EP RX status */
		toggle_Rx_EP_Status(0, EP_READY);
	}
	return EP_OK;
}

/*******************************************************************************************************/
/*******************************************************************************************************/
/******************** THIS IS A DEMO HOW TO IMPLEMENT OUT EP + CIRCULAR BUF  ***************************/	
/*******************************************************************************************************/
/*******************************************************************************************************/

/**
* brief  Perform some action with recieved data (EP1) and refresh EP buffer counter
* brief  Test function works as echo and shows number of recieved bytes
* param  a command or a dummy param
* param 
* retval 
*/

__WEAK uint32_t USB_CDC_transferRXCallback_EP1(uint32_t param){
	if(EndPoint[1].statusRx == EP_BUSY) return EP_FAILED;
	/* Toggle EP RX status */
//	toggle_Rx_EP_Status(1, EP_BUSY);
			
	/* CircBufferTest */
 	uint16_t len = EndPoint[1].rxCounter;
	/* CircBufferTest */	
		
/*******************************************************************************************************/
/******** This is a demonstration of both  EndPoint[1].rxCounter ***************************************/	
/******** and circular buffer, for Echo only you don't need to use rxCounter ***************************/	
/******** , you can write in circular buffer you can write directly in write_fifo() function ***********/
/*******************************************************************************************************/	
	
	/* reset RX counter and buffer pointer */
 	EndPoint[1].rxBuffer_ptr -= EndPoint[1].rxCounter;
	EndPoint[1].rxCounter = 0;	
	
	/* CircBufferTest */
 //	write_to_circBuffer(EndPoint[1].rxBuffer_ptr, len);
	/* CircBufferTest */
	USB_CDC_recieve_data(len);

	USB_EP_OUT(1)->DOEPTSIZ = 0;			
	USB_EP_OUT(1)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (DOEPT_TRANSFER_PCT << USB_OTG_DOEPTSIZ_PKTCNT_Pos)); 
	USB_EP_OUT(1)->DOEPTSIZ |= DOEPT_TRANSFER_SIZE; 
	USB_EP_OUT(1)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
	
	/* Toggle EP RX status */
//	toggle_Rx_EP_Status(1, EP_READY);

	return param;
}

/***************************************************
*
* 			USB enumeration
*
***************************************************/

/**
* brief  USB reset handler 
* param  
* param 
* retval 
*/

void enumerate_Reset(){
	device_state = DEVICE_STATE_RESET;  
	USB_OTG_FS->GINTSTS &= ~0xFFFFFFFF;
	
	USB_OTG_DEVICE->DAINTMSK = 0x30003;
	 /* Unmask interrupts IEPM, OEPM for EP0, EP1 ,   IEPM for EP2*/
	USB_OTG_DEVICE->DOEPMSK  = USB_OTG_DOEPMSK_STUPM | USB_OTG_DOEPMSK_XFRCM; /* Unmask SETUP Phase done Mask,  TransfeR Completed interrupt for OUT */
	USB_OTG_DEVICE->DIEPMSK  =  /* USB_OTG_DIEPMSK_ITTXFEMSK | */ USB_OTG_DIEPMSK_XFRCM; /* TransfeR Completed interrupt for IN */
    
	/* Flush All Fifos */
//	USB_FlushTxFifo(10, FLUSH_FIFO_TIMEOUT);
//	USB_FlushRxFifo(FLUSH_FIFO_TIMEOUT);
	
	USB_OTG_DEVICE->DCFG  &= ~USB_OTG_DCFG_DAD_Msk;  /* before Enumeration set address 0 */


	/* Endpoint 1 */
	USB_EP_IN(1)->DIEPCTL = USB_OTG_DIEPCTL_SNAK |	
				USB_OTG_DIEPCTL_TXFNUM_0 |  /* TX Number 1 */
				USB_OTG_DIEPCTL_EPTYP_1 |  /* Eptype 10 means Bulk */
				USB_OTG_DIEPCTL_USBAEP |  /* Set Endpoint active */
				USB_CDC_MAX_PACKET_SIZE;  /* Max Packet size (bytes) */ 
	
	USB_EP_OUT(1)->DOEPCTL = USB_OTG_DOEPCTL_EPENA | 	/* Enable Endpoint */
				USB_OTG_DOEPCTL_CNAK |  /* Clear NAK */
				USB_OTG_DOEPCTL_EPTYP_1 |  /* Eptype 10 means Bulk */
				USB_OTG_DOEPCTL_USBAEP | /* Set Endpoint active */
				USB_CDC_MAX_PACKET_SIZE; /* CHK MPSIZ The application must program this field with the maximum packet size for the current logical endpoint. This value is in bytes */

	USB_EP_OUT(1)->DOEPTSIZ = 0;			
	USB_EP_OUT(1)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (DOEPT_TRANSFER_PCT << USB_OTG_DOEPTSIZ_PKTCNT_Pos)); /* RM quote: Indicates the total number of USB packets that constitute the Transfer Size amount of data for this endpoint. This field is decremented every time a packet (maximum size or short packet) is written to the RxFIFO */

	USB_EP_OUT(1)->DOEPTSIZ |= DOEPT_TRANSFER_SIZE; /* Transfer size. If you set transfer size = max. packet, the core will interrupt the application at the end of each packet */
	
	/* Endpoint 2 */
	USB_EP_IN(2)->DIEPCTL = USB_OTG_DIEPCTL_SNAK |
				USB_OTG_DIEPCTL_TXFNUM_1 | 
				USB_OTG_DIEPCTL_EPTYP |  // Eptype 11 means Interrupt EP 
				USB_OTG_DIEPCTL_USBAEP | 
				0x08; 
																									
}

/**
* brief  Handle all host requests, send all descriptors data
* param  
* param 
* retval 
*/
void enumerate_Setup(){
	uint16_t len = setup_pkt_data.setup_pkt.wLength;
	uint8_t dest[128]={0};
			
	switch(setup_pkt_data.setup_pkt.wRequest){
		
		case REQ_TYPE_HOST_TO_DEVICE_GET_DEVICE_DECRIPTOR:
			switch(setup_pkt_data.setup_pkt.wValue){
				case DESCRIPTOR_TYPE_DEVICE: 				/* Request 0x0680  Value 0x0100 */
					if(DEVICE_DESCRIPTOR_LENGTH < len) len = DEVICE_DESCRIPTOR_LENGTH;
					memcpy(&dest, &deviceDescriptor, len);
					break;
				case DESCRIPTOR_TYPE_CONFIGURATION: 			/* Request 0x0680  Value 0x0200 */
					if(CONFIGURATION_DESCRIPTOR_LENGTH < len) len = CONFIGURATION_DESCRIPTOR_LENGTH;
					memcpy(&dest, &configurationDescriptor, len);
					break;    
				case DESCRIPTOR_TYPE_DEVICE_QUALIFIER: 			/* Request 0x0680  Value 0x0600 */
					if(DEVICE_QUALIFIER_LENGTH < len) len = DEVICE_QUALIFIER_LENGTH; 
					memcpy(&dest, &deviceQualifierDescriptor, len);
					//	return; /* CUBE MX CDC actually doesn't send any data here */
					break;          
				case DESCRIPTOR_TYPE_LANG_STRING: 			/* Request 0x0680  Value 0x0300 */
					if(LANG_DESCRIPTOR_LENGTH < len) len = LANG_DESCRIPTOR_LENGTH;   
					memcpy(&dest, &languageStringDescriptor, len);				
					break; 
				case DESCRIPTOR_TYPE_MFC_STRING: 			/* Request 0x0680  Value 0x0301 */
					if(MFC_DESCRIPTOR_LENGTH < len) len = MFC_DESCRIPTOR_LENGTH;
					memcpy(&dest, &manufactorStringDescriptor, len);				
					break;
				case DESCRIPTOR_TYPE_PROD_STRING: 			/* Request 0x0680  Value 0x0302 */
					if(PRODUCT_DESCRIPTOR_LENGTH < len) len = PRODUCT_DESCRIPTOR_LENGTH;
					memcpy(&dest, &productStringDescriptor, len);				
					break;                     
				case DESCRIPTOR_TYPE_SERIAL_STRING: 			/* Request 0x0680  Value 0x0303 */
					if(SERIAL_DESCRIPTOR_LENGTH < len) len = SERIAL_DESCRIPTOR_LENGTH;
					memcpy(&dest, &serialNumberStringDescriptor, len);
					break;
				case DESCRIPTOR_TYPE_CONFIGURATION_STRING: 		/* Request 0x0680  Value 0x0304 */
					if(CONFIG_STRING_LENGTH < len) len = CONFIG_STRING_LENGTH;					
					memcpy(&dest, &configurationStringDescriptor, len);
					break;
				case DESCRIPTOR_TYPE_INTERFACE_STRING: 			/* Request 0x0680  Value 0x0305 */
					if(INTERFACE_STRING_LENGTH < len) len = INTERFACE_STRING_LENGTH;
					memcpy(&dest, &stringInterface, len);
					break;
				default:
					return;
			}
			break;
			
		case REQ_TYPE_DEVICE_TO_HOST_SET_ADDRESS: 				/* Request 0x0500  */
			USB_OTG_DEVICE->DCFG |= (uint32_t)(setup_pkt_data.setup_pkt.wValue << 4);
			set_device_status(DEVICE_STATE_ADDRESSED);
			// device_state = DEVICE_STATE_ADDRESSED;
			break;
		case REQ_TYPE_DEVICE_TO_HOST_SET_CONFIGURATION: 			/* Request 0x0900  */
			len=0; /* ZLP */
			/* TODO: set configuration */
			break;     
		
		case CDC_GET_LINE_CODING: 						/* Request 0x21A1  */
			if(CDC_LINE_CODING_LENGTH < len) len = CDC_LINE_CODING_LENGTH;
			memcpy(&dest, &lineCoding, len);
			set_device_status(DEVICE_STATE_LINECODED);
			break;
		
		case CDC_SET_LINE_CODING: 						/* Request 0x2021  */
			len=0;		
			EndPoint[0].rxCallBack(CDC_SET_LINE_CODING); //TODO
			break;       
		case CDC_SET_CONTROL_LINE_STATE: 					/* Request 0x2221  */
			len=0;	
			break;	
		case CLEAR_FEATURE_ENDP: 						/* Request 0x0201  */
			return;
		default:
			break;
	} 
	
	EndPoint[0].setTxBuffer(0, dest, len);
}


/**
* brief  Schedule a new transmission after a previous one finished
* param  
* param 
* retval EP_FAILED if conditions are not met & (USB_EP_IN(1)->DIEPINT & USB_OTG_DIEPINT_TXFE)
*/

uint32_t USB_CDC_transmit_scheduler(){
#ifdef USB_CDC_CIRC_BUF_USED
//	if(get_circBuffer_freeSize() < (512)){
		//USB_MASK_INTERRUPT(USB_OTG_GINTSTS_RXFLVL); // CHK
		//toggle_Rx_EP_Status(1, EP_BUSY);
//	}
//	else if(get_circBuffer_freeSize() > (512)){
		//USB_UNMASK_INTERRUPT(USB_OTG_GINTSTS_RXFLVL); // CHK
		//toggle_Rx_EP_Status(1, EP_READY);
//	}
	
	if((is_tx_ep_fifo_ready(1, 1) == EP_OK) & (is_circBuffer_empty() !=0 )){

		circBufferAddress newMsgaddr = read_circBuffer(MAX_CDC_EP1_TX_SIZ);
		EndPoint[1].setTxBuffer(1, &circBufferTx[newMsgaddr.index], newMsgaddr.len /*newMsg.len*/);
		return EP_OK;
	}
#endif
	return EP_FAILED; 
}

extern void OTG_FS_IRQHandler(void);
void OTG_FS_IRQHandler(){
	
	/**************************************************************/	
	/****************** Start of Frame event **********************/
	/**************************************************************/
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_SOF){ 

		USB_CDC_transmit_scheduler();

		USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_SOF);  	
		return;
	}
	
	/**************************************************************/	
	/****************** ENUMDNEM event ****************************/
	/**************************************************************/
	/*	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_ENUMDNE){  
		USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_ENUMDNE);   
   		 device_state = DEVICE_STATE_READY;

    		return;
  }*/
	
	/**************************************************************/	
	/****************** USBRST Reset event ************************/
	/**************************************************************/
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_USBRST){  
		USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_USBRST);   
		enumerate_Reset();
		return;
	 }
	/**************************************************************/
	/*************** IN endpoint event ****************************/
	/**************************************************************/
	
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_IEPINT){  /* IN endpoint event */	
		uint32_t epnums  = USB_OTG_DEVICE->DAINT; /* Read out EndPoint INTerrupt bits */

		if(epnums & 0x0001){				/* EndPoint INTerrupt bits correspond to EP0 IN*/
			uint32_t IN_interrupt = USB_EP_IN(0)->DIEPINT; /* Read out EP interrupt bit */

			if(IN_interrupt & USB_OTG_DIEPINT_XFRC){  /* Transfer completed interrupt. */ 
				EndPoint[0].txCallBack(0);									/* Process TX transmission (if TX buffer is not empty) */
			}
			USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_IEPINT);	
			CLEAR_IN_EP_INTERRUPT(0, IN_interrupt);
		}

		if( epnums & 0x0002){ /* EndPoint INTerrupt bits correspond to EP1 IN*/
			uint32_t IN_interrupt = USB_EP_IN(1)->DIEPINT;

			if(IN_interrupt & USB_OTG_DIEPINT_XFRC){  /* Transfer completed interrupt.*/ 

				EndPoint[1].txCallBack(1);			/* Process TX transmission (if TX buffer is not empty) */

				USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_IEPINT);	
				CLEAR_IN_EP_INTERRUPT(1, USB_OTG_DIEPINT_XFRC);			
			}
		}
		return;
	}
	/***************************************************************/
	/*************** OUT endpoint event ****************************/
	/***************************************************************/
	
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_OEPINT){ /* OUT endpoint event */
		USB_CLEAR_INTERRUPT(USB_OTG_GINTSTS_OEPINT);	
		uint32_t epnums  = USB_OTG_DEVICE->DAINT;    /* Read out EndPoint INTerrupt bits */
		
	/****************** 		EP 0 			*****************************/
		if( epnums & 0x00010000){ /* EndPoint INTerrupt bits correspond to EP0 OUT */  
			uint32_t epint = USB_EP_OUT(0)->DOEPINT; /* Read out Endpoint Interrupt register for EP0 */
						
			if(epint & USB_OTG_DOEPINT_STUP){		/* Setup packet recieved */ 			
				enumerate_Setup();				
				}
			if(epint & USB_OTG_DOEPINT_XFRC){
				EndPoint[0].rxCallBack(0); //TODO
							/* CNAK and EPENA must be set again after every interrupt to let this EP recieve upcoming data */		
				USB_EP_OUT(0)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);	
			}
			CLEAR_OUT_EP_INTERRUPT(0, epint);
		}

	/****************** 		EP 1  			*****************************/		
		if( epnums & 0x00020000){ /* EndPoint INTerrupt bits correspond to EP1 OUT */
			uint32_t epint = USB_EP_OUT(1)->DOEPINT; /* Read out Endpoint Interrupt register for EP0 */
			
			if(epint & USB_OTG_DOEPINT_XFRC){	
												
				EndPoint[1].rxCallBack(EP_OK);	
				/* CNAK and EPENA must be set again after every interrupt to let this EP recieve upcoming data */
				USB_EP_OUT(1)->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
				
			}
			CLEAR_OUT_EP_INTERRUPT(1, epint);		
		}   				
		return;
	}

	/***************************************************************/
	/********************* RXFLVL event ****************************/
	/***************************************************************/  
	if(USB_OTG_FS->GINTSTS & USB_OTG_GINTSTS_RXFLVL){ /* RX fifo not empty event */
		uint32_t temp = USB_OTG_FS->GRXSTSP;   /* Read out PacKeT STatuS */ 
		USB_MASK_INTERRUPT(USB_OTG_GINTSTS_RXFLVL); 
		
	/********************* Some data for (EP0, EP1) ****************************/
		if(((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_DATA_UPDT){ /* 0010: OUT data packet received */ 
		
			if(temp & USB_OTG_GRXSTSP_BCNT){ /* Byte count > 0 ??? */ 
				uint16_t length = ((temp & USB_OTG_GRXSTSP_BCNT) >> USB_OTG_GRXSTSP_BCNT_Pos);
				uint8_t EpNum =	((temp & USB_OTG_GRXSTSP_EPNUM) >> USB_OTG_GRXSTSP_EPNUM_Pos);

				read_Fifo(EpNum, length); /*  Read data from DFIFO  */
			}
		}
		/********************* SETUP PACKET for EP0 ****************************/
		else  if(((temp & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_SETUP_UPDT){  /* 0110: SETUP data packet received */
			read_Setup_Fifo();
		} 
		USB_UNMASK_INTERRUPT(USB_OTG_GINTSTS_RXFLVL); 
		return;
  }  
}





/************************************************************/
/*************************** inline *************************/
/************************************************************/


/**
* brief  This function is called to ensure that data is written in TX FIFO properly 
* param  EP number, minimum free TX FIFO level
* param  
* retval 
*/
static inline uint32_t DTFXSTS_timeout(uint8_t Epnum, uint32_t dtxfsts_val){
	
	if(Epnum ==0) return EP_OK;

	volatile uint32_t count = 0;
	do{
		if (++count > DTFXSTS_TIMEOUT){
			//return EP_FAILED;
			return EP_FAILED;
		}
	} while (!(USB_EP_IN(Epnum)->DTXFSTS == dtxfsts_val));

	return EP_OK;
}

static inline uint32_t check_free_space_inFifo(uint8_t dfifo, uint32_t space){
	if(USB_EP_IN(dfifo)->DTXFSTS >= space){
		return EP_OK;
	}
	else return EP_FAILED;
}


static inline uint32_t is_epena_stuck(uint8_t EPnum){
	if((USB_EP_IN(EPnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA)  &  				/* EPENA stuck */
		!(USB_EP_IN(EPnum)->DIEPTSIZ & USB_OTG_DIEPTSIZ_XFRSIZ) &			/* no data pending */
		((USB_EP_IN(EPnum)->DIEPTSIZ & USB_OTG_HCTSIZ_PKTCNT) != 0)){		/* packet count pending */
			
		return EP_FAILED;
	}
	else return EP_OK;
}

/**
* brief  If IN endpoint is busy and some data is stuck in TX FIFO 
* brief  this procedure is called to handle this event
* param  EP number
* param  
* retval 
*/

static inline uint32_t recovery_routine_EP_IN (uint8_t EPnum){
	if((EPnum ==1) & (is_epena_stuck (1) == EP_FAILED)){
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
		USB_EP_IN(EPnum)->DIEPCTL |= USB_OTG_DIEPCTL_SNAK;
		USB_EP_IN(EPnum)->DIEPTSIZ =0;			
		return EP_OK;
	}
	return EP_FAILED;
}
/**
* brief  Device status functions. Set/clear/check
* param  
* param  
* retval 
*/
static inline void set_device_status(eDeviceState state){
	device_state |= state;
}

void clear_USB_device_status(eDeviceState state){
	device_state &= ~(uint32_t)state;
}

uint32_t check_USB_device_status(eDeviceState state){
	if(device_state & state){
		return EP_OK;
	}
	else return EP_FAILED;
}

/**
* brief  Check if TX FIFO is ready to push there data
* param  EP number
* param  param. If you use TX queue, "param" would be message count var pending in the queue
* param  if you have a var like message_counter, you use it here, otherwise use something > 0
* retval 
*/
static inline uint32_t is_tx_ep_fifo_ready(uint8_t EPnum, uint32_t param){
	if((param > 0) & !(device_state & DEVICE_STATE_TX_PR) &
		!(USB_EP_IN(EPnum)->DIEPTSIZ & USB_OTG_DIEPTSIZ_XFRSIZ) &
		((USB_EP_IN(EPnum)->DIEPTSIZ & USB_OTG_HCTSIZ_PKTCNT) == 0) &
		!(USB_EP_IN(EPnum)->DIEPCTL & USB_OTG_DIEPCTL_EPENA)  &
		((USB_EP_IN(EPnum)->DIEPINT & USB_OTG_DIEPINT_TXFE) != 0)){
		
		return EP_OK;
	}
	else return EP_FAILED;
}
/**
* brief  This function monitors SOF messages numbers to see if a "host to device" connection is establiched
* param  
* param 
* param 
* retval OK/FAIL
*/
eLinkState USB_CDC_process_watchdog(){
	if(!(check_USB_device_status(DEVICE_STATE_ADDRESSED))) return LINK_STATE_DEFAULT;
	
	static uint32_t last_usb_frame_watchdog = 0; 
	uint32_t current_usb_frame_watchdog = USB_OTG_DEVICE->DSTS & USB_OTG_DSTS_FNSOF_Msk;
	
	if(current_usb_frame_watchdog != last_usb_frame_watchdog){
		last_usb_frame_watchdog = current_usb_frame_watchdog;
		return LINK_STATE_CONNECTED;
	}
	else{
		clear_USB_device_status(DEVICE_STATE_ADDRESSED);
		return LINK_STATE_DISCONNECTED;
	}
}



/* @TODO update */
uint32_t USB_CDC_send_data(uint8_t *txBuff, uint16_t len){
	if(len==0) return EP_OK;
	
	/* if circular buffer used */
	#ifdef USB_CDC_CIRC_BUF_USED
	if(get_circBuffer_freeSize() < len) return EP_FAILED;
	else{
		write_to_circBuffer(txBuff, len);
		return EP_OK;
	}
	#endif
	
	#ifndef USB_CDC_CIRC_BUF_USED
	/******* DEVICE_STATE_READY ******/
	if(is_tx_ep_fifo_ready(1,1) == EP_OK){
		EndPoint[1].setTxBuffer(1, txBuff, len);
		return EP_OK;
	}
	else return EP_FAILED;
	#endif
}

/* it is recommended to store RX data in a buffer and process the data in a main loop or separated task */
__WEAK uint32_t USB_CDC_recieve_data(uint16_t length){
//	uint8_t *data = EndPoint[1].rxBuffer_ptr;
//	return EP_OK;
	return length;
}
