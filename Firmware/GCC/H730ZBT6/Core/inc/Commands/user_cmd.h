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
#include "BxCAN/can_override.h"
#include "Commands/common_cmd.h"
#include "Commands/cmd_set_vehicle_value.h"
#include "Commands/cmd_memchip_base.h"
#include "Commands/cmd_specific.h"
#include "Commands/cmd_lin.h"
#include "Commands/cmd_fdcan.h"
#include "Commands/cmd_raw.h"



//#define CMD_DMA_BUFFER_SIZE			128	/* size used for temporary read buffer. Memory read --> buffer --> process data */
#define CMD_CDC_TRANSACTION_SZ	MAX_CDC_EP1_TX_SIZ /* size used for "USB send" function */


//=========================================================================================================
//===========================================  DEBUG ======================================================
#ifdef DEBUG_MODE
#define	ELP_CMD_SEND_W_USART												0xD0000000	/* @SD0000000#02@?04@!Test@E --> Send 4 bytes of "Test" through USART2  */
#endif

//=========================================================================================================
//======================================  Memory chip base commands =======================================

/* Commands enumeration */
	/* Hide in comments down from here, if not used */	
#define	ELP_CMD_IDLE																0x00000000 /* Test connection.    @S 00000000 @E  --> Device --> $OK$ */
#define	ELP_CMD_ERROR																0x00000001 /* When failed to parse a command string, set this definition as cmd */
#define	ELP_CMD_RESET																0x00000002	/*@S00000002@E  equal to ELP_CMD_IDLE */
//#define	ELP_CMD_PRINT																0x00000003	/* @S00000003@?04@!Test@E --> com 00000003 param_cnt 00. Test function: a command string explained sent back.   */
//#define	ELP_CMD_PRINT_STRING												0x00000004	/* @S00000004@?04@!Test@E --> Test. Test function: a string arg sent back.  */
#define	ELP_CMD_SPI_MEMCHIP_READ										0x00000005	/* @S00000005#00#00#00#00#00#08@E --> 8 bytes from addr 0x000000 Load and send via USB a data from a certain address of size X bytes.  */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR						0x00000006	/* @S00000006#00#00#00@E --> Erase the sector from addr 0x000000 */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_CHIP							0x00000007	/* @S00000007@E --> Erase the whole chip. IMPORTANT: this proc can take up to 30 secs*/
#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP						0x00000008	/* @S00000008#00#00#00@?04@!Test@E --> Write the 4 bytes string "Test" as 'T' 'e' 's' 't' into the address 0x00000 16.000.000 address size limit*/
//#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_VAL				0x00000009
//#define	ELP_CMD_SPI_MEMCHIP_INPUT_STREAM						0x0000000A
//#define	ELP_CMD_SPI_MEMCHIP_READ_DMA								0x0000000B
//#define ELP_TEST_CMD_SPI_MX25_PROGRAMM_CHIP_DMA			0x0000000C
//#define ELP_TEST_CMD_SPI_MX25_GET_RDSR							0x0000000D	/* @S0000000D@E --> RDSR */
//#define ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_HEX				0x0000000E	/* @S0000000E#00#00#00@?04@!ABCD@E --> Write the 4 bytes string "ABCD" as 0xAB 0xCD into the address 0x00000 */
//#define ELP_TEST_CMD_SPI_MX25_GET_RDCR							0x0000000F	/* @S0000000D@E --> RDCR */
#define ELP_ERASE_AREA															0x00000010	/* @00000010#00#01#40#00#02#80@E --> Erase data starting from address -0x000140 0x000280 bytes */
//#define ELP_LOCK_AREA																0x00000011	/* @00000011#00#01#40#00#02#80@E --> lock WP data starting from address -0x000140 0x000280 bytes */
//#define ELP_UNLOCK_AREA															0x00000012	/* @00000012#00#01#40#00#02#80@E --> lock WP data starting from address -0x000140 0x000280 bytes */
#define	ELP_CMD_SPI_MEMCHIP_READ32                  0x00000013	/* @S00000013#00#00#00#00#12#34#56#78@E --> 0x12345678 bytes from addr 0x00000000 Load and send via USB a data from a certain address of size X bytes.  */

#define ELP_MEMCHIP_BASE_RANGE_END                  (0x00000A00 - 1)

//=========================================================================================================
//===========================================  Specific ===================================================
	/* Speedometer Calibrator */
// #define ELP_VEHICLE_GET_MEMORY_STATUS_STRING_HEX		0x00000A00  /* @S00000A00@E HEX This sends 128 bytes of the first memory page as hex.	*/

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

#define ELP_SPECIFIC_RANGE_END                      (0x00000C00 - 1)

//=========================================================================================================
//===========================================  LIN bus ====================================================
#ifdef SUPPORT_LIN
//#define ELP_LIN_SET_BAUDRATE 												0x00000C00	/* @S00000C00#XX@E   XX - is a baudrate preset */
//#define ELP_LIN_SET_MODE    												0x00000C01	/* @S00000C01#XY@E   XY -  Y is a LIN mode (gateway/scanner/etc) X - if 0x0, this means "reset", if 0x1- this means "set" */
#define ELP_LIN_POLL_PERIOD                         0x00000C02  /* @S00000C02#?08@!0000000A@E Set 0x000A as a poll period */
//#define ELP_LIN_SET_FILTER_MODE											0x00000C03	/* @S00000C03#XX@E   XX - is a filter mode */
//#define ELP_LIN_ENABLE        											0x00000C04	/* @S00000C04#XX@E   XX - if 0x00, this means disable, else this means enable */
//#define ELP_LIN_VALIDATION_ON 											0x00000C05	/* @S00000C05@E  */
//#define ELP_LIN_VALIDATION_OFF 											0x00000C06	/* @S00000C06@E  */
#define ELPR_LIN_GET_POLL_PERIOD                    0x00000C07  /* @S00000C07@E   */
#define ELPR_LIN_GET_MOSI_FILTER                    0x00000C08  /* @S00000C08@E   */
#define ELPR_LIN_GET_MISO_FILTER                    0x00000C09  /* @S00000C09@E   */
#define ELP_LIN_SET_FILTER                          0x00000C0A  /* @S00000C0A#NN#01#02#03#04#05#06#07#08#09#0A#0B#0C@E  NN - if 0x00, MOSI,  else - MISO 01-0C the lin_filter_raw bytes */
#endif

