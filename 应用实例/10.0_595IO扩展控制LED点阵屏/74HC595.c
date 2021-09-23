#include <REGX52.H>
#include "UserDef.H"
#include "74HC595.H"
#include "Delay.H"

/*******************************************************************************
* 函 数 名		: _74HC595_Initialization （595芯片初始化）
* 函数功能		: 595芯片复位初始化
* 输    入 		: 无
* 输    出		: 无
*******************************************************************************/
extern void _74HC595_Initialization()
{
	_595_SRCLK = 0;
	_595_RCLK = 0;
}

/*******************************************************************************
* 函 数 名		: _74HC595_SendByte （595写字节函数）
* 函数功能		: 595写入字节
* 输    入 		: amount  (595写入字节数）
				  _595_Byte1（写入字节1）
				  _595_Byte2（写入字节2，若没有输入0）
				  _595_Byte3（写入字节2，若没有输入0）
* 输    出		: 无
*******************************************************************************/
static void _74HC595_SendByte(INT8U amount, _595_Byte1, _595_Byte2, _595_Byte3)
{
	INT8U i;
	if(amount >= 1)
	{
		for(i = 0; i < 8; i++)
		{
			_595_SER = _595_Byte1 & (0x80 >> i);
			_595_SRCLK = 1;
			_595_SRCLK = 0;
		}
	}
	if(amount >= 2)
	{
		for(i = 0; i < 8; i++)
		{
			_595_SER = _595_Byte2 & (0x80 >> i);
			_595_SRCLK = 1;
			_595_SRCLK = 0;
		}
	}
	_595_RCLK = 1;
	_595_RCLK = 0;
}

/*******************************************************************************
* 函 数 名		: MatrixLED_ShowOneColumn （点阵LED显示函数）
* 函数功能		: 输入显示列数与显示内容
* 输    入 		: Show_Column（显示列数）
				  Show_Data（显示内容）
* 输    出		: 无
*******************************************************************************/
extern void MatrixLED_ShowOneColumn(INT8U Show_Column, INT8U Show_Data)
{
	INT8U MatrixLED_Column;
	MatrixLED_Column = ~( 0x01 << (Show_Column) );
	_74HC595_SendByte(2, Show_Data, MatrixLED_Column, 0);
	DelayXms(2);
//	_74HC595_SendByte(2, 0x00, 0xFF);  //消隐
}