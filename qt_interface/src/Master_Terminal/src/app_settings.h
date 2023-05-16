#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H
#include <stdlib.h>
#include <iostream>
#include <QString>
#include <QRegularExpression>
#include <QCoreApplication>


#define QT_IN_USE

#ifdef Q_OS_ANDROID
#define ANDROID_V
//#define PC_WINDOWS
#endif
#ifndef Q_OS_ANDROID
//#define PC_WINDOWS
#define PC_LINUX
#endif

#define USB_CDC_INTERFACE


/*********************************************************************************/
/*                                                                               */
/*                       Imported defs from firmware                             */
/*                                                                               */
/*     CanBusItem.h     <== can_override.h                                       */
/*     Vehicle.h        <== vehicle.h                                            */
/*     DeviceManager.h  <== device_model.h                                       */
/*                                                                               */
/*     QVehicle_ModelProperty.cpp - supported Vehicle models                     */
/*                                                                               */
/*********************************************************************************/


/****************************************************************
 *
 * Max Firmware size is assumed to be 64Kbytes
 *
*****************************************************************/

//========================================
//============ Debug settings ============
#define CURRENT_VERSION_IS_DEBUG
#define MEMORY_MONITOR_DEBUG

#ifdef QT_IN_USE
    #define DEBUG_OUT(i) qDebug() << QString::fromStdString(i);
    #define QDEBUG_OUT(i) qDebug() << i;
    #define DEBUG_OUT_POD(i) qDebug() << i;
#else
    #define DEBUG_OUT(i) cout << i;
    #define DEBUG_OUT_QSTR(i) cout << i.toStdString();
#endif


//=====================================
//=========  Responses ================
#define RESULT_OK true
#define RESULT_FAIL false

using namespace std;

class App_settings{
public:

//==============================================================================
//================================= App info ===================================
//==============================================================================
    static inline const QString INTERFACE_VERSION = "v1.08.05.23.0000";

//==============================================================================
//=========================== Firmware settings ================================
//==== The values in this block are duplicated from Firmware (STM32 programm) ==
//==============================================================================

    constexpr static inline const int DEFAULT_DEVICE_PID = 22336;
    constexpr static inline const int MAX_FIRMWARE_SIZE = ((64*1024) - 4);

    constexpr static inline const int MAX_DISCARD_ID_COUNT = 16;
    constexpr static inline const int MAX_OVERRIDE_FILTER_COUNT = 16;


//==============================================================================
//======================= Default serial port setings ==========================
//==============================================================================

#ifndef ANDROID_V
    int CDC_WRITE_TIMEOUT = 20; /* ms */
    int CDC_READ_TIMEOUT = 20; /* ms */
    int m_Cdc_cmd_process_timeout = 20; /* ms */
    int m_Cdc_Jni_drv_timeout = 100; /* ms */
    int m_Cdc_busy_cmd_trials = 5; /* count */

    int m_max_recieve_data_per_request = 64; /* bytes */
    int m_max_transmit_data_per_request = 64; /* bytes */
#endif
#ifdef ANDROID_V
    int m_Cdc_write_timeout = 50; /* ms */
    int m_Cdc_read_timeout = 50; /* ms */
    int m_Cdc_cmd_process_timeout = 75; /* ms */
    int m_Cdc_Jni_drv_timeout = 100; /* ms */
    int m_Cdc_busy_cmd_trials = 5; /* count */

    int m_max_recieve_data_per_request = 64; /* bytes */
    int m_max_transmit_data_per_request = 64; /* bytes */
#endif



//==============================================================================
//=========================== Interface presets ================================
//==============================================================================

    static inline const QString DEFAULT_VERSION_INFO_ADDRESS = "https://raw.githubusercontent.com/SvetlAl/test_public/master/version.txt";
    static inline const QString DEFAULT_UPDATE_ADDRESS = "https://raw.githubusercontent.com/SvetlAl";
    static inline const QString DEFAULT_CODE_OVERRIDE_ADDRESS = "https://raw.githubusercontent.com/SvetlAl/test_public/master/version.txt";

    static inline const QString VERSION_INFO_CACHE_PATH = "vinfo.cache";
    static inline const QString UPDATE_CACHE_PATH = "update_app.bin";
    static inline const QString CODE_OVERRIDE_CACHE_PATH = "code_override.cache";

    static inline const QString CONNECT_BUTTON_DISCONNECTED = "#949391";
    static inline const QString CONNECT_BUTTON_CONNECTED = "#00FF00";
    static inline const QString CONNECT_BUTTON_FAILED = "#FF0000";

