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
	'1',
	'4',
	'.',
	'0',
	'5',
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
}

void initDeviceGeneralPinout(void){
	#ifdef TEC_MODULE

	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(NO_REMAP_CAN2, CAN_BAUDRATE_500KB);
	
	
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

	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(REMAP_CAN2, CAN_BAUDRATE_500KB);
	
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
	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(REMAP_CAN2, CAN_BAUDRATE_500KB);
		
		
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
	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(NO_REMAP_CAN2, CAN_BAUDRATE_500KB);

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
	
	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(REMAP_CAN2, CAN_BAUDRATE_500KB);
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
	
	
	Can1_Init(REMAP_CAN1, CAN_BAUDRATE_500KB);  
	Can2_Init(NO_REMAP_CAN2, CAN_BAUDRATE_500KB);  	

	SPI3_init_pinout();
	AFIO->MAPR  |= AFIO_MAPR_SPI3_REMAP;
	SPI3_start(SPI_master_mode, SPI_polling_mode, SPI_b_mode, SPI_msb_mode, SPI_no_Dma);
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
	
	
	uint8_t *ovr_set_addr = get_override_settings_data();
	memory_chip_status.memchip_state = DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH;
	read_memchip(&memory_chip_status, DEVICE_OVERRIDE_FILTER_SETTINGS_ADDRESS, ovr_set_addr, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH, SPI_no_Dma);
	
	
	if(*get_override_settings_data() == 0xFF){ // Make sure the override status data is valid
		memset((void *)get_override_settings_data(), 0x00, DEVICE_OVERRIDE_FILTER_SETTINGS_LENGTH);
	}

}


uint8_t* getDeviceSoftwareVersion (){return &deviceSoftwareVersion[0];}
uint8_t* getHardwareVersion(){return &hardwareVersion[0];}
