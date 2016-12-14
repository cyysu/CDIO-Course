#include "myPidController.h"
#include "bsp_usart.h"

uint8_t Stop_Flag = 0;
float global_test = 0;
PID_Motor Motor =
{      
    6,  //P   46
    1,   //I   10
    0,   //D   1
    500,    //积分输出限制
    800,    //微分输出限制
    0,0,0,0,0,0,0,0
};
//闭环
MySpeed speed0 = {
    120,//zhangai
    90,//qiao
    160,//zhidao
    160,//shizi
    115,//ruwan
    105,//wandao
    90 //minspeed 
};
float DesiredSpeed = 0; //初始化希望控制的速度


/*
 *函数功能：计算给电机的占空比（增量）
 *时间：2016_08_03
 */
short PIDCalc(PID_Motor *pp)
{	
	 static float Bias,Last_bias;
	 //Bias = Encoder - Target;                //计算偏差
	 //pp->setpulse = 500;
	 Bias = pp->setpulse - pp->backpulse;
	 pp->out += pp->P * (Bias-Last_bias) + pp->I * Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return pp->out;                         //增量输出
}         