    constexpr static inline const uint32_t DEFAULT_MAX_TRACE_ITEMS = 5000000;

    static const QRegularExpression get_DeviceSoftwareVersion_Regex(){
        return QRegularExpression("[\\w ]{2}\\.(\\d{2}\\.){2}\\d{2}\\.[A-F\\d]{4}");
    }

    enum class ConnectionStatus: quint8{
        Disconnected = 0x00,
        Connected = 0x01,
        Failed = 0x02
    };

//==============================================================================
//=========================== Filesystem Paths =================================
//==============================================================================

#if defined(ANDROID_V) || defined(PC_LINUX)
    static inline const QString APP_DIR = "/";
#elif defined(PC_WINDOWS)
    static inline const QString APP_DIR = "./";
#endif
    static inline const QString APP_NAME = "app";
    static inline const QString APP_EXT = ".dat";

#if defined(ANDROID_V) || defined(PC_LINUX)
    static inline const QString USERPROFILES_DIR = "/Profiles/";
#elif defined(PC_WINDOWS)
    static inline const QString USERPROFILES_DIR = "./Profiles/";
#endif
    static inline const QString USERPROFILES_EXT = ".usr";

    static inline const QString SERIALPORTCONFIG_DIR = USERPROFILES_DIR;
    static inline const QString SERIALPORTCONFIG_EXT = ".cfg";

    static inline const QString WEBCONFIG_DIR = USERPROFILES_DIR;
    static inline const QString WEBCONFIG_EXT = ".wcfg";

#if defined(ANDROID_V) || defined(PC_LINUX)
    static inline const QString APPDESIGN_DIR = "/DesignSettings/";
#elif defined(PC_WINDOWS)
    static inline const QString APPDESIGN_DIR = "./DesignSettings/";
#endif

    static inline const QString APPDESIGN_EXT = ".dsg";
    static inline const QString DEFAULT_USERNAME = "default";

    static inline const QString TRANSLATIONS_PATH = ":/res/languages/";


//==============================================================================
//=============================== Miscelaneous =================================
//==============================================================================

    static inline bool isBigEndian(){
        int i = 1;
        char* c = (char*)&i;
        return (*c == 0);
    }
};

/*********************************************************************************/
/*                                                                               */
/*                       Imported defs from firmware                             */
/*                                                                               */
/*********************************************************************************/

/*********************************************************************************/
/*                       device_model.h import                                   */
/*********************************************************************************/

#define NULL_MCODE					'0'
#define ALLIGATOR_MCODE             '1'
#define TEC_MODULE_MCODE			'2'
#define DEVICE_2CAN_MCODE			'3'
#define DEVICE_2CAN_TJA1042_MCODE	'4'
#define DEVICE_2CAN_BOXED_MCODE		'5'
#define DEVICE_SIGMA_MCODE			'6'



/*********************************************************************************/
/*                       vehicle.h import                                        */
/*********************************************************************************/

#define STARTUP_SETTINGS_DEFAULT		0x00
#define STARTUP_SETTINGS_IWDG			0x01

#define CALIBRATOR_DEFAULT_MODE			0x00
#define CALIBRATOR_ODO_FREEZE_MODE		0x01
#define CALIBRATOR_TEST_MODE			0x02

#define MODEL_TOYOTA_LC300              0x0000
#define MODEL_TOYOTA_LC150              0x0001
#define MODEL_TOYOTA_HILUX              0x0002
#define MODEL_TOYOTA_TUNDRA_2008        0x0003
#define MODEL_GREAT_WALL_WINGLE7        0x0004
#define MODEL_DODGE_RAM_2013            0x0005
#define MODEL_ISUZU_DMAX_MUX            0x0006
#define MODEL_LAND_ROVER_DEFENDER_2022  0x0007
#define MODEL_MITSUBISHI_L200           0x0008
#define MODEL_MITSUBISHI_PAJERO_SPORT   0x0009
#define MODEL_GREAT_WALL_POER           0x000A
#define MODEL_TOYOTA_LC200              0x000B
#define MODEL_LEXUS_LX570               0x000C
#define MODEL_TOYOTA_TUNDRA_2022        0x000D
#define MODEL_TANK_300        			0x000E
#define MODEL_EXTRA        				0x000F

#define MODEL_COUNT						0x0010



/*********************************************************************************/
/*                           user_cmd.h import                                   */
/*********************************************************************************/

