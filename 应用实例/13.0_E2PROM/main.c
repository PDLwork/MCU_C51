/*******************************************************************************
ʵ�ֹ��ܣ�
���Ŷ��壺
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "AT24C02.H"
#include "Delay.H"
#include "ButtonScan.H"
	
INT16U Number;	

/*******************************************************************************
* �� �� ��         :  main ����������
* ��������		   :  ����ѭ��ִ��
* ��    ��         :  ��
* ��    ��         :  ��
*******************************************************************************/
void main(void)
{
	LCD_Initialization();
	LCD_ShowNumber(1, 1, Number);
	while(1)
	{
		ButtonScan();
		
		if(Button_Value != 0)
		{
			if(Button_Value == 1)
			{
				Number++;
				LCD_ShowNumber(1, 1, Number);
			}
			if(Button_Value == 2)
			{
				Number--;
				LCD_ShowNumber(1, 1, Number);
			}
			if(Button_Value == 3)
			{
				AT24C02_WriteByte(0, Number / 256);
				DelayXms(5);
				AT24C02_WriteByte(1, Number % 256);
				DelayXms(5);
				LCD_ShowString(2, 1, "Write OK!");
				DelayXms(1000);
				LCD_ShowString(2, 1, "         ");
			}
			if(Button_Value == 4)
			{
				Number = AT24C02_ReadByte(0);
				Number = (Number *256) + AT24C02_ReadByte(1);
				LCD_ShowNumber(1, 1, Number);
				LCD_ShowString(2, 1, "Read OK!");
				DelayXms(1000);
				LCD_ShowString(2, 1, "        ");
			}
		}
	}
}