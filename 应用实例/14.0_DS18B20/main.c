#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "DS18B20.H"
	
float Temperature;
	
/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	LCD_Initialization();
	LCD_ShowString(1, 1, "Temperature:");
	LCD_ShowChar(2, 4, '.');
	while(1)
	{
		DS18B20_ConverTemperature();
		Temperature = DS18B20_ReadTemperature();
		if(Temperature < 0)
			LCD_ShowChar(2, 1, '-');
		else
			LCD_ShowChar(2, 1, '+');
		LCD_ShowNumber(2, 2, Temperature);
		LCD_ShowNumber(2, 5, (unsigned long)(Temperature * 10000) % 10000);
	}
}