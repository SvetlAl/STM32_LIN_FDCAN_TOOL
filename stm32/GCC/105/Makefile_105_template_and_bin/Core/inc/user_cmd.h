/****************************************************************
* 
* User interface command parser
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#ifndef USER_CMD_H_INCLUDED
#define USER_CMD_H_INCLUDED


#include "main.h"

//#define CMD_DMA_BUFFER_SIZE			128	/* size used for temporary read buffer. Memory read --> buffer --> process data */
#define CMD_CDC_TRANSACTION_SZ	MAX_CDC_EP1_TX_SIZ /* size used for "USB send" function */



//=========================================================================================================
//===========================================  General ====================================================

/* Commands enumeration */
	/* Hide in comments down from here, if not used */	
#define	ELP_TEST	0xAAAAAAAA
#define	ELP_CMD_IDLE																0x00000000 /* Test connection.    @S 00000000 @E  --> Device --> $OK$ */
#define	ELP_CMD_ERROR																0x00000001 /* When failed to parse a command string, set this definition as cmd */
#define	ELP_CMD_RESET																0x00000002	/*@S00000002@E  equal to ELP_CMD_IDLE */
//#define	ELP_CMD_PRINT																0x00000003	/* @S00000003@?04@!Test@E --> com 00000003 param_cnt 00. Test function: a command string explained sent back.   */
//#define	ELP_CMD_PRINT_STRING												0x00000004	/* @S00000004@?04@!Test@E --> Test. Test function: a string arg sent back.  */
#define	ELP_CMD_SPI_MEMCHIP_READ										0x00000005	/* @S00000005#00#00#00#00#00#08@E --> 8 bytes from addr 0x000000 Load and send via USB a data from a certain address of size X bytes.  */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR						0x00000006	/* @S00000006#00#00#00@E --> Erase the sector from addr 0x000000 */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_CHIP							0x00000007	/* @S00000007@E --> Erase the whole chip. IMPORTANT: this proc can take up to 30 secs*/
#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP						0x00000008	/* @S00000008#00#00#00@?04@!Test@E --> Write the 4 bytes string "Test" as 'T' 'e' 's' 't' into the address 0x00000 */
//#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_VAL				0x00000009
//#define	ELP_CMD_SPI_MEMCHIP_INPUT_STREAM						0x0000000A
//#define	ELP_CMD_SPI_MEMCHIP_READ_DMA								0x0000000B
//#define ELP_TEST_CMD_SPI_MX25_PROGRAMM_CHIP_DMA			0x0000000C
#define ELP_TEST_CMD_SPI_MX25_GET_RDSR							0x0000000D	/* @S0000000D@E --> RDSR */
//#define ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_HEX				0x0000000E	/* @S0000000E#00#00#00@?04@!ABCD@E --> Write the 4 bytes string "ABCD" as 0xAB 0xCD into the address 0x00000 */
#define ELP_TEST_CMD_SPI_MX25_GET_RDCR							0x0000000F	/* @S0000000D@E --> RDCR */
#define ELP_ERASE_AREA															0x00000010	/* @00000010#00#01#40#00#02#80@E --> Erase data starting from address -0x000140 0x000280 bytes */
//#define ELP_LOCK_AREA																0x00000011	/* @00000011#00#01#40#00#02#80@E --> lock WP data starting from address -0x000140 0x000280 bytes */
//#define ELP_UNLOCK_AREA															0x00000012	/* @00000012#00#01#40#00#02#80@E --> lock WP data starting from address -0x000140 0x000280 bytes */


//=========================================================================================================
//===========================================  Specific ===================================================
	/* Speedometer Calibrator */
#define ELP_VEHICLE_GET_MEMORY_STATUS_STRING_HEX		0x00000A00  /* @S00000A00@E HEX This sends 128 bytes of the first memory page as hex.	*/

