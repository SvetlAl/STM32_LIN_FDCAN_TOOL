//*****************************************************************
// DMA features packed into the functions
// This library is borrowed from easyelectronics.ws lessons
// 
// 
//*****************************************************************

#include "10x_dma.h"

#ifdef STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif


/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA1_Channel2_IT_Mask    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA1_Channel3_IT_Mask    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA1_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA1_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))
#define DMA1_Channel6_IT_Mask    ((uint32_t)(DMA_ISR_GIF6 | DMA_ISR_TCIF6 | DMA_ISR_HTIF6 | DMA_ISR_TEIF6))
#define DMA1_Channel7_IT_Mask    ((uint32_t)(DMA_ISR_GIF7 | DMA_ISR_TCIF7 | DMA_ISR_HTIF7 | DMA_ISR_TEIF7))

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_Channel1_IT_Mask    ((uint32_t)(DMA_ISR_GIF1 | DMA_ISR_TCIF1 | DMA_ISR_HTIF1 | DMA_ISR_TEIF1))
#define DMA2_Channel2_IT_Mask    ((uint32_t)(DMA_ISR_GIF2 | DMA_ISR_TCIF2 | DMA_ISR_HTIF2 | DMA_ISR_TEIF2))
#define DMA2_Channel3_IT_Mask    ((uint32_t)(DMA_ISR_GIF3 | DMA_ISR_TCIF3 | DMA_ISR_HTIF3 | DMA_ISR_TEIF3))
#define DMA2_Channel4_IT_Mask    ((uint32_t)(DMA_ISR_GIF4 | DMA_ISR_TCIF4 | DMA_ISR_HTIF4 | DMA_ISR_TEIF4))
#define DMA2_Channel5_IT_Mask    ((uint32_t)(DMA_ISR_GIF5 | DMA_ISR_TCIF5 | DMA_ISR_HTIF5 | DMA_ISR_TEIF5))



#define CCR_CLEAR_Mask           ((uint32_t)0xFFFF8001)



void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Periph, uint32_t Mem, uint16_t Size, uint16_t Conf){
	uint32_t tmp = 0;

	tmp = Channel->CCR;
	tmp &= ~CCR_CLEAR_Mask;
	tmp |= Conf;

	Channel->CNDTR = Size;
	Channel->CPAR = Periph;
	Channel->CMAR = Mem;
	Channel->CCR = tmp;
}



uint32_t DMA_GetCurrentDataCounter(DMA_Channel_TypeDef* Channel){
	return Channel->CNDTR;
}
#ifdef MDK_ARM_ENV
void DMA_Enable(DMA_Channel_TypeDef* Channel){
	Channel->CCR |= DMA_CCR1_EN;
}

void DMA_Disable(DMA_Channel_TypeDef* Channel){
	Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
}
#else
void DMA_Enable(DMA_Channel_TypeDef* Channel){
	Channel->CCR |= DMA_CCR_EN;
}

void DMA_Disable(DMA_Channel_TypeDef* Channel){
	Channel->CCR &= (uint16_t)(~DMA_CCR_EN);
}
#endif

void DMA_DeInit(DMA_Channel_TypeDef* Channel){
#ifdef MDK_ARM_ENV
	Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
#else
	Channel->CCR &= (uint16_t)(~DMA_CCR_EN);
#endif

	Channel->CCR = 0;
	Channel->CNDTR = 0;
	Channel->CPAR = 0;
	Channel->CMAR = 0;
	
	if(Channel == DMA1_Channel1){
		/* Reset interrupt pending bits for DMA1 Channel1 */
		DMA1->IFCR |= DMA1_Channel1_IT_Mask;
	}
	else if (Channel == DMA1_Channel2){
		/* Reset interrupt pending bits for DMA1 Channel2 */
		DMA1->IFCR |= DMA1_Channel2_IT_Mask;
	}
	else if (Channel == DMA1_Channel3){
		/* Reset interrupt pending bits for DMA1 Channel3 */
		DMA1->IFCR |= DMA1_Channel3_IT_Mask;
	}
	else if (Channel == DMA1_Channel4){
		/* Reset interrupt pending bits for DMA1 Channel4 */
		DMA1->IFCR |= DMA1_Channel4_IT_Mask;
	}
	else if (Channel == DMA1_Channel5){
		/* Reset interrupt pending bits for DMA1 Channel5 */
		DMA1->IFCR |= DMA1_Channel5_IT_Mask;
	}
	else if (Channel == DMA1_Channel6){
		/* Reset interrupt pending bits for DMA1 Channel6 */
		DMA1->IFCR |= DMA1_Channel6_IT_Mask;
	}
	else if (Channel == DMA1_Channel7){
		/* Reset interrupt pending bits for DMA1 Channel7 */
		DMA1->IFCR |= DMA1_Channel7_IT_Mask;
	}
	else if (Channel == DMA2_Channel1){
		/* Reset interrupt pending bits for DMA2 Channel1 */
		DMA2->IFCR |= DMA2_Channel1_IT_Mask;
	}
	else if (Channel == DMA2_Channel2){
		/* Reset interrupt pending bits for DMA2 Channel2 */
		DMA2->IFCR |= DMA2_Channel2_IT_Mask;
	}
	else if (Channel == DMA2_Channel3){
		/* Reset interrupt pending bits for DMA2 Channel3 */
		DMA2->IFCR |= DMA2_Channel3_IT_Mask;
	}
	else if (Channel == DMA2_Channel4){
		/* Reset interrupt pending bits for DMA2 Channel4 */
		DMA2->IFCR |= DMA2_Channel4_IT_Mask;
	}
	else{
		if (Channel == DMA2_Channel5){
			/* Reset interrupt pending bits for DMA2 Channel5 */
			DMA2->IFCR |= DMA2_Channel5_IT_Mask;
		}
	}
}

#endif












