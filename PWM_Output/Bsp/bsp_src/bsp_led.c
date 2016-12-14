#include "bsp_led.h"   

 /**
  * @brief  LED_Init
  * @param  none
  * @retval none
  */
void LED_GPIO_Config(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
														   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);	
																	  
	/* πÿ±’À˘”–ledµ∆	*/
	GPIO_SetBits(LED_GPIO, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
}

void led_set(LED_e ledn, LED_status status)
{
	if(ledn < LED_MAX)
    {
		if(0 == status)
		{
			if(0 == ledn)
				digitalLo(LED_GPIO,GPIO_Pin_6)
			else if(1 == ledn)
				digitalLo(LED_GPIO,GPIO_Pin_7)
			else if(2 == ledn)
				digitalLo(LED_GPIO,GPIO_Pin_8)
			else
				digitalLo(LED_GPIO,GPIO_Pin_9)
		}
		else
		{
			if(0 == ledn)
				digitalHi(LED_GPIO,GPIO_Pin_6)
			else if(1 == ledn)
				digitalHi(LED_GPIO,GPIO_Pin_7)
			else if(2 == ledn)
				digitalHi(LED_GPIO,GPIO_Pin_8)
			else
				digitalHi(LED_GPIO,GPIO_Pin_9)
		}
			
    }
    else
    {
        ledn = LED_MAX;
		if(0 == status)
		{
			digitalLo(LED_GPIO,GPIO_Pin_6)
			digitalLo(LED_GPIO,GPIO_Pin_7)
			digitalLo(LED_GPIO,GPIO_Pin_8)
			digitalLo(LED_GPIO,GPIO_Pin_9)
		}
		else
		{
			digitalHi(LED_GPIO,GPIO_Pin_6)
			digitalHi(LED_GPIO,GPIO_Pin_7)
			digitalHi(LED_GPIO,GPIO_Pin_8)
			digitalHi(LED_GPIO,GPIO_Pin_9)
		}
    }
}

void led_turn(LED_e ledn)
{
	if(ledn < LED_MAX)
	{
		if(0 == ledn)
			digitalToggle(LED_GPIO,GPIO_Pin_6)
		else if(1 == ledn)
		    digitalToggle(LED_GPIO,GPIO_Pin_7)
		else if(2 == ledn)
		    digitalToggle(LED_GPIO,GPIO_Pin_8)
		else if(3 == ledn)
		    digitalToggle(LED_GPIO,GPIO_Pin_9)
	}
	else
	{
		ledn = LED_MAX;
		digitalToggle(LED_GPIO,GPIO_Pin_6);
		digitalToggle(LED_GPIO,GPIO_Pin_7);
		digitalToggle(LED_GPIO,GPIO_Pin_8);
		digitalToggle(LED_GPIO,GPIO_Pin_9);
	}
}
/*********************************************END OF FILE**********************/

