#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"
#include "74HC595.H"
#include "Timer.H"

INT8U move = 0;
INT8U code LED_Data[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
						 0x7F,0x48,0x4C,0x4A,0x31,0x00,0x00,0x02,
						 0x15,0x15,0x15,0x0F,0x00,0x00,0x18,0x05,
						 0x05,0x05,0x1E,0x00,0x00,0x1F,0x10,0x0C,
						 0x10,0x0F,0x00,0x00,0x0E,0x11,0x11,0x11,
						 0x0E,0x00,0x00,0x1F,0x08,0x10,0x10,0x0F,
						 0x00,0x00,0x0E,0x11,0x11,0x09,0x7F,
					     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};   //纵向取模，高位在上，低位在下
						 
/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  矩阵LED滚动显示
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	INT8U i;
	_74HC595_Initialization();
	Timer0_Initialization();
	_74HC595_SendByte1(0xf0);
	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			MatrixLED_ShowOneColumn(i, LED_Data[i + move]);
		}	
	}
}

/*******************************************************************************
* 函 数 名         : Timer_Routine 定时器主函数
* 函数功能		   : 计时器计时控制移动速度
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT16U count;
	TL0 = 0x18;		//重置定时初值
	TH0 = 0xFC;		//重置定时初值
    count++;
	if(count > 80)
	{
		count = 0;
		move++;
		if(move > 55)
			move = 0;
	}
}