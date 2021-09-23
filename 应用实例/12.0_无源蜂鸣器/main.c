/*******************************************************************************
实现功能：	1.矩阵键盘按下LCD显示虚键码
			2.按键按下有音效
引脚定义：	LCD_RS	→	P2^6
			LCD_RW	→	P2^5
			LCD_E	→	P2^7
			Buzzer	→	P2^4
			LCD_DataPort P0	→	P0
			Keyboard_line	→	P1
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "keyboard.H"
#include "LCD1602.H"
#include "Buzzer.H"

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	LCD_Initialization();
	LCD_ShowString(1, 1, "Hello World !");
	while(1)
	{
		KeyboardScan();
		if(KeyboardValue != 0)
		{
			Buzzer_Time(100);
			LCD_ShowNumber(2, 1, KeyboardValue);
		}
	}
}
