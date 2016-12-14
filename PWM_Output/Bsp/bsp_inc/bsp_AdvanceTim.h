#ifndef __BSP_ADVANCETIME_H
#define __BSP_ADVANCETIME_H

#include "stm32f10x.h"

/************高级定时器TIM参数定义，只限TIM1和TIM8************/
//高级控制定时器TIM1
#define            ADVANCE_TIM                   TIM1
#define            ADVANCE_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            ADVANCE_TIM_CLK               RCC_APB2Periph_TIM1
#define            ADVANCE_TIM_IRQ               TIM1_UP_IRQn
#define            ADVANCE_TIM_IRQHandler        TIM1_UP_IRQHandler
// TIM1 输出比较通道1
#define            ADVANCE_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            ADVANCE_TIM_CH1_PORT          GPIOA
#define            ADVANCE_TIM_CH1_PIN           GPIO_Pin_8
// TIM1 输出比较通道1的互补通道
#define            ADVANCE_TIM_CH1N_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            ADVANCE_TIM_CH1N_PORT          GPIOB
#define            ADVANCE_TIM_CH1N_PIN           GPIO_Pin_13

/**************************函数声明********************************/

void ADVANCE_TIM_Init(void);

#endif	/* __BSP_ADVANCETIME_H */


