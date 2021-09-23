#include <REGX52.H>
#include "UserDef.H"
#include "138showLEDsite.H"
#include "Delay.H"

INT8U NixieTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//�ֱ�Ϊ0~9�Ķδ���

/*******************************************************************************
* �� �� ��		: 
* ��������		: 
* ��    �� 		: Show_site(������ʾλ�� ��Χ1~8)
* ��    ��		: 
*******************************************************************************/
static void _74HC138_ShowChar(INT8U Show_site, Show_Char)
{
	_138_A = (Show_site - 1) % 2;			//Show_siteת��Ϊ�����Ʒֱ��ABC��ֵ��ȷ����ʾλ��
	_138_B = ((Show_site - 1) / 2) % 2;
	_138_C = ((Show_site - 1) / 2) / 2;
	
	if(Show_Char == '-')
		Nixie = 0x40;		//��-���Ŷδ���
	else
		Nixie = NixieTable[Show_Char];
	
	DelayXms(2);
	Nixie = 0x00;  //��ʱ����
}

extern void _74HC138_ShowNumber(INT8U Show_site, INT16U Show_Number)
{
	INT8U Hundred, Ten, One;
	Hundred = Show_Number / 100;    //�ֱ���ȡ����ʮ��λ����
	Ten = (Show_Number % 100) / 10;
	One = Show_Number % 10;
	
	_74HC138_ShowChar(Show_site, Hundred);
	_74HC138_ShowChar(Show_site + 1, Ten);
	_74HC138_ShowChar(Show_site + 2, One);
}


extern void _74HC138_ShowSignedNumber(INT8U Show_site, INT8S Show_Number)
{
	INT8U Ten, One;		//���ʮλ���ֺ͸�λ����
	if(Show_Number < 0)		//����ʾ����С��0ʱ
	{
		Show_Number = -Show_Number;
		Ten = Show_Number / 10;
		One = Show_Number % 10;
		
		_74HC138_ShowChar(Show_site, '-');
		_74HC138_ShowChar(Show_site + 1, Ten);
		_74HC138_ShowChar(Show_site + 2, One);
	}
	else		//����ʾ���ִ���0ʱ
	{
		Ten = Show_Number / 10;
		One = Show_Number % 10;
		
		_74HC138_ShowChar(Show_site, Ten);
		_74HC138_ShowChar(Show_site + 1, One);
	}
}