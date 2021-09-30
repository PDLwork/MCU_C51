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
	INT8U i;
	
	Oled_Initialization();
	Oled_Clear();
	
	for(i = 0; i < 5; i++)
		Oled_ShowChinse(16*i, 0, i);
	
	Oled_ShowChar(50, 2, 'A', MediumSize);
	Oled_ShowChar(58, 3, 'a', SmallSize);
	Oled_ShowString(0, 4, "Hello World !!! Hello World !!! ", MediumSize);
	
//	Oled_ShowPhoto();
	
	while(1)
	{
		
	}
}