#include <REGX52.H>
#include "UserDef.H"
#include "74HC595.H"

/*******************************************************************************
* 函 数 名		: _74HC595_Initialization
* 函数功能		: 74HC595C初始化函数
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void _74HC595_Initialization()
{
	_595_SRCLK = 0;
	_595_RCLK = 0;
}

/*******************************************************************************
* 函 数 名		: _74HC595_SendByte
* 函数功能		: 给四块595芯片分别写入字节
* 输    入 		: 	_595_Byte1  （写入的字节）
					_595_Byte2
					_595_Byte3
					_595_Byte4
* 输    出		: 无
*******************************************************************************/
static void _74HC595_SendByte(INT8U _595_Byte1, _595_Byte2, _595_Byte3, _595_Byte4)
{
	INT8U i;
	for(i = 0; i <= 7; i++)			//写入第四个字节
	{
		_595_SER = _595_Byte4 & (0x80 >> i);
		_595_SRCLK = 1;		//上升沿移位
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//写入第三个字节
	{
		_595_SER = _595_Byte3 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//写入第二个字节
	{
		_595_SER = _595_Byte2 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	for(i = 0; i <= 7; i++)			//写入第一个字节
	{
		_595_SER = _595_Byte1 & (0x80 >> i);
		_595_SRCLK = 1;
		_595_SRCLK = 0;
	}
	_595_RCLK = 1;	//上升沿锁存
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