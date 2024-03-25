#ifndef W25Q16_H_INCLUDED
#define W25Q16_H_INCLUDED

/******************************************************************
*							W25Q16 Commands
******************************************************************/

#define W25Q16_CMD_READ 0x03		/* Read */
#define W25Q16_CMD_WREN 0x06		/* Write enable */
#define W25Q16_CMD_WRDI 0x04		/* Write disable */
#define W25Q16_CMD_SE 	0x20		/* Sector erase */
#define W25Q16_CMD_PP 	0x02		/* Page programm */
#define W25Q16_CMD_CE 	0xC7		/* Chip erase */
#define W25Q16_CMD_RDSR 0x05		/* Read status register */
#define W25Q16_CMD_RDCR 0x15		/* read configuration register */

#define W25Q16_RDSR_WIP 0x01		/* write in progress bit */
#define W25Q16_RDSR_WRE 0x02		/* write enable bit */

#define W25Q16_WR_TIMEOUT 0xFFFFFFFF 	/* programming timeout */
#define W25Q16_ER_TIMEOUT 0xFFFFFFFF	/* erasing timeout */

/******************************************************************
*							W25Q16 Memory mapping
******************************************************************/

#define W25Q16_CMD_SECTOR_SIZE 				0x1000	/* Sector size 4096 bytes */
#define W25Q16_CMD_SECTOR_COUNT 			1024		/* 1024 sectors on the chip */
#define W25Q16_MAX_WRITE_CHUNK				0x100
#define W25Q16_ADDRESS_FROM_SEC(i) 		(i*W25Q16_CMD_SECTOR_SIZE)	/* pick the start address of a sector #i */

/******************************************************************
*							Current settings commands
******************************************************************/

#define MEMCHIP_CMD_READ 	W25Q16_CMD_READ				/* Read */
#define MEMCHIP_CMD_WREN 	W25Q16_CMD_WREN 			/* Write enable */
#define MEMCHIP_CMD_WRDI 	W25Q16_CMD_WRDI 			/* Write disable */
#define MEMCHIP_CMD_SE 		W25Q16_CMD_SE 				/* Sector erase */
#define MEMCHIP_CMD_PP 		W25Q16_CMD_PP 				/* Page programm */
#define MEMCHIP_CMD_CE		W25Q16_CMD_CE 				/* Chip erase */
#define MEMCHIP_CMD_RDSR	W25Q16_CMD_RDSR 			/* Read status register */
#define MEMCHIP_CMD_RDCR	W25Q16_CMD_RDCR 			/* read configuration register */

#define MEMCHIP_RDSR_WIP	W25Q16_RDSR_WIP 			/* write in progress bit */
#define MEMCHIP_RDSR_WRE	W25Q16_RDSR_WRE 			/* write enable bit */

#define MEMCHIP_WR_TIMEOUT W25Q16_WR_TIMEOUT		/* programming timeout */
#define MEMCHIP_ER_TIMEOUT W25Q16_ER_TIMEOUT		/* erasing timeout */
		
#define MEMCHIP_CMD_SECTOR_SIZE 		W25Q16_CMD_SECTOR_SIZE
#define MEMCHIP_MAX_WRITE_CHUNK			W25Q16_MAX_WRITE_CHUNK
#define MEMCHIP_CMD_SECTOR_COUNT 		W25Q16_CMD_SECTOR_COUNT		


#define MEMCHIP_CMD_SECTOR_SIZE W25Q16_CMD_SECTOR_SIZE
#define MEMCHIP_CMD_SECTOR_COUNT W25Q16_CMD_SECTOR_COUNT
#define MEMCHIP_ADDRESS_FROM_SEC(i) W25Q16_ADDRESS_FROM_SEC(i)

	

#endif // W25Q16_H_INCLUDED
