/****************************************************************
*
* FD CAN
*
* FDCAN periph functions and structs for STM32
* FDCAN1 and FDCAN2
*
*****************************************************************
* Default configuration:
* 500  Kb/s nominal bitrate
* 2000 Kb/s data bitrate
* FD mode on
* Bitrate switching mode on
*
* CAN filters accept all messages from both CANs
*
* FDCAN1 stores messages in FIFO0
* FDCAN2 stores messages in FIFO1
*
* FDCAN1 TX buffers located in 0-15 elements
* FDCAN2 TX buffers located in 16-31 elements
*
*
* Alex Svetlichnyy 2023 svetlal@outlook.com
*
*****************************************************************/

#include "device_model.h"

#ifdef SUPPORT_FDCAN
#include "FDCAN/fdcan.h"
#include "FDCAN/fdcan_ram_config.h"
#include "FDCAN/fdcan_can_override.h"
#include "FDCAN/fdcan_buffer.h"
#include "FDCAN/fdcan_scanner.h"
#include "FDCAN/fdcan_std_can_legacy.h"
#include "BxCAN/can_override.h"
#include "TIM/tim.h"
#include "main.h"
#include <string.h>

//=========================================================================================================
//=====================================      Global vars       ============================================
static u_fdcan_settings theFDCAN_Settings;

uint8_t *fdcan_get_settings_ptr(void){
	return &theFDCAN_Settings.raw_data[0];
}
fdcan_settings *fdcan_get_settings(void){
	return &theFDCAN_Settings.settings;
}

static FDCAN_GlobalTypeDef* FDCAN_PERIPH(uint8_t num){
	if(num == 0) return FDCAN1;
	else return FDCAN2;
}

//=========================================================================================================
//=====================================     Initialization     ============================================

/**
* brief  Init FDCAN filters. By default - accept all
* param  
* param  
* param  
* retval 
*/
static void init_filters(void){
	#ifndef FDCAN_ENABLE_FILTERS
	FDCAN1->SIDFC = 0; // How many filters engaged and start RAM address
	//GFC Reset value 0x0000 0000
	FDCAN1->GFC   &= ~FDCAN_GFC_RRFS; // Filter Remote Frames Standard
	FDCAN1->GFC   &= ~FDCAN_GFC_RRFE; // Filter Remote Frames Extended
	FDCAN1->GFC   &= ~FDCAN_GFC_ANFS; // Accept all Standard messages and store in FIFO 0
	FDCAN1->GFC   &= ~FDCAN_GFC_ANFE; // Accept all Extended messages and store in FIFO 1
	
	FDCAN2->SIDFC = 0; // How many filters engaged and start RAM address
	//GFC Reset value 0x0000 0000
	FDCAN2->GFC   &= ~FDCAN_GFC_RRFS; // Filter Remote Frames Standard
	FDCAN2->GFC   &= ~FDCAN_GFC_RRFE; // Filter Remote Frames Extended
	FDCAN2->GFC   |= (0x01 << FDCAN_GFC_ANFS_Pos); // Accept all Standard messages and store in FIFO 1
	FDCAN2->GFC   |= (0x01 << FDCAN_GFC_ANFE_Pos); // Accept all Extended messages and store in FIFO 1
	#endif
}

/**
* brief  Make a default configuration with 500 kb/s nominal and 2000 kb/s data bitrates
* param  FD CAN settinngs pointer
* param  
* param  
* retval 
*/
void fdcan_make_default_cfg(void){
	#ifdef FD_CAN_CK_FRQ_96MHZ
	for(uint8_t i = 0; i < CAN_INTERFACES_USED; i++){
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.PXHD = 0x00;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.FDOE = 0x01;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.BRSE = 0x01;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.DAR  = 0x00;
		
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.ASM  = 0x00;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.TXP  = 0x00;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.EFBI = 0x00;
		theFDCAN_Settings.settings.cccr_cfg[i].cfg.NISO = 0x00;

		// Nominal Bitrate  500 Kb/s
		theFDCAN_Settings.settings.nominal_bitrate[i].PSC     = 1;
		theFDCAN_Settings.settings.nominal_bitrate[i].TSEG1   = 143;
		theFDCAN_Settings.settings.nominal_bitrate[i].TSEG2   = 48;
		theFDCAN_Settings.settings.nominal_bitrate[i].SJW     = 24;
		// Data Bitrate  2000 Kb/s
		theFDCAN_Settings.settings.data_bitrate[i].PSC     = 2;
		theFDCAN_Settings.settings.data_bitrate[i].TSEG1   = 17;
		theFDCAN_Settings.settings.data_bitrate[i].TSEG2   = 6;
		theFDCAN_Settings.settings.data_bitrate[i].SJW     = 3;
	}
	#endif
}

