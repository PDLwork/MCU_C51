#include <REGX52.H>
#include "UserDef.H"
#include "Delay.H"
#include "Intrins.H"

#define LED P2

/*******************************************************************************
* 函 数 名         :  main主函数
* 函数功能		   :  执行初始化函数与循环函数 
* 输    入         :  无
* 输    出         :  无
*******************************************************************************/
//void main(void)   //IO口直接控制灯
//{
//	while(1)
//	{
//		LED = 0XA3;
//	}
//}

//void main(void)   //延时闪烁LED
//{
//	while(1)
//	{
//		LED = 0XAA;
//		DelayXms(300);
//		LED = 0X55;
//		DelayXms(300);
//	}
//}

void main(void)   //循环移位流水灯
{
	LED = 0X8F;
	while(1)
	{
		DelayXms(100);
//		LED = _crol_(LED,1);
		LED = _cror_(LED,1);
	}
}