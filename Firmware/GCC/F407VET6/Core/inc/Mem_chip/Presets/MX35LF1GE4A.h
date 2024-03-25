#ifndef MX35LF1GE4A_H_INCLUDED
#define MX35LF1GE4A_H_INCLUDED
#include "device_model.h"

/******************************************************************
*							MX35LF1GE4A Commands
******************************************************************/
#define NAND_CMD_DUMMY_BYTE                        0xFF   
#define NAND_WEL_SET_TIMEOUT                       0x1FF
#define NAND_PROG_PAGE_TIMEOUT                     0xFFF
#define NAND_STATUS_TIMEOUT                        0x1FFF
#define NAND_READ_PAGE_TIMEOUT                     0xFFFF
#define NAND_WREN_TIMEOUT                          0x0FFF
#define NAND_BLOCK_ERASE_TIMEOUT                   0x0FFFF

/********************* GET/SET FEATURE ***************************/
#define NAND_CMD_RESET_DEVICE                      0xFF

#define NAND_CMD_READ_ID                           0x9F
#define NAND_CMD_GET_FEATURE                       0x0F
#define NAND_CMD_SET_FEATURE                       0x1F

#define NAND_CMD_FEATURE_SECURE_OTP                0xB0
#define NAND_CMD_FEATURE_SECURE_OTP_QE             0x01
#define NAND_CMD_FEATURE_SECURE_OTP_ECC_EN         0x10
#define NAND_CMD_FEATURE_SECURE_OTP_SEC_EN         0x40
#define NAND_CMD_FEATURE_SECURE_OTP_SEC_PROTECT    0x80

#define NAND_CMD_FEATURE_STATUS                    0xC0
#define NAND_CMD_FEATURE_STATUS_OIP                0x01
#define NAND_CMD_FEATURE_STATUS_WEL                0x02
#define NAND_CMD_FEATURE_STATUS_E_FAIL             0x04
#define NAND_CMD_FEATURE_STATUS_P_FAIL             0x08
#define NAND_CMD_FEATURE_STATUS_ECC_S0             0x10
#define NAND_CMD_FEATURE_STATUS_ECC_S1             0x20

#define NAND_CMD_FEATURE_BLOCK_PROTEC              0xA0
#define NAND_CMD_FEATURE_BLOCK_PROTEC_SP           0x01
#define NAND_CMD_FEATURE_BLOCK_PROTEC_COMPLEMENT   0x02
#define NAND_CMD_FEATURE_BLOCK_PROTEC_INVERT       0x04
#define NAND_CMD_FEATURE_BLOCK_PROTEC_BP0          0x08
#define NAND_CMD_FEATURE_BLOCK_PROTEC_BP1          0x10
#define NAND_CMD_FEATURE_BLOCK_PROTEC_BP2          0x20
#define NAND_CMD_FEATURE_BLOCK_PROTEC_BPRWD        0x80

/************************* PAGE READ *****************************/
#define NAND_CMD_PAGE_READ                         0x13  // 3 bytes
#define NAND_CMD_READ_FROM_CACHE                   0x03  // 2 bytes

/************************* PAGE WRITE ****************************/
#define NAND_CMD_WRITE_ENABLE                      0x06
#define NAND_CMD_WRITE_DISABLE                     0x04

#define NAND_CMD_PROGRAM_LOAD                      0x02  // 2 bytes
#define NAND_CMD_PROGRAM_LOAD_RND_DAT              0x84  // 2 bytes
#define NAND_CMD_PROGRAM_EXECUTE                   0x10  // 3 bytes
#define NAND_CMD_ERASE_BLOCK                       0xD8

/************************* WRAP READ *****************************/
#define NAND_CMD_READ_WRAP_FULLPAGE                0x00
#define NAND_CMD_READ_WRAP_DATAPAGE                0x02
#define NAND_CMD_READ_WRAP_64                      0x01
#define NAND_CMD_READ_WRAP_16                      0x03

#define NAND_12BIT_ADDRESS_WRAP_MSK    		         (uint16_t)0xC000
#define NAND_CMD_READ_WRAP_POS                     0x0E
#define NAND_CMD_READ_WRAP_FULLPAGE_MSK            (uint16_t)(NAND_CMD_READ_WRAP_FULLPAGE << NAND_CMD_READ_WRAP_POS)
#define NAND_CMD_READ_WRAP_DATAPAGE_MSK            (uint16_t)(NAND_CMD_READ_WRAP_DATAPAGE << NAND_CMD_READ_WRAP_POS)
#define NAND_CMD_READ_WRAP_64_MSK                  (uint16_t)(NAND_CMD_READ_WRAP_64       << NAND_CMD_READ_WRAP_POS)
#define NAND_CMD_READ_WRAP_16_MSK                  (uint16_t)(NAND_CMD_READ_WRAP_16       << NAND_CMD_READ_WRAP_POS)




