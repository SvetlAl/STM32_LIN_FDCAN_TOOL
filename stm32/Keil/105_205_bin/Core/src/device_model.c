/****************************************************************
* 
* Device Model
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/
#include "device_model.h"
#include "flash_mem_chip_spi.h"
#include "user_cmd.h"

//=======================================================================
//=============== The Vehicle global var ================================

uDeviceModel theDeviceModel;


static uint8_t deviceSoftwareVersion[DEVICE_INFO_STRING_SZ] = {
	'v',
	'1',
	'.',
	'0',
	'5',
	'.',
	'0',
	'8',
	'.',
	'2',
	'3',
	'.',
	DEV_CODE_ASCII(0),
	DEV_CODE_ASCII(1),
	DEV_CODE_ASCII(2),
	DEV_CODE_ASCII(3),
};

#ifdef DEVICE_SIGMA
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'a',
	'r',
	'l',
	'i',
	'n',
	'e',
	'_',
	'S',
	'i',
	'g',
	'm',
	'a',
	'_',
	DEVICE_SIGMA_MCODE
};
#endif

// Starline2CAN30_
#ifdef DEVICE_2CAN_BOXED
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'a',
	'r',
	'l',
	'i',
	'n',
	'e',
	'2',
	'C',
	'A',
	'N',
	'3',
	'0',
	'_',
	DEVICE_2CAN_BOXED_MCODE
};
#endif


// Starline_2CAN__
#ifdef DEVICE_2CAN_TJA1042
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'a',
	'r',
	'l',
	'i',
	'n',
	'e',
	'_',
	'2',
	'C',
	'A',
	'N',
	'_',
	'_',
	DEVICE_2CAN_TJA1042_MCODE
};
#endif



#ifdef DEVICE_2CAN
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'r',
	'l',
	'n',
	'2',
	'C',
	'A',
	'N',
	'2',
	'L',
	'I',
	'N',
	'_',
	'_',
	DEVICE_2CAN_MCODE
};
#endif



#ifdef TEC_MODULE
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'A',
	'r',
	'c',
	't',
	'i',
	'c',
	'T',
	'r',
	'u',
	'c',
	'k',
	's',
	'T',
	'E',
	'C',
	TEC_MODULE_MCODE
};
#endif

#ifdef ALLIGATOR
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'A',
	'l',
	'l',
	'i',
	'g',
	'a',
	't',
	'o',
	'r',
	'_',
	'2',
	'C',
	'A',
	'N',
	'_',
	ALLIGATOR_MCODE
};
#endif

#ifdef DEVICE_1CAN2LIN
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'S',
	't',
	'r',
	'l',
	'n',
	'1',
	'C',
	'A',
	'N',
	'2',
	'L',
	'I',
	'N',
	'_',
	'_',
	DEVICE_1CAN2LIN_MCODE
};
#endif

#ifdef DEVICE_FCAN_V6
static uint8_t hardwareVersion[DEVICE_INFO_STRING_SZ] = {
	'F',
	'_',
	'C',
	'A',
	'N',
	'_',
	'V',
	'6',
	'_',
	'_',
	'_',
	'_',
	'_',
	'_',
	'_',
	DEVICE_FCAN_V6_MCODE
};
#endif


void initDeviceModelDefaults(uDeviceModel *p_deviceModel){
	p_deviceModel->deviceModel.canGatewayMode = DEVICE_OPERATION_MODE_ON;
	p_deviceModel->deviceModel.calibratorFilterMode = DEVICE_OPERATION_MODE_ON;
	p_deviceModel->deviceModel.canInjectionMode = DEVICE_OPERATION_MODE_OFF;
	p_deviceModel->deviceModel.canOverrideMode = DEVICE_OPERATION_MODE_OFF;
	
	#ifdef MEMCHIP_MX25L323
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_MX25L323;
	#endif
	
	#ifdef MEMCHIP_M45PE16
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_M45PE16;
	#endif
	

#ifdef MEMCHIP_MX25L16
	p_deviceModel->deviceModel.memChipModel = MEMCHIP_MODEL_MX25L16;
	#endif
	p_deviceModel->deviceModel.customBTR = DEVICE_OPERATION_MODE_OFF;
	p_deviceModel->deviceModel.customBTR_2 = DEVICE_OPERATION_MODE_OFF;
}


void initCANSettings(uint16_t vehicle_model, uDeviceModel *p_deviceModel){
	can_btr_setting  settings_can1;
	can_btr_setting  settings_can2;
	if(CUSTOM_BTR_MODE == DEVICE_OPERATION_MODE_OFF){
		if(vehicle_model < MODEL_COUNT){
			settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
			settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
		}	
		//========== default BTR preset =============
		else{
			settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
			settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
		}
	}
	else if(CUSTOM_BTR_MODE == DEVICE_OPERATION_MODE_ON){
		settings_can1.psc = p_deviceModel->deviceModel.val_BTR_PSC > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_PSC - 1) : 0;
		settings_can1.bs1 = p_deviceModel->deviceModel.val_BTR_BS1 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS1 - 1) : 0;
		settings_can1.bs2 = p_deviceModel->deviceModel.val_BTR_BS2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS2 - 1) : 0;
		settings_can1.sjw = p_deviceModel->deviceModel.val_BTR_SJW > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_SJW - 1) : 0;
		
		settings_can2.psc = p_deviceModel->deviceModel.val_BTR_PSC_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_PSC_2 - 1) : 0;
		settings_can2.bs1 = p_deviceModel->deviceModel.val_BTR_BS1_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS1_2 - 1) : 0;
		settings_can2.bs2 = p_deviceModel->deviceModel.val_BTR_BS2_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_BS2_2 - 1) : 0;
		settings_can2.sjw = p_deviceModel->deviceModel.val_BTR_SJW_2 > 0 ? (uint8_t)(p_deviceModel->deviceModel.val_BTR_SJW_2 - 1) : 0;
	}
	else{
		//========== default BTR preset =============
		settings_can1 = calculate_baudrate(CAN_BAUDRATE_500KB);
		#ifndef DEVICE_1CAN2LIN
		settings_can2 = calculate_baudrate(CAN_BAUDRATE_500KB);
		#endif
	}
	#ifdef TEC_MODULE
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(NO_REMAP_CAN2, settings_can2);
	#endif
	#ifdef ALLIGATOR
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_FCAN_V6
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_2CAN
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_2CAN_BOXED
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(NO_REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_2CAN_TJA1042 
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_SIGMA 
	Can1_Init(REMAP_CAN1, settings_can1);  
	Can2_Init(NO_REMAP_CAN2, settings_can2);
	#endif
	#ifdef DEVICE_1CAN2LIN
	Can1_Init(REMAP_CAN1, settings_can1);  
	#endif
}

void initDeviceGeneralPinout(void){
	#ifdef TEC_MODULE
	
	/* CAN 1 STB  B4  */
	GPIOB->MODER &= ~GPIO_MODER_MODER4;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD4_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_2;
	
	GPIOB->BSRR |= GPIO_BSRR_BR4;
	
	/* CAN 2 STB  B15 */
	GPIOB->MODER &= ~GPIO_MODER_MODER15;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD15;
	GPIOB->MODER |= GPIO_MODER_MODER15_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD15_1;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_0;
	GPIOB->AFR[1] |= GPIO_AFRH_AFSEL15_2;
	
	GPIOB->BSRR |= GPIO_BSRR_BR15;
	
	/* LED */
	
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	GPIOC->MODER |= (GPIO_MODER_MODER13_0) ;
	GPIOC->BSRR |= GPIO_BSRR_BR_13;
 
	/* PB3 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER3;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3;
 
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef ALLIGATOR
	GPIOB->MODER &= ~GPIO_MODER_MODER7;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7;
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_2;
	
		/* LED */
	GPIOA->MODER &= ~GPIO_MODER_MODER8;
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD8;
	GPIOA->MODER |= (GPIO_MODER_MODER8_0) ;
	GPIOA->BSRR |= GPIO_BSRR_BS_8;
	
	
		/* PB1 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER1;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	
	GPIOB->BSRR |= GPIO_BSRR_BR7;

	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_2CAN
		
		// STB PIN
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BR7;						
		
	GPIOB->CRH	&= ~GPIO_CRH_CNF14;					
	GPIOB->CRH 	|= GPIO_CRH_MODE14_0;				
	GPIOB->CRH 	|= GPIO_CRH_MODE14_1;
	GPIOB->BSRR |= GPIO_BSRR_BR14;
	
	// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	
	#endif
	
	#ifdef DEVICE_2CAN_BOXED 

	GPIOB->CRH	&= ~GPIO_CRH_CNF11;						
	GPIOB->CRH 	|= GPIO_CRH_MODE11_0;					
	GPIOB->CRH 	|= GPIO_CRH_MODE11_1;
	GPIOB->BSRR |= GPIO_BSRR_BS11;						
		
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BS7;
	
	// EMERGENCY PIN	
	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->ODR |= GPIO_ODR_ODR14;

	SPI1_init_pinout();
	//AFIO->MAPR  |= AFIO_MAPR_SPI3_REMAP;
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);

	#endif
	
	#ifdef DEVICE_2CAN_TJA1042 
	// STB PIN
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BS7;						
		
	GPIOB->CRL	&= ~GPIO_CRL_CNF4;						
	GPIOB->CRL 	|= GPIO_CRL_MODE4_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE4_1;
	GPIOB->BSRR |= GPIO_BSRR_BS4;
	
		// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	
	#ifdef DEVICE_SIGMA 
	
	GPIOB->CRL	&= ~GPIO_CRL_CNF1;						
	GPIOB->CRL 	|= GPIO_CRL_MODE1_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE1_1;
	GPIOB->BSRR |= GPIO_BSRR_BS1;						
		
	GPIOC->CRH	&= ~GPIO_CRH_CNF14;						
	GPIOC->CRH 	|= GPIO_CRH_MODE14_0;					
	GPIOC->CRH 	|= GPIO_CRH_MODE14_1;
	GPIOC->BSRR |= GPIO_BSRR_BS14;
	
		// EMERGENCY PIN	
	GPIOB->CRH &= ~GPIO_CRH_CNF14;
	GPIOB->CRH |= GPIO_CRH_CNF14_1;
	GPIOB->ODR |= GPIO_ODR_ODR14;
	
	SPI3_init_pinout();
	AFIO->MAPR  |= AFIO_MAPR_SPI3_REMAP;
	SPI3_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_1CAN2LIN
		// STB PIN
	GPIOB->CRL	&= ~GPIO_CRL_CNF7;						
	GPIOB->CRL 	|= GPIO_CRL_MODE7_0;					
	GPIOB->CRL 	|= GPIO_CRL_MODE7_1;
	GPIOB->BSRR |= GPIO_BSRR_BR7;						
	
	// EMERGENCY PIN	
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->ODR |= GPIO_ODR_ODR10;
	
	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
	
	#ifdef DEVICE_FCAN_V6
	GPIOB->MODER &= ~GPIO_MODER_MODER7;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7;
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_2;
	
		/* LED */
	GPIOB->MODER &= ~GPIO_MODER_MODER0;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0;
	GPIOB->MODER |= (GPIO_MODER_MODER0_0) ;
	GPIOB->BSRR |= GPIO_BSRR_BS_0;
	
	
		/* PB1 RST */
	GPIOB->MODER &= ~GPIO_MODER_MODER1;
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED1;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1;
	
	GPIOB->BSRR |= GPIO_BSRR_BR7;

	SPI1_init_pinout();
	SPI1_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
	#endif
}

