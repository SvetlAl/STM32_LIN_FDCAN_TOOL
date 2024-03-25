#ifndef COMPILER_SETTINGS_H_INCLUDED
#define COMPILER_SETTINGS_H_INCLUDED

//=========================================================================================================
//=====================================       Environment      ============================================
#define MDK_ARM_ENV // if MDK ARM Keil IDE is used
// #define  __GNUC__ 

//=========================================================================================================
//=====================================           Model        ============================================
//F1
//#define DEVICE_2CAN
//#define DEVICE_2CAN_TJA1042
//#define DEVICE_2CAN_BOXED
//#define DEVICE_SIGMA
//#define DEVICE_1CAN2LIN

//F2
#define DEVICE_ALLIGATOR
//#define DEVICE_TEC_MODULE
//#define DEVICE_FCAN_V6

//F4
//#define DEVICE_DEVBOARD_F407VET_A

//H7
//#define DEVICE_PRZRK8XL

//=========================================================================================================
//===========================================     ROM USAGE     ===========================================
//========================================    ADD/REMOVE FEATURES =========================================
//=================================    AFFECTS APPLICATION TOTAL SIZE =====================================

#if defined SUPPORT_BXCAN
//#define SUPPORT_MEMCHIP_CAN_INJECTION				// playing CAN trace from a memory chip **deprecated
#endif

//#define SUPPORT_SPEEDO_CALIBRATOR
//#define SUPPORT_SPEEDO_CALIBRATOR_MMC_RADAR
//#define SUPPORT_CELCIUM_FARENHEIT_TUNDRA
//#define SUPPORT_TUNDRA_SPOILER_REMOVAL
//#define SUPPORT_TUNDRA_ENGLISH_MULTIMEDIA


//====================================  PRZRK8XL (STM32H730) FEATURES  ====================================
#if defined(DEVICE_PRZRK8XL)
#define PRZRK_DEBUG
#endif

#if defined(PRZRK_DEBUG)
//#define NAND_FLASH_DEBUG
#endif


//====================================  2CAN2LIN (STM32F105)  EATURES  ====================================
#ifdef DEVICE_2CAN // USART is supported for DEVICE_2CAN only
//#define SUPPORT_USART

#ifdef SUPPORT_USART
#define SUPPORT_LIN     // Enable/disable LIN
#endif

#endif

//=====================================     LIN Settings    ===============================================
#ifdef SUPPORT_LIN 
#define LIN_PROGRAMM_PRESETS      // Enable/disable LIN programm presets
#define LIN_DEVICE_SUPPORT        // Device mode works as a regular LIN device with a Master logic in "void lin_device_master_rx()"/"void lin_device_master_tx()"
                                  // and Slave logic in "void lin_device_slave_rx()"/"void lin_device_slave_tx()"
#endif


//=========================================================================================================
//=================================     Extra functions and tests    ======================================



//=========================================================================================================
//======================================     RAM USAGE     ================================================
//=================================    ADD/REMOVE FEATURES ================================================
//===========================    AFFECTS APPLICATION (ZI and RW) DATA =====================================

//================= USB CDC circular buffer. Put data here to send to host ================================
#define USB_CDC_CIRC_BUFFER_SIZE                      0x200UL*8U //  0x200UL*16 - minimum for FD CAN

#define CAN_TX_BUFFER_SIZE                            512U*2U // bytes

// CAN injection from USB CDC
#define CDC_CAN_INJECTION_BUFFER_ITEMS                16U //256U
#define CDC_CAN_INJECTION_BUFFER_SIZE CDC_CAN_INJECTION_BUFFER_ITEMS*sizeof(can_message_info_raw) // elements count
	
// CAN injection from memory chip **Deprecated
#ifdef SUPPORT_MEMCHIP_CAN_INJECTION
#define CAN_INJECTION_BUFFER_ITEMS 2
#define CAN_INJECTION_BUFFER_SIZE CAN_INJECTION_BUFFER_ITEMS*sizeof(can_message_info_raw) // elements count
#endif

#define FDCAN_RX_ITEMS_IN_BUFFER                      6U
#define FDCAN_TX_ITEMS_IN_BUFFER                      64U
//========================================    FD CAN     ==================================================
// FD CAN buffer size definitions:  fdcan_buffer.h 





//=========================================================================================================
//====================================== Standart format defs  ============================================
#define OPERATION_OK               0U
#define OPERATION_FAIL             1U

#define DEVICE_INFO_STRING_SZ      16U

#define NULL_MCODE                 '0'
#define ALLIGATOR_MCODE            '1'
#define TEC_MODULE_MCODE           '2'
#define DEVICE_2CAN_MCODE          '3'
#define DEVICE_2CAN_TJA1042_MCODE  '4'
#define DEVICE_2CAN_BOXED_MCODE    '5'
#define DEVICE_SIGMA_MCODE         '6'
#define DEVICE_1CAN2LIN_MCODE      '7'
#define DEVICE_FCAN_V6_MCODE       '8'
#define PRZRK8XL_MCODE             '9'
#define DEVBOARD_F407VET_A_MCODE   'A'



#endif // COMPILER_SETTINGS_H_INCLUDED
