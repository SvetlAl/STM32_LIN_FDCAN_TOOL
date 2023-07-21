//*****************************************************************
// 
//
//	TEST FUNCTIONS
//
//
//*****************************************************************


#include "extras.h"

#ifdef TEST_SPEED_TRANSMITTER

static const uint32_t PCKT_CNT_TO_SEND = 500;
static uint32_t injection_counter = 0x0000;
static const uint32_t MSG_PCK_SIZE = 21;




static can_message LC300_SPD_ODO_0D7;
static can_message LC300_SPD_ODO_0D8;
static can_message LC300_CRS_399;
static uint8_t LC300_ODO = 0;

static can_message LC150_SPD_ODO_0B4;
static can_message LC150_SPD_ODO_0B5;
static uint8_t LC150_ODO = 0;
static can_message GW_SPD_SPD_265;
	
static can_message DODGE_SPD_11C;
static can_message DODGE_ODO_278;
	
static uint8_t DODGE_ODO = 0;
	
static can_message ISUZU_SPD_ODO_141;
static can_message ISUZU_CRS_46C;
	
static can_message LR_SPD_ODO_011;
static can_message LR_CRS_150;
	
	
static can_message MMC_SPD_ODO_214;
static can_message MMC_SPD_ODO_215;
	
static can_message GW_POER_SPD_SPD_266;
static can_message GW_POER_CRS_271;
static can_message GW_POER_TYRES_ERR_341;
static can_message GW_POER_TYRES_395;
	
static uint8_t POER_ODO1 = 0;
static uint8_t POER_ODO2 = 0;
	
static can_message  MMC_ACC_101;
static can_message  MMC_ACC_22B;
#endif

