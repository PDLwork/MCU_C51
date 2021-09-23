#include <REGX52.H>
#include "UserDef.H"
#include "138showLEDsite.H"
#include "Delay.H"

INT8U NixieTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//分别为0~9的段代码

/*******************************************************************************
* 函 数 名		: 
* 函数功能		: 
* 输    入 		: Show_site(输入显示位置 范围1~8)
* 输    出		: 
*******************************************************************************/
static void _74HC138_ShowChar(INT8U Show_site, Show_Char)
{
	_138_A = (Show_site - 1) % 2;			//Show_site转换为二进制分别给ABC赋值，确认显示位置
	_138_B = ((Show_site - 1) / 2) % 2;
	_138_C = ((Show_site - 1) / 2) / 2;
	
	if(Show_Char == '-')
		Nixie = 0x40;		//‘-’号段代码
	else
		Nixie = NixieTable[Show_Char];
	
	DelayXms(2);
	Nixie = 0x00;  //延时消隐
}

extern void _74HC138_ShowNumber(INT8U Show_site, INT16U Show_Number)
{
	INT8U Hundred, Ten, One;
	Hundred = Show_Number / 100;    //分别提取出个十百位数字
	Ten = (Show_Number % 100) / 10;
	One = Show_Number % 10;
	
	_74HC138_ShowChar(Show_site, Hundred);
	_74HC138_ShowChar(Show_site + 1, Ten);
	_74HC138_ShowChar(Show_site + 2, One);
}


extern void _74HC138_ShowSignedNumber(INT8U Show_site, INT8S Show_Number)
{
	INT8U Ten, One;		//存放十位数字和各位数字
	if(Show_Number < 0)		//当显示数字小于0时
	{
		Show_Number = -Show_Number;
		Ten = Show_Number / 10;
		One = Show_Number % 10;
		
		_74HC138_ShowChar(Show_site, '-');
		_74HC138_ShowChar(Show_site + 1, Ten);
		_74HC138_ShowChar(Show_site + 2, One);
	}
	else		//当显示数字大于0时
	{
		Ten = Show_Number / 10;
		One = Show_Number % 10;
		
		_74HC138_ShowChar(Show_site, Ten);
		_74HC138_ShowChar(Show_site + 1, One);
	}
}