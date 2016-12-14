#ifndef __MYPIDCONTROLLER_H
#define __MYPIDCONTROLLER_H

#include "math.h" 
#include "stm32f10x.h"
/*******************************************************************************
//变积分的实现方法(是积分分离的改进)：偏差大，积分减弱甚至全无；偏差小，积分加强，
故应根据偏差大小，改变积分速度
*******************************************************************************/
typedef struct
{
    short P;
    short I;
    short D;
    //可将比例积分微分三个系数进行同倍放大，移位还原，也可以避免浮点运算
    short I_limit;        //积分输出项的限制
    short D_limit;        
    short setpulse;       
    short backpulse;      
    short error;          
    short last_error;     //上一次速度误差
    short prev_error;     //上上次误差
    short d_error;        //速度误差之差
    short i_error;        //速度误差之和
    short out;            //电机控制输出占空比(0~990)与电压值“局部”呈线性关系
}PID_Motor;              
extern PID_Motor Motor;

//闭环速度参数
#pragma anon_unions
typedef union MySpeed
{
	struct
	{
		float zhangai;//障碍速度
		float qiao;   //桥的速度
		float zhidao; //直道速度
		float shizi;  //十字速度
		float ruwan;  //入弯速度
		float wandao; //弯道速度
		float zuixiao;//最小速度
	};
	float a[7];
}MySpeed;
extern MySpeed speed0,speed1,speed2,speed3,speed4;
extern float DesiredSpeed;//目标速度
extern uint8_t Stop_Flag;

extern short MotorPIDCalc(PID_Motor *pp);
extern short PIDCalc(PID_Motor *pp);

#endif