/**
* brief  (Re-)Init and start FDCAN1 and FDCAN2, init buffers 
* param  FD CAN settinngs pointer
* param  
* param  
* retval 
*/

 
void fdcan_init(void){
	//RCC->APB1HRSTR  |=  (RCC_APB1HRSTR_FDCANRST); // reset FDCAN
	//RCC->APB1HRSTR  &= ~(RCC_APB1HRSTR_FDCANRST); // reset FDCAN
	RCC->APB1HRSTR |= RCC_APB1HRSTR_FDCANRST;
	while((RCC->APB1HRSTR & RCC_APB1HRSTR_FDCANRST) != RCC_APB1HRSTR_FDCANRST){}
	fdcan_enable_buffers();
	RCC->APB1HRSTR &= ~RCC_APB1HRSTR_FDCANRST;
		while((RCC->APB1HRSTR & RCC_APB1HRSTR_FDCANRST) == RCC_APB1HRSTR_FDCANRST){}
	
	NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
	NVIC_DisableIRQ(FDCAN2_IT0_IRQn);

	//===========  Start init for each FDCAN  ===========
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		//FDCAN1->CCCR reset value is 0x0000 0001
		FDCAN_PERIPH(k)->CCCR |= FDCAN_CCCR_INIT;     
		
    while ((FDCAN_PERIPH(k)->CCCR & FDCAN_CCCR_INIT) == 0) {};
    //CCE bit enabled to start configuration
    FDCAN_PERIPH(k)->CCCR |= FDCAN_CCCR_CCE;
	}
		
	//===========        Set CCCR bits        ===========
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		uint32_t cccr_setting_msk = (theFDCAN_Settings.settings.cccr_cfg[k].cfg.ASM << FDCAN_CCCR_ASM_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.DAR << FDCAN_CCCR_DAR_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.FDOE << FDCAN_CCCR_FDOE_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.BRSE << FDCAN_CCCR_BRSE_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.PXHD << FDCAN_CCCR_PXHD_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.EFBI << FDCAN_CCCR_EFBI_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.TXP << FDCAN_CCCR_TXP_Pos) | 
																(theFDCAN_Settings.settings.cccr_cfg[k].cfg.NISO << FDCAN_CCCR_NISO_Pos);
		FDCAN_PERIPH(k)->CCCR &= ~(uint32_t)( (FDCAN_CCCR_ASM_Msk) | 
																          (FDCAN_CCCR_DAR_Msk) | 
																          (FDCAN_CCCR_FDOE_Msk) | 
																          (FDCAN_CCCR_BRSE_Msk) | 
																          (FDCAN_CCCR_PXHD_Msk) | 
																          (FDCAN_CCCR_EFBI_Msk) | 
																          (FDCAN_CCCR_TXP_Msk) | 
																          (FDCAN_CCCR_NISO_Msk));
		
		FDCAN_PERIPH(k)->CCCR |= cccr_setting_msk;
	}
	// Clean message memory
	uint32_t *i;
	for (i = (uint32_t*)FDCAN_MEM_START_ADDR; i < (uint32_t*)FDCAN_MEM_END_ADDR; i++) *i = 0; 
	
	// FDCAN bitrates
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		FDCAN_PERIPH(k)->NBTP  = (theFDCAN_Settings.settings.nominal_bitrate[k].SJW   - 1) << FDCAN_NBTP_NSJW_Pos;
		FDCAN_PERIPH(k)->NBTP |= (theFDCAN_Settings.settings.nominal_bitrate[k].PSC   - 1) << FDCAN_NBTP_NBRP_Pos;
		FDCAN_PERIPH(k)->NBTP |= (theFDCAN_Settings.settings.nominal_bitrate[k].TSEG1 - 1) << FDCAN_NBTP_NTSEG1_Pos;
		FDCAN_PERIPH(k)->NBTP |= (theFDCAN_Settings.settings.nominal_bitrate[k].TSEG2 - 1) << FDCAN_NBTP_NTSEG2_Pos;
		
		FDCAN_PERIPH(k)->DBTP  = (theFDCAN_Settings.settings.data_bitrate[k].SJW   - 1) << FDCAN_DBTP_DSJW_Pos;
		FDCAN_PERIPH(k)->DBTP |= (theFDCAN_Settings.settings.data_bitrate[k].PSC   - 1) << FDCAN_DBTP_DBRP_Pos;
		FDCAN_PERIPH(k)->DBTP |= (theFDCAN_Settings.settings.data_bitrate[k].TSEG1 - 1) << FDCAN_DBTP_DTSEG1_Pos;
		FDCAN_PERIPH(k)->DBTP |= (theFDCAN_Settings.settings.data_bitrate[k].TSEG2 - 1) << FDCAN_DBTP_DTSEG2_Pos;
	}

	init_filters();

  FDCAN1->RXF0C  = FDCAN_RX_FIFO_0_OFFSET << FDCAN_RXF0C_F0SA_Pos;        // Start addr
	FDCAN1->RXF0C |= (FDCAN_RX_FIFO_0_EL_CNT     << FDCAN_RXF0C_F0S_Pos);   // Set RX FIFO 0 size to 16 messages
	FDCAN1->RXF0C |= ((FDCAN_RX_FIFO_0_EL_CNT/2) << FDCAN_RXF0C_F0WM_Pos);  // Set RX FIFO 0 watermark to 8 messages

  FDCAN2->RXF1C  = FDCAN_RX_FIFO_1_OFFSET << FDCAN_RXF1C_F1SA_Pos;        // Start addr
	FDCAN2->RXF1C |= (FDCAN_RX_FIFO_1_EL_CNT     << FDCAN_RXF1C_F1S_Pos);   // Set RX FIFO 1 size to 16 messages
	FDCAN2->RXF1C |= ((FDCAN_RX_FIFO_1_EL_CNT/2) << FDCAN_RXF1C_F1WM_Pos);  // Set RX FIFO 1 watermark to 8 messages
	
	

  FDCAN1->RXESC = (0x7 << FDCAN_RXESC_F0DS_Pos) | (0x7 << FDCAN_RXESC_F1DS_Pos);  // Set RX buffer sizes to maximum
	FDCAN2->RXESC = (0x7 << FDCAN_RXESC_F0DS_Pos) | (0x7 << FDCAN_RXESC_F1DS_Pos);  // Set RX buffer sizes to maximum

	
	FDCAN1->TXBC &= ~(FDCAN_TXBC_TFQM); // FIFO operation
	FDCAN1->TXBC |= FDCAN_TX_FIFO_EL_CNT << FDCAN_TXBC_TFQS_Pos;
	FDCAN1->TXBC |= FDCAN1_TX_FIFO_OFFSET << FDCAN_TXBC_TBSA_Pos;
	FDCAN1->TXESC |= 0x07; // Max message data length : 64
	
	FDCAN2->TXBC &= ~(FDCAN_TXBC_TFQM); // FIFO operation
	FDCAN2->TXBC |= FDCAN_TX_FIFO_EL_CNT << FDCAN_TXBC_TFQS_Pos;
	FDCAN2->TXBC |= FDCAN2_TX_FIFO_OFFSET << FDCAN_TXBC_TBSA_Pos;
	FDCAN2->TXESC |= 0x07; // Max message data length : 64
	
	// FD CAN 1: New message FIFO 0 interrupt
	FDCAN1->IE |= FDCAN_IE_RF0NE;
	// FD CAN 2: New message FIFO 2 interrupt
	FDCAN2->IE |= FDCAN_IE_RF1NE;
	
	// Interrupt lines
	FDCAN1->ILE |= FDCAN_ILE_EINT0;
	FDCAN2->ILE |= FDCAN_ILE_EINT0;


	//===========  Finish init for each FDCAN  ===========
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		FDCAN_PERIPH(k)->CCCR &= ~(FDCAN_CCCR_INIT);
    while ((FDCAN_PERIPH(k)->CCCR & FDCAN_CCCR_INIT) == FDCAN_CCCR_INIT) {};
	}
}


