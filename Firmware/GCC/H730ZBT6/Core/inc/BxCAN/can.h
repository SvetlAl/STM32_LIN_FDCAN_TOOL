//*****************************************************************
// 
// STM32F105
// bxCAN controller functions
// todo: Add Extended id support, RTR
// Alex Svetlichnyy 2019
//*****************************************************************
#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include "BxCAN/can_macros.h"


#define CAN_INIT_TIMEOUT_MAX                0xFFF
#define CAN_BAUDRATE_1000KB                 1000U
#define CAN_BAUDRATE_500KB                  500U
#define CAN_BAUDRATE_250KB                  250U
#define CAN_BAUDRATE_125KB    	          	125U
#define CAN_BAUDRATE_83KB    	  	          83U

#define CAN_TX_MAILBOX_0                    0U
#define CAN_TX_MAILBOX_1                    1U
#define CAN_TX_MAILBOX_2                    2U
#define ERR_CAN_NO_EMPTY_MAILBOX            4U
#define ERR_CAN_TX_ERROR                    5U
#define ERR_CAN_ARB_ERROR                   6U
#define CAN_TX_OK                           7U
#define CAN_TX_IDLE                         8U

#define RQCP_STATUS                         CAN_TSR_RQCP0
#define ALST_STATUS                         CAN_TSR_ALST0
#define TERR_STATUS                         CAN_TSR_TERR0
#define TXOK_STATUS                         CAN_TSR_TXOK0

#define CAN_EMPTY_MAILBOX_TIMEOUT		        0xFF

#define CAN_TRANSMIT_TIMEOUT                0xFF // 0x01
#define CAN_BUFFERED_TRANSMIT_TIMEOUT       0x01 // 0x01
#define CAN_BUFFERED_EMPTY_MAILBOX_TIMEOUT	0xFFFFF // 0x01
#define CAN_BUFFERED_MAILBOX_STATUS_TIMEOUT	0xFFFFF // 0x01

#ifdef SUPPORT_BXCAN
#include "BxCAN/can_buffer.h"
//=================================================================================================
//=================================== Initialization ==============================================
can_btr_setting calculate_baudrate(uint32_t baudRate); 									// Configure CAN1 pins
uint32_t Can_Init(can_btr_setting _btr_set1, can_btr_setting _btr_set2); // General CAN2 initialization

//=================================================================================================
//=================================== Receive/Transmit ============================================

void Can_Recieve_StdMessage(CAN_TypeDef* _CAN_TP, uint32_t FifoNo, struct can_message *outup_msg);
uint32_t Can_Transmit_Message(CAN_TypeDef* _CAN_TP, struct can_message *canMessage);		// Transmit a CAN message

//=================================================================================================
//=================================== Buffer engine ===============================================
uint32_t process_buffered_can_tx(void);
#endif //SUPPORT_BXCAN

#endif /* CAN_H_INCLUDED*/
