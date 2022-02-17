/*******************************************************************************
ʵ�ֹ��� �� �ö�ʱ����ʱ��ͨ��LCD1602��ʾʱ��
���Ŷ��� ��	LCD_RS	��	P2^6
			LCD_RW	��	P2^5                              
			LCD_E	��	P2^7
			LCD_DataPort	��	P0
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "Delay.h"
#include "LCD1602.h"
#include "Timer.H"

char Second = 50, Minute = 59, Hour = 21;

/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	Timer0_Initialization();
	LCD_Initialization();
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowChar(2, 3, ':');
	LCD_ShowChar(2, 6, ':');
	while(1)
	{
		LCD_ShowNumber(2, 1, Hour);
		LCD_ShowNumber(2, 4, Minute);
		LCD_ShowNumber(2, 7, Second);
	}
}

/*******************************************************************************
* �� �� ��         : Timer0_Routine ��ʱ��0������
* ��������		   : ��ʱ����ʱһ��ʱ��ִ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0_Routine() interrupt 1
{
	static INT16U count;
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	count++;
	if(count >= 1000)
	{
		count = 0;
		Second++;
		if(Second >= 60)
		{
			Second = 0;
			Minute++;
			if(Minute >= 60)
			{
				Minute = 0;
				Hour++;
				if(Hour >= 24)
					Hour = 0;
			}
		}
	}
}