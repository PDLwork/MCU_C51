#include <REG52.H>
#include "UserDef.H"
#include "keyboard.h"
#include "Delay.h"

INT8U KeyboardValue;

/*******************************************************************************
* �� �� ��         : KeyboardScan(�������ɨ�躯��)
* ��������		   : ɨ�������̲����������
* ��    ��         : ��
* ��    ��         : KeyboardValue
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
			//������
			Keyboard_line = 0x0f;
			switch(Keyboard_line)
			{
				case(0X07):	KeyboardValue = 1; break;
				case(0X0B):	KeyboardValue = 2; break;
				case(0X0D): KeyboardValue = 3; break;
				case(0X0E):	KeyboardValue = 4; break;
			}
			//������
			Keyboard_line=0Xf0;
			switch(Keyboard_line)
			{
				case(0X70):	KeyboardValue = KeyboardValue; break;
				case(0XB0):	KeyboardValue = KeyboardValue + 4; break;
				case(0XD0): KeyboardValue = KeyboardValue + 8; break;
				case(0XE0):	KeyboardValue = KeyboardValue + 12; break;
			}
		}
		while(Keyboard_line != 0Xf0);	//���ּ��
	}
	return KeyboardValue; 	
}