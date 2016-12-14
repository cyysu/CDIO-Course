#ifndef __BSP_KEY_H
#define	__SBP_KEY_H

#include "stm32f10x.h"

/*******************************************************/
#define KEY0_PIN                  GPIO_Pin_0                   
#define KEY1_PIN                  GPIO_Pin_1                     
#define KEY2_PIN                  GPIO_Pin_2 
#define KEY3_PIN                  GPIO_Pin_3 
#define KEY_GPIO_PORT             GPIOE
#define KEY_GPIO_CLK              RCC_APB2Periph_GPIOE               
/*******************************************************/

#define KEY_ON	0
#define KEY_OFF	1

#define	KEY_VALUE_NULL				0x0000
#define	KEY_VALUE_ONE				0x0001
#define	KEY_VALUE_TWO				0x0002
#define	KEY_VALUE_THREE				0x0003
#define	KEY_VALUE_FOUR				0x0004


#define	KEY_VALUE_NEW_NULL				0
#define	KEY_VALUE_NEW_FLAG				1


#define	KEY_SCAN_NULL					0
#define	KEY_SCAN_DOWN_CNT				5
#define	KEY_SCAN_LONG_DOWN_CNT			500
#define	KEY_SCAN_LONG_DOWN_REPEAT_PRESS	100
#define	KEY_SCAN_LONG_DOWN_PRESS_CNT	(KEY_SCAN_LONG_DOWN_CNT + KEY_SCAN_LONG_DOWN_REPEAT_PRESS)

typedef enum {
	KEY_Sate_NULL = 0,
	KEY_State_ShortDown_Press_Start,
	KEY_State_ShortDown_Release,
	KEY_State_LongDown_Press_Start, 
	KEY_State_LongDown_Press,
	KEY_State_LongDown_Release,
	KEY_State_Double_Click
}Key_State_e;


typedef struct
{
	uint16_t    KeyValue;
	uint16_t    LastKeyValue;
	uint16_t    KeyCnt;
	uint16_t	KeyOverTime;
	uint16_t	KeyDealFlag;
	uint16_t	KeyDebugData;
	Key_State_e	KeyState;
}KEY_Flags;

extern void Key_GPIO_Config(void);
extern void KeyBoardScan(void);
extern void IndependentKeyDealPro(void);

#endif /* __LED_H */
