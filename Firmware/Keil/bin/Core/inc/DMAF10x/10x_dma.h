//*****************************************************************
// DMA features packed into the functions
// This library is borrowed from easyelectronics.ws lessons
// 
// 
//*****************************************************************
#ifndef DMA_H_INCLUDED
#define DMA_H_INCLUDED

#include "device_model.h"
#ifdef BOARD_MK_STM32F205
#include "stm32f205xx.h"
#endif
#ifdef BOARD_MK_STM32F105
#ifdef MDK_ARM_ENV
#include "stm32f10x.h"
#else
#include "stm32f1xx.h"
#endif


#define DMAEnable ((uint16_t)(1<<0))
#define DMADisable ((uint16_t)0)

#define TransCompl_Int_Enable ((uint16_t)(1<<1))
#define TransCompl_Int_Disable ((uint16_t)0)

#define HalfCompl_Int_Enable ((uint16_t)1<<2)
#define HalfCompl_Int_Disable ((uint16_t)0)

#define TransError_Int_Enable ((uint16_t)(1<<3))
#define TransError_Int_Disable ((uint16_t)0)

#define ReadMemory ((uint16_t)(1<<4))
#define ReadPerif ((uint16_t)0)

#define CircularMode_Enable ((uint16_t)1<<5)
#define CircularMode_Disable ((uint16_t)0)


#define PeripheralInc_Enable ((uint16_t)(1<<6))
#define PeripheralInc_Disable ((uint16_t)0)

#define MemoryInc_Enable ((uint16_t)(1<<7))
#define MemoryInc_Disable ((uint16_t)0)

#define PDataSize_B ((uint16_t)0)
#define PDataSize_W ((uint16_t)0x0100)
#define PDataSize_DW ((uint16_t)0x0200)

#define MDataSize_B ((uint16_t)0)
#define MDataSize_W ((uint16_t)0x0400)
#define MDataSize_DW ((uint16_t)0x0800)

#define DMA_Priority_Low ((uint16_t)0)
#define DMA_Priority_Med ((uint16_t)(1<<12))
#define DMA_Priority_Hi  ((uint16_t)(2<<12))
#define DMA_Priority_VHi ((uint16_t)(3<<12))

#define M2M_Enable (1<<14)
#define M2M_Disable 0



void DMA_Init(DMA_Channel_TypeDef* Channel, uint32_t Perif, uint32_t Mem, uint16_t Size, uint16_t Conf);
void DMA_Enable(DMA_Channel_TypeDef* Channel);
void DMA_Disable(DMA_Channel_TypeDef* Channel);

uint32_t DMA_GetCurrentDataCounter(DMA_Channel_TypeDef* Channel);
void DMA_DeInit(DMA_Channel_TypeDef* Channel);

#endif

#endif /* DMA_H_INCLUDED */
