#include "bsp_SysTick.h"

static __IO u32 TimingDelay;
 
void bsp_InitTimer(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us
	 * SystemFrequency / 1000000 1us
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 1000000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);//SysTick_Config() return 1，即配置错误；return 0正确
	}
	/*关闭滴答定时器*/  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	/*使能滴答定时器*/ 
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
