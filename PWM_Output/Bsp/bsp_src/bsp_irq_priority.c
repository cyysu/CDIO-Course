#include "bsp_irq_priority.h"

static void TIM6_NVIC_Configuration(void);//编码器脉冲捕获
static void TIM7_NVIC_Configuration(void);//用于按键扫描
void SetIrqAndPriority(void)
{
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	//内核异常
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//外设中断设置
	TIM6_NVIC_Configuration();//测速
	TIM7_NVIC_Configuration();//按键扫描
}

static void TIM6_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
 													
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	TIM6_1msIRQ_Config(5);
}
static void TIM7_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
 													
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	TIM7_1msIRQ_Config(3);
}