void init_extras(){
	
	#if (defined(TEST_SPEED_TRANSMITTER) | defined(TEST_SPEED_RESPONDER)) & defined(STM32F105)
		// LED A
	GPIOA->CRL	&= ~GPIO_CRL_CNF3;						
	GPIOA->CRL 	|= GPIO_CRL_MODE3_0;					
	GPIOA->CRL 	|= GPIO_CRL_MODE3_1;
	GPIOA->BSRR |= GPIO_BSRR_BR3;						
	// LED B	
	GPIOC->CRH	&= ~GPIO_CRH_CNF11;					
	GPIOC->CRH 	|= GPIO_CRH_MODE11_0;				
	GPIOC->CRH 	|= GPIO_CRH_MODE11_1;
	GPIOC->BSRR |= GPIO_BSRR_BR11;
	#endif
	
	
	#ifdef TEST_SPEED_TRANSMITTER

	LC300_SPD_ODO_0D8.id.std_id.id_highbyte=0x00;
	LC300_SPD_ODO_0D8.id.std_id.id_lowbyte=0xD8;
	LC300_SPD_ODO_0D8.dlc=8;
	LC300_SPD_ODO_0D8.data[0]=LC300_ODO ;
	LC300_SPD_ODO_0D8.data[1]=0x1A;
	LC300_SPD_ODO_0D8.data[2]=0x1A;
	LC300_SPD_ODO_0D8.data[3]=0x1A;
	LC300_SPD_ODO_0D8.data[4]=0x1A;
	LC300_SPD_ODO_0D8.data[5]=0x1A;
	LC300_SPD_ODO_0D8.data[6]=0x1A;
	LC300_SPD_ODO_0D8.data[7]=0x1A;
	
	LC300_CRS_399.id.std_id.id_highbyte=0x3;
	LC300_CRS_399.id.std_id.id_lowbyte=0x99;
	LC300_CRS_399.dlc=8;
	LC300_CRS_399.data[0]=0x1A ;
	LC300_CRS_399.data[1]=0x1A;
	LC300_CRS_399.data[2]=0x1A;
	LC300_CRS_399.data[3]=0x1A;
	LC300_CRS_399.data[4]=0x1A;
	LC300_CRS_399.data[5]=0x1A;
	LC300_CRS_399.data[6]=0x1A;
	LC300_CRS_399.data[7]=0x1A;
	
	LC300_SPD_ODO_0D7.id.std_id.id_highbyte=0x00;
	LC300_SPD_ODO_0D7.id.std_id.id_lowbyte=0xD7;
	LC300_SPD_ODO_0D7.dlc=8;
	LC300_SPD_ODO_0D7.data[0]=LC300_ODO ;
	LC300_SPD_ODO_0D7.data[1]=0x1A;
	LC300_SPD_ODO_0D7.data[2]=0x1A;
	LC300_SPD_ODO_0D7.data[3]=0x1A;
	LC300_SPD_ODO_0D7.data[4]=0x1A;
	LC300_SPD_ODO_0D7.data[5]=0x1A;
	LC300_SPD_ODO_0D7.data[6]=0x1A;
	LC300_SPD_ODO_0D7.data[7]=0x1A;

	LC150_SPD_ODO_0B4.id.std_id.id_highbyte=0x0;
	LC150_SPD_ODO_0B4.id.std_id.id_lowbyte=0xB4;
	LC150_SPD_ODO_0B4.dlc=8;
	LC150_SPD_ODO_0B4.data[0]=0x1A ;
	LC150_SPD_ODO_0B4.data[1]=0x1A;
	LC150_SPD_ODO_0B4.data[2]=0x1A;
	LC150_SPD_ODO_0B4.data[3]=0x1A;
	LC150_SPD_ODO_0B4.data[4]=LC150_ODO;
	LC150_SPD_ODO_0B4.data[5]=0x1A;
	LC150_SPD_ODO_0B4.data[6]=0x1A;
	LC150_SPD_ODO_0B4.data[7]=0x1A;
	
	LC150_SPD_ODO_0B5.id.std_id.id_highbyte=0x0;
	LC150_SPD_ODO_0B5.id.std_id.id_lowbyte=0xB5;
	LC150_SPD_ODO_0B5.dlc=8;
	LC150_SPD_ODO_0B5.data[0]=0x1A ;
	LC150_SPD_ODO_0B5.data[1]=0x1A;
	LC150_SPD_ODO_0B5.data[2]=0x1A;
	LC150_SPD_ODO_0B5.data[3]=0x1A;
	LC150_SPD_ODO_0B5.data[4]=LC150_ODO;
	LC150_SPD_ODO_0B5.data[5]=0x1A;
	LC150_SPD_ODO_0B5.data[6]=0x1A;
	LC150_SPD_ODO_0B5.data[7]=0x1A;

	GW_SPD_SPD_265.id.std_id.id_highbyte=0x2;
	GW_SPD_SPD_265.id.std_id.id_lowbyte=0x65;
	GW_SPD_SPD_265.dlc=8;
	GW_SPD_SPD_265.data[0]=0x3A ;
	GW_SPD_SPD_265.data[1]=0x3A;
	GW_SPD_SPD_265.data[2]=0x3A;
	GW_SPD_SPD_265.data[3]=POER_ODO1;
	GW_SPD_SPD_265.data[4]=POER_ODO2;
	GW_SPD_SPD_265.data[5]=0x3A;
	GW_SPD_SPD_265.data[6]=0x3A;
	GW_SPD_SPD_265.data[7]=0x3A;
	
	GW_POER_SPD_SPD_266.id.std_id.id_highbyte=0x2;
	GW_POER_SPD_SPD_266.id.std_id.id_lowbyte=0x66;
	GW_POER_SPD_SPD_266.dlc=8;
	GW_POER_SPD_SPD_266.data[0]=0x3A ;
	GW_POER_SPD_SPD_266.data[1]=0x3A;
	GW_POER_SPD_SPD_266.data[2]=0x3A;
	GW_POER_SPD_SPD_266.data[3]=POER_ODO1;
	GW_POER_SPD_SPD_266.data[4]=POER_ODO2;
	GW_POER_SPD_SPD_266.data[5]=0x3A;
	GW_POER_SPD_SPD_266.data[6]=0x3A;
	GW_POER_SPD_SPD_266.data[7]=0x3A;

	GW_POER_CRS_271.id.std_id.id_highbyte=0x2;
	GW_POER_CRS_271.id.std_id.id_lowbyte=0x71;
	GW_POER_CRS_271.dlc=8;
	GW_POER_CRS_271.data[0]=0x00 ;
	GW_POER_CRS_271.data[1]=0x00;
	GW_POER_CRS_271.data[2]=0x00;
	GW_POER_CRS_271.data[3]=0x00;
	GW_POER_CRS_271.data[4]=0x00;
	GW_POER_CRS_271.data[5]=0x3A;
	GW_POER_CRS_271.data[6]=0x3A;
	GW_POER_CRS_271.data[7]=0x00;
	
	GW_POER_TYRES_395.id.std_id.id_highbyte=0x3;
	GW_POER_TYRES_395.id.std_id.id_lowbyte=0x95;
	GW_POER_TYRES_395.dlc=8;
	GW_POER_TYRES_395.data[0]=0x00 ;
	GW_POER_TYRES_395.data[1]=0x00;
	GW_POER_TYRES_395.data[2]=0xB9;
	GW_POER_TYRES_395.data[3]=0xB9;
	GW_POER_TYRES_395.data[4]=0xB9;
	GW_POER_TYRES_395.data[5]=0xB9;
	GW_POER_TYRES_395.data[6]=0x00;
	GW_POER_TYRES_395.data[7]=0x00;	
	
	GW_POER_TYRES_ERR_341.id.std_id.id_highbyte=0x3;
	GW_POER_TYRES_ERR_341.id.std_id.id_lowbyte=0x41;
	GW_POER_TYRES_ERR_341.dlc=8;
	GW_POER_TYRES_ERR_341.data[0]=0x00 ;
	GW_POER_TYRES_ERR_341.data[1]=0x00;
	GW_POER_TYRES_ERR_341.data[2]=0x00;
	GW_POER_TYRES_ERR_341.data[3]=0x00;
	GW_POER_TYRES_ERR_341.data[4]=0x00;
	GW_POER_TYRES_ERR_341.data[5]=0x00;
	GW_POER_TYRES_ERR_341.data[6]=0x00;
	GW_POER_TYRES_ERR_341.data[7]=0x00;

	DODGE_SPD_11C.id.std_id.id_highbyte=0x1;
	DODGE_SPD_11C.id.std_id.id_lowbyte=0x1C;
	DODGE_SPD_11C.dlc=8;
	DODGE_SPD_11C.data[0]=0x1A ;
	DODGE_SPD_11C.data[1]=0x1A;
	DODGE_SPD_11C.data[2]=0x1A;
	DODGE_SPD_11C.data[3]=0x1A;
	DODGE_SPD_11C.data[4]=0x1A;
	DODGE_SPD_11C.data[5]=0x1A;
	DODGE_SPD_11C.data[6]=0x1A;
	DODGE_SPD_11C.data[7]=0x1A;
	
	DODGE_ODO_278.id.std_id.id_highbyte=0x02;
	DODGE_ODO_278.id.std_id.id_lowbyte=0x78;
	DODGE_ODO_278.dlc=8;
	DODGE_ODO_278.data[0]=DODGE_ODO ;
	DODGE_ODO_278.data[1]=0x1A;
	DODGE_ODO_278.data[2]=0x1A;
	DODGE_ODO_278.data[3]=0x1A;
	DODGE_ODO_278.data[4]=0x1A;
	DODGE_ODO_278.data[5]=0x1A;
	DODGE_ODO_278.data[6]=0x1A;
	DODGE_ODO_278.data[7]=0x1A;
	
	ISUZU_SPD_ODO_141.id.std_id.id_highbyte=0x1;
	ISUZU_SPD_ODO_141.id.std_id.id_lowbyte=0x41;
	ISUZU_SPD_ODO_141.dlc=8;
	ISUZU_SPD_ODO_141.data[0]=0x1A ;
	ISUZU_SPD_ODO_141.data[1]=0x1A;
	ISUZU_SPD_ODO_141.data[2]=0x1A;
	ISUZU_SPD_ODO_141.data[3]=0x1A;
	ISUZU_SPD_ODO_141.data[4]=0x1A;
	ISUZU_SPD_ODO_141.data[5]=0x1A;
	ISUZU_SPD_ODO_141.data[6]=0x1A;
	ISUZU_SPD_ODO_141.data[7]=0x1A;
	
	ISUZU_CRS_46C.id.std_id.id_highbyte=0x4;
	ISUZU_CRS_46C.id.std_id.id_lowbyte=0x6C;
	ISUZU_CRS_46C.dlc=8;
	ISUZU_CRS_46C.data[0]=0x11 ;
	ISUZU_CRS_46C.data[1]=0x1A;
	ISUZU_CRS_46C.data[2]=0x1A;
	ISUZU_CRS_46C.data[3]=0x1A;
	ISUZU_CRS_46C.data[4]=0x1A;
	ISUZU_CRS_46C.data[5]=0x1A;
	ISUZU_CRS_46C.data[6]=0x1A;
	ISUZU_CRS_46C.data[7]=0x1A;
	
	LR_SPD_ODO_011.id.std_id.id_highbyte=0x0;
	LR_SPD_ODO_011.id.std_id.id_lowbyte=0x11;
	LR_SPD_ODO_011.dlc=8;
	LR_SPD_ODO_011.data[0]=0x1A ;
	LR_SPD_ODO_011.data[1]=0x1A;
	LR_SPD_ODO_011.data[2]=0x1A;
	LR_SPD_ODO_011.data[3]=0x1A;
	LR_SPD_ODO_011.data[4]=0x1A;
	LR_SPD_ODO_011.data[5]=0x1A;
	LR_SPD_ODO_011.data[6]=0x1A;
	LR_SPD_ODO_011.data[7]=0x1A;
	
	LR_CRS_150.id.std_id.id_highbyte=0x1;
	LR_CRS_150.id.std_id.id_lowbyte=0x50;
	LR_CRS_150.dlc=8;
	LR_CRS_150.data[0]=0x1A ;
	LR_CRS_150.data[1]=0x1A;
	LR_CRS_150.data[2]=0x1A;
	LR_CRS_150.data[3]=0x1A;
	LR_CRS_150.data[4]=0x1A;
	LR_CRS_150.data[5]=0x1A;
	LR_CRS_150.data[6]=0x1A;
	LR_CRS_150.data[7]=0x1A;
	
	MMC_SPD_ODO_214.id.std_id.id_highbyte=0x2;
	MMC_SPD_ODO_214.id.std_id.id_lowbyte=0x14;
	MMC_SPD_ODO_214.dlc=8;
	MMC_SPD_ODO_214.data[0]=0x1A ;
	MMC_SPD_ODO_214.data[1]=0x1A;
	MMC_SPD_ODO_214.data[2]=0x1A;
	MMC_SPD_ODO_214.data[3]=0x1A;
	MMC_SPD_ODO_214.data[4]=0x1A;
	MMC_SPD_ODO_214.data[5]=0x1A;
	MMC_SPD_ODO_214.data[6]=0x1A;
	MMC_SPD_ODO_214.data[7]=0x1A;
	
	MMC_SPD_ODO_215.id.std_id.id_highbyte=0x2;
	MMC_SPD_ODO_215.id.std_id.id_lowbyte=0x15;
	MMC_SPD_ODO_215.dlc=8;
	MMC_SPD_ODO_215.data[0]=0x1A ;
	MMC_SPD_ODO_215.data[1]=0x1A;
	MMC_SPD_ODO_215.data[2]=0x1A;
	MMC_SPD_ODO_215.data[3]=0x1A;
	MMC_SPD_ODO_215.data[4]=0x1A;
	MMC_SPD_ODO_215.data[5]=0x1A;
	MMC_SPD_ODO_215.data[6]=0x1A;
	MMC_SPD_ODO_215.data[7]=0x1A;
	
	MMC_ACC_101.id.std_id.id_highbyte=0x1;
	MMC_ACC_101.id.std_id.id_lowbyte=0x01;
	MMC_ACC_101.dlc=8;
	MMC_ACC_101.data[0]=0x01 ;
	MMC_ACC_101.data[1]=0x00;
	MMC_ACC_101.data[2]=0x00;
	MMC_ACC_101.data[3]=0x00;
	MMC_ACC_101.data[4]=0x00;
	MMC_ACC_101.data[5]=0x00;
	MMC_ACC_101.data[6]=0x00;
	MMC_ACC_101.data[7]=0x00;
	
	MMC_ACC_22B.id.std_id.id_highbyte=0x2;
	MMC_ACC_22B.id.std_id.id_lowbyte=0x2B;
	MMC_ACC_22B.dlc=8;
	MMC_ACC_22B.data[0]=0x00 ;
	MMC_ACC_22B.data[1]=0x1A;
	MMC_ACC_22B.data[2]=0x1A;
	MMC_ACC_22B.data[3]=0x1A;
	MMC_ACC_22B.data[4]=0x00;
	MMC_ACC_22B.data[5]=0x00;
	MMC_ACC_22B.data[6]=0x00;
	MMC_ACC_22B.data[7]=0x00;
	#endif
}

