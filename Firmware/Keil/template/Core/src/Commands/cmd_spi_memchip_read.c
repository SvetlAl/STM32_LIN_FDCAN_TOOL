#include "Commands/cmd_spi_memchip_read.h"
#include "Commands/user_cmd.h"

static uint8_t spi_buf[CMD_CDC_TRANSACTION_SZ]; /* Memory chip data --> temp_spi_buf --> USB_send */

void read_mem_data_and_usb_send(uint32_t length, uint32_t addr){
	uint32_t send_status = EP_OK;
	volatile uint32_t address_pos = addr;
	
	while((length >= CMD_CDC_TRANSACTION_SZ) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){	
		#ifdef MEMCHIP_NAND_FLASH
		memchip_read_spare(address_pos, &spi_buf[0], CMD_CDC_TRANSACTION_SZ);
		#else 
		memchip_read(address_pos, &spi_buf[0], CMD_CDC_TRANSACTION_SZ);
		#endif		
		send_status = USB_CDC_send_data(&spi_buf[0], CMD_CDC_TRANSACTION_SZ);	

		if(send_status == EP_FAILED) return;
		
		length-=CMD_CDC_TRANSACTION_SZ;
		address_pos+=CMD_CDC_TRANSACTION_SZ;
	}
	if((length > 0) & (check_USB_device_status(DEVICE_STATE_ADDRESSED)) ){
		#ifdef MEMCHIP_NAND_FLASH
		memchip_read_spare(address_pos, &spi_buf[0], length);
		#else 
		memchip_read(address_pos, &spi_buf[0], length);
		#endif
		
		USB_CDC_send_data(&spi_buf[0], (uint16_t)length);
	}
}
