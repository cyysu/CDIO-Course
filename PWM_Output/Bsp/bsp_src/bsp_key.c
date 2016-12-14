#include "bsp_key.h" 
#include "bsp_led.h"

KEY_Flags gKey_Flags;
static void KeyVarInit(void)
{
	gKey_Flags.KeyValue 	= KEY_VALUE_NULL;
	gKey_Flags.LastKeyValue	= KEY_VALUE_NULL;
	gKey_Flags.KeyState 	= KEY_Sate_NULL;
	gKey_Flags.KeyCnt		= KEY_SCAN_NULL;
	gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_NULL;
	gKey_Flags.KeyOverTime	= 0x00;
	gKey_Flags.KeyDebugData	= 0x00;
}

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY0_PIN|KEY1_PIN|KEY2_PIN|KEY3_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);  
	
	KeyVarInit();  /*初始化按键结构体*/
}

static uint16_t KeyValueScan(void)
{
	uint16_t RetValue = KEY_VALUE_NULL;
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY0_PIN) == KEY_ON){
		RetValue |= KEY_VALUE_ONE;
	}
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_PIN) == KEY_ON){
		RetValue |= KEY_VALUE_TWO;
	}
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_PIN) == KEY_ON){
		RetValue |= KEY_VALUE_THREE;
	}
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY3_PIN) == KEY_ON){
		RetValue |= KEY_VALUE_FOUR;
	}
	return (RetValue);
}

void KeyBoardScan(void)
{
	uint16_t GetValueTemp;
	GetValueTemp = KeyValueScan();

	if(GetValueTemp==gKey_Flags.LastKeyValue){
		if(GetValueTemp!=KEY_VALUE_NULL){
			gKey_Flags.KeyCnt++;
			if(gKey_Flags.KeyCnt >= KEY_SCAN_LONG_DOWN_PRESS_CNT){
				gKey_Flags.KeyCnt		= KEY_SCAN_LONG_DOWN_CNT;
				gKey_Flags.KeyValue		= GetValueTemp;
				gKey_Flags.KeyState		= KEY_State_LongDown_Press;
				gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_FLAG;
			}
			else if(gKey_Flags.KeyCnt == KEY_SCAN_LONG_DOWN_CNT){//长按
				gKey_Flags.KeyValue		= GetValueTemp;
				gKey_Flags.KeyState		= KEY_State_LongDown_Press_Start;
				gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_FLAG;
			}
			else if(gKey_Flags.KeyCnt == KEY_SCAN_DOWN_CNT){//一次按下(15ms消抖)
				gKey_Flags.KeyValue		= GetValueTemp;
				gKey_Flags.KeyState		= KEY_State_ShortDown_Press_Start;
				gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_FLAG;
			}
		}
	}
	else{
		if(GetValueTemp==KEY_VALUE_NULL){
			if(gKey_Flags.KeyCnt >= KEY_SCAN_LONG_DOWN_CNT){
				gKey_Flags.KeyValue		= gKey_Flags.LastKeyValue;
				gKey_Flags.KeyState		= KEY_State_LongDown_Release;
				gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_FLAG;
			}
			else if(gKey_Flags.KeyCnt >= KEY_SCAN_DOWN_CNT){
				gKey_Flags.KeyValue		= gKey_Flags.LastKeyValue;
				gKey_Flags.KeyState		= KEY_State_ShortDown_Release;
				gKey_Flags.KeyDealFlag	= KEY_VALUE_NEW_FLAG;
			}
		}
		gKey_Flags.KeyCnt = KEY_SCAN_NULL;
	}
	gKey_Flags.LastKeyValue = GetValueTemp;
}

void IndependentKeyDealPro(void)
{
	if(gKey_Flags.KeyDealFlag == KEY_VALUE_NEW_FLAG){
		gKey_Flags.KeyDealFlag = KEY_VALUE_NEW_NULL;
		switch(gKey_Flags.KeyValue)
		{
			case KEY_VALUE_ONE:
				switch(gKey_Flags.KeyState)
				{
					case KEY_State_ShortDown_Press_Start:
						break;
					case KEY_State_ShortDown_Release:
						led_turn(LED0);
						break;
					case KEY_State_LongDown_Press_Start:
						break;
					case KEY_State_LongDown_Press:
						break;
					case KEY_State_LongDown_Release:
						break;
					default:
						break;
				}
				break;
			case KEY_VALUE_TWO:
				switch(gKey_Flags.KeyState)
				{
					case KEY_State_ShortDown_Press_Start:
						break;
					case KEY_State_ShortDown_Release:
						led_turn(LED1);
						break;
					case KEY_State_LongDown_Press_Start:
						break;
					case KEY_State_LongDown_Press:
						break;
					case KEY_State_LongDown_Release:
						break;
					default:
						break;
				}
				break;
			case KEY_VALUE_THREE:
				switch(gKey_Flags.KeyState)
				{
					case KEY_State_ShortDown_Press_Start:
						break;
					case KEY_State_ShortDown_Release:
						//led_turn(LED2);
						break;
					case KEY_State_LongDown_Press_Start:
						break;
					case KEY_State_LongDown_Press:
						break;
					case KEY_State_LongDown_Release:
						break;
					default:
						break;
				}
				break;
			case KEY_VALUE_FOUR:
				switch(gKey_Flags.KeyState)
				{
					case KEY_State_ShortDown_Press_Start:
						break;
					case KEY_State_ShortDown_Release:
						//led_turn(LED3);
						break;
					case KEY_State_LongDown_Press_Start:
						break;
					case KEY_State_LongDown_Press:
						break;
					case KEY_State_LongDown_Release:
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}
/*********************************************END OF FILE**********************/