void process_extra_transmission(void){
	#ifdef TEST_SPEED_TRANSMITTER
	//while(timeout--){}
	
	LC300_SPD_ODO_0D7.data[0]=LC300_ODO ;
	LC300_SPD_ODO_0D8.data[0]=LC300_ODO ;
	SIGNAL_LED_B_ON;

	if(Can_Transmit_Message(CAN1, &LC300_SPD_ODO_0D7)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}	

	if(Can_Transmit_Message(CAN1, &LC300_SPD_ODO_0D8)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
	if(LC300_ODO >= 0x3E) LC300_ODO = 0;
	else LC300_ODO++;


	LC150_SPD_ODO_0B4.data[4]=LC150_ODO;
	LC150_SPD_ODO_0B5.data[4]=LC150_ODO;
	SIGNAL_LED_B_ON;	
	if(Can_Transmit_Message(CAN1, &LC300_CRS_399)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;

				
	SIGNAL_LED_B_ON;					
	if(Can_Transmit_Message(CAN1, &LC150_SPD_ODO_0B4)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;

				
	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &LC150_SPD_ODO_0B5)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}			
	SIGNAL_LED_B_OFF;
	LC150_ODO+=0x04;

					
	GW_SPD_SPD_265.data[3]=POER_ODO1;
	GW_SPD_SPD_265.data[4]=POER_ODO2;
	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &GW_POER_CRS_271)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &GW_SPD_SPD_265)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
				

					
	GW_POER_SPD_SPD_266.data[3]=POER_ODO1; GW_POER_SPD_SPD_266.data[4]=POER_ODO2;
	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &GW_POER_SPD_SPD_266)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
				

					
	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &GW_POER_TYRES_ERR_341)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
				
	SIGNAL_LED_B_ON;

	if(Can_Transmit_Message(CAN1, &GW_POER_TYRES_395)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;

	POER_ODO2++;
	if(POER_ODO2 == 0x00) POER_ODO1++;
	if(POER_ODO1 == 0x04)  POER_ODO1 = 0x00;
	DODGE_ODO_278.data[0]=DODGE_ODO ;

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &DODGE_SPD_11C)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}		
	SIGNAL_LED_B_OFF;				

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &DODGE_ODO_278)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
	DODGE_ODO++;

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &ISUZU_SPD_ODO_141)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}	
	SIGNAL_LED_B_OFF;

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &ISUZU_CRS_46C)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}

	SIGNAL_LED_B_OFF;
				
					
					// Additional
					/*
				SIGNAL_LED_B_ON;	
				if(Can_Transmit_Message(CAN1, &LC300_CRS_399)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
				SIGNAL_LED_B_OFF;
				timeout = transmit_timeout; while(timeout--){}
					*/
					
				
	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &LR_SPD_ODO_011)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}	
	SIGNAL_LED_B_OFF;				

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &LR_CRS_150)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &MMC_SPD_ODO_214)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}	
	SIGNAL_LED_B_OFF;				

	SIGNAL_LED_B_ON;
	if(Can_Transmit_Message(CAN1, &MMC_SPD_ODO_215)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
	
	SIGNAL_LED_B_ON;

	if(Can_Transmit_Message(CAN1, &MMC_ACC_22B)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	//timeout = transmit_timeout;while(timeout--){}			
	SIGNAL_LED_B_OFF;
		
	SIGNAL_LED_B_ON;

	if(Can_Transmit_Message(CAN1, &MMC_ACC_101)!=ERR_CAN_NO_EMPTY_MAILBOX){IWDG_reset();}
	SIGNAL_LED_B_OFF;
	#endif
}




	
void calculate_cnt_and_transmit(){
	#ifdef TEST_SPEED_TRANSMITTER
	
	if(check_free_buffer_size(CAN1_BUF_NUM) < MSG_PCK_SIZE){
		return;
	}
	
	else if(injection_counter > 0){
		injection_counter--;
		process_extra_transmission();
	}
	#endif
}

void check_test_transmission_request(){
	#ifdef TEST_SPEED_TRANSMITTER
	static volatile uint32_t _ready = 0;
	static volatile uint32_t theMode = 0;
	
	if((GPIOA->IDR & GPIO_IDR_IDR10)){
		_ready = 0x01;
	}	
	if((!(GPIOA->IDR & GPIO_IDR_IDR10)) & _ready & (injection_counter == 0)){
		_ready = 0x00;
		theMode = 0x01;
	}
	if(theMode  & (injection_counter == 0)){
		//TOTAL_RX_MSGS = 0;
		//secs = 0;
		injection_counter = PCKT_CNT_TO_SEND;
		theMode = 0x00;
	}
	#endif
}


