#include <REG52.H>
#include "UserDef.H"
#include "keyboard.h"
#include "Delay.h"

INT8U KeyboardValue;

/*******************************************************************************
* 函 数 名         : KeyboardScan(矩阵键盘扫描函数)
* 函数功能		   : 扫描矩阵键盘并返回虚键码
* 输    入         : 无
* 输    出         : KeyboardValue
*******************************************************************************/
extern INT8U KeyboardScan(void)
{
	KeyboardValue = 0;
	Keyboard_line = 0x0f;
	if(Keyboard_line != 0x0f)
	{
		DelayXms(10);
		if(Keyboard_line != 0x0f)
		{
			//测试列
			Keyboard_line = 0x0f;
			switch(Keyboard_line)
			{
				case(0X07):	KeyboardValue = 1; break;
				case(0X0B):	KeyboardValue = 2; break;
				case(0X0D): KeyboardValue = 3; break;
				case(0X0E):	KeyboardValue = 4; break;
			}
			//测试行
			Keyboard_line=0Xf0;
			switch(Keyboard_line)
			{
				case(0X70):	KeyboardValue = KeyboardValue; break;
				case(0XB0):	KeyboardValue = KeyboardValue + 4; break;
				case(0XD0): KeyboardValue = KeyboardValue + 8; break;
				case(0XE0):	KeyboardValue = KeyboardValue + 12; break;
			}
		}
		while(Keyboard_line != 0Xf0);	//松手检测
	}
	return KeyboardValue; 	
}