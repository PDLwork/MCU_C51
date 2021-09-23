/*******************************************************************************
ʵ�ֹ��ܣ�	1.������̰���LCD��ʾ�����
			2.������������Ч
���Ŷ��壺	LCD_RS	��	P2^6
			LCD_RW	��	P2^5
			LCD_E	��	P2^7
			Buzzer	��	P2^4
			LCD_DataPort P0	��	P0
			Keyboard_line	��	P1
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "keyboard.H"
#include "LCD1602.H"
#include "Buzzer.H"

/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
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
