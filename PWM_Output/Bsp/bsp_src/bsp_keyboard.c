#include "bsp_keyboard.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "myPidController.h"
#include "lcd1602.h"

#if 1
uint8_t MatrixKey_value = 0;
void MatrixKeyboard_Init(void) 
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

    GPIO_Init(GPIOE,&GPIO_InitStructure);		
}

static uint8_t MatrixKey_scan(void) 
{
	uint8_t KeyVal;	
	GPIO_Write(GPIOE,(GPIOE->ODR & 0xf0ff | 0x0f00)); 
	if((GPIOE->IDR & 0xf000)==0x0000) 
		return 0;
	else
	{	
	    Delay_ms(5);    
	    if((GPIOE->IDR & 0xf000)==0x0000)
	    return 0;
	}

	GPIO_Write(GPIOE,(GPIOE->ODR & 0xf0ff | 0x0100));
	switch(GPIOE->IDR & 0xf000)
	{
		case 0x1000: KeyVal='D';break;
		case 0x2000: KeyVal='C';break;
		case 0x4000: KeyVal='B';break;
		case 0x8000: KeyVal='A';break;
	}	   
	GPIO_Write(GPIOE,(GPIOE->ODR & 0xf0ff | 0x0200));
	switch(GPIOE->IDR & 0xf000)		     
	{
		case 0x1000: KeyVal='#';break;
		case 0x2000: KeyVal='9';break;
		case 0x4000: KeyVal='6';break;
		case 0x8000: KeyVal='3';break;
	}

	GPIO_Write(GPIOE,(GPIOE->ODR & 0xf0ff | 0x0400));	
	switch(GPIOE->IDR & 0xf000)		     
	{
		case 0x1000: KeyVal='0';break;
		case 0x2000: KeyVal='8';break;
		case 0x4000: KeyVal='5';break;
		case 0x8000: KeyVal='2';break;
	}
	GPIO_Write(GPIOE,(GPIOE->ODR & 0xf0ff | 0x0800));	
	switch(GPIOE->IDR & 0xf000)		     
	{
		case 0x1000: KeyVal='*';break;
		case 0x2000: KeyVal='7';break;
		case 0x4000: KeyVal='4';break;
		case 0x8000: KeyVal='1';break;
	}									  
	return KeyVal;		
}

void MatrixKeyDealPro(void)
{
	  static unsigned int set_Speed = 0;
		if(MatrixKey_scan() >= '0' && MatrixKey_scan() <= '9')
		{
				set_Speed = set_Speed * 10 + (MatrixKey_scan() - '0');
				if(set_Speed >= 600)
						set_Speed = 600;
				InfoDisplay((int32_t)set_Speed,(int32_t)Motor.backpulse);
				
		}
		else
		{
			 switch(MatrixKey_scan())
			 {
					 case 'A':
							printf("set_Speed = %d",set_Speed);
							Motor.setpulse = set_Speed ;
							set_Speed = 0;
							break;
					 
					 case 'B':
							printf("按下了B键");
							break;
					 
					 case 'C':
							printf("按下了C键");
							break;
					 
					 case 'D':
							printf("按下了D键");
							break;
						
					 case '#':
							printf("按下了#键");
							break;
					 
					 case '*':
							printf("按下了*键");
							break;
			 }
		}
}

#elif 0
void MatrixKey_Clock_Enable(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIOE->CRH &= 0X00000000;
    GPIOE->CRH |= 0X33333333;//配置高8位推挽输出
    //初值:低4位为低,次低4位为高
    GPIOE->ODR &= 0X00FF;
    GPIOE->ODR |= 0XF0FF;
	
    GPIOE->CRH &= 0X0000FFFF;//清空12-15位
    GPIOE->CRH |= 0X88880000;//上拉输入
}

uint8_t scan_MatrixKey(void)
{
    uint8_t column, row;
    uint8_t tmp;
	uint8_t MatrixKey_value = 20;//初始值不能为0~15 
	static uint8_t key_count = 0;

    tmp = KEYPORT;
    if (tmp != 0XF0)//有键按下
    {   
        //防止长按时,持续自增导致变量溢出
        if (key_count <= 2)
        {
            key_count++;
        }
    }
    //若产生抖动按键被抬起则计数清0 
    else
    {
        key_count = 0;
    }
    //若按键连续2次扫描均处于按下状态,则认为按键确实被按下了
    if (key_count == 2)
    {          
        column = tmp & 0XF000;//获取列坐标 
        
        GPIOE->CRH &= 0X00000000;
        GPIOE->CRH |= 0X33333333;
		
        GPIOE->ODR &= 0X00FF;
        GPIOE->ODR |= 0X0F00;//低4位为高,次低4位为低

		GPIOE->CRH &= 0X0000FFFF;
		GPIOE->CRH |= 0X88880000;
								
        row = KEYPORT & 0X0F00;//获取行坐标                                       
        switch (column | row)  //整合坐标
        {   
            case 0XEE: MatrixKey_value = '1'; break;
            case 0XDE: MatrixKey_value = '2'; break;
            case 0XBE: MatrixKey_value = '3'; break;                
            case 0X7E: MatrixKey_value = 'A'; break;                                              
            case 0XED: MatrixKey_value = '4'; break;
            case 0XDD: MatrixKey_value = '5'; break;
            case 0XBD: MatrixKey_value = '6'; break;
            case 0X7D: MatrixKey_value = 'B'; break;                                  
            case 0XEB: MatrixKey_value = '7'; break;
            case 0XDB: MatrixKey_value = '8'; break;
            case 0XBB: MatrixKey_value = '9'; break;
            case 0X7B: MatrixKey_value = 'C'; break;                                    
            case 0XE7: MatrixKey_value = '*'; break;
            case 0XD7: MatrixKey_value = '0'; break;
            case 0XB7: MatrixKey_value = '#'; break;
            case 0X77: MatrixKey_value = 'D'; break;
            default:   break;     
        }
			printf("键值：%c\r\n",MatrixKey_value);
    } 
    //若没有按键被按下(已松手)则扫描次数清0
    if ((KEYPORT & 0XFF00) == 0xF000)
    {
        key_count = 0;  
    }
    return MatrixKey_value;
}
#endif

