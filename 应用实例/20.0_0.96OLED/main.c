#include <REGX52.H>
#include "UserDef.H"
#include "Oled.H"

/*******************************************************************************
* 函 数 名         :  main （主函数）
* 函数功能		   :  主程循环执行
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
void main(void)
{
	Oled_Initialization();
	Oled_Clear();
	Oled_ShowChar(5, 1, 'A');
	Oled_Test();
	Oled_ShowString(0, 7, "Hello World !!! ");
	while(1)
	{
		
	}
}