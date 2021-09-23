#include <REGX52.H>
#include "UserDef.H"
#include "Delay.h"
#include "Uart.h"
#include "LCD1602.H"

sbit button1 = P2^0;
sbit button2 = P2^1;

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  按下按键1发送字符串Hello World，按下按键二发送字符回车
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Uart_Initialization();
	LCD_Initialization();
	button1 = 1;
	button2 = 1;
	LCD_ShowString(1, 1, "Li Yun !");
	while(1)
	{
		if(button1 == 0)
		{
			DelayXms(10);
			if(button1 == 0)
			{
				Uart_SendString("Hello World !\n");
			}
			while(button1 == 0);
		}
		if(button2 == 0)
		{
			DelayXms(10);
			if(button2 == 0)
			{
				Uart_SendByte('\n');
			}
			while(button2 == 0);
		}
	}
}