#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"
//定义TIM1-5,TIM8的通道号
typedef enum
{
    TIM_CH1 = 1,
    TIM_CH2,
    TIM_CH3,
    TIM_CH4,
} TIM_CHn_e;

extern void TIM3_PWM_Init(void);
extern void motor_go(short motor_pwm_out);
extern void BangBangGo(short x);
extern void BangBangBack(short y);
extern void motor_stop(void);
extern void velocity_measurement_printf(void);
#endif /* __PWM_OUTPUT_H */

