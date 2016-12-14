#include "bsp_encoder_capture.h"

void TIM2_Encoder_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_ICInitTypeDef TIM_ICInitStructure; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;/*PA0 1设为fukong输入*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*计数器计数模式设定*/
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD-1; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;	         //预分频不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	 //外部时钟不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, 
							   TIM_ICPolarity_Rising, 
							   TIM_ICPolarity_Rising);//使用编码器模式3

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;			//IC滤波器设置
  	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
//	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM_SetCounter(TIM2,0);
	TIM_Cmd(TIM2, ENABLE); 
}