void initModelSettings(){
	uint32_t length = DEVICE_MODES_SETTINGS_LENGTH;
	uint32_t addr = DEVICE_MODES_ADDRESS;
	memory_chip_status.memchip_state = length;

	read_memchip(&memory_chip_status, addr, theDeviceModel.data, length, SPI_no_Dma);	
		
	// Gateway is always on by default
	if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_DEFAULT){
		initDeviceModelDefaults(&theDeviceModel);
	}
	// Memory programming is always off from the start
	SET_MEMCHIP_MEMORY_PROGRAMM_MODE(DEVICE_OPERATION_MODE_OFF);
	// CDC CAN injection is always off from the start
	SET_CAN_INJECTION_CDC_MODE(DEVICE_OPERATION_MODE_OFF);
	// Scanner is always off from the start
	SET_CANSCANNER_MODE(DEVICE_OPERATION_MODE_OFF);
	SET_CAN2SCANNER_MODE(DEVICE_OPERATION_MODE_OFF);
	
	// If custom calibration filter is default, set it on
	// and set all settings according to calibration preset
	if(CALIBRATOR_FILTER_MODE == DEVICE_OPERATION_MODE_DEFAULT) SET_CALIBRATOR_FILTER_MODE(DEVICE_OPERATION_MODE_ON);
	if(CALIBRATOR_FILTER_MODE == DEVICE_OPERATION_MODE_ON){
		SET_CAN_GATEWAY_MODE(DEVICE_OPERATION_MODE_ON);
		SET_CAN_OVERRIDE_MODE(DEVICE_OPERATION_MODE_OFF);
		SET_CAN_INJECTION_MODE(DEVICE_OPERATION_MODE_OFF);
	}
	
	// if not inited, set cdc threshold mode to auto
	if((CAN_INJECTION_CDC_THRESHOLD_MODE != DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD) ||
		(CAN_INJECTION_CDC_THRESHOLD_MODE != DEVICE_OPERATION_MODE_CDC_TRACE_FIXED_THRESHOLD)){
			SET_CAN_INJECTION_CDC_THRESHOLD_MODE(DEVICE_OPERATION_MODE_CDC_TRACE_AUTO_THRESHOLD);
	}
	
	if((CAN_INJECTION_CDC_THRESHOLD_VALUE < CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD) || (CAN_INJECTION_CDC_THRESHOLD_VALUE == 0xFF))
		SET_CAN_INJECTION_CDC_THRESHOLD_VALUE(CDC_CAN_INJECTING_TIMER_LOWER_THRESHOLD);
	
	// hardware filter is off from the start
	if(CAN_SCANNER_HARDWARE_FILTER == DEVICE_OPERATION_MODE_DEFAULT) SET_CAN_SCANNER_HARDWARE_FILTER(DEVICE_OPERATION_MODE_OFF);
	
	uint8_t *ovr_set_addr = get_override_settings_data();
	memory_chip_status.memchip_state = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	read_memchip(&memory_chip_status, DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS, ovr_set_addr, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH, SPI_no_Dma);
	
	
	if(*get_override_settings_data() == 0xFF){ // Make sure the override status data is valid
		memset((void *)get_override_settings_data(), 0x00, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH);
	}
}

