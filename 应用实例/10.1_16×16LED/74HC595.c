#include <REGX52.H>
#include "UserDef.H"
#include "74HC595.H"

/*******************************************************************************
* �� �� ��		: _74HC595_Initialization
* ��������		: 74HC595C��ʼ������
* ��    �� 		: ��
* ��    ��		: ��
*******************************************************************************/
extern void _74HC595_Initialization()
{
	_595_SRCLK = 0;
	_595_RCLK = 0;
}

/*******************************************************************************
* �� �� ��		: _74HC595_SendByte
* ��������		: ���Ŀ�595оƬ�ֱ�д���ֽ�
* ��    �� 		: 	_595_Byte1  ��д����ֽڣ�
					_595_Byte2
					_595_Byte3
					_595_Byte4
* ��    ��		: ��
*******************************************************************************/
static void _74HC595_SendByte(INT8U _595_Byte1, _595_Byte2, _595_Byte3, _595_Byte4)
{
	INT8U i;
	for(i = 0; i <= 7; i++)			//д����ĸ��ֽ�
	{
		_595_SER = _595_Byte4 & (0x80 >> i);
		_595_SRCLK = 1;		//��������λ
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//д��������ֽ�
	{
		_595_SER = _595_Byte3 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//д��ڶ����ֽ�
	{
		_595_SER = _595_Byte2 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//д���һ���ֽ�
	{
		_595_SER = _595_Byte1 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	_595_RCLK = 1;	//����������
	_595_RCLK = 0;
}

extern void MatrixLED(INT8U Column, Byte1, Byte2)
{
	INT8U Column1, Column2;
	if(Column <= 8)
	{
		Column1 = (0x01 << (Column - 1)); 
		Column2 = 0x00;
	}
	if((Column > 8) && (Column <= 16))
	{
		Column2 = (0x01 << (Column - 9)); 
		Column1 = 0x00;
	}
	_74HC595_SendByte(Byte1, Byte2, Column1, Column2);
}