#ifndef MX25L323_H_INCLUDED
#define MX25L323_H_INCLUDED

/******************************************************************
*							MX25L323 Commands
******************************************************************/

#define MX25L323_CMD_READ 0x03		/* Read */
#define MX25L323_CMD_WREN 0x06		/* Write enable */
#define MX25L323_CMD_WRDI 0x04		/* Write disable */
#define MX25L323_CMD_SE 	0x20		/* Sector erase */
#define MX25L323_CMD_PP 	0x02		/* Page programm */
#define MX25L323_CMD_CE 	0xC7		/* Chip erase */
#define MX25L323_CMD_RDSR 0x05		/* Read status register */
#define MX25L323_CMD_RDCR 0x15		/* read configuration register */

#define MX25L323_RDSR_WIP 0x01		/* write in progress bit */
#define MX25L323_RDSR_WRE 0x02		/* write enable bit */

#define MX25L323_WR_TIMEOUT 0xFFFFFFFF 	/* programming timeout */
#define MX25L323_ER_TIMEOUT 0xFFFFFFFF	/* erasing timeout */

/******************************************************************
*							MX25L323 Memory mapping
******************************************************************/

#define MX25L323_CMD_SECTOR_SIZE 				0x1000	/* Sector size 4096 bytes */
#define MX25L323_CMD_SECTOR_COUNT 			1024		/* 1024 sectors on the chip */
#define MX25L323_MAX_WRITE_CHUNK				0x100
#define MX25L323_ADDRESS_FROM_SEC(i) 		(i*MX25L323_CMD_SECTOR_SIZE)	/* pick the start address of a sector #i */

/******************************************************************
*							Current settings commands
******************************************************************/

#define MEMCHIP_CMD_READ 	MX25L323_CMD_READ				/* Read */
#define MEMCHIP_CMD_WREN 	MX25L323_CMD_WREN 			/* Write enable */
#define MEMCHIP_CMD_WRDI 	MX25L323_CMD_WRDI 			/* Write disable */
#define MEMCHIP_CMD_SE 		MX25L323_CMD_SE 				/* Sector erase */
#define MEMCHIP_CMD_PP 		MX25L323_CMD_PP 				/* Page programm */
#define MEMCHIP_CMD_CE		MX25L323_CMD_CE 				/* Chip erase */
#define MEMCHIP_CMD_RDSR	MX25L323_CMD_RDSR 			/* Read status register */
#define MEMCHIP_CMD_RDCR	MX25L323_CMD_RDCR 			/* read configuration register */

#define MEMCHIP_RDSR_WIP	MX25L323_RDSR_WIP 			/* write in progress bit */
#define MEMCHIP_RDSR_WRE	MX25L323_RDSR_WRE 			/* write enable bit */

#define MEMCHIP_WR_TIMEOUT MX25L323_WR_TIMEOUT		/* programming timeout */
#define MEMCHIP_ER_TIMEOUT MX25L323_ER_TIMEOUT		/* erasing timeout */
		
#define MEMCHIP_CMD_SECTOR_SIZE 		MX25L323_CMD_SECTOR_SIZE
#define MEMCHIP_MAX_WRITE_CHUNK			MX25L323_MAX_WRITE_CHUNK
#define MEMCHIP_CMD_SECTOR_COUNT 		MX25L323_CMD_SECTOR_COUNT		


#define MEMCHIP_CMD_SECTOR_SIZE MX25L323_CMD_SECTOR_SIZE
#define MEMCHIP_CMD_SECTOR_COUNT MX25L323_CMD_SECTOR_COUNT
#define MEMCHIP_ADDRESS_FROM_SEC(i) MX25L323_ADDRESS_FROM_SEC(i)

	

#endif // MX25L323_H_INCLUDED