//=========================================================================================================
//===================================== Send/Recieve functions ============================================
/**
* brief  Read a single received message from FDCAN RAM
* param  FD CAN num (1 or 2)
* param  output data pointer
* param  FIFO index
* retval 
*/
static void fdcan_read_msg (uint8_t can_num, uint8_t* output, uint8_t idx){
	u_fdcan_fifo_element *fifo;
	u_fdcan_message_hdr *output_msg_hdr = (u_fdcan_message_hdr*)output;
	
	// Init Fifo and message pointers
	uint8_t *output_msg_data = &output[sizeof(fdcan_message_hdr)];
	
	if(can_num == FDCAN1_E){
		fifo = (u_fdcan_fifo_element*)(FDCAN_RX_FIFO_0_START_ADDR + idx * FDCAN_RX_FIFO_0_EL_SIZE);
	}
	else if(can_num == FDCAN2_E){
		fifo = (u_fdcan_fifo_element*)(FDCAN_RX_FIFO_1_START_ADDR + idx * FDCAN_RX_FIFO_1_EL_SIZE);
	}
	else return;
	
	// Set ESI, XTD, FDF, BRS
	output_msg_hdr->msg_hdr.fdflags.flags.ESI = (uint8_t)((fifo->word_arr.word[0] >> 31) & 0x01);
	output_msg_hdr->msg_hdr.fdflags.flags.XTD = (uint8_t)((fifo->word_arr.word[0] >> 30) & 0x01);
	output_msg_hdr->msg_hdr.fdflags.flags.FDF = (uint8_t)((fifo->word_arr.word[1] >> 21) & 0x01);
	output_msg_hdr->msg_hdr.fdflags.flags.BRS = (uint8_t)((fifo->word_arr.word[1] >> 20) & 0x01);
	
	// Set ID
	if(output_msg_hdr->msg_hdr.fdflags.flags.XTD == 0x01){
		output_msg_hdr->msg_hdr.id		= (fifo->word_arr.word[0] & 0x1FFFFFFF);
	}
	else{
		output_msg_hdr->msg_hdr.id		= ((fifo->word_arr.word[0] >> 18) & 0x7FF);
	}
	
	// Set DLC
	output_msg_hdr->msg_hdr.dlc		= ((fifo->word_arr.word[1] >> 16) & 0x0F);
	output_msg_hdr->msg_hdr.rxts		= ((fifo->word_arr.word[1] >> 0 ) & 0xFFFF);
	
	// Init message length and copy data
	const fdcan_message_hdr *msg_hdr = &output_msg_hdr->msg_hdr;
	uint32_t total_msg_sz = FDCAN_FD_MSG_LENGTH(msg_hdr);
	memcpy(output_msg_data, &fifo->data[8], total_msg_sz);
}

