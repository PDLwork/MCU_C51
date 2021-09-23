/*******************************************************************************
ʵ�ֹ��� ��	XPT2046ʵ��ADת��
			ͨ����ѹ�ķ�ʽ��ȡ����λ�����������衢��������ķ�ѹֵ
			ͨ��LCD1602��ʾ
			
���Ŷ��� ��	LCD_RS	��	P2^6
			LCD_RW	��	P2^5
			LCD_E	��	P2^7
			LCD_DataPort	��	P0
			
			XPT2046_DCLK	��	P2^0
			XPT2046_CS		��	P2^1
			XPT2046_DIN		��	P2^2
			XPT2046_DOUT	��	P2^3
*******************************************************************************/

#include <REGX52.H>
#include "UserDef.H"
#include "LCD1602.H"
#include "XPT2046.H"
#include "Delay.H"
	
INT16U ADValue;

/*******************************************************************************
* �� �� ��         :  main ����������
*******************************************************************************/
void main(void)
{
	LCD_Initialization();
	LCD_ShowString(1, 1, "ADJ   NTC   RG");		//����ԭ��ͼ�ֱ���λ�����������衢���������ADת��ֵ
	while(1)
	{
		ADValue = XPT2046_ReadAD(XPT2046_XP_8);		//��ȡ��Ӧ�ӿڵ�ADֵ
		LCD_ShowNumber(2, 1, ADValue, 3);
		
		ADValue = XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNumber(2, 7, ADValue, 3);
		
		ADValue = XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNumber(2, 13, ADValue, 3);
	}
}