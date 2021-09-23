#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"

#define smg P0

INT8U NixieTable[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//共阳数码管代码表"0-F"(a为最低位)
//INT8U NixieTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//共阴数码管代码表"0-F"(a为最低位)

/*******************************************************************************
* 函 数 名         :  main主函数
* 函数功能		   :  执行初始化函数与循环函数 
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
//void main(void)   //数码管显示相应字符
//{
//	while(1)
//	{
//		smg = NixieTable[10];
//	}
//}

void main(void)   //倒计时
{
	INT8S i = 9;
	while(1)
	{
		smg = NixieTable[i];
		DelayXms(1000);
		i--;
		if(i < 0)
		{
			i = 9;
		}
	}
}