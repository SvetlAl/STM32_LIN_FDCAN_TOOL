#ifndef STM32H7XX_USBDFS_MACROS_H_INCLUDED
#define STM32H7XX_USBDFS_MACROS_H_INCLUDED

/******************************************************************************
*
* This file contains some macroses and defines for better compatibility
* with other libs. If you find any conflicting types, delete them from here
*
*
*******************************************************************************/

#include "device_model.h"

/*
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
*/
#include "stm32h730xx.h"

typedef struct
{
	__IO uint32_t PCGCR;
} USB_OTG_PWRCLKTypeDef;


#define USB_OTG_PWRCLK              ((USB_OTG_PWRCLKTypeDef *) (USB1_OTG_HS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))

#define USB_CLEAR_INTERRUPT(IRQ)    ((USB1_OTG_HS->GINTSTS) &= (IRQ))
#define USB_MASK_INTERRUPT(IRQ)     (USB1_OTG_HS->GINTMSK &= ~(IRQ))
#define USB_UNMASK_INTERRUPT(IRQ)   (USB1_OTG_HS->GINTMSK |= (IRQ))

#define CLEAR_IN_EP_INTERRUPT(NUM, IRQ)          (USB_EP_IN(NUM)->DIEPINT = (IRQ))
#define CLEAR_OUT_EP_INTERRUPT(NUM, IRQ)         (USB_EP_OUT(NUM)->DOEPINT = (IRQ))

#define USB_OTG_DEVICE      		((USB_OTG_DeviceTypeDef *) (USB_OTG_HS_PERIPH_BASE + USB_OTG_DEVICE_BASE))

#define USB_EP_OUT(i) 			((USB_OTG_OUTEndpointTypeDef *) ((USB_OTG_HS_PERIPH_BASE +  USB_OTG_OUT_ENDPOINT_BASE) + ((i) * USB_OTG_EP_REG_SIZE)))
#define USB_EP_IN(i)    		((USB_OTG_INEndpointTypeDef *)	((USB_OTG_HS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE) + ((i) * USB_OTG_EP_REG_SIZE)))
 
 
#define USB_OTG_DFIFO(i)    *(__IO uint32_t *)((uint32_t)USB_OTG_HS_PERIPH_BASE  + USB_OTG_FIFO_BASE + (i) * USB_OTG_FIFO_SIZE)

/*
typedef struct{
	__IO uint32_t PCGCCTL;
}
USB_OTG_PCGCCTLTypeDef;

#define USB_OTG_PCGCCTL      ((USB_OTG_PCGCCTLTypeDef *)( USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))
*/

#endif /* STM32H7XX_USBDFS_MACROS_H_INCLUDED */
