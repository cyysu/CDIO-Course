#ifndef __BSP_LED_H
#define	__BSP_LED_H

#include "stm32f10x.h"

typedef enum
{
	LED0,
	LED1,
	LED2,
	LED3,
	LED_MAX,
}LED_e;

typedef enum LED_status
{
  LED_ON  =   0,            //灯亮(对应低电平)
  LED_OFF =   1             //灯暗(对应高电平)
}LED_status; 

/* 直接操作寄存器的方法控制IO */
#define LED_GPIO                GPIOB
#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i; }			//输出低电平
#define digitalToggle(p,i)		{p->ODR^=i;}			//输出反转状态


extern void LED_GPIO_Config(void);
extern void led_set(LED_e ledn, LED_status status);
extern void led_turn(LED_e ledn);
#endif /* __LED_H */
