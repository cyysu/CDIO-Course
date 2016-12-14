#ifndef __MYI2C_H
#define __MYI2C_H

#include "stm32f10x.h"
#include "sys.h"

//I/O方向设置
#define SDA_OUT() {GPIOB->CRH &= 0XFFFF0FFF;(u32)GPIOB->CRH |= 3<<12;}	//0011 通用推挽输出，50M
#define SDA_IN() {GPIOB->CRH &= 0X0FFF0FFF;(u32)GPIOB->CRH |= 8<<12;}	//1000 上拉/下拉输入

//I/O操作函数
#define IIC_SCL PBout(10)
#define IIC_SDA PBout(11)
#define READ_SDA PBin(11)


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);



#endif

