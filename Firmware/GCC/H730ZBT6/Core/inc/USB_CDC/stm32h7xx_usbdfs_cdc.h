#ifndef STM32H7XX_USBDFS_CDC_H_INCLUDED
#define STM32H7XX_USBDFS_CDC_H_INCLUDED


/****************************************************************
* STM32H730
* USB OTG FS device (CDC) implementation
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*
****************************************************************/

#include "device_model.h" /* used for circular buffer defs */
#ifdef USB_PERIPH_HS_IN_FS_MODE
#include <string.h>
#include "stm32h730xx.h"

#include "USB_CDC/stm32h7xx_usbdfs_macros.h"



/***************************************************
 * 			User settings
***************************************************/


#define FLUSH_FIFO_TIMEOUT             200000U
#define DTFXSTS_TIMEOUT                200000U //TODO

#define RX_FIFO_SIZE                   0x200 									// 35 - minimum working   / 128
#define TX_EP0_FIFO_SIZE               0x80 									  // 16 - minimum working  64
#define TX_EP1_FIFO_SIZE               0x174                   //320-(RX_FIFO_SIZE+TX_EP0_FIFO_SIZE)   // 128
#define TX_EP2_FIFO_SIZE               0
#define TX_EP3_FIFO_SIZE               0

#define EP1_DTFXSTS_SIZE    		TX_EP1_FIFO_SIZE	/* TX FIFO empty level */
#define EP1_MIN_DTFXSTS_LVL		         16   /* Minimum TX FIFO empty level */

#define MAX_CDC_EP0_TX_SIZ             64   /* Max TX transaction size for EP0. "64" means that you can send maximum one packet of max size
in TXCallback, then you send the rest bytes (or ZLP) in next function call. Max USB_OTG_DIEPTSIZ_XFRSIZ value.     */
#define MAX_CDC_EP1_TX_SIZ  		       64*4   /* Max TX transaction size for EP1.  Max USB_OTG_DIEPTSIZ_XFRSIZ value.      */

#define DOEPT_TRANSFER_SIZE		         0x40   /* Value used in DOEPTSIZ for EP1 */
#define DOEPT_TRANSFER_PCT 		         0x01   /* Value used in DOEPTSIZ for EP1 */



/***************************************************
 * 			EP statuses
***************************************************/
#define EP_READY 				0U
#define EP_BUSY  				1U
#define EP_ZLP   				2U

/***************************************************
 * 			EP functions return values
***************************************************/

#define EP_OK					1U
#define EP_FAILED			0U

/***************************************************
 * 			Device states
***************************************************/
typedef enum{
	DEVICE_STATE_DEFAULT =					0,
	DEVICE_STATE_RESET =						1,
	DEVICE_STATE_ADDRESSED =				2,
	DEVICE_STATE_LINECODED =				4,
	DEVICE_STATE_TX_PR =						8, /* TX transmission active */
	DEVICE_STATE_TX_FIFO1_ERROR =		16 } eDeviceState;

	typedef enum{
	LINK_STATE_DEFAULT =							0, 
	LINK_STATE_DISCONNECTED =					1,
	LINK_STATE_CONNECTED =						2 } eLinkState;


/***************************************************
 * 			SETUP stage request templates
***************************************************/
	
#define REQ_TYPE_HOST_TO_DEVICE_GET_DEVICE_DECRIPTOR		0x0680
#define REQ_TYPE_DEVICE_TO_HOST_SET_ADDRESS							0x0500
#define REQ_TYPE_DEVICE_TO_HOST_SET_CONFIGURATION				0x0900

#define DESCRIPTOR_TYPE_DEVICE													0x0100
#define DESCRIPTOR_TYPE_CONFIGURATION										0x0200
#define DESCRIPTOR_TYPE_LANG_STRING											0x0300
#define DESCRIPTOR_TYPE_MFC_STRING											0x0301
#define DESCRIPTOR_TYPE_PROD_STRING											0x0302
#define DESCRIPTOR_TYPE_SERIAL_STRING										0x0303
#define DESCRIPTOR_TYPE_CONFIGURATION_STRING						0x0304
#define DESCRIPTOR_TYPE_INTERFACE_STRING								0x0305
#define DESCRIPTOR_TYPE_DEVICE_QUALIFIER								0x0600

#define CDC_GET_LINE_CODING															0x21A1
#define CDC_SET_LINE_CODING															0x2021
#define CDC_SET_CONTROL_LINE_STATE											0x2221

#define CLEAR_FEATURE_ENDP				0x0102
#define USB_FEATURE_EP_HALT				0x0000

/***************************************************
 * 		RX packet statuses
***************************************************/

#define STS_GOUT_NAK                           1
#define STS_DATA_UPDT                          2
#define STS_XFER_COMP                          3
#define STS_SETUP_COMP                         4
#define STS_SETUP_UPDT                         6

/***************************************************
* 		Endpoint structure
***************************************************/

typedef struct EndPointStruct{
	uint16_t statusRx;
	uint16_t statusTx;

	uint16_t rxCounter;
	uint16_t txCounter;
	
	uint8_t *rxBuffer_ptr;
	uint8_t *txBuffer_ptr;
	
	uint32_t (*txCallBack)(uint8_t EPnum);
	uint32_t (*rxCallBack)(uint32_t param);
	uint32_t (*setTxBuffer)(uint8_t EPnum, uint8_t *txBuff, uint16_t len);	
} EndPointStruct; //creating new type

extern EndPointStruct EndPoint[];
/***************************************************
*
* 	Setup packet structure
* 	is used in union to access data both
* 	as structure and as raw data
*
***************************************************/
typedef struct{
	uint16_t  wRequest;
	uint16_t  wValue;
	uint16_t  wIndex;
	uint16_t  wLength;
} USB_setup_req;	/* SETUP packet buffer. Always 8 bytes */
 

typedef union{
	USB_setup_req setup_pkt;
	uint32_t raw_data[2];
} USB_setup_req_data;


/***************************************************
 *
 * 		Functions' declaration
 *
***************************************************/

/* init functions */
void USB_OTG_HS_init_pinout(void);
void USB_OTG_HS_init_device(void);

uint32_t USB_CDC_transferTXCallback(uint8_t EPnum);
uint32_t USB_CDC_transferRXCallback_EP1(uint32_t param);

uint32_t check_USB_device_status(eDeviceState state);
void clear_USB_device_status(eDeviceState state);

/* User code functions */
uint32_t USB_CDC_send_data(uint8_t *txBuff, uint16_t len);
uint32_t USB_CDC_send_2data(uint8_t *txBuff, uint16_t len, uint8_t *txBuff2, uint16_t len2);
uint32_t USB_CDC_recieve_data(uint16_t length);
eLinkState USB_CDC_process_watchdog(void);
uint32_t USB_CDC_send_array(uint8_t *txBuff, uint16_t len);

uint32_t USB_CDC_receive_data(uint16_t length);


/***************************************************
*
* 			Circular buffer example
* 			Customize it in the way you need
*
***************************************************/

#define CIRC_BUFFER_TX_SIZE USB_CDC_CIRC_BUFFER_SIZE

typedef struct {
	uint16_t  index;
	uint16_t  len;                                                       
} circBufferAddress;



#endif // USB_PERIPH_HS_IN_FS_MODE


#endif /* STM32H7XX_USBDFS_CDC_H_INCLUDED */