/* Commands enumeration */
/* Hide in comments down from here, if not used */
#define	ELP_CMD_IDLE											0x00000000 /* Test connection.    @S 00000000 @E  --> Device --> $OK$ */
#define	ELP_CMD_ERROR											0x00000001 /* When failed to parse a command string, set this definition as cmd */
#define	ELP_CMD_RESET											0x00000002	/*@S 00000002 @E  equal to ELP_CMD_IDLE */
//#define	ELP_CMD_PRINT										0x00000003	/* @S00000003@?04@!Test@E --> com 00000003 param_cnt 00. Test function: a command string explained sent back.   */
//#define	ELP_CMD_PRINT_STRING								0x00000004	/* @S00000004@?04@!Test@E --> Test. Test function: a string arg sent back.  */
#define	ELP_CMD_SPI_MEMCHIP_READ								0x00000005	/* @S00000005#00#00#00#00#08@E --> 8 bytes from addr 0x000000 Load and send via USB a data from a certain address of size X bytes.  */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_SECTOR						0x00000006	/* @S00000006#00#00#00@E --> Erase the sector from addr 0x000000 */
#define	ELP_CMD_SPI_MEMCHIP_ERASE_CHIP							0x00000007	/* @S00000007@E --> Erase the whole chip. IMPORTANT: this proc can take up to 30 secs*/
#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP						0x00000008	/* @S00000008#00#00#00@?04@!Test@E --> Write the 4 bytes string "Test" as 'T' 'e' 's' 't' into the address 0x00000 */
//#define	ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_VAL				0x00000009
//#define	ELP_CMD_SPI_MEMCHIP_INPUT_STREAM					0x0000000A
//#define	ELP_CMD_SPI_MEMCHIP_READ_DMA						0x0000000B
//#define ELP_TEST_CMD_SPI_MX25_PROGRAMM_CHIP_DMA               0x0000000C
#define ELP_TEST_CMD_SPI_MX25_GET_RDSR							0x0000000D	/* @S0000000D@E --> RDSR */
//#define ELP_CMD_SPI_MEMCHIP_PROGRAMM_CHIP_HEX                 0x0000000E	/* @S0000000E#00#00#00@?04@!ABCD@E --> Write the 4 bytes string "ABCD" as 0xAB 0xCD into the address 0x00000 */
#define ELP_TEST_CMD_SPI_MX25_GET_RDCR							0x0000000F	/* @S0000000D@E --> RDCR */
#define ELP_ERASE_AREA											0x00000010	/* @00000010#00#01#40#00#02#80@E --> Erase data starting from address -0x000140 0x000280 bytes */

/* Speedometer Calibrator */
//#define ELP_VEHICLE_GET_MEMORY_STATUS_STRING_HEX                0x00000A00  /* @S00000A00@E HEX This sends 128 bytes of the first memory page as hex.	*/

#define ELP_VEHICLE_SET_MODEL									0x00000A01	/* @S00000A01@?08@!0000000A@E Set 0x000A as a model */
// #define ELP_VEHICLE_SET_STARTUP_SETTINGS                     0x00000A02
#define ELP_VEHICLE_SET_SPEEDOMETER_MLT							0x00000A03	/* @S00000A03@?02@!64@E Set 0x64 (100) as a SPEEDOMETER_MLT */
#define ELP_VEHICLE_SET_ODOMETER_MLT							0x00000A04	/* @S00000A04@?02@!64@E Set 0x64 (100) as a ODOMETER_MLT */
#define ELP_VEHICLE_SET_CRUISE_MLT								0x00000A05	/* @S00000A05@?02@!64@E Set 0x64 (100) as a CRUISE_MLT */
#define ELP_VEHICLE_SET_TYRES_THRESHOLD							0x00000A06	/* @S00000A06@?02@!64@E Set 0x64 (100) as a TYRES_THRESHOLD */

/* expanded ODOMETER_MODE */
/* Applying a mask: uint32_t value 0x00001234, 0x12 - is a mask to "&= ~", 34 is a mask to "|= "*/
#define ELP_VEHICLE_SET_MODE 									0x00000A07	/* @S00000A07@?08@!00000102@E reset 0x02 and set 0x01 */
#define ELP_VEHICLE_SET_MODE_CMDSTR_LENGTH                      8	/* proper length of the value string */
/* deprecated, use ELP_VEHICLE_SET_MODE */
#define ELP_VEHICLE_SET_TEST_MODE	/* deprecated */            0x00000A08	/* @S00000A08@?02@!02@E Set 0x02 (100) as a TEST_MODE */

