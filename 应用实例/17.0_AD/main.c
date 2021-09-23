/*******************************************************************************
实现功能 ：	XPT2046实现AD转换
			通过分压的方式读取出电位器、热敏电阻、光敏电阻的分压值
			通过LCD1602显示
			
引脚定义 ：	LCD_RS	→	P2^6
			LCD_RW	→	P2^5
			LCD_E	→	P2^7
			LCD_DataPort	→	P0
			
			XPT2046_DCLK	→	P2^0
			XPT2046_CS		→	P2^1
			XPT2046_DIN		→	P2^2
			XPT2046_DOUT	→	P2^3
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "XPT2046.H"
#include "Delay.H"
	
INT16U ADValue;

/*******************************************************************************
* 函 数 名         :  main （主函数）
*******************************************************************************/
void main(void)
{
	LCD_Initialization();
	LCD_ShowString(1, 1, "ADJ   NTC   RG");		//查阅原理图分别测电位器、热敏电阻、光敏电阻的AD转换值
	while(1)
	{
		ADValue = XPT2046_ReadAD(XPT2046_XP_8);		//读取对应接口的AD值
		LCD_ShowNumber(2, 1, ADValue, 3);
		
		ADValue = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNumber(2, 7, ADValue, 3);
		
		ADValue = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNumber(2, 13, ADValue, 3);
	}
}