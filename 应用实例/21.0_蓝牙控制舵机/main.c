#include <REGX52.H>
#include "UserDef.H"
#include "Uart.H"
#include "Oled.H"
#include "Timer.H"

sbit Motor = P2^2;		
INT8U Compare = 7;		//7-90  27 -90

/*******************************************************************************
* 函 数 名         :  main函数
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Oled_Initialization();
	Oled_Clear();
	Uart_Initialization();
	Timer0_Initialization();
	Oled_ShowString(0, 2, "Hello World !!! ", MediumSize);
	while(1)
	{
		
	}
}

/*******************************************************************************
* 函 数 名         : Timer_Routine 定时器主函数
* 函数功能		   : 计时器计时一定时间执行内容
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT8U count;
	TL0 = 0x9C;		//重置定时初始值100微秒 
	TH0 = 0xFF;
    count++;
	count %= 200;	//实现超过100归零  可以取代if判断  一个PWM的周期为200*0.1ms即20ms
	if(count < Compare)
		Motor = 1;
	else
		Motor = 0;
}

/*******************************************************************************
* 函 数 名		: Uart_Routine 串口中断函数
* 函数功能		: 发送完或接收到数据时执行相应操作
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
void Uart_Routine() interrupt 4
{
	if(TI == 1)
	{
		TI = 0;
	}
	if(RI == 1)
	{
		RI = 0;
		Uart_SendByte(SBUF);
		if(SBUF == 'A')
			Compare = 15;
		if(SBUF == 'B')
			Compare = 11;
	}
}