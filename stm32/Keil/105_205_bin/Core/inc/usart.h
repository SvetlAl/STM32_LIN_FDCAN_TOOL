#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED
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

#include "usart_rx_buffer.h"

#ifdef STM32F105
#include "10x_dma.h"
#endif

#define USART_FUNC_ON  1
#define USART_FUNC_OFF 0

#ifdef SUPPORT_USART
typedef struct usart_gpio_init_preset{
	GPIO_TypeDef* port;
	uint32_t pin; 
}usart_gpio_init_preset;


typedef enum{
	Baudrate_1200  = 1200,
	Baudrate_2400  = 2400,
	Baudrate_4800  = 4800,
	Baudrate_9600  = 9600,
	Baudrate_19200 = 19200,
	Baudrate_38400 = 38400,
	Baudrate_57600 = 57600,
	Baudrate_115200 = 115200,
	Baudrate_921600 = 921600} eUsartBaudrate;

	
//=============================== Baudrate ==================================

	
//================================= Pinout ==================================

//============================== General ====================================	
void usart_configure_periph(uint8_t usart_num, eUsartBaudrate _baudRate);
void init_device_usart(eUsartBaudrate default_baudRate);
void usart_reinit_baudrate(uint8_t usart_num, eUsartBaudrate _baudRate);
	
//=============================== Read/write ================================	
uint32_t usart_recieve_data(uint8_t usart_num, uint16_t length);
void usart_send_byte_array(uint8_t usart_num, uint8_t *data, uint8_t length);

//=========================== GPIO definitions ==============================	
	
#if defined(DEVICE_2CAN)
//================================= USARTS ==================================	
	#define MAX_USART_NUM_USED 3
	
	#define USART_USED(usart)       usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
	#define USART_IRQ_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
	#define USART_DMA_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
	#define USART_RTS_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
	#define USART_CTS_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
#if defined(SUPPORT_LIN)
	#define USART_LIN_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
#else 
	#define USART_LIN_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF  : usart==2 ? 1 : USART_FUNC_OFF
#endif
	
//================================= USART 1 =================================	
	#define USART1_TX_PORT    GPIOA
	#define USART1_TX_PIN     6
	#define USART1_RX_PORT    GPIOA
	#define USART1_RX_PIN     7
	#define USART1_REMAP      0
	#define USART1_BUF_SZ 0
	
//================================= USART 2 =================================	
	#define USART2_TX_PORT GPIOA
	#define USART2_TX_PIN  2
	#define USART2_RX_PORT GPIOA
	#define USART2_RX_PIN  3
	#define USART2_REMAP   0 // leave 0 if not used
	#define USART2_BUF_SZ 32

//================================= USART 3 =================================	
	#define USART3_TX_PORT GPIOC
	#define USART3_TX_PIN  10
	#define USART3_RX_PORT GPIOC
	#define USART3_RX_PIN  11
	#define USART3_REMAP   AFIO_MAPR_USART3_REMAP_0 // leave 0 if not used
	#define USART3_BUF_SZ 32
	
	#else	
//================================= USARTS ==================================	
	#define USART_USED      (usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
	#define USART_IRQ_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
	#define USART_DMA_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
	#define USART_RTS_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
	#define USART_CTS_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_OFF : usart==2 ? 1 : USART_FUNC_OFF
#if defined(SUPPORT_LIN)
	#define USART_LIN_ENABLE(usart) usart==1 ? USART_FUNC_OFF : usart==2 ? USART_FUNC_ON  : usart==2 ? 1 : USART_FUNC_ON
#endif
	
//================================= USART 1 =================================	
	#define USART1_TX_PORT    GPIOA
	#define USART1_TX_PIN     6
	#define USART1_RX_PORT    GPIOA
	#define USART1_RX_PIN     7
	#define USART1_REMAP      AFIO_MAPR_USART1_REMAP
	#define USART1_BUF_SZ 0
	
//================================= USART 2 =================================	
	#define USART2_TX_PORT GPIOA
	#define USART2_TX_PIN  2
	#define USART2_RX_PORT GPIOA
	#define USART2_RX_PIN  3
	#define USART2_REMAP   0 // leave 0 if not used
	#define USART2_BUF_SZ 32

//================================= USART 3 =================================	
	#define USART3_TX_PORT GPIOC
	#define USART3_TX_PIN  10
	#define USART3_RX_PORT GPIOC
	#define USART3_RX_PIN  11
	#define USART3_REMAP   0 // leave 0 if not used
	#define USART3_BUF_SZ 32
#endif

//================================ Buffer ===================================

typedef struct usart_rx_buffer usart_rx_buffer;
#if USART_USED(1)
extern usart_rx_buffer usart1_rx_buf;
#endif
#if USART_USED(2)
extern usart_rx_buffer usart2_rx_buf;
#endif
#if USART_USED(3)
extern usart_rx_buffer usart3_rx_buf;
#endif
extern usart_rx_buffer *usart_bufs[];

#endif /* SUPPORT_USART */


#endif /* USART_H_INCLUDED */
