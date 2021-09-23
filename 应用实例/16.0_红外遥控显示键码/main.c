#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "Infrared.H"

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	INT8U Number = 10;
	Infrared_Initialization();
	LCD_Initialization();
	while(1)
	{
		if(Infrared_DataFlag || Infrared_RepeatFlag)
		{
			if(Infrared_Command == Infrared_PREVIOUS)
				Number--;
			if(Infrared_Command == Infrared_NEXT)
				Number++;
			Infrared_RepeatFlag = 0;
			Infrared_DataFlag = 0;
		}
		LCD_ShowNumber(1, 1, Infrared_Address);
		LCD_ShowNumber(1, 8, Infrared_Command);
		LCD_ShowNumber(2, 1, Number);
	}
}