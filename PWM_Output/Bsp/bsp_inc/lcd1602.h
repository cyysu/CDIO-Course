#ifndef __LCD1602_H
#define __LCD1602_H
#include "stm32f10x.h"

extern void LCD_Init(void);
extern void Lcd_Write_Command(unsigned char x,char Busy) ;
extern void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *string);//Ïò1602Ð´Ò»¸ö×Ö·û´® 
extern unsigned char *tr_2(unsigned int outData2);
extern unsigned char *tr_3(unsigned int outData3);
extern unsigned char *tr_4(unsigned int outData4);
extern void InfoDisplay(int32_t a,int32_t b);
#endif
