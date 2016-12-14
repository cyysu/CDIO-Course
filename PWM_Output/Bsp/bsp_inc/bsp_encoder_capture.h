#ifndef __BSP_ENCODER_CAPTURE_H
#define __BSP_ENCODER_CAPTURE_H

#include "stm32f10x.h"

#define ENCODER_TIM_PERIOD  0xFFFF//(0x7FFF) 

extern void TIM2_Encoder_Init(void);

#endif