/******************************************************************
*							MX35LF1GE4A Memory mapping
******************************************************************/
#define NAND_PAGE_SIZ_DATA_SPARE                (uint16_t)0x840   // Bytes 2112: Data + Spare
#define NAND_PAGE_SIZ_DATA                      (uint16_t)0x800   // Bytes 2048: Data
#define NAND_BLOCK_SIZ_PAGES                    (uint16_t)0x40    // Pages 64
#define NAND_SIZ_BLOCKS                         (uint16_t)0x400   // Blocks 1024


#define NAND_BLOCK_SIZE_DATA_SPARE	            (uint32_t)0x21000       	// BLOCK size 135'168 bytes 
#define NAND_BLOCK_SIZE_DATA	                  (uint32_t)0x20000       	// BLOCK size 131'072 bytes
#define NAND_CHIP_VOLUME    	                  (uint32_t)0x8000000


#define NAND_12BIT_ADDRESS_MSK        		      0xFFF
#define NAND_24BIT_ADDRESS_MSK        		      0xFFFFFF
#define NAND_ROW_ADDRESS_FROM_BLK(b) 		        (uint32_t)((b << 6) & 0x1FFC0) // block must be <= 1023. Pick the start address of a block #b
#define NAND_ROW_ADDRESS_FROM_PAGE(p) 		      (uint32_t)((p << 0) & 0x3F)	   // page must be <= 63. Pick the start address of a page #p
#define NAND_ROW_ADDRESS_FROM_BLK_AND_PAGE(b,p) (uint32_t) (NAND_ROW_ADDRESS_FROM_BLK(b) | NAND_ROW_ADDRESS_FROM_PAGE(p)) 

// Column address: byte pos
// data[8] 1 data[8] 0
// **** **** **** ****
// ca[] ca[] ca[] ca[]
//  Usage:
// data[8] 1 data[8] 0 dummy
// **** **** **** **** **** ****
// ra[] ra[] ra[] ra[] dummy

typedef union nand_12bit_address{
	uint16_t word16;
	uint8_t data8[2];
}nand_12bit_address;

#define NAND_12_BIT_BYTE_0(addr)                (uint8_t)(addr.data8[1])
#define NAND_12_BIT_BYTE_1(addr)                (uint8_t)(addr.data8[0])

// 16-bit row address and 8-bit dummy
// Block + page
// data[8] 3 data[8] 2 data[8] 1 data[8] 0
// **** **** **** **** **** **** **** ****
// **** **** **** **** ra[] ra[] ra[] ra[]
//  Usage:
// data[8] 1 data[8] 0 dummy
// **** **** **** **** **** ****
// ra[] ra[] ra[] ra[] dummy
typedef union nand_24bit_address{
	uint32_t word32;
	uint8_t data8[4];
}nand_24bit_address;

#define NAND_24_BIT_BYTE_0(addr)                (uint8_t)(addr.data8[0])
#define NAND_24_BIT_BYTE_1(addr)                (uint8_t)(addr.data8[1])
#define NAND_24_BIT_BYTE_2(addr)                (uint8_t)(addr.data8[2]) // dummy

/******************************************************************
*							MX35LF1GE4A BAD BLOCK HANDLE
******************************************************************/
#define NAND_BAD_BLOCK_BYTE_POS                  NAND_PAGE_SIZ_DATA
#define NAND_BAD_BLOCK_PAGE_POS_0                0U
#define NAND_BAD_BLOCK_PAGE_POS_1                1U
#define NAND_BAD_BLOCK_PAGE_POS_2                2U


/******************************************************************
*							Application configuration
******************************************************************/
/*****************************************************************************************************************
block 10 (Address 0x14A000) Vehicle Settings
block 11
block 12
block 13
block 14
block 15
block 16
block 17
block 18
block 19
block 20
block 21
block 22
block 23
block 24
block 25
block 26
block 27
block 28
block 29

block 30 (Address 0x3DE000) Device model
block 31
block 32
block 33
block 34
block 35
block 36
block 37
block 38
block 39
block 40
block 41
block 42
block 43
block 44
block 45
block 46
block 47
block 48
block 49

block 50 (Address 0x672000) FDCAN Settings
block 51
block 52
block 53
block 54
block 55
block 56
block 57
block 58
block 59
block 60
block 61
block 62
block 63
block 64
block 65
block 66
block 67
block 68
block 69

block 70 (Address 0x906000) Bootloader Emergency
block 71
block 72
block 73
block 74
block 75
block 76
block 77
block 78
block 79
block 80
block 81
block 82
block 83
block 84
block 85
block 86
block 87
block 88
block 89

block 90 (Address 0xB9A000) Bootloader Update
block 91
block 92
block 93
block 94
block 95
block 96
block 97
block 98
block 99
block 100
block 101
block 102
block 103
block 104
block 105
block 106
block 107
block 108
block 109

block 110 Free memspace
*****************************************************************************************************************/

#endif // MX35LF1GE4A_H_INCLUDED
