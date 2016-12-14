#include "myi2c.h"
#include "delay.h"

//I2C初始化
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);	 //将PB6 7 置高，相当于默认设置scl sda上拉输入

	IIC_SDA = 1;
	IIC_SCL = 1;

}

//起始信号
void IIC_Start(void)
{
	SDA_OUT();				//设为主机输出
	IIC_SDA = 1;
	IIC_SCL = 1;
	delay_us(4);
	IIC_SDA = 0;				//scl为高电平时，SDA出现低电平跳变，表示传输开始
	delay_us(5);
	IIC_SCL = 0;				   //钳位SCL,方便接下来进行数据传输

}
//终止信号
void IIC_Stop(void)
{
	SDA_OUT();			   //设为主机输出
	IIC_SDA = 0;
	IIC_SCL = 1;
	delay_us(2);			  //scl为高电平，SDA出现高电平跳变，表示传输结束
	IIC_SDA = 1;
		
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u16 Errtime=0;
	SDA_IN();			//此时设置为输入
	IIC_SCL = 1;
	IIC_SDA = 1;		//线与的关系
	if(READ_SDA)
	{
		Errtime++;
		if(Errtime > 250)
		{
			IIC_Stop();
			return 1;		
		}
	}
	else
	IIC_SCL = 0;	//钳位，方便下次传输
	return 0;
}
//产生应答信号
void IIC_Ack(void)
{
	SDA_OUT();		 //此时，相当于主机在接收数据，是被动方
	IIC_SCL = 0;
	IIC_SDA = 0;
	IIC_SCL = 1;
	delay_us(2);
	IIC_SCL = 0;
}
//不产生应答信号
void IIC_NAck(void)
{
	SDA_OUT();		 //此时，相当于主机在接收数据，是被动方
	IIC_SCL = 0;
	IIC_SDA = 1;
	IIC_SCL = 1;
	delay_us(2);
	IIC_SCL = 0;	

}
//发送一个字节数据
void IIC_Send_Byte(u8 txd)
{
	u8 i;
	SDA_OUT();
	IIC_SCL=0;//拉低时钟开始数据传输
	for(i=0;i<8;i++)
	{
		if(txd & 0x80)
			IIC_SDA = 1;
		else
			IIC_SDA = 0;
		txd <<= 1;
		delay_us(2);
		IIC_SCL = 1;
		delay_us(2);
		IIC_SCL = 0;
		delay_us(2);
	}
} 
//读一个字节数据   ack = 1 时，产生应答	   ack = 0  ,不产生应答
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;		  //高电平时数据已经稳定，故进行数据的读取
		receive <<= 1;
		if(READ_SDA)
			receive++;	
	}
	if(ack)
		IIC_Ack();
	else
		IIC_NAck();
	return receive;

}





