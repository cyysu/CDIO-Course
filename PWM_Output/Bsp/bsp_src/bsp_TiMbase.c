#include "bsp_TiMbase.h" 

void TIM6_1msIRQ_Config(uint8_t count)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    //TIM_DeInit(TIM6);
    //中断周期为 = 1/(72MHZ/72) * 1000 = 1ms
    TIM_TimeBaseStructure.TIM_Period=1000*count;
    TIM_TimeBaseStructure.TIM_Prescaler= 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM6, ENABLE);																		
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , DISABLE);/*先关闭等待使用*/
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);    
}

void TIM7_1msIRQ_Config(uint8_t count)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    //TIM_DeInit(TIM7);
    //中断周期为 = 1/(72MHZ/72) * 1000 = 1ms
    TIM_TimeBaseStructure.TIM_Period=1000*count;
    TIM_TimeBaseStructure.TIM_Prescaler= 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM7, ENABLE);																		
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , DISABLE);/*先关闭等待使用*/
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);    
}
/*********************************************END OF FILE**********************/
