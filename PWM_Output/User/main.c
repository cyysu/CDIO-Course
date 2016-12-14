#include "include.h"
/*
 * PROTOTYPES
 */
static void initializeHardware(void);
static void main_delay(__IO uint32_t numLoops);
/*
 * FUNCTIONS
 */
 
//œ‘ æ ±º‰
int main(void)
{
	initializeHardware();
	main_delay(0x0ffffe);
	DisableInterrupts
	SetIrqAndPriority();
	EnableInterrupts
	printf("========main========\n");
	
	for(;;) 
	{
			InfoDisplay((int32_t)Motor.setpulse,(int32_t)Motor.backpulse);
			MatrixKeyDealPro();		//Matrix keyboard
			IndependentKeyDealPro();//Independent keyboard
	}
}

static void initializeHardware(void)
{
	bsp_InitTimer();
	LCD_Init();
	LED_GPIO_Config();
	Key_GPIO_Config();
	MatrixKeyboard_Init();
	USART1_Config(115200);
	TIM3_PWM_Init();/*10*1000Hz*/
	TIM2_Encoder_Init();
}

static void main_delay(__IO uint32_t numLoops)
{
	for(; numLoops != 0; numLoops--);
}
/*********************************************END OF FILE**********************/
