/*******************************************************************************
实现功能 ： 用定时器延时并通过LCD1602显示时钟
引脚定义 ：	LCD_RS	→	P2^6
			LCD_RW	→	P2^5                              
			LCD_E	→	P2^7
			LCD_DataPort	→	P0
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer.H"

char Second = 50, Minute = 59, Hour = 21;

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	LCD_Initialization();
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowChar(2, 3, ':');
	LCD_ShowChar(2, 6, ':');
	while(1)
	{
		LCD_ShowNumber(2, 1, Hour);
		LCD_ShowNumber(2, 4, Minute);
		LCD_ShowNumber(2, 7, Second);
	}
}

/*******************************************************************************
* 函 数 名         : Timer0_Routine 定时器0主函数
* 函数功能		   : 计时器计时一定时间执行内容
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT16U count;
	TL0 = 0x18;		//重置定时初值
	TH0 = 0xFC;		//重置定时初值
	count++;
	if(count >= 1000)
	{
		count = 0;
		Second++;
		if(Second >= 60)
		{
			Second = 0;
			Minute++;
			if(Minute >= 60)
			{
				Minute = 0;
				Hour++;
				if(Hour >= 24)
					Hour = 0;
			}
		}
	}
}