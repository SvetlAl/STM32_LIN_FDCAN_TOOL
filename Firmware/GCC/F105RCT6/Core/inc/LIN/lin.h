#ifndef LIN_H_INCLUDED
#define LIN_H_INCLUDED
/*****************************************************************
* 
* LIN
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*
* DEVICE_2CAN:
* USART3 C10 C11 LIN2 wire next to LIN1    Pullup - B0   Slave
* USART2 A2  A3  LIN1 wire next to 2CANH   Pullup - C4   Master
*
******************************************************************/

//#include "device_model.h"
#include "USART/usart.h"
#include "LIN/lin_macros.h"
#include "LIN/lin_filter.h"
#include "LIN/lin_item.h"

//===============================================================================================
//=================================== Global var declared in lin.c ==============================
extern GatewayLin gatewayLIN;

//===============================================================================================
//========================================= Local var access ====================================
uint8_t *lin_get_mosi_filter(void);
uint8_t *lin_get_miso_filter(void);
void lin_set_user_filter(uint8_t* bytes);

//===============================================================================================
//======================================== Initialization =======================================
void enable_lin             (volatile uint8_t *_mode, volatile uint8_t *_baudrate_preset, volatile uint8_t *_filter_preset, TIM_TypeDef* _TIM_TP, volatile uint32_t *sec);
void disable_lin            (void);
void restart_lin            (void);
void lin_select_poll_period (uint16_t poll_period);
uint16_t lin_get_poll_period(void);
//void set_lin_mode           (uint8_t mode);
//void reset_lin_mode         (uint8_t mode);
void set_lin_filter_mode    (uint8_t mode);



//===============================================================================================
//========================================== Master =============================================
//===============================================================================================
void master_schedule_item(LinItem *_item);
__WEAK void master_poll     (void);
__WEAK void master_device_tx(void);  // this functions defines device mode behavior for master tx
__WEAK void master_device_rx(void);  // this functions defines device mode behavior for master rx

//===============================================================================================
//========================================== Slave ==============================================
//===============================================================================================
void slave_schedule_item(LinItem *_item);
__WEAK void slave_device_tx(void);  // this functions defines device mode behavior for slave tx
__WEAK void slave_device_rx(void);  // this functions defines device mode behavior for slave rx

//===============================================================================================
//========================================== Main ==============================================
//===============================================================================================
void lin_process_engine(void);

#endif /* LIN_H_INCLUDED*/
