#include "Commands/device_modes.h"
#include "Commands/user_cmd.h"

static inline void resolve_mode_conflicts(uint32_t dev_mode_num, uint32_t value){
	#if defined(BOARD_MK_STM32F105) | defined(BOARD_MK_STM32F205) | defined(BOARD_MK_STM32F407)
	//============== CAN INJECTION from memory chip ===============
	if((dev_mode_num == Enm_canInjectionMode) & (value != DEVICE_OPERATION_MODE_OFF)){
		if(theDeviceModel.data[Enm_canInjectionMode_CDC] != DEVICE_OPERATION_MODE_OFF){
			theDeviceModel.data[Enm_canInjectionMode_CDC] = DEVICE_OPERATION_MODE_OFF;
			// stopMessageInjection();
		}
	}
	//============== CAN INJECTION from USB CDC ===============
	else if((dev_mode_num == Enm_canInjectionMode_CDC) & (value != DEVICE_OPERATION_MODE_OFF)){
		if(theDeviceModel.data[Enm_canInjectionMode] != DEVICE_OPERATION_MODE_OFF){
			theDeviceModel.data[Enm_canInjectionMode] = DEVICE_OPERATION_MODE_OFF;
			stopMessageInjection();
		}
	}
	#else
	UNUSED(dev_mode_num);
	UNUSED(value);
	#endif
}

//=========================================================================================================
//=====================================   Device modes handling   =========================================
/** 
* brief  Set a mode value in the uDeviceModel var
* param  command pointer
* param  
* retval 
*/	
void user_cmd_set_device_mode(elp_cmd *com){
	if(com->param_counter == 4){
		uint32_t dev_mode_num = extract_address_from_cmd(com);
		uint8_t value = com->param[3];
		if(dev_mode_num <= sizeof(DeviceModel)){
			resolve_mode_conflicts(dev_mode_num, value); // To prevent mode conflicts
			theDeviceModel.data[dev_mode_num] = value;
					
			//========================= Scanner mode ===================================
			if(((dev_mode_num == Enm_canScannerMode) | (dev_mode_num == Enm_can2ScannerMode)) & (value == DEVICE_OPERATION_MODE_ON)){ /* If the command is to start scanner */
				resetCanTimer(MAIN_TIMER);
				return;
			}
			//=================== CAN injection from memory chip ========================
			else if(dev_mode_num == Enm_canInjectionMode){
				if (value != DEVICE_OPERATION_MODE_OFF){ /* If the command is to start injection */
					#ifdef SUPPORT_MEMCHIP_CAN_INJECTION
					startMessageInjection(&theCanInjectionStatus, value);
					#endif	
					return;					
				}
				else if (value == DEVICE_OPERATION_MODE_OFF){ /* If the command is to stop injection */
					#ifdef SUPPORT_MEMCHIP_CAN_INJECTION
					stopMessageInjection();
					#endif
					return;
				}
			}
			//=================== CAN injection from USB CDC ============================
			#ifdef SUPPORT_BXCAN
			else if(dev_mode_num == Enm_canInjectionMode_CDC){
				if (value != DEVICE_OPERATION_MODE_OFF){ /* If the command is to start injection */
					CDC_initMessageInjection();
					return;
				}
				else if (value == DEVICE_OPERATION_MODE_OFF){ /* If the command is to stop injection */
					return;
					//stopMessageInjection();
					}
			}
			#endif // SUPPORT_BXCAN
			#ifdef SUPPORT_LIN
			else if((dev_mode_num <= Enm_lin_filter) & (dev_mode_num >= Enm_lin_filter)){
			restart_lin();
			}
			#endif
			protocol_response(ELP_OK);
			el_reset_state();
			return;
		}
	}
	protocol_response(ELP_ERROR);
}
