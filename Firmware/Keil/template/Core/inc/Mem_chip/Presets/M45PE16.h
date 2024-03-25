#ifndef M45PE16_H_INCLUDED
#define M45PE16_H_INCLUDED



/******************************************************************
*							M45PE16 Commands
******************************************************************/

#define M45PE16_CMD_READ 0x03		/* Read */
#define M45PE16_CMD_WREN 0x06		/* Write enable */
#define M45PE16_CMD_WRDI 0x04		/* Write disable */
#define M45PE16_CMD_SE 	0xD8		/* Sector erase */
#define M45PE16_CMD_PP 	0x02		/* Page programm */
#define M45PE16_CMD_CE 	0xC7		/* Chip erase */
#define M45PE16_CMD_RDSR 0x05		/* Read status register */

#define M45PE16_RDSR_WIP 0x01		/* write in progress bit */
#define M45PE16_RDSR_WRE 0x02		/* write enable bit */

#define M45PE16_WR_TIMEOUT 0xFFFFFFFF /* programming timeout */
#define M45PE16_ER_TIMEOUT 0xFFFFFFFF	/* erasing timeout */

/******************************************************************
*							M45PE16 Memory mapping
******************************************************************/
#define M45PE16_CMD_SECTOR_SIZE 				64*1024	/* Sector size 64000 bytes */
#define M45PE16_CMD_SECTOR_COUNT 				32		/* 32 sectors on the chip */
#define M45PE16_MAX_WRITE_CHUNK					0x100
#define M45PE16_ADDRESS_FROM_SEC(i) 		(i*M45PE16_CMD_SECTOR_SIZE)	/* pick the start address of a sector #i */


	
#define MEMCHIP_CMD_READ 	M45PE16_CMD_READ				/* Read */
#define MEMCHIP_CMD_WREN 	M45PE16_CMD_WREN 			/* Write enable */
#define MEMCHIP_CMD_WRDI 	M45PE16_CMD_WRDI 			/* Write disable */
#define MEMCHIP_CMD_SE 		M45PE16_CMD_SE 				/* Sector erase */
#define MEMCHIP_CMD_PP 		M45PE16_CMD_PP 				/* Page programm */
#define MEMCHIP_CMD_CE		M45PE16_CMD_CE 				/* Chip erase */
#define MEMCHIP_CMD_RDSR	M45PE16_CMD_RDSR 			/* Read status register */
#define MEMCHIP_CMD_RDCR	M45PE16_CMD_RDCR 			/* read configuration register */

#define MEMCHIP_RDSR_WIP	M45PE16_RDSR_WIP 			/* write in progress bit */
#define MEMCHIP_RDSR_WRE	M45PE16_RDSR_WRE 			/* write enable bit */

#define MEMCHIP_WR_TIMEOUT M45PE16_WR_TIMEOUT		/* programming timeout */
#define MEMCHIP_ER_TIMEOUT M45PE16_ER_TIMEOUT		/* erasing timeout */
		
#define MEMCHIP_CMD_SECTOR_SIZE 		M45PE16_CMD_SECTOR_SIZE	/* Sector size 64000 bytes */
#define MEMCHIP_MAX_WRITE_CHUNK			M45PE16_MAX_WRITE_CHUNK             
#define MEMCHIP_CMD_SECTOR_COUNT 		M45PE16_CMD_SECTOR_COUNT		/* 32 sectors on the chip */


/******************************************************************
*							Current settings memory mapping
******************************************************************/

#define MEMCHIP_CMD_SECTOR_SIZE M45PE16_CMD_SECTOR_SIZE
#define MEMCHIP_CMD_SECTOR_COUNT M45PE16_CMD_SECTOR_COUNT
#define MEMCHIP_ADDRESS_FROM_SEC(i) M45PE16_ADDRESS_FROM_SEC(i)

	


#endif // M45PE16_H_INCLUDED
