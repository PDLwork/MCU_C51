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
	Oled_ShowChar(50, 0, 'A', MediumSize);
//	Oled_Test();
	Oled_ShowString(0, 2, "Hello World !!! Hello World !!! Hello World !!! ", MediumSize);
	while(1)
	{
		
	}
}