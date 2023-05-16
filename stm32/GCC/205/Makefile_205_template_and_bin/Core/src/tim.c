/****************************************************************
* 
* Timer functions
*
* Alex Svetlichnyy 2021 svetlal@outlook.com
*
*****************************************************************/

#include "tim.h"

/**
* brief  
* param  TIMx_PSC 
* param  TIMx_ARR, timer number (TIM1, TIM2, TIM3, TIM4)
* retval 0 - OK  1 - Err
Update Event is handled in TIM1_UP_TIM10_IRQHandler

*/

void startBasicTimer(uint16_t prescaler, uint16_t reloadValue, TIM_TypeDef * TIM_n){
		TIM_n->PSC = prescaler;
		TIM_n->ARR = reloadValue;
    TIM_n->CNT = 0;		
		TIM_n->CR1 |= TIM_CR1_ARPE; // register is buffered. Updated with UEV event   **Not Important
		TIM_n->CR1 |= TIM_CR1_URS;  // Only counter overflow/underflow generates an update interrupt **Not Important
		TIM_n->CR1 &= ~TIM_CR1_UDIS;// UEV enabled. The Update (UEV) event is enabled
		TIM_n->CR2 |= TIM_CR2_MMS_1; //MMS = 010   Trigger output - update
		
		TIM_n->EGR |=TIM_EGR_UG;
		
		TIM_n->DIER |= TIM_DIER_UIE; // Enable Interrupts
		
		TIM_n->CR1 |= TIM_CR1_CEN; // Start
}

void stopBasicTimer(TIM_TypeDef * TIM_n){	
	TIM_n->CR1 &= ~TIM_CR1_CEN; // Start
	TIM_n->DIER &= ~TIM_DIER_UIE;
}