#define ELP_VEHICLE_SET_MODEL												0x00000A01	/* @S00000A01@?08@!0000000A@E Set 0x000A as a model */
// #define ELP_VEHICLE_SET_STARTUP_SETTINGS					0x00000A02
#define ELP_VEHICLE_SET_SPEEDOMETER_MLT							0x00000A03	/* @S00000A03@?02@!64@E Set 0x64 (100) as a SPEEDOMETER_MLT */
#define ELP_VEHICLE_SET_ODOMETER_MLT								0x00000A04	/* @S00000A04@?02@!64@E Set 0x64 (100) as a ODOMETER_MLT */
#define ELP_VEHICLE_SET_CRUISE_MLT									0x00000A05	/* @S00000A05@?02@!64@E Set 0x64 (100) as a CRUISE_MLT */
#define ELP_VEHICLE_SET_TYRES_THRESHOLD							0x00000A06	/* @S00000A06@?02@!64@E Set 0x64 (100) as a TYRES_THRESHOLD */

/* expanded ODOMETER_MODE */
/* Applying a mask: uint32_t value 0x00001234, 0x12 - is a mask to "&= ~", 34 is a mask to "|= "*/
#define ELP_VEHICLE_SET_MODE 												0x00000A07	/* @S00000A07@?08@!00000102@E reset 0x02 and set 0x01 */
#define ELP_VEHICLE_SET_MODE_CMDSTR_LENGTH					8	/* proper length of the value string */
/* deprecated, use ELP_VEHICLE_SET_MODE */
#define ELP_VEHICLE_SET_TEST_MODE	/* deprecated */	0x00000A08	/* @S00000A08@?02@!02@E Set 0x02 (100) as a TEST_MODE */

#define ELP_VEHICLE_GET_SW_VERSION									0x00000A09	/* @S00000A09@E Get device software version */
#define ELP_VEHICLE_GET_DEV_MODEL										0x00000A0A	/* @S00000A0A@E Get 16 bytes of device Hw model */

#define ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII	0x00000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings */
#define ELP_VEHICLE_SAVE_STATUS											0x00000AA0	/* @S00000AA0@E Save current vehicle settings into (0x0000) VEHICLE_SETTINGS_ADDRESS */


#define ELP_DEVICE_SET_MODE 												0x00000B07	/* @S00000B07#00#00#01#02@E set the first (0x 000001)var in DeviceModel as 02 */
#define ELP_OVR_FLTR_SET_VALUE											0x00000B08	/* @S00000B08#X0
																																							00 - ignored id
																																							01 - override id ------.
																																							  #X1									 |
																																								 00 remove					 |
																																								 01 add ---.				 |
																																									 #X2 <---'				 |
																																									  01 CAN 1				 |
																																										02 CAN 2				 |
																																										  #X3 CAN Id		 |
																																											#X4						 |
																																											#X5						 |
																																											#X6						 |----.
																																											   #X7 flt_msk <    |
																																													  #X8		<-------'
																																														#X9
																																														#XA
																																														#XB
																																														#XC
																																														#XD
																																														#XE
																																														#XF Filter */


#define ELP_DEVICE_SAVE_STATUS											0x00000BA0	/* @S00000BA0@E Save current device settings into (0x00FA00) DEVICE_MODES_ADDRESS */
#define ELP_UPDATE_OVR_FILTERS											0x00000BA1	/* @S00000BA1@E Start filter update procedure */
#define ELPR_DEVICE_GET_CURRENT_STATUS 							0xF0000BB0	/* @SF0000BB0@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
#define ELPR_OVR_FLTR_GET_CURRENT_STATUS 						0xF0000BB1	/* @SF0000BB1@E ASCII Get sizeof(can_override_status) of current override settings in raw data*/
#define ELPR_OVR_FLTR_GET_FILTER_NUMS		 						0xF0000BB2	/* @SF0000BB2@E ASCII Get uint16_t ignored_id_num; uint16_t overrided_id_num; */

/* All commands starting with F and named with ELPR use raw data, without converting into Ascii */
#define ELPR_VEHICLE_GET_CURRENT_STATUS 						0xF0000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings in raw data*/

#define	ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP					0xF0000008	//* @SF0000008#00#01#02#12#23#45#FF@E Start programming procedure at addr 0x000102 with 0x122345 bytes  00 - append, FF - rewrite*/








void process_protocol_cmd(elp_cmd *com);
void protocol_response(uint32_t param);

/***  @DD ***/
extern void set_vehicle_value(uint32_t count, uint32_t _value);
/***  @DD ***/
extern uint8_t *get_vehicle_settings_data(void);

#endif /* USER_CMD_H_INCLUDED*/