#ifdef STM32F205
void set_bor_level(uint8_t br_lvl){
	if(br_lvl > 0x03) return;
	uint32_t current_br_lvl = (uint32_t)((FLASH->OPTCR & FLASH_OPTCR_BOR_LEV_Msk) >> FLASH_OPTCR_BOR_LEV_Pos);
	if(current_br_lvl == br_lvl){
		return;
	}
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->KEYR = ((uint32_t)0x45670123);
	FLASH->KEYR = ((uint32_t)0xCDEF89AB);
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTKEYR = ((uint32_t)0x08192A3B);
  FLASH->OPTKEYR = ((uint32_t)0x4C5D6E7F);
	
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTCR &= ~((uint32_t)(FLASH_OPTCR_BOR_LEV_Msk)); // clear BOR bits
	
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	FLASH->OPTCR |= (uint8_t)(br_lvl << FLASH_OPTCR_BOR_LEV_Pos);
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	
	FLASH->OPTCR |= FLASH_OPTCR_OPTSTRT;
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
	while((FLASH->SR & FLASH_SR_BSY) != 0); //
	FLASH->CR |= FLASH_CR_LOCK;
	while((FLASH->SR & FLASH_SR_BSY) != 0);
}
#endif


uint8_t* getDeviceSoftwareVersion (){return &deviceSoftwareVersion[0];}
uint8_t* getHardwareVersion(){return &hardwareVersion[0];}
