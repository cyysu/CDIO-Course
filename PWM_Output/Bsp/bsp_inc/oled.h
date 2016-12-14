#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "sys.h"



#define OLED_ADDRESS	0x78  //DC 对应SA0       R/W非   默认写

void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite);
void OLED_WriteCmd(unsigned char I2C_Command);//写命令
void OLED_WriteDat(unsigned char I2C_Data);//写数据
void OLED_Init(void);
void OLED_Fill(unsigned char fill_Data);//全屏填充
void OLED_CLS(void);//清屏
void OLED_ON(void);
void OLED_OFF(void);
void OLED_SetPos(unsigned char x, unsigned char y); //设置起始点坐标
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


#endif