/**
* brief  Send a single message
* param  FD CAN num (1 or 2)
* param  input data pointer
* param 
* retval header size + data size
*/
static uint16_t fdcan_send_msg (uint8_t can_num, uint8_t* input){
	u_fdcan_fifo_element *fifo;
	uint8_t tx_index;
	
	if ((FDCAN_PERIPH(can_num)->TXFQS & FDCAN_TXFQS_TFQF) != 0){ // FDCAN_TXFQS TFQF: Tx FIFO/queue Full
		return 0;
	}
	// Get put index
	tx_index = (FDCAN_PERIPH(can_num)->TXFQS >> 16) & 0xF; // Bits 20:16 TFQPI[4:0]: Tx FIFO/queue put index  Tx FIFO/queue write index pointer, range 0 to 31

	// Init fifo pointer
	
	if(can_num == FDCAN1_E){
		fifo = (u_fdcan_fifo_element *)(FDCAN1_TX_FIFO_START_ADDR + (tx_index * FDCAN_TX_FIFO_EL_SIZE));
	}
	else if(can_num == FDCAN2_E){
		fifo = (u_fdcan_fifo_element *)(FDCAN2_TX_FIFO_START_ADDR + (tx_index * FDCAN_TX_FIFO_EL_SIZE));
	}
	else return 0;
	
	// clear RAM area
	for(uint32_t i = 0; i < FDCAN_TX_FIFO_EL_W_SIZE; i++){
		fifo->word_arr.word[i] = 0x00000000;
	}
	
	// Init message pointer
	u_fdcan_message_hdr *input_msg_hdr = (u_fdcan_message_hdr*)input;
	uint8_t *input_msg_data = &input[sizeof(fdcan_message_hdr)];
	
	// Init message length
	const fdcan_message_hdr *msg_hdr = &input_msg_hdr->msg_hdr;
	uint32_t total_msg_sz = FDCAN_FD_MSG_LENGTH(msg_hdr);
	
	// Set ID and XTD
	if(!FDCAN_IS_MSG_XTD(msg_hdr)){
		fifo->word_arr.word[0] = (input_msg_hdr->msg_hdr.id << 18);
	}
	else{
		fifo->word_arr.word[0] = (input_msg_hdr->msg_hdr.id);
		fifo->word_arr.word[0] |= 1UL << 30; // extended flag
	}
	
	// Set FDF
	// Set ESI
	// Set BRS
	if(FDCAN_IS_MSG_FDF(msg_hdr)){
		fifo->word_arr.word[1] |= (1UL << 21);
	}
	if(FDCAN_IS_MSG_ESI(msg_hdr)){
		fifo->word_arr.word[0] |= (1UL << 31);
	}
	if(FDCAN_IS_MSG_BRS(msg_hdr)){
		fifo->word_arr.word[1] |= (1UL << 20);
	}
	// Set DLC
	fifo->word_arr.word[1] |= (input_msg_hdr->msg_hdr.dlc << 16);
	memcpy(&fifo->data[8], input_msg_data, total_msg_sz);
	
	FDCAN_PERIPH(can_num)->TXBAR |= (1UL << tx_index);   // TXBAR: FDCAN Tx buffer add request register
	return total_msg_sz + sizeof(fdcan_message_hdr);
}