#define ELP_VEHICLE_GET_SW_VERSION								0x00000A09	/* @S00000A09@E Get device software version */
#define RESPONSE_LENGTH_GET_SW_VERSION                          16
#define ELP_VEHICLE_GET_DEV_MODEL								0x00000A0A	/* @S00000A0A@E Get 16 bytes of device Hw model */
#define RESPONSE_LENGTH_GET_DEV_MODEL                           16

#define ELP_VEHICLE_GET_CURRENT_STATUS_STRING_ASCII             0x00000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings */
#define RESPONSE_LENGTH_CURRENT_STATUS_STRING_ASCII             16
#define ELP_VEHICLE_SAVE_STATUS									0x00000AA0	/* @S00000AA0@E Save current vehicle settings into (0x0000) VEHICLE_SETTINGS_ADDRESS */

#define ELP_OVR_FLTR_SET_VALUE									0x00000B08	/* @S00000B08#X0
                                                                                          00 - ignored id
                                                                                          01 - override id ------.
                                                                                            #X1					 |
                                                                                            00 remove			 |
                                                                                            01 add ---.			 |
                                                                                              #X2 <---'			 |
                                                                                               01 CAN 1			 |
                                                                                               02 CAN 2			 |
                                                                                                #X3 CAN Id		 |
                                                                                                #X4				 |
                                                                                                #X5				 |
                                                                                                #X6				 |----.
                                                                                                     #X7 flt_msk <    |
                                                                                                        #X8   <-------'
                                                                                                          #X9
                                                                                                          #XA
                                                                                                          #XB
                                                                                                          #XC
                                                                                                          #XD
                                                                                                          #XE
                                                                                                          #XF Filter */

#define ELP_DEVICE_SET_MODE 									0x00000B07	/* @S00000B07#01#02@E set the first var in DeviceModel as 02 */
#define ELP_DEVICE_SAVE_STATUS									0x00000BA0	/* @S00000BA0@E Save current device settings into (0x00FA00) DEVICE_MODES_ADDRESS */
#define ELP_UPDATE_OVR_FILTERS									0x00000BA1	/* @S00000BA1@E Start filter update procedure */
#define ELPR_DEVICE_GET_CURRENT_STATUS 							0xF0000BB0	/* @SF0000BB0@E ASCII Get sizeof(DeviceModel) of current vehicle settings in raw data*/
#define ELPR_OVR_FLTR_GET_CURRENT_STATUS 						0xF0000BB1	/* @SF0000BB1@E ASCII Get sizeof(can_override_status) of current override settings in raw data*/
#define ELPR_OVR_FLTR_GET_FILTER_NUMS		 					0xF0000BB2	/* @SF0000BB2@E ASCII Get uint16_t ignored_id_num; uint16_t overrided_id_num; */

/* All commands starting with F and named with ELPR use raw data, without converting into Ascii */
#define ELPR_VEHICLE_GET_CURRENT_STATUS 						0xF0000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings in raw data*/


/* All commands starting with F and named with ELPR use raw data, without converting into Ascii */
#define ELPR_VEHICLE_GET_CURRENT_STATUS 						0xF0000AB0	/* @S00000AB0@E ASCII Get 8 bytes of current vehicle settings in raw data*/
#define RESPONSE_LENGTH_CURRENT_STATUS_STRING_HEX               8

#define	ELPR_CMD_SPI_MEMCHIP_PROGRAMM_CHIP                      0xF0000008	/* @S00000008#00#00#00@?04@!Test@E --> Write the 4 bytes string "Test" as 'T' 'e' 's' 't' into the address 0x00000 */
#define INVALID_MEMCHIP_ADDRESS                                 (uint32_t)0xFFFFFFFF

/*********************************************************************************/
/*                           can_override.h import                                   */
/*********************************************************************************/


#define OVERRIDE_CMD_BYTE0_IGNORE_ID	(uint8_t)0x00
#define OVERRIDE_CMD_BYTE0_OVERRD_ID	(uint8_t)0x01

#define OVERRIDE_CMD_BYTE1_RMV	(uint8_t)0x00
#define OVERRIDE_CMD_BYTE1_ADD	(uint8_t)0x01

#define OVERRIDE_CMD_BYTE2_CAN1	(uint8_t)0x01
#define OVERRIDE_CMD_BYTE2_CAN2	(uint8_t)0x02


#endif // APP_SETTINGS_H
