/****************************************************************
* A device based on STM32F105 / F205 / H730
*
* CAN/LIN scanner, gateway, filter, multi-purpose tool
*
* Alex Svetlichnyy 2022 svetlal@outlook.com
*
*****************************************************************/


#include "main.h"

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan.h"
#endif // SUPPORT_FDCAN

#define MAIN_LOOP_TIMEOUT 0xFF
//=========================================================================================================
//===================================== Global vars	 and getters ==========================================
static void load_vehicle_from_memchip(void);
static void load_override_settings_from_memchip(void);
static void load_device_settings_from_memchip(void);
static void load_fdcan_settings_from_memchip(void);

//=========================================================================================================
//=============================================== Main timer ==============================================
static volatile uint32_t secs = 0x00; /* Timer, that counts seconds from the start */
volatile uint32_t *get_main_tim_sec_ptr(void){return &secs;}
         uint32_t  get_main_tim_secs   (void){return  secs;}


/**********************************************************************************************************
/
/
/                                            MAIN
/
/
**********************************************************************************************************/
 int main(void){
   /* Start HSE, PLL, Flash latency, all the RCC configuration */
	/* Enable all the Peripherial clocks */
	
	if(ClockInit() == CLOCK_ERROR){ /* Start HSE, PLL, Flash latency, all the RCC configuration */
		NVIC_SystemReset();
	}
	set_bor_level(BOR_VALUE);
	enable_peripherals();
	
	__disable_irq();	
	init_device_general_pinout();
	SPI_start_memchip_spi();
	
	load_device_settings_from_memchip();
	init_device_settings(); // here uDeviceModel (Scanner or Gateway or whatever), theOverrideStatus (filters) are initialized
	
	load_override_settings_from_memchip();
	init_CAN_override_settings();
	
	load_vehicle_from_memchip(); // 0x00014B880
	if(initVehicleSettings() == STARTUP_SETTINGS_IWDG) Init_IWDG(STARTUP_TIMEOUT);  // here theVehicle structure is initialized

	load_fdcan_settings_from_memchip();
	init_CAN_settings(vehicle_model());
	
	//======================================================================================
	//================================= Interrupt init =====================================
	//======================================================================================
	ENABLE_CAN1_RX_IRQ
	ENABLE_CAN2_RX_IRQ
	ENABLE_MAIN_TIM_IRQ
	ENABLE_TRACE_PLAYER_TIM_IRQ
	ENABLE_USB_CDC
	
	__enable_irq ();
	
	SIGNAL_LED_OFF;
	startBasicTimer(WATCHDOG_PROCEDURE_PSC, WATCHDOG_PROCEDURE_CNT, WATCHDOG_PROCEDURE_TIM);

	//======================================================================================
	//=================================   Main loop    =====================================
	//======================================================================================
	
	static volatile uint32_t timeout = MAIN_LOOP_TIMEOUT;
	while(1){
		PROCESS_LIN_ENGINE
		
		#ifdef PRZRK_DEBUG
		if(EMERGENCY_PIN_SET) start_stop_TEST_TANK500();
		#endif // PRZRK_DEBUG
		
		reset_hw_watchdog();
		
		timeout = MAIN_LOOP_TIMEOUT;
		while(timeout-- > 0){
			//*******************************************************************
			//******************** buffered transmission procedure ***************
			//*******************************************************************
			process_buffered_can_tx();
		}
		findAndProcess_cmd();
		//********** LED blinking **************
		main_led_blink();
	}
}



//=========================================================================================================
//====================================== Main (Watchdog) timer ============================================

#if defined BOARD_MK_STM32F205 | defined BOARD_MK_STM32F407
extern void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void){
	if(TIM1->SR & TIM_SR_UIF){
		TIM1->SR &= ~TIM_SR_UIF; // Flag down
		__disable_irq();
		TIM1->CNT = 0;
		secs++;
		__enable_irq();
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_ON)))
			runWatchdogProcedure();
		else if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON) IWDG_reset();
	}
}
#elif defined(BOARD_MK_STM32F105)
extern void TIM1_UP_IRQHandler(void);
void TIM1_UP_IRQHandler(void){
	if(TIM1->SR & TIM_SR_UIF){
		TIM1->SR &= ~TIM_SR_UIF; // Flag down
		__disable_irq();
		TIM1->CNT = 0;
		secs++;
		__enable_irq();
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_ON)))
			runWatchdogProcedure();
		else if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON) IWDG_reset();
	}
}
#elif defined(BOARD_MK_STM32H730)
extern void TIM2_IRQHandler(void);
void TIM2_IRQHandler(void){
	if(TIM2->SR & TIM_SR_UIF){
		TIM2->SR &= ~TIM_SR_UIF; // Flag down
		__disable_irq();
		TIM2->CNT = 0;
		secs++;
		__enable_irq();
		
		if((CAN2SCANNER_MODE != DEVICE_OPERATION_MODE_ON) & ((CAN_INJECTION_MODE != DEVICE_OPERATION_MODE_ON)))
			runWatchdogProcedure();
		else if(CAN2SCANNER_MODE == DEVICE_OPERATION_MODE_ON) IWDG_reset();
	}
}
#endif


static void load_vehicle_from_memchip(void){
	uint32_t length = VEHICLE_STATUS_SETTINGS_LENGTH;
	uint32_t addr = memchip_make_app_address(memchipVehicle);
	uint8_t *vhcl_data = get_vehicle_settings_data();
	memchip_read(addr, vhcl_data, length);
}
/**
* brief  Read out override settings from memory and init     
* param  can_override_status var 
* param  
* retval 
*/
static void load_override_settings_from_memchip(void){
	#ifdef SUPPORT_BXCAN
	uint32_t length = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	uint32_t address = memchip_make_app_address(memchipOverrideFilters);
	can_override_status *sts = can_override_get_status();
	memchip_read(address, (uint8_t *)sts, length);
	#endif // SUPPORT_BXCAN	
}

static void load_device_settings_from_memchip(void){
	uint32_t length = DEVICE_MODES_SETTINGS_LENGTH;
	uint32_t addr = memchip_make_app_address(memchipModes);
	memchip_read(addr, theDeviceModel.data, length);
}


static void load_fdcan_settings_from_memchip(void){
	#ifdef SUPPORT_FDCAN
	uint32_t length = DEVICE_MODES_SETTINGS_LENGTH;
	uint32_t addr = memchip_make_app_address(memchipFdcanSettings);
	uint8_t* dest_data = fdcan_get_settings_ptr();
	memchip_read(addr, dest_data, length);
	#endif
}



void resetCanTimer(TIM_TypeDef * TIM_n){
	TIM_n->CNT = 0;
	secs = 0;
}