//=========================================================================================================
//=====================================    FDCAN interrupts    ============================================
/**
* brief  Interrupt processing. Invoked from FDCAN RX interrupt
* param  FD CAN num (1 or 2)
* param 
* param 
* retval 
*/
void fdcan_irq_procedure(uint8_t can_num){
	const uint32_t _fifo_new_msg_flag = (can_num == FDCAN1_E) ? FDCAN_IR_RF0N : FDCAN_IR_RF1N; //Rx FIFO 0 New message
	const uint8_t gtw_ouput_can_num = (can_num == FDCAN1_E) ? FDCAN2_E : FDCAN1_E;
	
	uint8_t rx_fifo_get_index;
	FDCAN_PERIPH(can_num)->IR |= _fifo_new_msg_flag; // clear flag 
	
	if(can_num == FDCAN1_E){
		rx_fifo_get_index = (uint8_t)((FDCAN_PERIPH(can_num)->RXF0S >> FDCAN_RXF0S_F0GI_Pos) & 0x3F); // F0GI[5:0]: Rx FIFO 0 get index Rx FIFO 0 read index pointer, range 0 to 63.
	}
	else{
		rx_fifo_get_index = (uint8_t)((FDCAN_PERIPH(can_num)->RXF1S >> FDCAN_RXF1S_F1GI_Pos) & 0x3F); // F0GI[5:0]: Rx FIFO 0 get index Rx FIFO 0 read index pointer, range 0 to 63.
	}
	
	uint16_t lock_sts = FDCAN_BUFFER_STS_FAIL;
	
		//============== Gateway Mode =====================
	if(CAN_GATEWAY_MODE == DEVICE_OPERATION_MODE_ON){
		
		if(fdcan_get_buf_freesize(FDCAN_TX_BUF_PTR(gtw_ouput_can_num)) >= FDCAN_BUFFER_MAX_ITEM_SZ){
			lock_sts = fdcan_buf_w_lock(FDCAN_TX_BUF_PTR(gtw_ouput_can_num));
		}
		
		if(lock_sts != FDCAN_BUFFER_STS_FAIL){
			fdcan_read_msg (can_num, FDCAN_TX_BUF_W_POS_PTR(gtw_ouput_can_num), rx_fifo_get_index);
			
			u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*) FDCAN_TX_BUF_W_POS_PTR(gtw_ouput_can_num);
			
			const uint16_t total_message_size = fdcan_calculate_total_msg_size(msg_ptr);
			//============ CAN scanner + Gateway Mode ===================
			if(CANSCANNER_MODE == DEVICE_OPERATION_MODE_ON){
				uint32_t *secs = (uint32_t*)get_main_tim_sec_ptr();
				fdcan_usb_transmit_msg(can_num, WATCHDOG_PROCEDURE_TIM, FDCAN_TX_BUF_W_POS_PTR(gtw_ouput_can_num), secs);
				} // CAN scanner + Gateway Mode
				
				fdcan_mov_w_idx(FDCAN_TX_BUF_PTR(gtw_ouput_can_num), total_message_size);
				fdcan_buf_w_unlock(FDCAN_TX_BUF_PTR(gtw_ouput_can_num));
			}  // lock_sts != FDCAN_BUFFER_STS_FAIL)
		} // Gateway Mode
		
		//============ CAN scanner Mode ===================
		else if((CANSCANNER_MODE == DEVICE_OPERATION_MODE_ON) && (CAN_GATEWAY_MODE != DEVICE_OPERATION_MODE_ON)){
			
			if(fdcan_get_buf_freesize(FDCAN_TX_BUF_PTR(can_num)) >= FDCAN_BUFFER_MAX_ITEM_SZ){
				lock_sts = fdcan_buf_w_lock(FDCAN_RX_BUF_PTR(can_num));
			}
			
			if(lock_sts != FDCAN_BUFFER_STS_FAIL){
				fdcan_read_msg (can_num, FDCAN_RX_BUF_W_POS_PTR(can_num), rx_fifo_get_index);
				
				
				uint32_t *secs = (uint32_t*)get_main_tim_sec_ptr();
				fdcan_usb_transmit_msg(can_num, WATCHDOG_PROCEDURE_TIM, FDCAN_RX_BUF_W_POS_PTR(can_num), secs);

				fdcan_buf_w_unlock(FDCAN_RX_BUF_PTR(can_num));
			}  // lock_sts != FDCAN_BUFFER_STS_FAIL)
		} // CAN scanner only
		
		if(can_num == FDCAN1_E){
			FDCAN1->RXF0A = rx_fifo_get_index;
		}
		else{
			FDCAN2->RXF1A = rx_fifo_get_index;
		}
}

