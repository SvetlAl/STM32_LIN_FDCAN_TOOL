//****************************************************************************************
// 
// 
// bxCAN gateway override functions
//
// Alex Svetlichnyy 2019
//****************************************************************************************
#ifndef CAN_OVERRIDE_H_INCLUDED
#define CAN_OVERRIDE_H_INCLUDED

#include "device_model.h"
#include "BxCAN/can_macros.h"

/****************************************************************************************/
/****** User settings customized here. Comment/uncomment unused/used configurations *****/
/****************************************************************************************/

#define MAX_OVERRIDE_FILTERS                  16U
#define MAX_IGNORED_IDS                       16U

#define OVERRIDE_CMD_BYTE0_IGNORE_ID          (uint8_t)0x00
#define OVERRIDE_CMD_BYTE0_OVERRD_ID          (uint8_t)0x01

#define OVERRIDE_CMD_BYTE1_RMV                (uint8_t)0x00
#define OVERRIDE_CMD_BYTE1_ADD                (uint8_t)0x01

#define OVERRIDE_CMD_BYTE2_CAN1               (uint8_t)0x01
#define OVERRIDE_CMD_BYTE2_CAN2               (uint8_t)0x02


#define DISCARD_MSG                           0U
#define PROCESS_MSG                           1U


/* CAN override filter */
typedef struct can_override_filter{	
	can_id id;
	uint8_t override_data[8];
} can_override_filter; //creating new type

/* STATUS CAN override */
typedef struct can_override_status{	
	uint16_t ignored_id_num;
	uint16_t overrided_id_num;
	uint16_t ignored_id_dirs_msk;   // 0 - CAN1, 1 - CAN2
	uint16_t overrided_id_dirs_msk; // 0 - CAN1, 1 - CAN2
	can_override_filter filters[MAX_OVERRIDE_FILTERS];
	can_id ignored_ids[MAX_IGNORED_IDS];
	uint8_t override_msks[MAX_OVERRIDE_FILTERS];
} can_override_status; //creating new type

/* Union */
typedef union u_can_override_status{	
	can_override_status status;
	uint8_t raw_data[sizeof(can_override_status)];
} u_can_override_status; //creating new type

//===============================================================================================
//======================================== Initialization =======================================
//===============================================================================================

//===============================================================================================
//======================================== Override =============================================
//===============================================================================================
void can_override_calibrate(can_message *newMessage);
void can_override_proc_reverse_calibrate(can_message *newMessage);

#ifdef SUPPORT_BXCAN
uint32_t can_override_process_filters(can_message *newMessage, uint32_t _can_num /* CAN1 or CAN2 */);
#endif // SUPPORT_BXCAN

//===============================================================================================
//======================================== Setters/Getters ======================================
//===============================================================================================
uint8_t *can_override_get_dataptr(void);

#ifdef SUPPORT_BXCAN
can_override_status *can_override_get_status(void);
#endif


#endif /* CAN_OVERRIDE_H_INCLUDED*/