#define ELP_LIN_RANGE_END                          (0x0000F000 - 1)

//===========================================  FD CAN  ====================================================
#ifdef SUPPORT_FDCAN
#define ELP_UPDATE_FDCAN_STNGS                      0x0000F000	/* @S0000F000@E Start FD CAN settings update */
#define ELP_RESTART_FDCAN                           0x0000F001	/* @S0000F001@E Restart FD CAN  */
#define ELP_SAVE_FDCAN_STNGS                        0x0000F002	/* @S0000F002@E Save FD CAN Settings */
#endif

#define ELP_FDCAN_MSK                               0x0000F000

//===========================================  NAND TEST  =================================================
#ifdef NAND_FLASH_DEBUG
#define ELP_NAND_TEST_READ_ID                       0x000F0000	/* @S000F0000@E Read memchip ID */
#define ELP_NAND_TEST_GET_FEATURE                   0x000F0001	/* @S000F0001#OP@E Get feature  OP - "address" */
#define ELP_NAND_TEST_READ_FROM_CACHE               0x000F0002	/* @S000F0002#AD#DR#WR#SZ@E */
#define ELP_NAND_TEST_READ_PAGE                     0x000F0003	/* @S000F0003#AD#DR@E */
#define ELP_NAND_TEST_RESET                         0x000F0004	/* @S000F0004@E */
#define ELP_NAND_TEST_SET_FEATURE                   0x000F0005	/* @S000F0005#AD#VL@E */
#define ELP_NAND_TEST_RST_FEATURE                   0x000F0006	/* @S000F0006#AD#VL@E */
#define ELP_NAND_TEST_READ_BADBLK_MRK               0x000F0007	/* @S000F0007@E */
#define ELP_NAND_TEST_ERASE_BLOCK                   0x000F0008	/* @S000F0008#BL#CK@E */
#define ELP_NAND_TEST_24_BIT_ADDR                   0x000F0009	/* @S000F0009#BL#CK#PA#GE@E */
#define ELP_NAND_TEST_MAKE_INDEX                    0x000F000A	/* @S000F000A#AD#DR#ES#S @E */
#define ELP_NAND_TEST_MAKE_START                    0x000F000B	/* @S000F000B#BL#CK#PA#GE#BY#TE@E */
#define ELP_NAND_TEST_PROGRAMM_LOAD                 0x000F000C	/* @S000F000C@!Test@E -->*/
#define ELP_NAND_TEST_PROGRAMM_EXEC                 0x000F000D	/* @S000F000D@E memchip_programm_execute(index) */
#define ELP_NAND_TEST_WREN                          0x000F000E	/* @S000F000E@E  */
#define ELP_NAND_TEST_WRDIS                         0x000F000F	/* @S000F000F@E  */
#define ELP_NAND_TEST_LOAD_PRESET                   0x000F0010	/* @S000F0010#PR@E  */

#define ELP_TEST_NAND_MSK                           0x000F0000

#endif // NAND_FLASH_DEBUG

//=========================================================================================================
//===========================================  Raw data ===================================================

#define ELPR_DEVICE_GET_CURRENT_STATUS              0xF0000BB0	/* @SF0000BB0@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
#define ELPR_OVR_FLTR_GET_CURRENT_STATUS            0xF0000BB1	/* @SF0000BB1@E ASCII Get sizeof(can_override_status) of current override settings in raw data*/
#define ELPR_OVR_FLTR_GET_FILTER_NUMS               0xF0000BB2	/* @SF0000BB2@E ASCII Get uint16_t ignored_id_num; uint16_t overrided_id_num; */

/* All commands starting with F and named with ELPR use raw data, without converting into Ascii */
#define ELPR_VEHICLE_GET_CURRENT_STATUS             0xF0000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings in raw data*/
#define	ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP					0xF0000008	//* @SF0000008#00#01#02#12#23#45#FF@E Start programming procedure at addr 0x000102 with 0x122345 bytes  00 - append, FF - rewrite*/
#define	ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP32				0xF0000009	//* @SF0000008#00#00#01#02#12#00#23#45#FF@E Start programming procedure at addr 0x00000102 with 0x00122345 bytes  00 - append, FF - rewrite*/

//===========================================  FD CAN  ====================================================
#ifdef SUPPORT_FDCAN
#define ELPR_FDCAN_GET_SETTINGS                     0xF0000AB1	/* @SF0000AB1@E ASCII Send u_fdcan_settings in raw data from device to host */
#define ELPR_SEND_CUSTOM_FDCAN_MSG                  0xF0000AB2	/* @SF0000AB2#SI#ZE#CN@E start recieving SIZE bytes of data and use this to make and transmit an fdcan message CN: 0 - CAN1, 1 - CAN2 */
//#define ELPR_FDCAN_TEST_TANK_500                    0xF0000AB3
#endif

#define ELP_RAW_DATA_MSK                            0xF0000000



void process_protocol_cmd(elp_cmd *com);
void protocol_response(uint32_t param);

#endif /* USER_CMD_H_INCLUDED*/
