#ifndef USB_DESC_H_INCLUDED
#define USB_DESC_H_INCLUDED

/******************************************************************************
*
* USB CDC device descriptors
* borrowed from STMicroelectronics for educational purposes
*
*
*******************************************************************************/

#include "device_model.h"

#ifdef STM32F205
#include "stm32f205xx.h"
#endif
#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif
#endif
#include "stm32f105_usbdfs_cdc.h"
#include "stm32f105_usbdfs_macros.h"


#define USB_CDC_MAX_PACKET_SIZE       64
#define CDC_CMD_PACKET_SIZE           8  /* Control Endpoint Packet size */
#define EP0_SIZE                      64
#define EP_COUNT                      3


#define USBD_VID                      1155
#define USBD_LANGID_STRING            1033
#define USBD_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_PID_FS                   22336
#define USBD_PRODUCT_STRING_FS        "STM32 Virtual ComPort"

#define DEVICE_DESCRIPTOR_LENGTH          18
#define CONFIGURATION_DESCRIPTOR_LENGTH   67

#define LANG_DESCRIPTOR_LENGTH            4
#define MFC_DESCRIPTOR_LENGTH             38
#define PRODUCT_DESCRIPTOR_LENGTH         44
#define SERIAL_DESCRIPTOR_LENGTH          26
#define DEVICE_QUALIFIER_LENGTH           10
#define INTERFACE_STRING_LENGTH           28
#define CONFIG_STRING_LENGTH              22

#define CDC_LINE_CODING_LENGTH            7

/* Device string descriptor */
static const uint8_t deviceDescriptor[DEVICE_DESCRIPTOR_LENGTH] = {
	DEVICE_DESCRIPTOR_LENGTH, //
	0x01, /* Descriptor type - device */
	0x00, /*  0x0110 = usb 1.1 ; 0x0200 = usb 2.0 */
	0x02,
	0x02, /* CDC */
	0x02, /*  Abstract Control Model subclass */
	0x00,  /* protocol */
	EP0_SIZE, /* EP0 size */
	LOBYTE(USBD_VID), 
	HIBYTE(USBD_VID),
	LOBYTE(USBD_PID_FS),
	HIBYTE(USBD_PID_FS),
	0x00, /* ver. (BCD) */
	0x02, /* ver. (BCD) */	
	0x01, /* Manufactor string index */
	0x02, /* Product string index */
	0x03, /* Serial number string index */
	1 /* configuration count */
};

