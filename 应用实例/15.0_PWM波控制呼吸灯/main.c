/*******************************************************************************
实现功能：通过控制延时函数实现LED呼吸灯
			（延时函数实现，比较消耗单片机资源 不推荐使用）
引脚定义：LED → P1^1
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
			
sbit LED1 = P1^1;

INT8U Time;

void Delay(INT8U i)		//声明一个延时较短的函数   实现PWM波周期短
{
	while(i--);
}

void main(void)
{
	INT8U j;
	while(1)
	{
		for(Time = 0; Time <= 100; Time++)		//以100为周期
		{
			for(j = 0; j < 20; j++)		//在每个周期内延时一定时间
			{
				LED1 = 0;
				Delay(Time);
				LED1 = 1;
				Delay(100 - Time);
			}
		}
		for(Time = 0; Time <= 100; Time++)
		{
			for(j = 0; j < 20; j++)
			{
				LED1 = 0;
				Delay(100 - Time);
				LED1 = 1;
				Delay(Time);
			}
		}
	}
}