//=========================================================================================================
//===================================== Buffered transmission =============================================


/**
* brief Transmit pending messages
* param  
* param  
* retval How many messages were sent
*/
uint32_t process_buffered_can_tx(){	
	uint16_t sent_bytes = 0;
	for (uint16_t i = 0; i < FDCANC_E; i++){  // пробежаться по интерфейсам

		if(fdcan_get_buf_freesize(FDCAN_TX_BUF_PTR(i)) != FDCAN_BUFFER_SIZE_TX){ // There is something in a buffer		
			if((FDCAN_PERIPH(i)->TXFQS & FDCAN_TXFQS_TFQF) != 0) continue; // FDCAN_TXFQS TFQF: Tx FIFO/queue Full
			// if(fdcan_get_buf_freesize (FDCAN_TX_BUF_PTR(i)) == FDCAN_BUFFER_SIZE_TX) continue; // buffer is empty
			
			//=========================== sieze a message ===========================
			volatile uint16_t lock_sts = fdcan_buf_r_lock(FDCAN_TX_BUF_PTR(i));
			if(lock_sts == FDCAN_BUFFER_STS_FAIL){
				continue;
			}
			u_fdcan_message_hdr* msg_ptr = (u_fdcan_message_hdr*) FDCAN_TX_BUF_R_POS_PTR(i);
			fdcan_message_hdr *msg_hdr = &msg_ptr->msg_hdr;
			uint16_t data_sz = (uint16_t)FDCAN_FD_MSG_LENGTH(msg_hdr);
			
			//============ Calibrator Mode ====================
			if(CALIBRATOR_MODE == DEVICE_OPERATION_MODE_ON){
				uint32_t id = msg_ptr->msg_hdr.id;
				// legacy std can procedure
				const uint32_t vcl_strp_stt = vehicle_startup_settings();
				if((vcl_strp_stt & STARTUP_SETTINGS_FDCAN) != STARTUP_SETTINGS_FDCAN){
					volatile uint8_t fdf_sts = FDCAN_IS_MSG_FDF(msg_hdr);
					if(fdf_sts == FDCAN_FLAG_RST){
						can_message *theLegacyMsg = legacy_can_message();
						legacy_fdcan_to_can(theLegacyMsg, FDCAN_TX_BUF_R_POS_PTR(i));
						can_override_calibrate(theLegacyMsg);
						legacy_can_to_fdcan(theLegacyMsg, FDCAN_TX_BUF_R_POS_PTR(i));
					}
				}
				// fdcan procedure
				else{
					uint8_t *data_ptr = (uint8_t *)FDCAN_TX_BUF_R_POS_PTR(i);
					fdcan_can_override_calibrate(data_ptr);
				}	
				//process_calibrator_procedure(newMessage);		
			} // Calibrator Mode

			
			
			//============ Override Mode ====================
			if(CAN_OVERRIDE_MODE == DEVICE_OPERATION_MODE_ON){	
				uint32_t id = msg_ptr->msg_hdr.id;
				if(filter_condition_match(i, id) != 0){
					fdcan_apply_filter(i, data_sz);
				}// filter_condition_match
			} // Override Mode
			
			
			
		sent_bytes = fdcan_send_msg (i, FDCAN_TX_BUF_R_POS_PTR(i));
		fdcan_mov_r_idx(FDCAN_TX_BUF_PTR(i), sent_bytes);

			
		fdcan_buf_r_unlock(FDCAN_TX_BUF_PTR(i));
		} // There is something in a buffer
		
	}	// пробежаться по интерфейсам
	
	return sent_bytes;
}