/* Configuration descriptor */
static const uint8_t configurationDescriptor[CONFIGURATION_DESCRIPTOR_LENGTH] = {
	/*Configuration Descriptor*/
	0x09,   /* bLength: Configuration Descriptor size */
	0x02,      /* bDescriptorType: Configuration */
	CONFIGURATION_DESCRIPTOR_LENGTH,                /* wTotalLength:no of returned bytes */
	0x00,
	0x02,   /* bNumInterfaces: 2 interface */
	0x01,   /* bConfigurationValue: Configuration value */
	0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
	0xC0,   /* bmAttributes: self powered */
	0x32,   /* MaxPower 0 mA */

	/*---------------------------------------------------------------------------*/

	/*Interface Descriptor */
	0x09,   /* bLength: Interface Descriptor size */
	0x04,  /* bDescriptorType: Interface */
	/* Interface descriptor type */
	0x00,   /* bInterfaceNumber: Number of Interface */
	0x00,   /* bAlternateSetting: Alternate setting */
	0x01,   /* bNumEndpoints: One endpoints used */
	0x02,   /* bInterfaceClass: Communication Interface Class */
	0x02,   /* bInterfaceSubClass: Abstract Control Model */
	0x01,   /* bInterfaceProtocol: Common AT commands */
	0x00,   /* iInterface: */

	/*Header Functional Descriptor*/
	0x05,   /* bLength: Endpoint Descriptor size */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x00,   /* bDescriptorSubtype: Header Func Desc */
	0x10,   /* bcdCDC: spec release number */
	0x01,

	/*Call Management Functional Descriptor*/
	0x05,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x01,   /* bDescriptorSubtype: Call Management Func Desc */
	0x00,   /* bmCapabilities: D0+D1 */
	0x01,   /* bDataInterface: 1 */

	/*ACM Functional Descriptor*/
	0x04,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
	0x02,   /* bmCapabilities */

	/*Union Functional Descriptor*/
	0x05,   /* bFunctionLength */
	0x24,   /* bDescriptorType: CS_INTERFACE */
	0x06,   /* bDescriptorSubtype: Union func desc */
	0x00,   /* bMasterInterface: Communication class interface */
	0x01,   /* bSlaveInterface0: Data Class Interface */

	/*Endpoint 2 Descriptor*/
	0x07,                           /* bLength: Endpoint Descriptor size */
	0x05,   /* bDescriptorType: Endpoint */
	0x82,                     /* bEndpointAddress */
	0x03,                           /* bmAttributes: Interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
	HIBYTE(CDC_CMD_PACKET_SIZE),
	0x10,                           /* bInterval: */
	/*---------------------------------------------------------------------------*/

	/*Data class interface descriptor*/
	0x09,   /* bLength: Endpoint Descriptor size */
	0x04,  /* bDescriptorType: */
	0x01,   /* bInterfaceNumber: Number of Interface */
	0x00,   /* bAlternateSetting: Alternate setting */
	0x02,   /* bNumEndpoints: Two endpoints used */
	0x0A,   /* bInterfaceClass: CDC */
	0x00,   /* bInterfaceSubClass: */
	0x00,   /* bInterfaceProtocol: */
	0x00,   /* iInterface: */

	/*Endpoint OUT Descriptor*/
	0x07,   /* bLength: Endpoint Descriptor size */
	0x05,      /* bDescriptorType: Endpoint */
	0x01,                        /* bEndpointAddress */
	0x02,                              /* bmAttributes: Bulk */
	LOBYTE(USB_CDC_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
	HIBYTE(USB_CDC_MAX_PACKET_SIZE),
	0x00,                              /* bInterval: ignore for Bulk transfer */

	/*Endpoint IN Descriptor*/
	0x07,   /* bLength: Endpoint Descriptor size */
	0x05,      /* bDescriptorType: Endpoint */
	0x81,                         /* bEndpointAddress */
	0x02,                              /* bmAttributes: Bulk */
	LOBYTE(USB_CDC_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
	HIBYTE(USB_CDC_MAX_PACKET_SIZE),
	0x00                               /* bInterval: ignore for Bulk transfer */
};


/* Language string descriptor */
static const uint8_t languageStringDescriptor[LANG_DESCRIPTOR_LENGTH] = {
	LANG_DESCRIPTOR_LENGTH,				 /* USB_LEN_LANGID_STR_DESC */
	0x03,    			/* USB_DESC_TYPE_STRING */
	LOBYTE(USBD_LANGID_STRING),
	HIBYTE(USBD_LANGID_STRING)
};
/* Manufactor string descriptor */
static const uint8_t manufactorStringDescriptor[MFC_DESCRIPTOR_LENGTH] = {
	MFC_DESCRIPTOR_LENGTH,				 
	0x03,	/* USB_DESC_TYPE_STRING */
	'S', 0x00,
	'T', 0x00, 
	'M', 0x00, 
	'i', 0x00, 
	'c', 0x00, 
	'r', 0x00, 
	'o', 0x00, 
	'e', 0x00, 
	'l', 0x00, 
	'e', 0x00, 
	'c', 0x00, 
	't', 0x00, 
	'r', 0x00, 
	'o', 0x00,			
	'n', 0x00, 
	'i', 0x00, 
	'c', 0x00, 
	's', 0x00
};
/* Product string descriptor */
static const uint8_t productStringDescriptor[PRODUCT_DESCRIPTOR_LENGTH] = {
	PRODUCT_DESCRIPTOR_LENGTH, 
	0x03,	/* USB_DESC_TYPE_STRING */
	'S', 0x00, 
	'T', 0x00, 
	'M', 0x00, 
	'3', 0x00, 
	'2', 0x00, 
	' ', 0x00, 
	'V', 0x00, 
	'i', 0x00, 
	'r', 0x00, 
	't', 0x00, 
	'u', 0x00, 
	'a', 0x00, 
	'l', 0x00, 
	' ', 0x00,
	'C', 0x00, 
	'o', 0x00, 
	'm', 0x00, 
	'P', 0x00, 
	'o', 0x00, 
	'r', 0x00, 
	't', 0x00
};
/* Serial number string descriptor */
static const uint8_t serialNumberStringDescriptor[SERIAL_DESCRIPTOR_LENGTH] = {
	SERIAL_DESCRIPTOR_LENGTH,	 
	0x03,	/* USB_DESC_TYPE_STRING */
	0x34, 0x00,
	0x38, 0x00, 
	0x00, 0x00, 
	0x45, 0x00, 
	0x37, 0x00, 
	0x34, 0x00, 
	0x46, 0x00, 
	0x37, 0x00, 
	0x36, 0x00, 
	0x33, 0x00, 
	0x30, 0x00, 
	0x38, 0x00
};
/* Device qualifier string descriptor */
static const uint8_t deviceQualifierDescriptor[DEVICE_QUALIFIER_LENGTH] = {
	DEVICE_QUALIFIER_LENGTH,
	0x06,	/* Device Qualifier */
	0x00,
	0x02,
	0x00,
	0x00,
	0x00,
	0x40,
	0x01,
	0x00
};


static const uint8_t stringInterface[INTERFACE_STRING_LENGTH] = {
	INTERFACE_STRING_LENGTH, 
	0x03,	/* USB_DESC_TYPE_STRING */
	'C', 0x00, 
	'D', 0x00, 
	'C', 0x00, 
	' ', 0x00, 
	'I', 0x00, 
	'n', 0x00, 
	't', 0x00, 
	'e', 0x00, 
	'r', 0x00, 
	'f', 0x00, 
	'a', 0x00, 
	'c', 0x00, 
	'e', 0x00
};

static const uint8_t configurationStringDescriptor[CONFIG_STRING_LENGTH] = {
	CONFIG_STRING_LENGTH, 
	0x03,	/* USB_DESC_TYPE_STRING */
	'C', 0x00, 
	'D', 0x00, 
	'C', 0x00, 
	' ', 0x00, 
	'C', 0x00, 
	'o', 0x00, 
	'n', 0x00, 
	'f', 0x00, 
	'i', 0x00, 
	'g', 0x00
};

#endif /* USB_DESC_H_INCLUDED */

