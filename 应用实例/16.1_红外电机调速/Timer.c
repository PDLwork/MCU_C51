#include <REGX52.H>
#include "UserDef.H"
#include "Timer.H"

INT8U Compare;

/*******************************************************************************
* 函 数 名         : Timer0_Initialization 定时器初始化函数
* 函数功能		   : 定时器初始化设置（1毫秒@12.000MHz）
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
extern void Timer0_Initialization(void)
{
	EA = 1;  		//总中断打开
	ET0 = 1; 		//定时器0打开
	TMOD &= 0xF0;	//与或赋值
	TMOD |= 0x01;	//设置定时器模式1
	TF0 = 0;		//清除TF0标志
//	TR0 = 1;		//定时器0开始计时
}

extern void Timer0_Run(void)
{
	TL0 = 0;		
	TH0 = 0;
	TR0 = 1;		//将计数值归零后开始计时
}

extern INT16U Timer0_GetCounter(void)
{
	INT16U GetCounter;
	TR0 = 0;		//将定时器停止后获取计数值
	GetCounter = (TH0 << 8) | TL0;
	return GetCounter;
}

extern void Timer1_Initialization(void)
{
	EA = 1;  		//总中断打开
	ET1 = 1; 		//定时器0打开
	TMOD &= 0x0F;	//与或赋值
	TMOD |= 0x10;	//设置定时器模式1
	TL1 = 0x9C;		//设置定时初始值100微秒 
	TH1 = 0xFF;
	TF1 = 0;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
}

void Timer1_Routine() interrupt 3
{
	static INT8U count;
	TL1 = 0x9C;		//重置定时初始值100微秒 
	TH1 = 0xFF;
    count++;
	count %= 100;	//实现超过100归零  可以取代if判断  一个PWM的周期为100*100us即10ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}