//=========================================================================================================
//=======================================   Miscelaneous   ================================================
/**
* brief Calculate total (header + data) message size
* param header pointer
* param  
* retval How many messages were sent
*/


uint16_t fdcan_calculate_total_msg_size(u_fdcan_message_hdr* _hdr){
	const fdcan_message_hdr *msg_hdr = &_hdr->msg_hdr;
	uint16_t total_msg_sz = (uint16_t)FDCAN_MSG_LENGTH(msg_hdr);
	
	return (uint16_t)(total_msg_sz + sizeof(fdcan_message_hdr));
}

uint32_t fdcan_watchdog(void){
	for(uint8_t k = FDCAN1_E; k < FDCANC_E; k++){
		if((FDCAN_PERIPH(k)->PSR & FDCAN_PSR_EP) == FDCAN_PSR_EP){
			FDCAN_PERIPH(k)->IR = FDCAN_IR_EP;
			
			FDCAN_PERIPH(k)->IR = FDCAN_IR_PED;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_PEA;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_EW;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_ELO;
			return FDCAN_PSR_EP;
		}
		if((FDCAN_PERIPH(k)->PSR & FDCAN_PSR_BO) == FDCAN_PSR_BO){
			FDCAN_PERIPH(k)->IR = FDCAN_IR_BO;
			
			FDCAN_PERIPH(k)->IR = FDCAN_IR_PED;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_PEA;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_EW;
			FDCAN_PERIPH(k)->IR = FDCAN_IR_ELO;
			return FDCAN_PSR_BO;
		}
	}
	return 0;
}

#endif // SUPPORT_FDCAN

