#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "DS1302.H" 

INT8U Year = 21, Month = 7, Date = 21, Hour = 17, Minute = 59, Second = 50, Day = 3;

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	DS1302_Initialization();
	LCD_Initialization();
	LCD_ShowChar(1, 3, '-');
	LCD_ShowChar(1, 6, '-');
	LCD_ShowChar(2, 3, ':');
	LCD_ShowChar(2, 6, ':');
//	DS1302_SetTime();
	while(1)
	{
		DS1302_ReadTime();
		LCD_ShowNumber(1, 1, Year);
		LCD_ShowNumber(1, 4, Month);
		LCD_ShowNumber(1, 7, Date);
		LCD_ShowNumber(2, 1, Hour);
		LCD_ShowNumber(2, 4, Minute);
		LCD_ShowNumber(2, 7, Second);
	}
}